
// MainView.h: CMainView 类的接口
//

#pragma once

#include "CMemoryDC.h"
class CMainView : public CScrollView
{
	int m_nIndex{ID_DRAW_DRAG};
	//CArray<SLayer*> &m_ls;
	CMemoryDC m_dc;
	CColorBox& m_colorBox{theApp.m_colorBox};
	BOOL CheckLayer(CPoint point);
	void SelectLayer(CPoint point);
	BOOL OffsetLayer(CPoint point);
	static SLayer* CreateLayer(int nIndex);
protected: // 仅从序列化创建
	CMainView() ;
	DECLARE_DYNCREATE(CMainView)

// 特性
public:
	CMainDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMainView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnDrawPen();
	afx_msg void OnDrawBrush();
	afx_msg void OnDrawWidth();
	afx_msg void OnDrawTools(UINT);
	afx_msg void OnUpdateDrawTools(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

};

#ifndef _DEBUG  // MainView.cpp 中的调试版本
inline CMainDoc* CMainView::GetDocument() const
   { return reinterpret_cast<CMainDoc*>(m_pDocument); }
#endif

