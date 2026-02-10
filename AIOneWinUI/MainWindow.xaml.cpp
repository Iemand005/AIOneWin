#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <microsoft.ui.xaml.window.h>
#include <ShObjIdl_core.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Windows::Foundation::Collections;
//using namespace Microsoft::UI::Windowing

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::AIOneWinUI::implementation
{
    IObservableVector<AIOneWinUI::MessageControl> MainWindow::Messages() {
        return m_messages;
    }

    void MainWindow::Messages(winrt::Windows::Foundation::Collections::IObservableVector<AIOneWinUI::MessageControl> messages) {

    }
}

void winrt::AIOneWinUI::implementation::MainWindow::SendButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{

}

void winrt::AIOneWinUI::implementation::MainWindow::LoadModelButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    //auto pick/*er = new Windows::Storage::Pickers::fi();*/
    winrt::Windows::Storage::Pickers::FileOpenPicker picker;
    //HWND hwnd = winrt::WindowNative::GetWindowHandle(m_window);/
    //picker.
    auto windowNative{ this->try_as<::IWindowNative>() };
    HWND hWnd{ 0 };
    windowNative->get_WindowHandle(&hWnd);

    picker.as<IInitializeWithWindow>()->Initialize(hWnd);

    picker.ViewMode(winrt::Windows::Storage::Pickers::PickerViewMode::List);
    picker.SuggestedStartLocation(winrt::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
    picker.FileTypeFilter().Append(L".gguf");

    //winrt::Windows::Storage::StorageFile file = 
    picker.PickSingleFileAsync().Completed([this](auto const& operation, auto const& status) {
        if (status != winrt::Windows::Foundation::AsyncStatus::Completed) return;

        auto file = operation.GetResults();
    

    if (file)
    {
        std::wstring path = file.Path().c_str();

        LLModelOptionsAsync options;

        options.onProgress = [this](float progress) {
            winrt::Microsoft::UI::Dispatching::DispatcherQueue dispatcher = this->DispatcherQueue();
            dispatcher.TryEnqueue([this, progress]() {
                this->LoadProgressBar().Value(progress * 100);
            });
        };

        options.onDone = [this]() {
            this->DispatcherQueue().TryEnqueue([this]() {
                this->MessageControl().IsEnabled(true);
            });
        };

        modelManager->loadLLMAsync(path, options);
    }
        });
}

void  winrt::AIOneWinUI::implementation::MainWindow::Send() {
    auto text = this->MessageInput().Text().c_str();

    //this->MessageInput().Text("");

    //auto message = t



    AsyncTextGenOptions options;

    options.onToken = [this](const std::string& token) {
        this->DispatcherQueue().TryEnqueue([this, token]() {
            //auto  message  = winrt::make<MessageItem>("assistant", "");
            //this->Messages.Append(winrt::to_hstring(token));
            //this->Messages.Append(winrt::make<MessageItem>("assistant", ""));
            //Messages.Append(winrt::make<MessageItem>(L"user", L"Hello world"));
        });
    };

    modelManager->getChatManager()->sendAsync(text, options);
}

void winrt::AIOneWinUI::implementation::MainWindow::TextBox_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& e)
{
    //if ( e.Key == winrt::Microsoft::UI::Xaml::Input::IKeyRoutedEventArgs)
    if ( e.Key() == winrt::Windows::System::VirtualKey::Enter) Send();
}


//Windows::Foundation::Collections::IObservableVector<winrt::AIOneWinUI::implementation::MessageItem> winrt::AIOneWinUI::implementation::MainWindow::Messages()
//{
//    return m_messages;
//}