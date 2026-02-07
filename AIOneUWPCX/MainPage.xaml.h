//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include <collection.h>
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Data;

#include <AIOne>
#include "Message.h"

namespace AIOneUWPCX
{
	public ref class BoolToVisibilityConverter sealed : IValueConverter
	{
	public:
		virtual Object^ Convert(Object^ value, Windows::UI::Xaml::Interop::TypeName targetType, Object^ parameter, String^ language)
		{
			auto b = dynamic_cast<IBox<bool>^>(value);
			if (b != nullptr && b->Value)
				return Windows::UI::Xaml::Visibility::Visible;
			else
				return Windows::UI::Xaml::Visibility::Collapsed;
		}

		virtual Object^ ConvertBack(Object^ value, Windows::UI::Xaml::Interop::TypeName targetType, Object^ parameter, String^ language)
		{
			throw ref new Platform::NotImplementedException();
		}
	};

	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

		property Windows::Foundation::Collections::IObservableVector<Message^>^ Messages;
	private:
		void ListView_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Button_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		void LoadLLModel(String^ path);

		ModelManagerPtr modelManager;

	};
}
