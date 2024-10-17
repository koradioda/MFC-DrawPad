// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"
#include <gdiplus.h>
#include <afxsock.h>
#include "resource.h"

enum { ID_DRAW_WIDTH = ID_DRAW_DRAG + 100 ,
ID_DRAW_PEN,
ID_DRAW_BRUSH

};

struct SLayer
{//图形软件开发的关键架构:virtual
	enum STAT
	{
		ST_DRAW=0,//绘制状态
		ST_NORMAL,//正常状态
		ST_SELECT,//选中状态
	};
	STAT m_stat{ ST_NORMAL };
	int m_nType{};
	COLORREF m_clPen, m_clBrush;
	static CPoint m_ptDrag, m_pt2, m_ptLast;  // 全局静态变量
	int m_nWidth{1};
	static double distance(CPoint pt1, CPoint pt2)
	{
		return sqrt((pt2.x - pt1.x) * (pt2.x - pt1.x) + (pt2.y - pt1.y) * (pt2.y - pt1.y));
	}
	static void DrawSelect(CDC* pDC, CPoint pt)
	{
		static CPen pen{ PS_SOLID,1,GetSysColor(COLOR_WINDOWFRAME) };
		pDC->SelectStockObject(WHITE_BRUSH);
		pDC->SelectObject(&pen);
		pDC->Ellipse(pt.x - 5, pt.y - 5, pt.x + 5, pt.y + 5);
	}
	virtual void OnLButtonDown(UINT nFlags, CPoint point)=0;
	virtual void OnLButtonUp(UINT nFlags, CPoint point)=0;
	virtual void OnMouseMove(UINT nFlags, CPoint point,CDC* pDC=NULL)=0;
	virtual void OnDraw(CDC* pDC , CWnd* hwnd=NULL)=0;  // 重写以绘制该视图
	virtual BOOL Check(CPoint point) const = 0;//光标在图层上方（点击即可选中和拖动）
	virtual void Offset(int x,int y) = 0;//整个图层平移
	virtual void Serialize(CArchive& ar)=0;//通过序列化实现树状存储结构
	virtual ~SLayer() {

	}

};
#endif //PCH_H
