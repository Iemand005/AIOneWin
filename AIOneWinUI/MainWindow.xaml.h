#pragma once

#include "MainWindow.g.h"

#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.h>
#include "MessageItem.h"
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <windows.ui.xaml.hosting.h>
#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>
#include <Windows.h>

#include "BlankUserControl.h"

//auto GetOrLoadDll(const wchar_t* name) noexcept {
//    auto dll = GetModuleHandleW(name);
//    if (!dll) { dll = LoadLibraryExW(name, nullptr, 0); }
//    return dll;
//}

//void MakeWindowEligibleForDCompResizeSync(HWND hwnd) {
//    // OS expects to synchronize with UWP, so create an XAML Islands window to trick OS.
//    // WARNING: XAML Islands requires a manifest stating support for >=Win10 1903 to work!
//    static Windows::UI::Xaml::Hosting::DesktopWindowXamlSource dwxs;
//    check_hresult(dwxs.as<IDesktopWindowXamlSourceNative>()->AttachToWindow(hwnd));
//
//    // Enable synchronization with DComp.
//    EnableResizeLayoutSynchronization(hwnd, TRUE);
//}

namespace winrt::AIOneWinUI::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        ModelManagerPtr modelManager;

        //Vector

        //winrt::Windows::Foundation::Collections::IObservableVector<MessageItem> Messages{ nullptr };
        //winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> Messages{ nullptr };
        //winrt::Windows::Foundation::Collections::IObservableVector<MessageItem> Messages {nullptr};
        //winrt::Windows::Foundation::Collections::IObservableVector<MessageItem> Messages();
        //winrt::Windows::Foundation::Collections::IObservableVector<winrt::AIOneWinUI::MessageItem> Messages();

        //HMODULE mod_user32 = GetOrLoadDll(L"user32");
        //using tGetResizeDCompositionSynchronizationObject = void(WINAPI*)(HWND hwnd, LPHANDLE pHandle);
        //tGetResizeDCompositionSynchronizationObject GetResizeDCompositionSynchronizationObject = (tGetResizeDCompositionSynchronizationObject)GetProcAddress(mod_user32, MAKEINTRESOURCEA(2614));
        //using tEnableResizeLayoutSynchronization = void(WINAPI*)(HWND hwnd, BOOL enable);
        //tEnableResizeLayoutSynchronization EnableResizeLayoutSynchronization = (tEnableResizeLayoutSynchronization)GetProcAddress(mod_user32, MAKEINTRESOURCEA(2615));
        //Windows::UI::Core::CoreWindowResizeManager::GetForCurrentView().NotifyLayoutCompleted();

        MainWindow()
        {
            //Messages = winrt::single_threaded_observable_vector<winrt::Windows::Foundation::IInspectable>();
            //Messages = winrt::single_threaded_observable_vector<winrt::Windows::Foundation::IInspectable>();
            //Messages = winrt::single_threaded_observable_vector<MessageItem>();
            //m_messages = single_threaded_observable_vector<MessageItem>();
            modelManager = std::make_unique<ModelManager>();

            m_messages = winrt::single_threaded_observable_vector<AIOneWinUI::BlankUserControl>();

            ///*AIOneWinUI::implementation:*/:BlankUserControl control;
            AIOneWinUI::BlankUserControl control = winrt::make<AIOneWinUI::implementation::BlankUserControl>();
            m_messages.Append(control);

            //m_messages.Append(winrt::make<AIOneWinUI::BlankUserControl>());

            //AppWindow().TitleBar().ExtendsContentIntoTitleBar(true);

        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
        void SendButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void LoadModelButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void TextBox_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& e);

        void Send();
        private:
            winrt::Windows::Foundation::Collections::IObservableVector<AIOneWinUI::BlankUserControl> m_messages;
    };
}

namespace winrt::AIOneWinUI::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
