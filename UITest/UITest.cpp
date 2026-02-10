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

#include "..\DirectUI\DirectUI.h"

#pragma comment(lib,"dui70.lib")
#pragma comment(lib, "comctl32.lib")
#include "resource.h"

using namespace DirectUI;

void ThrowIfFailed(HRESULT hr) {
  if (hr == S_OK)
    return;
  throw hr;
}

struct LogListener : public IElementListener {

	//0
	void OnListenerAttach(Element *elem) override {
		OutputDebugString(std::format(L"attach: {:p}\n", (void*)elem).c_str());
	}
	//1
	void OnListenerDetach(Element *elem) override {
		OutputDebugString(std::format(L"detach: {:p}\n", (void*)elem).c_str());
	}
	//2
	bool OnPropertyChanging(Element* elem, const PropertyInfo *prop, int unk, Value* v1, Value* v2) override {
		OutputDebugString(std::format(L"prop change: {:p} {} {} {:p}<{}> {:p}<{}>\n",
			(void*)elem, (PCWSTR)prop->name, unk, (void*)v1, v1->GetType(), (void*)v2, v2->GetType()).c_str());
		return true;
	}
	//3
	void OnListenedPropertyChanged(Element *elem, const PropertyInfo*prop, int type, Value*v1, Value*v2) override {
		OutputDebugString(std::format(L"listened prop change: {:p} {} {} {:p}<{}> {:p}<{}>\n",
			(void*)elem, (PCWSTR)prop->name, type, (void*)v1, v1->GetType(), (void*)v2, v2->GetType()).c_str());
	}
	//4
	void OnListenedEvent(Element*elem, struct Event*ev) override {
		 OutputDebugString(std::format(L"listened event: {:p} {:p}\n", (void*)elem, (void*)ev).c_str());
	}
	//5
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

long (* RealClassFactoryRegister)(CClassFactory *, IClassInfo*) = 0;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	ThrowIfFailed(CoInitializeEx(NULL, 0));

	ThrowIfFailed(InitProcessPriv(14, NULL, 0, true));
    ThrowIfFailed(InitThread(2));

	// uncomment to update class definitions
	// HookClassFactoryRegister();
    ThrowIfFailed(RegisterAllControls());


	NativeHWNDHost* pwnd;

	NativeHWNDHost::Create((UCString)L"Microsoft DirectUI Test", NULL, NULL,
		//CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		600, 400, 800, 600,
		WS_EX_WINDOWEDGE, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0,&pwnd);

	DUIXmlParser* pParser;

	ThrowIfFailed(DUIXmlParser::Create(&pParser, NULL, NULL, NULL, NULL));

	pParser->SetParseErrorCallback([](UCString err1, UCString err2, int unk, void*ctx) {
		OutputDebugString(std::format(L"err: {}; {}; {}\n", (LPCWSTR)err1, (LPCWSTR)err2, unk).c_str());
		DebugBreak();
	}, NULL);

	auto hr=pParser->SetXMLFromResource(IDR_UIFILE1, hInstance,(HINSTANCE)hInstance);

	unsigned long defer_key;
	HWNDElement* hwnd_element;

	HWNDElement::Create(pwnd->GetHWND(),true,0,NULL,&defer_key,(Element**)&hwnd_element);

	Element* pWizardMain;
	hr = pParser->CreateElement((UCString)L"WizardMain", hwnd_element,NULL,NULL,(Element**)&pWizardMain);

	ThrowIfFailed(hr);


	pWizardMain->SetVisible(true);
	pWizardMain->EndDefer(defer_key);
	pwnd->Host(pWizardMain);

	pwnd->ShowWindow(SW_SHOW);

	auto *title_elem = pWizardMain->FindDescendent(StrToID((UCString)L"SXTitle"));

	auto *accept_btn = (Button *)pWizardMain->FindDescendent(StrToID((UCString)L"SXWizardDefaultButton"));
	auto *reject_btn = (Button *)pWizardMain->FindDescendent(StrToID((UCString)L"SXWizardAlternateButton"));

	auto *messageInput = (Edit *)pWizardMain->FindDescendent(StrToID((UCString)L"MessageEditBox"));

	auto *progressSpinner = pWizardMain->FindDescendent(StrToID((UCString)L"SXWizardLoadingProgress"));

	LogListener lis;
	hr = pWizardMain->AddListener(&lis);
    ThrowIfFailed(hr);

	int btn_count = 0;

	EventListener click_listener([&](Element*elem, Event*ev) {
		if (ev->flag != GMF_BUBBLED)
			return;
		if (ev->type == TouchButton::Click) {
			btn_count++;
            ThrowIfFailed(title_elem->SetContentString((UCString)std::format(L"Clicked {} times", btn_count).c_str()));
			progressSpinner->SetVisible(true);
		}
		if (ev->type == Edit::Enter) {
			progressSpinner->SetVisible(false);
			Value *txt;
			messageInput->GetContentString(&txt);
			ThrowIfFailed(title_elem->SetContentString((UCString)std::format(L"Entered: {}",(LPCWSTR)txt->GetString()).c_str()));
		}
	});
	hr = pWizardMain->AddListener(&click_listener);
        ThrowIfFailed(hr);

	DumpDuiTree(pWizardMain, 0);

	StartMessagePump();

	UnInitProcessPriv(NULL);
	return 0;
}
