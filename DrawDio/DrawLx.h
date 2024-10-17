
// DrawLx.h: DrawLx 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号


// CApp:
// 有关此类的实现，请参阅 DrawLx.cpp
//
#include "CColorBox.h"
#include "CComboLx.h"
class CApp : public CWinApp
{
public:
	CApp() noexcept;
	CColorBox m_colorBox;
	CComboLx m_comboLine;
	CDialogBar m_dlgBar;
	HCURSOR m_hDraw, m_hDrag;
// 重写
public:
	void InitDlgBar(CFrameWnd* pMainFrame);
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CApp theApp;
