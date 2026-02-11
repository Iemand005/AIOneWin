#include <Windows.h>

#include <Vsstyle.h>
#include <vssym32.h>
//
//#include <wil/common.h>
//#include <wil/result.h>

#include <fstream>
#include <sstream>
#include <format>
#include <functional>
#include <filesystem>
#include <locale>
#include <codecvt>
#include <string>


#include "..\DirectUI\DirectUI.h"

#include <AIOne>

#pragma comment(lib,"dui70.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "AIOneCore.lib")
#include "resource.h"

using namespace DirectUI;

void ThrowIfFailed(HRESULT hr) {
  if (hr == S_OK)
    return;
  throw hr;
}

struct LogListener : public IElementListener {

	void OnListenerAttach(Element *elem) override {
		OutputDebugString(std::format(L"attach: {:p}\n", (void*)elem).c_str());
	}
	void OnListenerDetach(Element *elem) override {
		OutputDebugString(std::format(L"detach: {:p}\n", (void*)elem).c_str());
	}
	bool OnPropertyChanging(Element* elem, const PropertyInfo *prop, int unk, Value* v1, Value* v2) override {
		OutputDebugString(std::format(L"prop change: {:p} {} {} {:p}<{}> {:p}<{}>\n",
			(void*)elem, (PCWSTR)prop->name, unk, (void*)v1, v1->GetType(), (void*)v2, v2->GetType()).c_str());
		return true;
	}
	void OnListenedPropertyChanged(Element *elem, const PropertyInfo*prop, int type, Value*v1, Value*v2) override {
		OutputDebugString(std::format(L"listened prop change: {:p} {} {} {:p}<{}> {:p}<{}>\n",
			(void*)elem, (PCWSTR)prop->name, type, (void*)v1, v1->GetType(), (void*)v2, v2->GetType()).c_str());
	}
	void OnListenedEvent(Element*elem, struct Event*ev) override {
		 OutputDebugString(std::format(L"listened event: {:p} {:p}\n", (void*)elem, (void*)ev).c_str());
	}
	void OnListenedInput(Element*elem, struct InputEvent*iev) override {
		OutputDebugString(std::format(L"listened input: {:p} {:p}\n", (void*)elem, (void*)iev).c_str());
	}

};


struct EventListener : public IElementListener {

	using handler_t = std::function<void(Element*, Event*)>;

	handler_t f;

	EventListener(handler_t f) : f(f) { }

	void OnListenerAttach(Element *elem) override { }
	void OnListenerDetach(Element *elem) override { }
	bool OnPropertyChanging(Element* elem, const PropertyInfo *prop, int unk, Value* v1, Value* v2) override {
		return true;
	}
	void OnListenedPropertyChanged(Element *elem, const PropertyInfo*prop, int type, Value*v1, Value*v2) override { }
	void OnListenedEvent(Element*elem, struct Event*iev) override {
		f(elem, iev);
	}
	void OnListenedInput(Element*elem, struct InputEvent*ev) override { }
};

#define WM_DIRECTUI_INVOKE (WM_USER + 101)

static std::string output = "";

