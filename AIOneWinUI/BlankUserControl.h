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
            //m_text = winrt::make<hstring>("Bark");
            m_text = L"Bark";
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        winrt::hstring Text();
        void Text(winrt::hstring value);

        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;

        private:
        event<winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;

        winrt::hstring m_text;

        //void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::AIOneWinUI::factory_implementation
{
    struct BlankUserControl : BlankUserControlT<BlankUserControl, implementation::BlankUserControl>
    {
    };
}
