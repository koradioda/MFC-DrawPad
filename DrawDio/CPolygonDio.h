#pragma once
#include "pch.h"
class CPolygonDio : public SLayer
{
    CArray<CPoint> m_ps{};
    void OnLButtonDown(UINT nFlags, CPoint point);
    void OnLButtonUp(UINT nFlags, CPoint point);
    void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC = NULL);
    void OnDraw(CDC* pDC, CWnd* hwnd = NULL);  // 重写以绘制该视图
    BOOL Check(CPoint point) const;//光标在图层上方（点击即可选中和拖动）
    void Offset(int x, int y);//整个图层平移
    void Serialize(CArchive& ar);//通过序列化实现树状存储结构


};

