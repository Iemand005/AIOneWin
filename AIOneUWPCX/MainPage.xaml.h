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
using namespace Windows::UI::Xaml::Input;
using namespace Windows::Foundation::Collections;

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

		property IObservableVector<Message^>^ Messages;
	private:
		void LoadModelButton_Click(Platform::Object^ sender, RoutedEventArgs^ e);
		void SendButton_Click(Platform::Object^ sender, RoutedEventArgs^ e);
		void InputTextBox_KeyDown(Platform::Object^ sender, KeyRoutedEventArgs^ e);

		void LoadLLModel(String^ path);
		void SendMessage();

		ModelManagerPtr AIManager;
		Message^ AssistantMessage;
		//Boolean HasAssistantSent = false;

	};
}
