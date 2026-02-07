#pragma once

#include "MainWindow.g.h"

#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.h>
#include "MessageItem.h"

namespace winrt::AIOneWinUI::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        ModelManagerPtr modelManager;

        //Vector

        //winrt::Windows::Foundation::Collections::IObservableVector<MessageItem> Messages{ nullptr };
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> Messages{ nullptr };

        MainWindow()
        {
            Messages = winrt::single_threaded_observable_vector<MessageItem>();
            modelManager = std::make_unique<ModelManager>();

            //AppWindow().TitleBar().ExtendsContentIntoTitleBar(true);

        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
        void SendButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void LoadModelButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void TextBox_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& e);

        void Send();
    };
}

namespace winrt::AIOneWinUI::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
