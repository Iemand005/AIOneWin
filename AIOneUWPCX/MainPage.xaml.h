//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include <collection.h>          // Vector/IObservableVector
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::UI::Xaml::Data;

#include <AIOne>

namespace AIOneUWPCX
{
	public ref class Message sealed
	{
	public:
		property Platform::String^ Role;
		property Platform::String^ Text;
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

		ModelManagerPtr modelManager;

	};
}
