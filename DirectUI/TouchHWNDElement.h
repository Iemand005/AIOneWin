#pragma once

namespace DirectUI
{
    enum TouchHWNDElementFlags : unsigned int
    {
        None = 0,
        Flag1 = 1,
        Flag2 = 2,
    };

    enum class TOUCHTOOLTIP_INPUT : unsigned int
    {
        None = 0,
        Input1 = 1,
        Input2 = 2,
    };

    enum class TOUCHTOOLTIP_OPTION_FLAGS : unsigned int
    {
        None = 0,
        Option1 = 1,
        Option2 = 2,
    };

    class UILIB_API TouchHWNDElement : public Element
    {
    public:
        TouchHWNDElement();
        TouchHWNDElement(TouchHWNDElement const&) = delete;
        TouchHWNDElement& operator=(TouchHWNDElement const&) = delete;
        virtual ~TouchHWNDElement();

        static long __stdcall Create(HWND, bool, unsigned int, Element*parent, unsigned long* deferKey, Element**newElement);
        static IClassInfo* __stdcall GetClassInfoPtr();
        static long __stdcall Register();

        long Initialize(HWND, bool, unsigned int, Element* parent, unsigned long* deferKey);

        void ActivateTooltip(Element*, unsigned long);
        long DismissIHMAsync();
        long HideTouchTooltip();
        long IHMNotify();
        unsigned int MessageCallback(tagGMSG*);
        long MonitorPowerSettingsChange();
        long ProcessingKeyboardNavigation();
        long RegisterForAnimationStatusChanges();
        long RegisterForIHMChanges();
        long RegisterForMonitorPowerChanges();
        void RemoveTooltip(Element*);
        long ScaleChanged();
        void SetFlags(TouchHWNDElementFlags, TouchHWNDElementFlags);
        void SetLightDismissIHM(bool);
        void SetTooltipMaximumLineCount(int);
        void SetWindowAccessGradientColor(Value*);
        void ShowRichTooltip(TOUCHTOOLTIP_INPUT, TOUCHTOOLTIP_OPTION_FLAGS, Element*);
        void StartRichTooltipTimer(TOUCHTOOLTIP_INPUT);
        void UpdateTooltip(Element*);
        void UsePerMonitorScaling(HMONITOR*);
        LRESULT WndProc(HWND*, UINT, WPARAM, LPARAM);
        void _ClearTooltipState();
        void _DestroyTooltip();
        void _OnUIStateChanged(unsigned short, unsigned short);
        void UnregisterForAnimationStatusChanges();
        void UnregisterForIHMChanges();
        void UnregisterForMonitorPowerChanges();

        bool IsActivityOccuring() const;
        bool IsAddLayeredRef() const;
        bool IsMSAAEnabled() const;
        bool IsRegisteredForAnimationStatusChanges() const;
        bool ShouldUsePerMonitorScaling() const;

        TouchHWNDElementFlags GetFlags() const;
        int GetIHMState() const;
        int GetTooltipMaximumLineCount() const;

        void GetIHMRect(RECT*) const;
        Value* GetWindowAccessGradientColor() const;
        bool GetLightDismissIHM() const;
        bool TextTooltipShowing() const;
        bool RichTooltipShowing() const;

        virtual IClassInfo* GetClassInfoW() ;
        virtual void OnHosted(Element*) ;
        virtual void OnUnHosted(Element*) ;
        virtual void OnDestroy();
        virtual void OnPropertyChanged(PropertyInfo const*, int, Value*, Value*) ;
        virtual void OnEvent(Event*) ;
        virtual void OnInput(InputEvent*) ;
        virtual void OnKeyFocusMoved(Element*, Element*) ;
        virtual void Paint(HDC, RECT const*, RECT const*, RECT*, RECT*) ;

        static const PropertyInfo* __stdcall FlagsProp();
        static const PropertyInfo* __stdcall LightDismissIHMProp();
        static const PropertyInfo* __stdcall TooltipMaximumLineCountProp();
        static const PropertyInfo* __stdcall ForwardingWindowMessage();
        static const PropertyInfo* __stdcall WindowAccessGradientColorProp();

    private:
        static IClassInfo* s_pClassInfo;
    };
}
