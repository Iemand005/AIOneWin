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
    }

    hstring MessageControl::Text()
    {
        return m_text;
    }

    void MessageControl::Text(hstring value)
    {
        m_text = value;
    }

    winrt::event_token MessageControl::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    void MessageControl::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }

    /*void MessageControl::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }*/
}
