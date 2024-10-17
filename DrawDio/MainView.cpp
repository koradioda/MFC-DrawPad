
// MainView.cpp: CMainView 类的实现
//

#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "DrawLx.h"
#endif
#include "MainDoc.h"
#include "MainView.h"// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#include "CLine.h"
#include "CPencil.h"
#include "CRecta.h"
#include "CEllipse.h"
#include "CRRect.h"
#include "CPolygonDio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainView

IMPLEMENT_DYNCREATE(CMainView, CScrollView)

BEGIN_MESSAGE_MAP(CMainView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND_RANGE(ID_DRAW_DRAG, ID_DRAW_PENCIL,&CMainView::OnDrawTools)
	ON_COMMAND(ID_DRAW_WIDTH, &CMainView::OnDrawWidth)
	ON_COMMAND(ID_DRAW_PEN, &CMainView::OnDrawPen)
	ON_COMMAND(ID_DRAW_BRUSH, &CMainView::OnDrawBrush)
	ON_UPDATE_COMMAND_UI_RANGE(ID_DRAW_DRAG, ID_DRAW_PENCIL, &CMainView::OnUpdateDrawTools)

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

// CMainView 构造/析构

BOOL CMainView::CheckLayer(CPoint point)
{
	auto& ls = GetDocument()->m_ls;

	auto nCount = ls.GetCount();
	int i = -1;
	while (++i < nCount)
	{
		if (ls[i]->Check(point))
			return TRUE;
	}
	return FALSE;
}

void CMainView::SelectLayer(CPoint point)
{
	auto& ls = GetDocument()->m_ls;
	auto nCount = ls.GetCount();
	int i = -1;
	while (++i < nCount)
	{
		auto pLayer = ls[i];
		pLayer->m_stat = pLayer->Check(point) ? SLayer::ST_SELECT : SLayer::ST_NORMAL;
	}
	SLayer::m_pt2= SLayer::m_ptDrag = point;
	Invalidate(FALSE);

}

BOOL CMainView::OffsetLayer(CPoint point)
{//返回值代表有没有图层参与拖动
	auto pt = point - SLayer::m_ptDrag;
	auto& ls = GetDocument()->m_ls;
	auto nCount = ls.GetCount();
	int i = -1;
	BOOL bResult = FALSE;
	while (++i < nCount)
	{
		auto pLayer = ls[i];
		if (SLayer::ST_SELECT == pLayer->m_stat)
		{
			pLayer->Offset(pt.cx, pt.cy);
			bResult = TRUE;
		}
			
	}	
	SLayer::m_ptDrag.SetPoint(MAXWORD, MAXWORD);
	return bResult;
}

void CMainView::OnDrawPen()
{
	auto& ls = GetDocument()->m_ls;

	auto nCount = ls.GetCount();
	int i = -1;
	auto color = theApp.m_colorBox.GetPenColor();
	while (++i < nCount)
	{
		auto pLayer = ls[i];
		if (SLayer::ST_SELECT == pLayer->m_stat)
			pLayer->m_clPen = color;
	}
	Invalidate(FALSE);
}

void CMainView::OnDrawBrush()
{
	auto& ls = GetDocument()->m_ls;

	auto nCount = ls.GetCount();
	int i = -1;
	auto color = theApp.m_colorBox.GetBrushColor();
	while (++i < nCount)
	{
		auto pLayer = ls[i];
		if (SLayer::ST_SELECT == pLayer->m_stat)
			pLayer->m_clBrush = color;
	}
	Invalidate(FALSE);
}

void CMainView::OnDrawWidth()
{
	auto& ls = GetDocument()->m_ls;

	auto nCount = ls.GetCount();
	int i = -1;
	int nWidth = theApp.m_comboLine.GetCurSel() + 1;
	while (++i < nCount)
	{
		auto pLayer = ls[i];
		if (SLayer::ST_SELECT == pLayer->m_stat)
			pLayer->m_nWidth = nWidth;
	}
	Invalidate(FALSE);
}


SLayer* CMainView::CreateLayer(int nIndex)
{
	SLayer* pLayer = nullptr;
	switch (nIndex)
	{
	case ID_DRAW_LINE:
		pLayer = new CLine;
		break;
	case ID_DRAW_ELLIPSE:
		pLayer = new CEllipse;
		break;
	case ID_DRAW_RRECT:
		pLayer = new CRRect;
		break;
	case ID_DRAW_RECT:
		pLayer = new CRecta;
		break;
	case ID_DRAW_PENCIL:
		pLayer = new CPencil;
		break;
	case ID_DRAW_POLYGON:
		pLayer = new CPolygonDio;
		break;

	}
	
	return pLayer;
}

CMainView::CMainView() 
{
	
	
}

CMainView::~CMainView()
{
}

BOOL CMainView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CMainView 绘图

void CMainView::OnDraw(CDC* pDC)
{
	auto& ls = GetDocument()->m_ls;

	auto nCount = ls.GetCount();
	CRect rect;
	GetClientRect(rect);
	m_dc.FillSolidRect(rect, 0xffffff);
	int i = -1;
	while (++i<nCount)
	{
		auto pLayer = ls[i];
		CPen pen(PS_SOLID, pLayer->m_nWidth, pLayer->m_clPen);
		m_dc.SelectObject(&pen);
		ls[i]->OnDraw(&m_dc,this);
	}
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dc, 0, 0, SRCCOPY);
}

