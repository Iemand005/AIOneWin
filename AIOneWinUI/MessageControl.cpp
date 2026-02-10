#include "pch.h"
#include "MessageControl.h"
#if __has_include("MessageControl.g.cpp")
#include "MessageControl.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Data;

namespace winrt::AIOneWinUI::implementation
{

    hstring MessageControl::Role()
    {
        return m_role;
    }

    void MessageControl::Role(hstring value)
    {
        m_role = value;
        ReportPropertyChanged(L"Role");
    }

    hstring MessageControl::Text()
    {
        return m_text;
    }

    void MessageControl::Text(hstring value)
    {
        m_text = value;
        ReportPropertyChanged(L"Text");
    }

    hstring MessageControl::Thoughts()
    {
        return m_thoughts;
    }

    void MessageControl::Thoughts(hstring value)
    {
        m_thoughts = value;
        ReportPropertyChanged(L"Thoughts");
        ReportPropertyChanged(L"HasThought");
    }

    bool MessageControl::Thinking()
    {
        return m_thinking;
    }

    bool MessageControl::HasThought()
    {
        return m_thoughts.size();
    }

    void MessageControl::Thinking(bool thinking)
    {
        m_thinking = thinking;
        ReportPropertyChanged(L"Thinking");
    }

    void MessageControl::AppendReasoningToken(winrt::hstring token)
    {
        Text(Text() + token);
    }
    
    void MessageControl::AppendToken(winrt::hstring token)
    {
        Text(Text() + token);
    }

    winrt::event_token MessageControl::PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    void MessageControl::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }

    void MessageControl::ReportPropertyChanged(hstring functionName)
    {
        m_propertyChanged(*this, PropertyChangedEventArgs(functionName));
    }
}
