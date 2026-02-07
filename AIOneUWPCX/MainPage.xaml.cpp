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
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
	InitializeComponent();

	AIManager = std::make_unique<ModelManager>();
	Messages = ref new Vector<Message^>();
}

void MainPage::LoadLLModel(String^ path)
{
	ModelProgressBar->Visibility = Windows::UI::Xaml::Visibility::Visible;
	LLModelOptionsAsync options;
	auto self = this;
	options.onProgress = [self](float progress) -> void {
		self->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([self, progress]() {
			self->ModelProgressBar->Value = progress * 100;
		}));
	};

	options.onDone = [self]() {
		self->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([self]() {
			self->ModelProgressBar->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
			self->MessageControl->IsEnabled = true;
		}));
	};

	AIManager->loadLLMAsync(path->Data(), options);
}

void MainPage::LoadModelButton_Click(Object^ sender, RoutedEventArgs^ e)
{
	auto picker	 = ref new FileOpenPicker();
	picker->SuggestedStartLocation = PickerLocationId::DocumentsLibrary;
	picker->FileTypeFilter->Append(".gguf");

	auto operation = picker->PickSingleFileAsync();
	operation->Completed = ref new AsyncOperationCompletedHandler<StorageFile^>([this](IAsyncOperation<StorageFile^>^ operation, AsyncStatus status) {
		if (status != AsyncStatus::Completed) return;
			
		auto file = operation->GetResults();
		if (file == nullptr) return;
		auto self = this;
		self->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([self, file]() {
			self->LoadLLModel(file->Path);
		}));
	});
}

void MainPage::SendMessage()
{
	auto message = MessageInput->Text;
	MessageInput->Text = "";

	Messages->Append(ref new Message("User", message));
	AssistantMessage = ref new Message("Assistant");

	AsyncTextGenOptions options;
	auto self = this;

	options.onThinkStateChange = [self](bool thinking) {
		self->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([self, thinking]() {
			self->AssistantMessage->IsReasoning = thinking;
		}));
	};

	options.onGenerationStart = [self]() {
		self->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([self]() {
			self->Messages->Append(self->AssistantMessage);
		}));
	};

	options.onDone = [self](const TextGenResult &result) {
		//self->HasAssistantSent = false;
	};

	options.onTokenReasoning = [self](std::string token, bool reasoning) {
		self->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([self, token, reasoning]() {
			try {
				/*if (!self->HasAssistantSent) {
					self->Messages->Append(self->AssistantMessage);
					self->HasAssistantSent = true;
				}*/

				std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
				String^ newToken = ref new String(converter.from_bytes(token).c_str());;
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

void MainPage::SendButton_Click(Object^ sender, RoutedEventArgs^ e)
{
	SendMessage();
}

void MainPage::InputTextBox_KeyDown(Object^ sender, KeyRoutedEventArgs^ e)
{
	if (e->Key == VirtualKey::Enter) SendMessage();
}