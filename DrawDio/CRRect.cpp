#include "pch.h"
#include "CRRect.h"
using namespace Gdiplus;
void CRRect::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_rect.TopLeft() = point;
}

void CRRect::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_rect.BottomRight() = point;
	m_rect.NormalizeRect();
}

void CRRect::OnMouseMove(UINT nFlags, CPoint point, CDC* pDC)
{
	if (ST_DRAW == m_stat)
		m_rect.BottomRight() = point;
}
//void CRRect::DrawRoundRect(Graphics* graphics, Pen* pen, Rect rectangle, int cx,int cy)
//{
//	// 创建具有指定半径和矩形边框的圆角矩形路径
//	if (cy < 0)
//		cy *= -1;
//	cx = cy;
//	GraphicsPath path;
//	path.AddArc(rectangle.X, rectangle.Y, cx * 2, cy * 2, 180, 90); // 左上角
//	path.AddLine(rectangle.GetLeft() + cx, rectangle.GetTop(), rectangle.GetRight() - cx * 2, rectangle.GetTop());
//	path.AddArc(rectangle.GetRight() - cx * 2, rectangle.GetTop(), cy * 2,  cy* 2, 270, 90); // 右上角
//	path.AddLine(rectangle.GetRight(), rectangle.GetTop() + cy * 2, rectangle.GetRight(), rectangle.GetBottom() - cy * 2);
//	path.AddArc(rectangle.GetRight() - cx * 2, rectangle.GetBottom() - cy * 2, cx * 2, cy * 2, 0, 90); // 右下角
//	path.AddLine(rectangle.GetRight() - cx * 2, rectangle.GetBottom(), rectangle.GetLeft() + cy * 2, rectangle.GetBottom());
//	path.AddArc(rectangle.GetLeft(), rectangle.GetBottom() - cy * 2, cx * 2, cy* 2, 90, 90); // 左下角
//	path.AddLine(rectangle.GetLeft(), rectangle.GetBottom() - cy * 2, rectangle.GetLeft(), rectangle.GetTop() + cy * 2);
//
//	// 使用 Graphics 对象绘制路径
//	graphics->DrawPath(pen, &path);
//}
void CRRect::OnDraw(CDC* pDC, CWnd* hwnd)
{
	int nWidth = m_rect.Width();
	int nHeight = m_rect.Height();
	CBrush br{ m_clBrush };
	pDC->SelectObject(&br);

	pDC->RoundRect(m_rect,{nWidth/5,nHeight/5});
	if (ST_SELECT == m_stat)
	{
		CPoint pt = m_rect.CenterPoint();
		DrawSelect(pDC, { pt.x,m_rect.top });
		DrawSelect(pDC, { pt.x,m_rect.bottom });
		DrawSelect(pDC, { m_rect.left,pt.y });
		DrawSelect(pDC, { m_rect.right,pt.y });

		CRect rect{ m_rect };
		rect.OffsetRect(m_pt2 - m_ptDrag);
		pDC->SelectObject(&br);
		pDC->RoundRect(rect, { nWidth / 4,nHeight / 4 });
	}

}
BOOL CRRect::Check(CPoint point) const
{
	CRgn rgn;
	auto& r = m_rect;
	rgn.CreateRoundRectRgn(r.left, r.top, r.right, r.bottom, r.Width() / 5, r.Height() / 5);
	return rgn.PtInRegion(point);
}
void CRRect::Offset(int x, int y)
{
	m_rect.OffsetRect(x, y);
}
	//g.FillEllipse(&brush, m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height());
	//g.DrawEllipse(&pen, m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height());

void CRRect::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
		ar << m_rect;
	else
		ar >> m_rect;
}
