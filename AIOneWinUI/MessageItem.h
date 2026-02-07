//#pragma once
//#include "winrt/Microsoft.UI.Xaml.Data.h"
//
//namespace winrt::AIOneWinUI
//{
//    struct MessageItem : winrt::implements<MessageItem, winrt::Microsoft::UI::Xaml::Data::INotifyPropertyChanged>
//    {
//        MessageItem() = default;
//
//        winrt::hstring Role() { return m_role; }
//        void Role(winrt::hstring const& value)
//        {
//            if (m_role != value)
//            {
//                m_role = value;
//                PropertyChanged(*this, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Role" });
//            }
//        }
//
//        winrt::hstring Text() { return m_text; }
//        void Text(winrt::hstring const& value)
//        {
//            if (m_text != value)
//            {
//                m_text = value;
//                PropertyChanged(*this, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Text" });
//            }
//        }
//
//        winrt::event<winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> PropertyChanged;
//
//    private:
//        winrt::hstring m_role;
//        winrt::hstring m_text;
//    };
//}