void CMainView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CMainView 打印

BOOL CMainView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMainView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMainView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMainView 诊断

#ifdef _DEBUG
void CMainView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMainView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMainDoc* CMainView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainDoc)));
	return (CMainDoc*)m_pDocument;
}
#endif //_DEBUG


// CMainView 消息处理程序


void CMainView::OnDrawTools(UINT nID)
{
	m_nIndex = nID;
}

void CMainView::OnUpdateDrawTools(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI ->m_nID == m_nIndex);
}

void CMainView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_nIndex == ID_DRAW_DRAG)
	{
		SLayer::m_ptDrag = point;
		SelectLayer(point);
		return;
	}
	auto pLayer = CreateLayer(m_nIndex);//工厂模式
	if (pLayer)
	{
		pLayer->m_stat = SLayer::ST_DRAW;
		pLayer->m_nWidth = theApp.m_comboLine.GetCurSel() + 1;
		pLayer->m_clBrush = m_colorBox.GetBrushColor();
		pLayer->m_clPen = m_colorBox.GetPenColor();
		pLayer->OnLButtonDown(nFlags, point);  // 按下点的位置
		auto pDoc = GetDocument();
		pDoc ->m_ls.Add(pLayer);
		pDoc->SetModifiedFlag();
	}

	CScrollView::OnLButtonDown(nFlags, point);
}


void CMainView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CScrollView::OnLButtonUp(nFlags, point);
	if (ID_DRAW_DRAG == m_nIndex)
	{
		if (OffsetLayer(point))
		{
			Invalidate(FALSE);
			GetDocument()->SetModifiedFlag();//脏了dirty
		}
		return;
	}
	auto& ls = GetDocument()->m_ls;

	auto nCount = ls.GetCount();
	if (nCount < 1)
		return;
	auto pLayer = ls[nCount - 1];
	if (SLayer::ST_DRAW == pLayer->m_stat)
	{
		m_nIndex = ID_DRAW_DRAG;
		pLayer->OnLButtonUp(nFlags, point);  // 绘制最终点
		pLayer->m_stat = SLayer::ST_SELECT;
		Invalidate(FALSE);
	}
	 
}


void CMainView::OnMouseMove(UINT nFlags, CPoint point)
{
	CScrollView::OnMouseMove(nFlags, point);
	if (ID_DRAW_DRAG == m_nIndex && SLayer::m_ptDrag.x != MAXWORD)  // 拖动
	{	
		SLayer::m_pt2 = point;
		// OffsetLayer(point);
		Invalidate(FALSE);
		return;
	}
	auto& ls = GetDocument()->m_ls;

	auto nCount = ls.GetCount();
	if (nCount < 1)
		return;
	auto pLayer = ls[nCount - 1];
	if (SLayer::ST_DRAW == pLayer->m_stat)
	{
		pLayer->OnMouseMove(nFlags, point);
		Invalidate(FALSE);
	}
}


BOOL CMainView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


void CMainView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	m_dc.DeleteDC();
	m_dc.Create(cx, cy);
}


BOOL CMainView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	auto& ls = GetDocument()->m_ls;

	auto nCount = ls.GetCount();
	if (m_nIndex == ID_DRAW_DRAG)
	{
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);
		if (SLayer::m_ptDrag.x != MAXWORD ||CheckLayer(point) )
		{
			SetCursor(theApp.m_hDrag);
			return TRUE;
		}
	}
	else
	{
		SetCursor(theApp.m_hDraw);
		return TRUE;
	}
		
	

	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}
