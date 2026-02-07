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
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();

	modelManager = std::make_unique<ModelManager>();

	Messages = ref new Vector<Message^>();
}

void AIOneUWPCX::MainPage::ListView_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{

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
		auto name = file->Name;

		LLModelOptionsAsync options;
		//options.
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

		this->modelManager->loadLLMAsync(file->Path->Data(), options);
		});
	//this->modelManager->
}

void AIOneUWPCX::MainPage::Button_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	//auto message = MexxageInput
	auto message = MessageInput->Text;

	Messages->Append(ref new Message("User", MessageInput->Text));

	AsyncTextGenOptions options;
	auto self = this;

	options.onDone = [](const TextGenResult& output) {
		
		};

		options.onToken = [self](std::string token) {
			self->Dispatcher->RunAsync(CoreDispatcherPriority::Normal,
				ref new Windows::UI::Core::DispatchedHandler([self, token]()
					{
					std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
						//self->MessageInput->Text = ref new String(converter.from_bytes(token).c_str());
						String^ msg = ref new String(converter.from_bytes(token).c_str());;
						self->Messages->Append(ref new Message("Assistant", msg));
						//self->messages->
						
					}));;;;
		};
	modelManager->getChatManager()->sendAsync(this->MessageInput->Text->Data(), options);
}
