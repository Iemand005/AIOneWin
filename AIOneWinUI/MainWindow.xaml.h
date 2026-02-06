#pragma once

#include "MainWindow.g.h"

#include <AIOne>
#pragma comment(lib, "AIOneCore.lib")

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
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::AIOneWinUI::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
