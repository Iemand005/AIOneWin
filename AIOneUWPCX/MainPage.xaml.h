//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include <collection.h>
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::UI::Xaml::Data;

#include <AIOne>

namespace AIOneUWPCX
{
	public ref class Message sealed : INotifyPropertyChanged
	{
	public:
		property String^ Role
		{
			String^ get() { return _role; }
			void set(String^ value)
			{
				if (_role == value) return;
				_role = value;
				OnPropertyChanged("Role");
			}
		}

		property String^ Text
		{
			String^ get() { return _text; }
			void set(String^ value)
			{
				if (_text == value) return;
				_text = value;
				OnPropertyChanged("Text");
			}
		}

		property String^ Thoughts
		{
			String^ get() { return _thoughts; }
			void set(String^ value)
			{
				if (_thoughts == value) return;
				_thoughts = value;
				OnPropertyChanged("Thoughts");
			}
		}

		Message() {
			_role = "";
			_text = "";
		}

		Message(String^ role) {
			_role = role;
			_text = "";
		}

		Message(String^ role, String^ text) {
			_role = role;
			_text = text;
		}

		virtual event PropertyChangedEventHandler^ PropertyChanged;

	protected:
		void OnPropertyChanged(String^ propertyName)
		{
			PropertyChanged(this, ref new PropertyChangedEventArgs(propertyName));
		}

	private:
		String^ _role;
		String^ _text;
		String^ _thoughts;
	};

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

		ModelManagerPtr modelManager;

	};
}
