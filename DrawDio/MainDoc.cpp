
// MainDoc.cpp: CMainDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DrawLx.h"
#endif

#include "MainDoc.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "CLine.h"
#include "CPencil.h"
#include "CRecta.h"
#include "CEllipse.h"
#include "CRRect.h"

// CMainDoc

IMPLEMENT_DYNCREATE(CMainDoc, CDocument)

BEGIN_MESSAGE_MAP(CMainDoc, CDocument)
END_MESSAGE_MAP()


// CMainDoc 构造/析构

CMainDoc::CMainDoc() noexcept
{
	

}

CMainDoc::~CMainDoc()
{
}

BOOL CMainDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}

SLayer* CMainDoc::CreateLayer(int nIndex)
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

	}

	return pLayer;
}


// CMainDoc 序列化

void CMainDoc::Serialize(CArchive& ar)
{
	int nCount = 0;
	if (ar.IsStoring())
	{
		nCount = (int)m_ls.GetCount();
		ar << nCount;//Version
		int i = -1;
		while (++i < nCount)
		{
			auto pLayer = m_ls[i];
			ar << pLayer->m_nType << pLayer->m_nWidth << pLayer->m_clPen << pLayer->m_clBrush;
			pLayer->Serialize(ar);
		}
	}
	else
	{
		ar >> nCount;
		while (nCount--)
		{
			int nType = 0;
			ar >> nType;  // 
			auto pLayer = CreateLayer(nType);
			pLayer->m_nType = nType;
			ar >>  pLayer->m_nWidth >> pLayer->m_clPen >> pLayer->m_clBrush;
			pLayer->Serialize(ar);
			m_ls.Add(pLayer);
			
		}
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMainDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMainDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMainDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMainDoc 诊断

#ifdef _DEBUG
void CMainDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMainDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMainDoc 命令


void CMainDoc::DeleteContents()
{
	// TODO: 在此添加专用代码和/或调用基类
	int i = -1;
	while (++i < m_ls.GetCount())
	{
		auto p = m_ls[i];
		delete p;
	}
	m_ls.RemoveAll();

	CDocument::DeleteContents();
}
