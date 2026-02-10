#pragma once

#include <winrt/Microsoft.UI.Xaml.h>
#include "MessageControl.g.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml::Data;

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
            m_text = L"";
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

        winrt::hstring Thoughts();
        void Thoughts(winrt::hstring value);

        bool Thinking();
        void Thinking(bool thinking);

        bool HasThought();

        void AppendToken(winrt::hstring token);
        void AppendReasoningToken(winrt::hstring token);

        winrt::event_token PropertyChanged(PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;

        private:
        event<PropertyChangedEventHandler> m_propertyChanged;

        winrt::hstring m_role = L"";
        winrt::hstring m_text = L"";
        winrt::hstring m_thoughts = L"";
        bool m_thinking = false;

        void ReportPropertyChanged(hstring functionName);
    };
}

namespace winrt::AIOneWinUI::factory_implementation
{
    struct MessageControl : MessageControlT<MessageControl, implementation::MessageControl>
    {
    };
}
