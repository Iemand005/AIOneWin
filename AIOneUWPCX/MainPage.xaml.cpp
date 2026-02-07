//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace AIOneUWPCX;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::System;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
//using namespace Windows::UI::Core::;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();

	AIManager = std::make_unique<ModelManager>();
	Messages = ref new Vector<Message^>();
}

void AIOneUWPCX::MainPage::ListView_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{

}

void AIOneUWPCX::MainPage::LoadLLModel(String^ path)
{
	LLModelOptionsAsync options;
	auto self = this;
	options.onProgress = [self](float progress) -> void
		{
			self->Dispatcher->RunAsync(CoreDispatcherPriority::Normal,
				ref new Windows::UI::Core::DispatchedHandler([self, progress]()
					{
						self->ModelProgressBar->Value = progress * 100;
					}));;;;
		};
	options.onDone = []() {

		};

	AIManager->loadLLMAsync(path->Data(), options);
}

void AIOneUWPCX::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto picker	 = ref new FileOpenPicker();
	picker->SuggestedStartLocation = PickerLocationId::DocumentsLibrary;
	picker->FileTypeFilter->Append(".gguf");

	auto operation = picker->PickSingleFileAsync();
	operation->Completed = ref new AsyncOperationCompletedHandler<StorageFile^>([this](IAsyncOperation<StorageFile^>^ operation, AsyncStatus status)
	{
		if (status != AsyncStatus::Completed) return;
			
		auto file = operation->GetResults();
		if (file == nullptr) return;

		this->LoadLLModel(file->Path);
	});
}

std::string trimLeadingNewlines(const std::string& s) {
	size_t start = 0;
	while (start < s.size() && s[start] == '\n') ++start;
	return s.substr(start);
}

void AIOneUWPCX::MainPage::Button_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	SendMessage();
}

////t/*emplate<typename Fn>
//void MainPage::RunAsync(std::function<T> func) {
//	Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler(func));
//}*/

void MainPage::SendMessage()
{
	auto message = MessageInput->Text;

	Messages->Append(ref new Message("User", message));
	MessageInput->Text = "";
	AssistantMessage = ref new Message("Assistant");

	AsyncTextGenOptions options;
	auto self = this;

	options.onThinkStateChange = [self](bool thinking)
	{
		self->RunAsync([self, thinking]()
		{
			self->AssistantMessage->Reasoning = thinking;
		});
	};

	options.onDone = [self](const TextGenResult &result) {
		self->HasAssistantSent = false;
	};

	options.onTokenReasoning = [self](std::string token, bool reasoning) {
		self->RunAsync([self, token, reasoning]()
		{
			try {
				if (!self->HasAssistantSent) {
					self->Messages->Append(self->AssistantMessage);
					self->HasAssistantSent = true;
				}
				auto trimmedToken = token;
				if (!reasoning && self->AssistantMessage->Text->IsEmpty())
					trimmedToken = trimLeadingNewlines(token);

				std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
				String^ newToken = ref new String(converter.from_bytes(trimmedToken).c_str());;
				if (reasoning)
					self->AssistantMessage->Thoughts += newToken;
				else self->AssistantMessage->Text += newToken;
			}
			catch (...) {
				self->AssistantMessage->Text += "";
			}
		}));
	};
	AIManager->getChatManager()->sendAsync(message->Data(), options);
}

void MainPage::InputTextBox_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	if (e->Key == VirtualKey::Enter)
	{
		auto textBox = dynamic_cast<TextBox^>(sender);
		auto message = textBox->Text;

		SendMessage();

		textBox->Text = "";

		e->Handled = true;
	}
}
