#include "pch.h"
#include "CRecta.h"

void CRecta::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_rect.TopLeft() = point;
}

void CRecta::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_rect.BottomRight() = point;
	m_rect.NormalizeRect();
}

void CRecta::OnMouseMove(UINT nFlags, CPoint point, CDC* pDC)
{
	if (ST_DRAW == m_stat)
		m_rect.BottomRight() = point;
}

void CRecta::OnDraw(CDC* pDC,CWnd* hwnd)
{
	CBrush br{m_clBrush};
	pDC->SelectObject(&br);
	pDC->Rectangle(m_rect);

	if (ST_SELECT == m_stat)
	{
		// CRect rect{m_rect};
		DrawSelect(pDC, m_rect.TopLeft());
		DrawSelect(pDC, m_rect.BottomRight());
		DrawSelect(pDC, { m_rect.left,m_rect.bottom });
		DrawSelect(pDC, { m_rect.right,m_rect.top});
		
		// CClientDC dc(hwnd);  //pDC->GetWindow()
		// dc.SetROP2(R2_NOT);
		CRect rect{ m_rect };
		rect.OffsetRect(m_pt2 - m_ptDrag);
		pDC->SelectObject(&br);
		pDC->Rectangle(rect);

		// dc.DeleteDC();
	}
}

BOOL CRecta::Check(CPoint point) const
{
	return m_rect.PtInRect(point);
}

void CRecta::Offset(int x, int y)
{
	m_rect.OffsetRect(x, y);
}

void CRecta::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
		ar << m_rect;
	else
		ar >> m_rect;
}
