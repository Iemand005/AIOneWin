#include "pch.h"
#include "MessageViewModel.h"
#if __has_include("MessageViewModel.g.cpp")
#include "MessageViewModel.g.cpp"
#endif

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
}
