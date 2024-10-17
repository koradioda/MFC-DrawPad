#pragma once
#include "pch.h"
class CLine :
    public SLayer
{
    CPoint m_ps, m_pe;//start-end
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC);
	void OnDraw(CDC* pDC, CWnd* hwnd = NULL);  // 重写以绘制该视图
	BOOL Check(CPoint point) const ;
	void Offset(int x, int y);
	void Serialize(CArchive& ar);//序列化的魅力：存储架构多态并且实现树状结构！
public:
	CLine()
	{
		m_nType = ID_DRAW_LINE;
	}
};

