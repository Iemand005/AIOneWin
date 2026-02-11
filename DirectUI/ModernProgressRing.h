#pragma once

namespace DirectUI
{
    class UILIB_API ModernProgressRing : public Element
    {
    public:
        ModernProgressRing(void);
        ModernProgressRing(ModernProgressRing const&) = delete;
        ModernProgressRing& operator=(ModernProgressRing const&) = delete;
        virtual ~ModernProgressRing(void);

        static long __stdcall Create(Element* parent, unsigned long* deferKey, Element** newElement);
        static IClassInfo* __stdcall GetClassInfoPtr(void);
        static long __stdcall Register(void);

        bool IsActivityOccuring(void);
        bool IsAddLayeredRef(void);

        long SetActivityOccuring(bool);
        long SetAddLayeredRef(bool);

        //virtual IClassInfo* GetClassInfoW(void);
        //virtual void Paint(
        //    HDC,
        //    RECT const*,
        //    RECT const*,
        //    RECT*,
        //    RECT*);

        ////virtual void OnHosted(Element*);
        ////virtual void OnUnHosted(Element*);
        ////void OnDestroy(void)    ;
        //virtual void OnPropertyChanged(
        //    PropertyInfo const*,
        //    int,
        //    Value*,
        //    Value*);

    private:
        static IClassInfo* s_pClassInfo;
    };
}
