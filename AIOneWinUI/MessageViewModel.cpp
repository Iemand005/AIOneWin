#include "pch.h"
#include "MessageViewModel.h"
#if __has_include("MessageViewModel.g.cpp")
#include "MessageViewModel.g.cpp"
#endif

#include "BlankUserControl.h"

namespace winrt::AIOneWinUI::implementation
{
    int32_t MessageViewModel::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MessageViewModel::MyProperty(int32_t /*value*/)
    {
        throw hresult_not_implemented();
    }

    MessageViewModel::MessageViewModel() {
        m_messages = winrt::single_threaded_observable_vector<AIOneWinUI::BlankUserControl>();

        AIOneWinUI::BlankUserControl control = winrt::make<AIOneWinUI::implementation::BlankUserControl>();
        m_messages.Append(control);
    }

    winrt::Windows::Foundation::Collections::IObservableVector<AIOneWinUI::BlankUserControl> MessageViewModel::Messages() {
        return m_messages;
    }
}
