#pragma once

#include "MessageViewModel.g.h"

namespace winrt::AIOneWinUI::implementation
{
    struct MessageViewModel : MessageViewModelT<MessageViewModel>
    {
        MessageViewModel();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        winrt::Windows::Foundation::Collections::IObservableVector<AIOneWinUI::BlankUserControl> Messages();

        private:
            winrt::Windows::Foundation::Collections::IObservableVector<AIOneWinUI::BlankUserControl> m_messages;
    };
}

namespace winrt::AIOneWinUI::factory_implementation
{
    struct MessageViewModel : MessageViewModelT<MessageViewModel, implementation::MessageViewModel>
    {
    };
}
