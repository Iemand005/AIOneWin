#pragma once

namespace DirectUI
{
	class UILIB_API ModernProgressBar : public Element
	{
	public:
		Progress(Progress const&);
		Progress(void);
		virtual ~Progress(void);
		Progress& operator=(Progress const&);

		static long __stdcall Create(Element*, unsigned long*, Element**);
		static IClassInfo* __stdcall GetClassInfoPtr(void);
		static PropertyInfo const* __stdcall PositionProp(void);
		static long __stdcall Register(void);
		static void __stdcall SetClassInfoPtr(IClassInfo*);
		static PropertyInfo const* __stdcall MaximumProp(void);
		static PropertyInfo const* __stdcall MinimumProp(void);

		int GetMaximum(void);
		int GetMinimum(void);
		int GetPosition(void);
		long Initialize(Element*, unsigned long*);
		long SetMaximum(int);
		long SetMinimum(int);
		long SetPosition(int);

		virtual IClassInfo* GetClassInfoW(void);
		virtual SIZE GetContentSize(int, int, Surface*);
		virtual void Paint(HDC, RECT const*, RECT const*, RECT*, RECT*);

			int Create(DirectUI::Element*, ulong*, DirectUI::Element**)	;
			int DeterminateProp(void)	;
			int GetClassInfoPtr(void)	;
			int GetClassInfoW(void)	;
			int GetMaximum(void)	;
			int GetMinimum(void)	;
			int GetPosition(void)	;
			int GetState(void)	;
			int IsActivityOccuring(void)	;
			int IsAddLayeredRef(void)	;
			int IsAutoHeight(void)	;
			int IsDeterminate(void)	;
			int IsIndependentAnimations(void)	;
			int IsSmoothFillAnimation(void)	;
			int MaximumProp(void)	;
			int MinimumProp(void)	;
			int ModernProgressBar(void)	;
			int OnDestroy(void)	;
			int OnHosted(DirectUI::Element*)	;
			int OnPropertyChanged(DirectUI::PropertyInfo const*, int, DirectUI::Value*, DirectUI::Value*)	;
			int OnUnHosted(DirectUI::Element*)	;
			int Paint(HDC__*, tagRECT const*, tagRECT const*, tagRECT*, tagRECT*)	;
			int PositionProp(void)	;
			int Register(void)	;
			int SetActivityOccuring(bool)	;
			int SetAddLayeredRef(bool)	;
			int SetAutoHeight(bool)	;
			int SetDeterminate(bool)	;
			int SetIndependentAnimations(bool)	;
			int SetMaximum(int)	;
			int SetMinimum(int)	;
			int SetPosition(int)	;
			int SetSmoothFillAnimation(bool)	;
			int SetState(int)	;
			int StateProp(void)	;
			~ModernProgressBar(void)	;
			DirectUI::ModernProgressRing::Create(DirectUI::Element*, ulong*, DirectUI::Element**)	;
			DirectUI::ModernProgressRing::GetClassInfoPtr(void)	;
			DirectUI::ModernProgressRing::GetClassInfoW(void)	;
			DirectUI::ModernProgressRing::IsActivityOccuring(void)	;
			DirectUI::ModernProgressRing::IsAddLayeredRef(void)	;
			DirectUI::ModernProgressRing::ModernProgressRing(void)	;
			DirectUI::ModernProgressRing::OnDestroy(void)	;
			DirectUI::ModernProgressRing::OnHosted(DirectUI::Element*)	;
			DirectUI::ModernProgressRing::OnPropertyChanged(DirectUI::PropertyInfo const*, int, DirectUI::Value*, DirectUI::Value*)	;
			DirectUI::ModernProgressRing::OnUnHosted(DirectUI::Element*)	;
			DirectUI::ModernProgressRing::Paint(HDC__*, tagRECT const*, tagRECT const*, tagRECT*, tagRECT*)	;
			DirectUI::ModernProgressRing::Register(void)	;
			DirectUI::ModernProgressRing::SetActivityOccuring(bool)	;
			DirectUI::ModernProgressRing::SetAddLayeredRef(bool)	;
			DirectUI::ModernProgressRing::~ModernProgressRing(void)	;
			const DirectUI::ModernProgressBarRangeValueProxy::`vftable'	;

	private:
		static IClassInfo* s_pClassInfo;

	};

	class UILIB_API ProgressRangeValueProxy : public IProxy
	{
	public:
		ProgressRangeValueProxy(ProgressRangeValueProxy const&);
		ProgressRangeValueProxy(void);
		ProgressRangeValueProxy& operator=(ProgressRangeValueProxy const&);

		virtual long DoMethod(int, char*);
	protected:
		virtual void Init(Element*);
	};
}