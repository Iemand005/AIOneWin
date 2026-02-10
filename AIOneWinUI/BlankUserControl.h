#pragma once

#include <winrt/Microsoft.UI.Xaml.h>
//#include "winrt/Windows.UI.Xaml.Markup.h"
//#include "winrt/Windows.UI.Xaml.Interop.h"
//#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "BlankUserControl.g.h"

namespace winrt::AIOneWinUI::implementation
{
    struct BlankUserControl : BlankUserControlT<BlankUserControl>
    {
        BlankUserControl() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        winrt::hstring Text();
        void Text(winrt::hstring value);

        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;

        private:
        event<winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;

        //void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::AIOneWinUI::factory_implementation
{
    struct BlankUserControl : BlankUserControlT<BlankUserControl, implementation::BlankUserControl>
    {
    };
}
