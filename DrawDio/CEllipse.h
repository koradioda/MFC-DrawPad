#pragma once
#include "pch.h"
class CEllipse : public SLayer
{
	CRect m_rect;
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC);
	void OnDraw(CDC* pDC, CWnd* hwnd = NULL);  // 重写以绘制该视图
	BOOL Check(CPoint point) const;
	void Offset(int x, int y);
	void Serialize(CArchive& ar);
public:
	CEllipse()
	{
		m_nType = ID_DRAW_ELLIPSE;

	}
};

