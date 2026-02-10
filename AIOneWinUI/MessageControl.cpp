#include "pch.h"
#include "MessageControl.h"
#if __has_include("MessageControl.g.cpp")
#include "MessageControl.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
//using namespace Microsoft::Foundation;

namespace winrt::AIOneWinUI::implementation
{

    hstring MessageControl::Role()
    {
        return m_role;
    }

    void MessageControl::Role(hstring value)
    {
        m_role = value;
        //m_propertyChanged("Role");
        //m_propertyChanged(*this, PropertyChangedEventArgs(L"Role"));
        m_propertyChanged(*this, winrt::Windows::UI::Xaml::Data::PropertyChangedEventArgs(L"Role"));
    }

    hstring MessageControl::Text()
    {
        return m_text;
    }

    void MessageControl::Text(hstring value)
    {
        m_text = value;
        //m_propertyChanged(*this, PropertyChangedEventArgs(L"Text"));
        //m_propertyChanged("Text");
        m_propertyChanged(*this, winrt::Windows::UI::Xaml::Data::PropertyChangedEventArgs(L"Text"));
    }

    void MessageControl::AppendReasoningToken(winrt::hstring token)
    {
        m_text = m_text  + token;;;;;;;
        //m_propertyChanged(*this, PropertyChangedEventArgs(L"Token"));
        //m_text.
        //m_propertyChanged(this, L"Text");
        m_propertyChanged(*this, winrt::Windows::UI::Xaml::Data::PropertyChangedEventArgs(L"Text"));
    }
    
    void MessageControl::AppendToken(winrt::hstring token)
    {
        m_text = m_text + token;;
        m_propertyChanged(*this, winrt::Windows::UI::Xaml::Data::PropertyChangedEventArgs(L"Text"));
        //m_text += token;
        //m_propertyChanged(L"Text");
    }

    winrt::event_token MessageControl::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    void MessageControl::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
}
