// CComboLx.cpp: 实现文件
//

#include "pch.h"
#include "DrawLx.h"
#include "CComboLx.h"

/*
//行关联数据
    ASSERT(lpDrawItemStruct->CtlType == ODT_COMBOBOX);
    LPCTSTR lpszText = (LPCTSTR)lpDrawItemStruct->itemData;
   // LPCTSTR lpszText = (LPCTSTR)lpDrawItemStruct->itemData;
   // ASSERT(lpszText != NULL);
    CDC dc;

    dc.Attach(lpDrawItemStruct->hDC);

    // Save these value to restore them when done drawing.
    COLORREF crOldTextColor = dc.GetTextColor();
    COLORREF crOldBkColor = dc.GetBkColor();

    // If this item is selected, set the background color
    // and the text color to appropriate values. Erase
    // the rect by filling it with the background color.

    if ((lpDrawItemStruct->itemState & ODS_SELECTED))
    {
        dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
        dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
        dc.FillSolidRect(&lpDrawItemStruct->rcItem, ::GetSysColor(COLOR_HIGHLIGHT));
    }
    else
    {
        dc.FillSolidRect(&lpDrawItemStruct->rcItem, crOldBkColor);
    }
    dc.SelectStockObject(DEFAULT_GUI_FONT);
    // Draw the text.

    dc.DrawText(
        lpszText,
        (int)_tcslen(lpszText),
        &lpDrawItemStruct->rcItem,
        DT_CENTER | DT_SINGLELINE | DT_VCENTER);

    // Reset the background color and the text color back to their
    // original values.
    dc.SetTextColor(crOldTextColor);
    dc.SetBkColor(crOldBkColor);

    dc.Detach();
*/
// CComboLx
//
//void CComboLx::DrawItem(LPDRAWITEMSTRUCT lpDIS)
//{
//    int nIndex = lpDIS->itemID;
//    CDC* pDC = CDC::FromHandle(lpDIS->hDC);
//    CRect rect{lpDIS ->rcItem};
//    if (nIndex < 0)
//        return;
//   
//    CPen pen;
//    if (lpDIS->itemState & ODS_SELECTED)
//        pen.CreatePen(PS_SOLID, nIndex + 1, GetSysColor(COLOR_HIGHLIGHTTEXT));
//    else
//        pen.CreatePen(PS_SOLID, nIndex + 1, GetSysColor(COLOR_WINDOWTEXT));
//    static  COLORREF col1 = GetSysColor(COLOR_WINDOW);
//    static COLORREF col2 = GetSysColor(COLOR_HIGHLIGHT);
//   
//    int y = (rect.bottom + rect.top) / 2;
//    int x = rect.Height() / 4;
//  
//    pDC->FillSolidRect(rect, lpDIS->itemState & ODS_SELECTED?col2:col1);
// 
//    pDC->SelectObject(&pen);
//    
//    pDC->MoveTo(x, y);
//    pDC->LineTo(rect.Width() - x, y);
//}
IMPLEMENT_DYNAMIC(CComboLx, CComboBox)

void CComboLx::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
    int nIndex = lpDIS->itemID;
    CDC* pDC = CDC::FromHandle(lpDIS->hDC);
    CRect rect{lpDIS ->rcItem};
    if (nIndex < 0)
        return;
   
    CPen pen(PS_SOLID, nIndex + 1, GetSysColor(COLOR_WINDOWTEXT));
    static  COLORREF col1 = GetSysColor(COLOR_WINDOW);
    static COLORREF col2 = RGB(206,229,252);
   
    int y = (rect.bottom + rect.top) / 2;
    int x = rect.Height() / 4;
  
    pDC->FillSolidRect(rect, lpDIS->itemState & ODS_SELECTED?col2:col1);
 
    pDC->SelectObject(&pen);
    
    pDC->MoveTo(x, y);
    pDC->LineTo(rect.Width() - x, y);
}

void CComboLx::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
    lpMIS->itemHeight = 28;
    lpMIS->itemWidth = 300;
}

int CComboLx::CompareItem(LPCOMPAREITEMSTRUCT lpCIS)
{
    return 0;
}

CComboLx::CComboLx()
{

}

CComboLx::~CComboLx()
{
}


BEGIN_MESSAGE_MAP(CComboLx, CComboBox)
	ON_WM_CREATE()
    ON_CONTROL_REFLECT(CBN_SELCHANGE, &CComboLx::OnCbnSelchange)
END_MESSAGE_MAP()



// CComboLx 消息处理程序




int CComboLx::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	
		SetCurSel(2);

	return 0;
}


void CComboLx::OnCbnSelchange()
{
    GetParent()->PostMessage(WM_COMMAND, ID_DRAW_WIDTH,0);
}
