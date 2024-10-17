#pragma once


// CColorBox

class CColorBox : public CWnd
{
		enum {
		COLOR_SELECT = RGB(201, 224, 247),
		COLOR_BORDER = RGB(98, 162, 228),
		COLOR_FRAME = RGB(128, 128, 128)
	};
	const COLORREF COLOR_NORMAL{ GetSysColor(COLOR_BTNFACE) };
	const COLORREF COLOR_SHADOW{ GetSysColor(COLOR_BTNSHADOW) };
	COLORREF m_clPen{}, m_clBrush{ 0xffffff };
	static COLORREF CColorBox::m_cs[30];
	int m_nIndex{};
	void DrawLeft(CDC* pDC, int nHeight);
	void DrawRight(CDC* pDC, int nHeight);
	void DrawSelection(CDC* pDC, int nHeight);
	void DrawBoxes(CDC* pDC, int nHeight);
	void DrawButton(CDC* pDC);
	int GetBoxIndex(CPoint point, int nHeight);

	DECLARE_DYNAMIC(CColorBox)

public:
	CColorBox();
	virtual ~CColorBox();
	COLORREF GetPenColor() const
	{
		return m_clPen;
	}
	COLORREF GetBrushColor() const
	{
		return m_clBrush;
	}
	void SetPenColor(COLORREF col,BOOL bRedraw=FALSE) 
	{
		m_clPen = col;
		if (bRedraw)
		{//窗口已经创建才能执行
			CRect rect;
			GetClientRect(rect);
			int nHeight = rect.Height();
			InvalidateRect(CRect(0, 0, nHeight, nHeight), FALSE);
		}
	
	}
	void SetBrushColor(COLORREF col,BOOL bRedraw=FALSE)
	{
		m_clBrush = col;
		if (bRedraw)
		{//窗口已经创建才能执行
			CRect rect;
			GetClientRect(rect);
			int nHeight = rect.Height();
			InvalidateRect(CRect(0, 0, nHeight, nHeight), FALSE);
		}
	}
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
	{
		return CWnd::Create(NULL, NULL, WS_CHILD | dwStyle, rect, pParentWnd, nID);
	}
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

};