LRESULT CALLBACK InvokeSubclass(HWND hWnd, UINT uMsg, WPARAM wParam,
                                  LPARAM lParam, UINT_PTR uIdSubclass,
                                  DWORD_PTR dwRefData) {
  if (uMsg == WM_DIRECTUI_INVOKE) {
    std::string *token = (std::string *)lParam;
    std::string thing = *token;
    output += thing;
    auto title = (Element *)wParam;
    //Value *content;
    //title->GetContentString(&content);
     std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(output);
     //auto bibi = std::format(L"{}{}", (LPCWSTR)content, wide);
    title->SetContentString(UCString(wide.c_str()));
        //    .c_str() content +
        //token);
    return 0;
  }
  return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	ThrowIfFailed(CoInitializeEx(NULL, 0));

	ThrowIfFailed(InitProcessPriv(14, NULL, 0, true));
    ThrowIfFailed(InitThread(2));

	// uncomment to update class definitions
	// HookClassFactoryRegister();
    ThrowIfFailed(RegisterAllControls());

	ModelManager *modelManager = new ModelManager();

    NativeHWNDHost *pwnd;

	NativeHWNDHost::Create((UCString)L"AIOne", NULL, NULL,
		600, 400, 800, 600, WS_EX_WINDOWEDGE,
                               WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0,
                               (NativeHWNDHost **)&pwnd);

	HWND hMainWnd = pwnd->GetHWND();
    SetWindowSubclass(hMainWnd, InvokeSubclass, 1, 0);
	//AIOneHost *pwnd = (AIOneHost *)nativePwnd;

	DUIXmlParser* pParser;

	ThrowIfFailed(DUIXmlParser::Create(&pParser, NULL, NULL, NULL, NULL));

	pParser->SetParseErrorCallback([](UCString err1, UCString err2, int unk, void*ctx) {
		OutputDebugString(std::format(L"err: {}; {}; {}\n", (LPCWSTR)err1, (LPCWSTR)err2, unk).c_str());
		DebugBreak();
	}, NULL);

	auto hr=pParser->SetXMLFromResource(IDR_UIFILE1, hInstance,(HINSTANCE)hInstance);

	unsigned long deferKey;
	HWNDElement* hwnd_element;

	HWNDElement::Create(pwnd->GetHWND(),true,0,NULL,&deferKey,(Element**)&hwnd_element);

	Element* pWizardMain;
	hr = pParser->CreateElement((UCString)L"WizardMain", hwnd_element,NULL,NULL,(Element**)&pWizardMain);

	ThrowIfFailed(hr);


	pWizardMain->SetVisible(true);
	pWizardMain->EndDefer(deferKey);
	pwnd->Host(pWizardMain);

	pwnd->ShowWindow(SW_SHOW);

	auto *title_elem = pWizardMain->FindDescendent(StrToID((UCString)L"SXTitle"));

	ATOM sendButtonId = StrToID(UCString(L"SXWizardDefaultButton"));
    auto *sendButton = (Button *)pWizardMain->FindDescendent(sendButtonId);
    
	ATOM loadButtonId = StrToID(UCString(L"LoadModelButton"));
    auto *loadButton = (Button *)pWizardMain->FindDescendent(loadButtonId);

	auto *messageInput = (Edit *)pWizardMain->FindDescendent(StrToID((UCString)L"MessageEditBox"));

	auto *progressSpinner = pWizardMain->FindDescendent(StrToID((UCString)L"SXWizardLoadingProgress"));

	LogListener lis;
	hr = pWizardMain->AddListener(&lis);
    ThrowIfFailed(hr);


	auto loadModel = [&]() {
          OPENFILENAME ofn;
          TCHAR szFile[260] = {0};

          ZeroMemory(&ofn, sizeof(ofn));
          ofn.lStructSize = sizeof(ofn);
          ofn.hwndOwner = pwnd->GetHWND();
          ofn.lpstrFile = szFile;
          ofn.nMaxFile = sizeof(szFile);
          ofn.lpstrFilter = L"All\0*.*\GGUF\0*.gguf\0";
          ofn.nFilterIndex = 1;
          ofn.lpstrFileTitle = NULL;
          ofn.nMaxFileTitle = 0;
          ofn.lpstrInitialDir = NULL;
          ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

          if (GetOpenFileName(&ofn) == TRUE) {
            auto fileName = ofn.lpstrFile;

			LLModelOptionsAsync options;

			options.onDone = [&]() {
                          progressSpinner->SetVisible(false);
                        };

            modelManager->loadLLMAsync(fileName, options);
          }
	};

	auto send = [&]() {
          Value *txt;
          messageInput->GetContentString(&txt);
          std::wstring message = (LPCWSTR)txt->GetString();

		  AsyncTextGenOptions options;


		  options.onToken = [&](std::string token) {
                    std::string *wawa = new std ::string(
                    token);
			  //title_elem->
     //               pwnd->output += token;

					//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
     //                     std::wstring wide = converter.from_bytes(token);
     //                                   UCString finaly = UCString(wide.c_str());
     //                                   std::wstring ee =
     //                                       std::format(L"Entered: {}",
     //                                                   (LPCWSTR)wide.c_str());

					PostMessage(pwnd->GetHWND(), WM_DIRECTUI_INVOKE,
                                      (WPARAM)title_elem, (LPARAM)wawa); 

                     //ThrowIfFailed(title_elem->SetContentString(UCString(ee.c_str())));
                  };

		  modelManager->getChatManager()->sendAsync(message, options);
          //ThrowIfFailed(title_elem->SetContentString(
          //    (UCString)std::format(L"Entered: {}", (LPCWSTR)txt->GetString())
          //        .c_str()));

    };

	EventListener clickListener([&](Element*elem, Event*ev) {

		if (ev->flag != GMF_BUBBLED)
			return;

        auto id = ev->target->GetID();
		if (ev->type == TouchButton::Click) {
          if (loadButtonId == id)
            loadModel();
                    
            return;
            if (id == sendButtonId)
              send();
			progressSpinner->SetVisible(true);
          } else if (ev->type == Edit::Enter)
            send();
	});

    ThrowIfFailed(pWizardMain->AddListener(&clickListener));

	DumpDuiTree(pWizardMain, 0);

	StartMessagePump();

	UnInitProcessPriv(NULL);
	return 0;
}
