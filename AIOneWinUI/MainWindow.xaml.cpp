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
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage::Pickers;
using namespace AIOneWinUI::implementation;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::AIOneWinUI::implementation
{
    IObservableVector<AIOneWinUI::MessageControl> MainWindow::Messages() {
        return m_messages;
    }
}

void MainWindow::SendButton_Click(IInspectable const& sender, RoutedEventArgs const& e)
{
    Send();
}

void MainWindow::LoadModelButton_Click(IInspectable const& sender, RoutedEventArgs const& e)
{
    winrt::Windows::Storage::Pickers::FileOpenPicker picker;
    HWND hWnd{ 0 };
    this->try_as<::IWindowNative>()->get_WindowHandle(&hWnd);

    picker.as<IInitializeWithWindow>()->Initialize(hWnd);

    picker.ViewMode(PickerViewMode::List);
    picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
    picker.FileTypeFilter().Append(L".gguf");

    picker.PickSingleFileAsync().Completed([this](auto const& operation, auto const& status) {
        if (status != winrt::Windows::Foundation::AsyncStatus::Completed) return;

        auto file = operation.GetResults();

        if (file)
        {
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

            modelManager->loadLLMAsync(file.Path().c_str(), options);
        }
    });
}

void MainWindow::Send()
{
    auto message = this->MessageInput().Text();
    this->MessageInput().Text(L"");

    Messages().Append(winrt::make<implementation::MessageControl>(L"User", message));

    AIOneWinUI::MessageControl assistantMessage = winrt::make<implementation::MessageControl>(L"Assistant");
    auto messageControl = assistantMessage.as<implementation::MessageControl>();

    AsyncTextGenOptions options;

    options.onTokenReasoning = [this, assistantMessage, messageControl](const std::string& token, bool reasoning) {
        this->DispatcherQueue().TryEnqueue([this, assistantMessage, messageControl, token, reasoning]() {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            hstring newToken = converter.from_bytes(token).c_str();

            
            if (reasoning) messageControl->AppendReasoningToken(newToken);
            else messageControl->AppendToken(newToken);
        });
    };

    options.onThinkStateChange = [this, messageControl](bool thinking) {
        messageControl->Thinking(thinking);
    };
    

    options.onGenerationStart = [this, assistantMessage, messageControl]() {
        this->DispatcherQueue().TryEnqueue([this, assistantMessage, messageControl]() {
            Messages().Append(assistantMessage);
            //messageControl->Thinking
        });
    };

    

    modelManager->getChatManager()->sendAsync(message.c_str(), options);
}

void winrt::AIOneWinUI::implementation::MainWindow::TextBox_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& e)
{
    if ( e.Key() == winrt::Windows::System::VirtualKey::Enter) Send();
}
