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
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

		property Windows::Foundation::Collections::IObservableVector<Message^>^ Messages;
	private:
		void LoadModelButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void SendButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void InputTextBox_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e);

		void LoadLLModel(String^ path);
		void SendMessage();

		ModelManagerPtr AIManager;
		Message^ AssistantMessage;
		Boolean HasAssistantSent = false;

	};
}
