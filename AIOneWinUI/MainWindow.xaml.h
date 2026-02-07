#pragma once

#include "MainWindow.g.h"

#include <AIOne>
//#pragma comment(lib, "AIOneCore.lib")

namespace winrt::AIOneWinUI::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        ModelManagerPtr modelManager;

        MainWindow()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

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
