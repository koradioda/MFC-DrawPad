#pragma once


// CComboLx

class CComboLx : public CComboBox
{
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	DECLARE_DYNAMIC(CComboLx)
public:
	CComboLx();
	virtual ~CComboLx();
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCbnSelchange();
};


/*BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
	{
		return CWnd::Create(NULL, NULL, WS_CHILD | dwStyle, rect, pParentWnd, nID);
	}*/
	/*int GetWidth() const
	{
		return m_nWidth;
	}
	void SetWidth(int nWidth,BOOL bRedraw=TRUE)
	{
		ASSERT(nWidth > 0);
		m_nWidth = nWidth;
		if (bRedraw)
			SetCurSel(nWidth - 1);
	}*/