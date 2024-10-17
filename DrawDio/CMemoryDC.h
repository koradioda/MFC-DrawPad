#pragma once
/*内存DC类简介：author：吕鑫老师
1、BOOL LoadBitmap(UINT nBitmapID,CDC* pDC = NULL)
从资源中按照，按位图ID加载位图
2、BOOL LoadFile(LPCTSTR sFile, CDC* pDC = NULL)
从exe外部加载图片（调用LoadImage）
3、BOOL Create(int cx, int cy, CDC* pDC = NULL)
创建空白位图（默认是全黑）
4、总共有4种构造函数，包含以上3种还有空构造：
CMemoryDC(UINT nBitmapID)//从资源按照位图编号来加载
CMemoryDC(LPCTSTR sFile, CDC* pDC = NULL)//从exe外部加载
CMemoryDC(int cx, int cy, CDC* pDC=NULL)//指定高宽创建空白位图

5、void MakeRgn(CRgn& r,COLORREF col)
生成透明区域
6、int GetWidth() const
int GetHeight() const
方便地获取图片高宽：
7、
透明显示：BitTrans和StrecthTrans
*/
class CMemoryDC :public CDC
{
	CSize m_size;

public:
	void MakeRgn(CRgn& r,COLORREF col)
	{
		r.CreateRectRgn(0, 0, 0, 0);
		int i = -1,cx = m_size.cx;
		int j = -1, cy = m_size.cy;
		while (++j < cy)
		{
			i = -1;
			while (++i < cx)
			{
				if (GetPixel(i, j) != col)
				{
					CRgn r1;
					r1.CreateRectRgn(i, j, i + 1, j + 1);//1x1 像素
					r.CombineRgn(&r, &r1, RGN_OR);
				}
			}
		}
	}
	int GetWidth() const
	{
		return m_size.cx;
	}
	int GetHeight() const
	{
		return m_size.cy;
	}
	CSize GetSize() const
	{
		return m_size;
	}
	void BitTrans(
		int nXDest,		// 目标起点X
		int nYDest,		// 目标起点Y
		int nWidthDest,	// 目标宽度
		int nHeightDest,// 目标高度
		CDC* pDC,		// 目标DC
		int nXSrc,		// 来源起点X
		int nYSrc,		// 来源起点Y
		COLORREF crTrans// 透明色
	)
	{
		CMemoryDC dcImage(nWidthDest, nHeightDest, pDC);//临时DC
		CBitmap bmpMask;
		bmpMask.CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);            // 创建单色掩码位图
		CDC dcMask;//掩码DC 
		dcMask.CreateCompatibleDC(pDC);
		dcMask.SelectObject(bmpMask);
		//将载入位图的内存DC中的位图，拷贝到临时DC中
		dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, this, nXSrc, nYSrc, SRCCOPY);

		// 设置临时DC的透明色
		dcImage.SetBkColor(crTrans);
		//掩码DC的透明区域为白色其它区域为黑色
		dcMask.BitBlt(0, 0, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCCOPY);

		//临时DC透明区域为黑色，其它区域保持不变
		dcImage.SetBkColor(RGB(0, 0, 0));
		dcImage.SetTextColor(RGB(255, 255, 255));
		dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);

		// 目标DC透明部分保持屏幕不变，其它部分变成黑色
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCPAINT);
	}
	void StretchTrans(
		int nXDest,			// 目标起点X
		int nYDest,			// 目标起点Y
		int nWidthDest,     // 目标宽度
		int nHeightDest,    // 目标高度
		CDC* pDC,			// 目标DC
		int nXSrc,			// 来源起点X
		int nYSrc,			// 来源起点Y
		int nWidthSrc,		// 来源宽度
		int nHeightSrc,		// 来源高度
		COLORREF crTrans	// 透明色
	)
	{
		CMemoryDC dcImage(nWidthDest, nHeightDest, pDC);//临时DC
		CBitmap bmpMask;
		// 创建单色掩码位图
		bmpMask.CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);
		CDC dcMask;
		dcMask.CreateCompatibleDC(pDC);
		dcMask.SelectObject(bmpMask);

		// 将载入位图的内存DC中的位图，拷贝到临时DC中
		if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
			dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, this, nXSrc, nYSrc, SRCCOPY);
		else
			dcImage.StretchBlt(0, 0, nWidthDest, nHeightDest,
				this, nXSrc, nYSrc, nWidthSrc, nHeightSrc, SRCCOPY);

		// 设置临时DC的透明色
		dcImage.SetBkColor(crTrans);
		//掩码DC的透明区域为白色其它区域为黑色
		dcMask.BitBlt(0, 0, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCCOPY);

		//临时DC透明区域为黑色，其它区域保持不变
		dcImage.SetBkColor(RGB(0, 0, 0));
		dcImage.SetTextColor(RGB(255, 255, 255));
		dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);

		// 目标DC透明部分保持屏幕不变，其它部分变成黑色
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCPAINT);
	}
	BOOL Create(int cx, int cy, CDC* pDC = NULL)
	{
		if (!CreateCompatibleDC(pDC))
			return FALSE;
		CBitmap bmp;
		if (pDC)
		{
			if (!bmp.CreateCompatibleBitmap(pDC, cx, cy))
			{
				DeleteDC();
				return FALSE;
			}
		}
		else
		{
			if (!bmp.CreateCompatibleBitmap(&CClientDC(NULL), cx, cy))
			{
				DeleteDC();
				return FALSE;
			}
		}
		SelectObject(&bmp);
		m_size.SetSize(cx, cy);
		return TRUE;
	}
	//加载一张exe外部位图
	BOOL LoadFile(LPCTSTR sFile, CDC* pDC = NULL)
	{
		HBITMAP hBitmap = (HBITMAP)LoadImage(NULL,sFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (!hBitmap)
			return FALSE;
		if (!CreateCompatibleDC(pDC))
		{
			DeleteObject(hBitmap);
			return FALSE;
		}
			
		SelectObject(hBitmap);
		BITMAP bm;
		GetObject(hBitmap, sizeof(bm), &bm);
		m_size.SetSize(bm.bmWidth, bm.bmHeight);
		DeleteObject(hBitmap);
		return TRUE;
	}
	//加载一张资源位图
	BOOL LoadBitmap(UINT nBitmapID,CDC* pDC = NULL)
	{
		if (!CreateCompatibleDC(NULL))
			return FALSE;
		CBitmap bmp;
		if (!bmp.LoadBitmap(nBitmapID))
		{
			DeleteDC();
			return FALSE;
		}
			
		SelectObject(&bmp);
		BITMAP bm;
		bmp.GetBitmap(&bm);
		m_size.SetSize(bm.bmWidth, bm.bmHeight);
		return TRUE;
	}
	CMemoryDC(int cx, int cy, CDC* pDC=NULL)
	{
		Create(cx, cy, pDC);
	}
	CMemoryDC(LPCTSTR sFile, CDC* pDC = NULL)
	{
		LoadFile(sFile, pDC);
	}
	CMemoryDC(UINT nBitmapID)
	{
		LoadBitmap(nBitmapID);
	}
	CMemoryDC() :m_size{}
	{
		
	}
};