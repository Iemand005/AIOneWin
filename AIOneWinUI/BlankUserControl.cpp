#include "pch.h"
#include "BlankUserControl.h"
#if __has_include("BlankUserControl.g.cpp")
#include "BlankUserControl.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
//using namespace Microsoft::Foundation;

namespace winrt::AIOneWinUI::implementation
{
    int32_t BlankUserControl::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void BlankUserControl::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    winrt::event_token BlankUserControl::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    void BlankUserControl::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }

    /*void BlankUserControl::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }*/
}
