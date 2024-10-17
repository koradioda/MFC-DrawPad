#include "pch.h"
#include "CEllipse.h"
#include "DrawLx.h"
using namespace Gdiplus;

void CEllipse::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_rect.TopLeft() = point;
}

void CEllipse::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_rect.BottomRight() = point;
	m_rect.NormalizeRect();
}

void CEllipse::OnMouseMove(UINT nFlags, CPoint point, CDC* pDC)
{
	if(ST_DRAW==m_stat)
		m_rect.BottomRight() = point;
}
#include <gdiplusbrush.h>
void CEllipse::OnDraw(CDC* pDC, CWnd* hwnd)
{
	Graphics g(pDC->GetSafeHdc());
	Pen pen({ 0xff,GetRValue(m_clPen),GetGValue(m_clPen),GetBValue(m_clPen) }, (REAL)m_nWidth);
	//SolidBrush
	auto a = m_stat == ST_DRAW ? 0x80 : 0xff;
	
	Color color(a,GetRValue(m_clBrush),GetGValue(m_clBrush),GetBValue(m_clBrush) );
	SolidBrush brush(color);
	CRect rect{ m_rect };
	g.FillEllipse(&brush, rect.left, rect.top, rect.Width(), rect.Height());
	g.DrawEllipse(&pen, rect.left, rect.top, rect.Width(), rect.Height());

	if (ST_SELECT == m_stat)
	{
		CPoint pt = m_rect.CenterPoint();
		DrawSelect(pDC, { pt.x,m_rect.top });
		DrawSelect(pDC, { pt.x,m_rect.bottom });
		DrawSelect(pDC, { m_rect.left,pt.y });
		DrawSelect(pDC, { m_rect.right,pt.y });
		if (m_ptDrag.x != MAXWORD)
		{
			Color color(0x80, GetRValue(m_clBrush), GetGValue(m_clBrush), GetBValue(m_clBrush));
			SolidBrush brush(color);
			rect.OffsetRect(m_pt2 - m_ptDrag);
			g.FillEllipse(&brush, rect.left, rect.top, rect.Width(), rect.Height());
			g.DrawEllipse(&pen, rect.left, rect.top, rect.Width(), rect.Height());
		}
	}

}

/*	
	Point startPoint{m_rect.left,m_rect.top}; // 设置起始点的 x 和 y 坐标
	Point endPoint(m_rect.right,m_rect.bottom); // 设置终止点的 x 和 y 坐标
		//LinearGradientBrush brush(startPoint, endPoint, Color(a, 255, 0, 0), Color(a, 0, 0, 255));


DrawSelect(pDC, m_rect.TopLeft());
DrawSelect(pDC, m_rect.BottomRight());
DrawSelect(pDC, { m_rect.left,m_rect.bottom });
DrawSelect(pDC, { m_rect.right,m_rect.top });*/

BOOL CEllipse::Check(CPoint point) const
{
	CRgn r;
	r.CreateEllipticRgnIndirect(m_rect);
	return r.PtInRegion(point);
}
void CEllipse::Offset(int x, int y)
{
	m_rect.OffsetRect(x, y);
}
void CEllipse::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
		ar << m_rect;
	else
		ar >> m_rect;
}
//Pen p2({ 0xff,0,0xff,0 }, 5.0f);
//g.DrawLine(&p2, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
//g.DrawEllipse(&pen, m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height());
//pDC->Ellipse(m_rect);
