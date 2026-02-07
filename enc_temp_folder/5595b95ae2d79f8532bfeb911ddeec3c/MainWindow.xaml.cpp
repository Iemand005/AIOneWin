#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Foundation.h>
//#include <winrt/WinRT.Interop.h>
//#include <Microsoft.UI.Windowing.h>
//#include <Win32Interop.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include <microsoft.ui.xaml.window.h>
#include <ShObjIdl_core.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Windowing;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::AIOneWinUI::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}

void winrt::AIOneWinUI::implementation::MainWindow::SendButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{

}

void winrt::AIOneWinUI::implementation::MainWindow::LoadModelButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    //auto pick/*er = new Windows::Storage::Pickers::fi();*/
    winrt::Windows::Storage::Pickers::FileOpenPicker picker;
    //HWND hwnd = winrt::WindowNative::GetWindowHandle(m_window);/
    //picker.
    auto windowNative{ this->try_as<::IWindowNative>() };
    HWND hWnd{ 0 };
    windowNative->get_WindowHandle(&hWnd);

    picker.as<IInitializeWithWindow>()->Initialize(hWnd);

    picker.ViewMode(winrt::Windows::Storage::Pickers::PickerViewMode::List);
    picker.SuggestedStartLocation(winrt::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
    picker.FileTypeFilter().Append(L".gguf");

    picker.PickSingleFileAsync();
}
