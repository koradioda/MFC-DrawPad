
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "DrawLx.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	//ON_MESSAGE(UM_TEST, &CMainFrame::OnUmTest)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构


CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
	GdiplusStartup(&m_gdiToken, &m_gdiStartupInput, NULL);
}

CMainFrame::~CMainFrame()
{
	GdiplusShutdown(m_gdiToken);
}

void CMainFrame::InitTools()
{
	int i = -1,nCount = m_wndToolBar.GetCount();
	LPCTSTR ts[] =
	{
		_T("新建"),_T("打开"),_T("保存"),_T(""),_T("剪切"),_T("拷贝"),_T("粘贴"),_T(""),_T("打印"),_T("帮助")
	};
	while(++i<nCount)
		m_wndToolBar.SetButtonText(i,ts[i]);
	CRect rect;
	m_wndToolBar.GetItemRect(0,rect);
	
	m_wndToolBar.SetSizes(rect.Size(), { 16,15 });
	GetWindowRect(rect);
	//auto b = m_toolBox.IsFloating();

	m_toolBox.SetButtonStyle(1, TBBS_BUTTON | TBBS_WRAPPED);
	m_toolBox.SetButtonStyle(3, TBBS_BUTTON | TBBS_WRAPPED);
	m_toolBox.SetButtonStyle(5, TBBS_BUTTON | TBBS_WRAPPED);
	m_toolBox.SetButtonStyle(7, TBBS_BUTTON | TBBS_WRAPPED);
	FloatControlBar(&m_toolBox, { rect.right - 60,rect.top + 100 });
	theApp.InitDlgBar(this);
	//b = m_toolBox.IsFloating();
}
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_toolBox.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED) ||
		!m_toolBox.LoadToolBar(IDR_TOOLBOX))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	//int nCount = m_wndStatusBar.GetCount();
	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_toolBox.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	

	m_toolBox.SetWindowTextW(_T("工具箱"));
	m_wndToolBar.SetWindowText(_T("标准"));
	InitTools();
	return 0;
}
//
//LRESULT CMainFrame::OnUmTest(WPARAM w, LPARAM l)
//{
//	return LRESULT();
//}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

