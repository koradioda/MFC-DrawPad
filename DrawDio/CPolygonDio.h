#pragma once
#include "pch.h"
class CPolygonDio : public SLayer
{
    CArray<CPoint> m_ps{};
    void OnLButtonDown(UINT nFlags, CPoint point);
    void OnLButtonUp(UINT nFlags, CPoint point);
    void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC = NULL);
    void OnDraw(CDC* pDC, CWnd* hwnd = NULL);  // ��д�Ի��Ƹ���ͼ
    BOOL Check(CPoint point) const;//�����ͼ���Ϸ����������ѡ�к��϶���
    void Offset(int x, int y);//����ͼ��ƽ��
    void Serialize(CArchive& ar);//ͨ�����л�ʵ����״�洢�ṹ


};

