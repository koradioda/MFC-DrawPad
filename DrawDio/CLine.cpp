#include "pch.h"
#include "CLine.h"

void CLine::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_ps = point;
}

void CLine::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (ST_DRAW == m_stat)
		m_pe = point;
		
}

void CLine::OnMouseMove(UINT nFlags, CPoint point, CDC* pDC)
{
	if (ST_DRAW == m_stat)
		m_pe = point;
	
}

void CLine::OnDraw(CDC* pDC, CWnd* hwnd)
{
	
	pDC->MoveTo(m_ps);
	pDC->LineTo(m_pe);
	if (ST_SELECT == m_stat)
	{
		DrawSelect(pDC, m_ps);
		DrawSelect(pDC, m_pe);

		CPoint ps{ m_ps }, pe{m_pe};
		ps.Offset(m_pt2-m_ptDrag);
		pe.Offset(m_pt2-m_ptDrag);

		pDC->MoveTo(ps);
		pDC->LineTo(pe);
	}
}

BOOL CLine::Check(CPoint point) const
{//计算点到直线的距离，解析几何，平面几何等来实现
	double A = distance(point, m_pe);
	double B = distance(point, m_ps);
	double C = distance(m_ps, m_pe);
	double p = (A + B + C) / 2;
	double S = sqrt(p * (p - A) * (p - B) * (p - C));
	double d = S * 2 / C;
	//TRACE("d=%g\n", d);
	CRect r{m_ps,m_pe};
	r.NormalizeRect();
	r.InflateRect(10, 10);

	return d < 10 && r.PtInRect(point);
}

void CLine::Offset(int x, int y)
{
	m_ps.Offset(x, y);
	m_pe.Offset(x, y);
}

void CLine::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
		ar << m_ps << m_pe;
	else
		ar >> m_ps >> m_pe;
}
