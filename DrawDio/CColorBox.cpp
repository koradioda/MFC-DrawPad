// CColorBox.cpp: 实现文件
//

#include "pch.h"
#include "DrawLx.h"
#include "CColorBox.h"

COLORREF CColorBox::m_cs[30]{ 0,0x7F7F7F,RGB(136,0,21),RGB(237,28,36),RGB(225,127,39),
RGB(255,242,0),RGB(34,177,76),RGB(0,162,232),RGB(63,72,204),RGB(163,74,164),0xFFFFFF,RGB(195,195,195),
RGB(185,122,87), RGB(255,174,201), RGB(255,201,14), RGB(239,228,176), RGB(181,230,29),
RGB(153,217,234), RGB(112,146,190), RGB(200,191,231), 0xffffff, 0xffffff,
0xffffff, 0xffffff, 0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff };

// CColorBox

IMPLEMENT_DYNAMIC(CColorBox, CWnd)
//
//void CColorBox::DrawSelect(CDC* pDC, CRect rect)
//{
//	COLORREF c1 = m_nIndex ? COLOR_NORMAL : COLOR_SELECT;
//	COLORREF c2 = m_nIndex ? COLOR_SELECT : COLOR_NORMAL;
//	CPen p1{ PS_SOLID,1,COLOR_BORDER };
//	CPen p2{ PS_SOLID,1,COLOR_FRAME };
//	CBrush b1{ c1 }, b2{ c2 };
//
//	auto pOldPen = pDC->SelectObject(&p1);
//	auto pOldBrush = pDC->SelectObject(&b1);
//	pDC->Rectangle(rect);
//	CRect rc = rect;
//	rc.bottom = rc.Width();
//
//	rc.DeflateRect(5, 2);
//	pDC->SelectObject(&p2);
//	pDC->SelectStockObject(NULL_BRUSH);
//	pDC->Rectangle(rc);
//	rc.DeflateRect(2, 2);
//	pDC->FillSolidRect(rc, m_nIndex? m_clBrush: m_clPen);
//	rc = rect;
//	rc.top = rect.Width();
//	pDC->SelectStockObject(DEFAULT_GUI_FONT);
//	pDC->SelectObject(pOldBrush);
//	//pDC->FillSolidRect(rect, 0xff);
//	pDC->SetBkMode(TRANSPARENT);
//	auto str = rect.left < 5 ? _T("边\r\n框") : _T("填\r\n充");
//
//	pDC->DrawText(str, rc, DT_CENTER);
//}
//
//void CColorBox::DrawNormal(CDC* pDC, CRect rect)
//{
//
//}

void CColorBox::DrawLeft(CDC* pDC, int nHeight)
{
	CRect rect{ 0,0,nHeight / 2,nHeight };
	if (m_nIndex)
	{
		pDC->FillSolidRect(rect, COLOR_NORMAL);
	}
	else
	{
		CPen pen{ PS_SOLID,1,COLOR_BORDER };
		pDC->SelectObject(&pen);
		CBrush br{ COLOR_SELECT };
		pDC->SelectObject(&br);

		pDC->Rectangle(rect);
	}
	CPen pen{ PS_SOLID,1,COLOR_FRAME };

	 pDC->SelectObject(&pen);
	 pDC->SelectStockObject(NULL_BRUSH);
	 rect.bottom = rect.Width();
	 rect.DeflateRect(4, 4);
	pDC->Rectangle(rect);

	rect.DeflateRect(2, 2);
	pDC->FillSolidRect(rect, m_clPen);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(_T("边\r\n框"), CRect(0,nHeight/2,nHeight/2,nHeight), DT_CENTER);
}

void CColorBox::DrawRight(CDC* pDC, int nHeight)
{
	CRect rect{ nHeight / 2,0,nHeight,nHeight };
	if (m_nIndex)
	{
		CPen pen{ PS_SOLID,1,COLOR_BORDER };
		pDC->SelectObject(&pen);
		CBrush br{ COLOR_SELECT };
		pDC->SelectObject(&br);

		pDC->Rectangle(rect);
	}
	else
	{
		pDC->FillSolidRect(rect, COLOR_NORMAL);
	}
	CPen pen{ PS_SOLID,1,COLOR_FRAME };

	pDC->SelectObject(&pen);
	pDC->SelectStockObject(NULL_BRUSH);
	rect.bottom = rect.Width();
	rect.DeflateRect(8, 8);
	pDC->Rectangle(rect);

	rect.DeflateRect(2, 2);
	pDC->FillSolidRect(rect, m_clBrush);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(_T("填\r\n充"), CRect(nHeight / 2, nHeight / 2, nHeight , nHeight), DT_CENTER);
}

