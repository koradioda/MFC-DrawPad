
// MainFrm.h: CMainFrame 类的接口
//

#pragma once
#include "pch.h"
using namespace Gdiplus;
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
		void InitTools();
public:
	GdiplusStartupInput m_gdiStartupInput;
	ULONG_PTR m_gdiToken;
	CMainFrame() noexcept;

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar	m_toolBox;
	CToolBar	m_wndToolBar;
	CStatusBar  m_wndStatusBar;
	
// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

};


