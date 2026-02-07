//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace AIOneUWPCX;

using namespace Platform;
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

		LLModelOptions options;
		auto self = this;
		options.onProgress = [self](float progress) -> void
		{
			self->Dispatcher->RunAsync(CoreDispatcherPriority::Normal,
				ref new Windows::UI::Core::DispatchedHandler([self, progress]()
					{
					self->ModelProgressBar->Value = progress * 100;
					}));;;;
		};

		this->modelManager->loadLLMAsync(file->Name->Data(), options);
		});
	//this->modelManager->
}
