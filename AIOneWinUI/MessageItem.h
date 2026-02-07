#pragma once

#include <pch.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Windows.Foundation.h>

struct MessageItem : winrt::implements<MessageItem,
    winrt::Windows::Foundation::IInspectable,
    winrt::Microsoft::UI::Xaml::Data::INotifyPropertyChanged>
{
public:
    MessageItem(winrt::hstring role, winrt::hstring text) : _role(role), _text(text) {}

    winrt::hstring Role() { return _role; }

    void Role(winrt::hstring const& value)
    {
        if (_role != value)
        {
            _role = value;
            PropertyChanged(*this, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Role" });
        }
    }

    winrt::hstring Text() { return _text; }

    void Text(winrt::hstring const& value)
    {
        if (_text != value)
        {
            _text = value;
            PropertyChanged(*this, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Text" });
        }
    }

    winrt::event<winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> PropertyChanged;

private:
    winrt::hstring _role;
    winrt::hstring _text;
};
