#pragma once

namespace DirectUI
{
    class UILIB_API ModernProgressBar : public Element
    {
    public:
        ModernProgressBar(void);
        ModernProgressBar(ModernProgressBar const&) = delete;
        ModernProgressBar& operator=(ModernProgressBar const&) = delete;
        virtual ~ModernProgressBar(void);

        static long __stdcall Create(Element*, unsigned long*, Element**);
        static IClassInfo* __stdcall GetClassInfoPtr(void);
        static PropertyInfo const* __stdcall PositionProp(void);
        static PropertyInfo const* __stdcall MaximumProp(void);
        static PropertyInfo const* __stdcall MinimumProp(void);
        static PropertyInfo const* __stdcall StateProp(void);
        static PropertyInfo const* __stdcall DeterminateProp(void);
        static long __stdcall Register(void);

        int  GetMaximum(void);
        int  GetMinimum(void);
        int  GetPosition(void);
        int  GetState(void);

        bool IsDeterminate(void);
        bool IsActivityOccuring(void);
        bool IsAddLayeredRef(void);
        bool IsAutoHeight(void);
        bool IsIndependentAnimations(void);
        bool IsSmoothFillAnimation(void);

        long SetMaximum(int);
        long SetMinimum(int);
        long SetPosition(int);
        long SetState(int);

        long SetDeterminate(bool);
        long SetActivityOccuring(bool);
        long SetAddLayeredRef(bool);
        long SetAutoHeight(bool);
        long SetIndependentAnimations(bool);
        long SetSmoothFillAnimation(bool);

        virtual IClassInfo* GetClassInfoW(void);
        virtual void Paint(
            HDC,
            RECT const*,
            RECT const*,
            RECT*,
            RECT*);

        virtual void OnHosted(Element*);
        virtual void OnUnHosted(Element*);
        virtual void OnDestroy(void);
        virtual void OnPropertyChanged(
            PropertyInfo const*,
            int,
            Value*,
            Value*);

    private:
        static IClassInfo* s_pClassInfo;
    };

    class UILIB_API ModernProgressBarRangeValueProxy : public IProxy
    {
    public:
        ModernProgressBarRangeValueProxy(void);
        ModernProgressBarRangeValueProxy(ModernProgressBarRangeValueProxy const&);
        ModernProgressBarRangeValueProxy(ModernProgressBarRangeValueProxy&&);

        ModernProgressBarRangeValueProxy&
            operator=(ModernProgressBarRangeValueProxy const&);
        ModernProgressBarRangeValueProxy&
            operator=(ModernProgressBarRangeValueProxy&&);

        virtual long DoMethod(int, char*);

    protected:
        virtual void Init(Element*);
    };
}
