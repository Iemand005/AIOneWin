#pragma once

#include "MainWindow.g.h"

#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <windows.ui.xaml.hosting.h>
#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>
#include <Windows.h>

#include "BlankUserControl.h"

namespace winrt::AIOneWinUI::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        ModelManagerPtr modelManager;

        MainWindow()
        {
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

        winrt::Windows::Foundation::Collections::IObservableVector<AIOneWinUI::BlankUserControl> Messages();
        void Messages(winrt::Windows::Foundation::Collections::IObservableVector<AIOneWinUI::BlankUserControl> messages);
        //void Messages(AIOneWinUI::BlankUserControl control);

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
