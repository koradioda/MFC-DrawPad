#pragma once
#include "pch.h"
class CLine :
    public SLayer
{
    CPoint m_ps, m_pe;//start-end
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC);
	void OnDraw(CDC* pDC, CWnd* hwnd = NULL);  // ��д�Ի��Ƹ���ͼ
	BOOL Check(CPoint point) const ;
	void Offset(int x, int y);
	void Serialize(CArchive& ar);//���л����������洢�ܹ���̬����ʵ����״�ṹ��
public:
	CLine()
	{
		m_nType = ID_DRAW_LINE;
	}
};

