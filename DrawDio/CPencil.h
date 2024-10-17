#pragma once
#include "pch.h"
class CPencil : public SLayer
{
	CArray<CPoint> m_ps{};
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC);
	void OnDraw(CDC* pDC, CWnd* hwnd = NULL);  // 重写以绘制该视图
	BOOL Check(CPoint point) const;
	void Offset(int x, int y);
	void Serialize(CArchive& ar);
public:
	CPencil()
	{
		m_nType = ID_DRAW_PENCIL;

	}
	~CPencil()
	{
		// m_ps.RemoveAll();

	}
};

