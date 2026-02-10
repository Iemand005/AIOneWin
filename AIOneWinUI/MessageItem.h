#pragma once
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Windows.Foundation.h>

struct MyViewModel : winrt::implements<MyViewModel, winrt::Windows::Foundation::IInspectable, winrt::Microsoft::UI::Xaml::Data::INotifyPropertyChanged>
{
    winrt::event<winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;

    winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    void PropertyChanged(winrt::event_token const& token)
    {
        m_propertyChanged.remove(token);
    }

    void RaisePropertyChanged(winrt::hstring const& name)
    {
        m_propertyChanged(*this, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ name });
    }

    winrt::hstring Title() const { return m_title; }
    void Title(winrt::hstring const& value)
    {
        if (m_title != value)
        {
            m_title = value;
            RaisePropertyChanged(L"Title");
        }
    }

private:
    winrt::hstring m_title;
};