void CColorBox::DrawSelection(CDC* pDC,int nHeight)
{
	pDC->SelectStockObject(DEFAULT_GUI_FONT);
	DrawLeft(pDC, nHeight);
	DrawRight(pDC, nHeight);
}

void CColorBox::DrawBoxes(CDC* pDC,int nHeight)
{
	int h = nHeight/3-3;
	CRect rect{0,0,h,h};
	rect.OffsetRect(nHeight, 0);
	int j = -1;
	CPen pen(PS_SOLID,1, COLOR_SHADOW);
	pDC->SelectStockObject(NULL_BRUSH);
	
	pDC->SelectObject(&pen);
	while (++j < 3)
	{
		int i = -1;
		CRect r = rect;
		r.DeflateRect(1, 1);
		while (++i < 10)
		{
			pDC->Rectangle(r);
			CRect rc = r;
			rc.DeflateRect(2, 2);
			auto color = m_cs[j * 10 + i];
			pDC->FillSolidRect(rc, color);
			r.OffsetRect(h, 0);

		}
		rect.OffsetRect(0, h);
	}


}

void CColorBox::DrawButton(CDC* pDC)
{
}

int CColorBox::GetBoxIndex(CPoint point,int nHeight)
{
	int h = nHeight / 3 - 3;
	CRect rect{ 0,0,h,h };
	rect.OffsetRect(nHeight, 0);
	int j = -1;

	while (++j < 3)
	{
		int i = -1;
		CRect r = rect;
		
		while (++i < 10)
		{
			if (r.PtInRect(point))
				return i + j * 10;
			r.OffsetRect(h, 0);

		}
		rect.OffsetRect(0, h);
	}

	return -1;
}

CColorBox::CColorBox()
{
}

CColorBox::~CColorBox()
{
}


BEGIN_MESSAGE_MAP(CColorBox, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CColorBox 消息处理程序




BOOL CColorBox::PreCreateWindow(CREATESTRUCT& cs)
{
	//WNDCLASS wc{CS_HREDRAW|CS_VREDRAW};
	//wc.lpszClassName = _T("COLOR_BOX_LX");
	//if (AfxRegisterClass(&wc))
	//	cs.lpszClass = wc.lpszClassName;
	
	return CWnd::PreCreateWindow(cs);
}


void CColorBox::OnPaint()
{
	CPaintDC dc(this); 
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, GetSysColor(COLOR_BTNFACE));
	
	DrawSelection(&dc, rect.Height());
	DrawBoxes(&dc,rect.Height());
	DrawButton(&dc);
}


BOOL CColorBox::OnEraseBkgnd(CDC* pDC)
{

	return TRUE;
}


void CColorBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonDown(nFlags, point);
	CRect rect,rc;
	GetClientRect(rect);
	rc = rect;
	int nHeight = rect.Height();
	int nIndex = m_nIndex;
	if (point.x < nHeight / 2)
		nIndex = 0;
	else if (point.x < nHeight)
		nIndex = 1;
	if (nIndex != m_nIndex)
	{//切换算法
		m_nIndex = nIndex;
		
		InvalidateRect(CRect(0,0,nHeight,nHeight),FALSE);
		return;
	}
	nIndex = GetBoxIndex(point,nHeight);
	if (nIndex > -1 && nIndex < 30)
	{
		auto color = m_cs[nIndex];
		COLORREF* pColor = m_nIndex?&m_clBrush:&m_clPen;
		if (*pColor != color)
		{//切换算法
			*pColor = color;
			theApp.WriteProfileInt(_T("COLOR"), _T("PEN"), m_clPen);
			theApp.WriteProfileInt(_T("COLOR"), _T("BRUSH"), m_clBrush);
			InvalidateRect(CRect(0, 0, nHeight, nHeight), FALSE);
			GetParent()->PostMessage(WM_COMMAND, ID_DRAW_PEN + m_nIndex);
		}
	}

}
