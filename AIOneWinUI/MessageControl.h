#pragma once

#include <winrt/Microsoft.UI.Xaml.h>
//#include "winrt/Windows.UI.Xaml.Markup.h"
//#include "winrt/Windows.UI.Xaml.Interop.h"
//#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "MessageControl.g.h"

namespace winrt::AIOneWinUI::implementation
{
    struct MessageControl : MessageControlT<MessageControl>
    {
        MessageControl() 
        {
            m_role = L"User";
            m_text = L"Bark";
        }

        MessageControl(winrt::hstring role)
        {
            m_role = role;
            m_text = L" ";
        }

        MessageControl(winrt::hstring role, winrt::hstring text)
        {
            m_role = role;
            m_text = text;
        }

        winrt::hstring Role();
        void Role(winrt::hstring value);

        winrt::hstring Text();
        void Text(winrt::hstring value);

        void AppendToken(winrt::hstring token);
        void AppendReasoningToken(winrt::hstring token);

        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;

        private:
        event<winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;

        winrt::hstring m_role = L" ";
        winrt::hstring m_text = L" ";
    };
}

namespace winrt::AIOneWinUI::factory_implementation
{
    struct MessageControl : MessageControlT<MessageControl, implementation::MessageControl>
    {
    };
}
