#pragma once

#include "MessageViewModel.g.h"

namespace winrt::AIOneWinUI::implementation
{
    struct MessageViewModel : MessageViewModelT<MessageViewModel>
    {
        MessageViewModel() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::AIOneWinUI::factory_implementation
{
    struct MessageViewModel : MessageViewModelT<MessageViewModel, implementation::MessageViewModel>
    {
    };
}
