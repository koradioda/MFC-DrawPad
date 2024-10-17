#include "pch.h"
#include "CPencil.h"

void CPencil::OnLButtonDown(UINT nFlags, CPoint point)
{
        m_ps.Add(point);
}

void CPencil::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (m_stat == ST_DRAW)
        m_ps.Add(point);
}

void CPencil::OnMouseMove(UINT nFlags, CPoint point, CDC* pDC)
{
    // if(m_stat==ST_DRAW)
    m_ps.Add(point);
}

void CPencil::OnDraw(CDC* pDC, CWnd* hwnd)
{
    int i = 0;
    pDC->MoveTo(m_ps[0]);
    while (++i<m_ps.GetCount())
    {
        pDC->LineTo(m_ps[i]);
    }
    
    if (ST_SELECT == m_stat)
    {
        // CRect rect{m_rect};
        DrawSelect(pDC, m_ps[1]);
        DrawSelect(pDC, m_ps[m_ps.GetCount()-1]);

        CArray<CPoint> ps;
        ps.Copy(m_ps);
        i = 0; 
        CPoint offp = m_pt2 - m_ptDrag;
        ps[i].Offset(offp);
        pDC->MoveTo(ps[i]);
        while (++i < ps.GetCount())
        {
            ps[i].Offset(offp);
            pDC->LineTo(ps[i]);
        }

    }
}

BOOL CPencil::Check(CPoint point) const
{
    int i = -1;
    
    while (++i < m_ps.GetCount())
    {
        CRect rect{ m_ps[i].x - 10, m_ps[i].y - 10,
                    m_ps[i].x + 10, m_ps[i].y + 10 };
        if (rect.PtInRect(point))
            return true;
    }
    //CRect r{ m_ps[0],m_ps[m_ps.GetCount()-1]};
    //r.NormalizeRect();
    //r.InflateRect(10, 10);
    return false;
}


void CPencil::Offset(int x, int y)
{
    int i = -1;
    CPoint offp = m_pt2 - m_ptDrag;
    while (++i < m_ps.GetCount())
    {
        m_ps[i].Offset(x, y);
    }
}

void CPencil::Serialize(CArchive& ar)
{
    int nCount = 0;
    if (ar.IsStoring())
    {
        nCount= m_ps.GetCount();
        ar << nCount;
        auto* pts = m_ps.GetData();
        while (nCount--)
            ar << *pts++;
    }
    else
    {
        ar >> nCount;
        CPoint point;
        m_ps.RemoveAll();
        while (nCount--)
        {
            ar >> point;
            m_ps.Add(point);
        }
    }
}
