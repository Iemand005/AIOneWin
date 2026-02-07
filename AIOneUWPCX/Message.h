#pragma once
#pragma once

#include <collection.h>
#include <ppltasks.h>

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Data;

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

		property Boolean IsReasoning
		{
			Boolean get() { return _thinking; }
			void set(Boolean value)
			{
				if (_thinking == value) return;
				_thinking = value;
				_hasThought = true;
				OnPropertyChanged("Reasoning");
				OnPropertyChanged("ReasoningVisibility");
			}
		}

		property Visibility ReasoningVisibility
		{
			Visibility get() {
				return _hasThought ? Visibility::Visible : Visibility::Collapsed;
			}
		}

		Message() {
			_role = "";
			_text = "";
			_thoughts = "";
			_thinking = false;
		}

		Message(String^ role) {
			_role = role;
			_text = "";
			_thoughts = "";
			_thinking = false;
		}

		Message(String^ role, String^ text) {
			_role = role;
			_text = text;
			_thoughts = "";
			_thinking = false;
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
		Boolean _thinking;
		bool _hasThought = false;
	};

}
