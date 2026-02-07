#pragma once
#include "winrt/Microsoft.UI.Xaml.Data.h"

namespace winrt::AIOneWinUI
{
    class NotifyPropertyChangedBase {
    public:

        using PropertyChangedEventHandler = winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler;
        using PropertyChangedEventArgs = winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs;

        NotifyPropertyChangedBase() = default;

        auto PropertyChanged(PropertyChangedEventHandler const& handler) -> winrt::event_token {

            return propertyChangedEvent.add(handler);
        }

        auto PropertyChanged(winrt::event_token token) -> void {

            propertyChangedEvent.remove(token);
        }

    protected:

        auto OnPropertyChanged(this auto& self, PropertyChangedEventArgs const& args) -> void {

            self.propertyChangedEvent(self, args);
        }

        auto OnPropertyChanged(this auto& self, winrt::hstring const& propertyName) -> void {

            self.propertyChangedEvent(self, PropertyChangedEventArgs{ propertyName });
        }

    private:

        winrt::event<PropertyChangedEventHandler> propertyChangedEvent;
    };

    class MessageItem : NotifyPropertyChangedBase {

    };

    //class MessageItem// : winrt::implements<MessageItem, winrt::Microsoft::UI::Xaml::Data::INotifyPropertyChanged>
    //{
    ////    MessageItem() = default;

    ////    // Getter
    ////    winrt::hstring Text() const { return m_text; }

    ////    // Setter
    ////    void Text(winrt::hstring const& value)
    ////    {
    ////        if (value != m_text)
    ////        {
    ////            m_text = value;
    ////            PropertyChanged(*this, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Text" });
    ////        }
    ////    }

    ////    // INotifyPropertyChanged event
    ////    winrt::event<winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> PropertyChanged;

    ////private:
    ////    winrt::hstring m_text;
    //};
}
