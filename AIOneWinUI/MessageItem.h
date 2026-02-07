#pragma once

#include <pch.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Windows.Foundation.h>
#include <string>

class MessageItem : winrt::implements<MessageItem, winrt::Windows::Foundation::IInspectable, winrt::Microsoft::UI::Xaml::Data::INotifyPropertyChanged> {
public:
	winrt::hstring Role;
	winrt::hstring Text;

	MessageItem(winrt::hstring role, winrt::hstring text) {

	}
};