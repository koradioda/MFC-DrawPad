#pragma once
/*�ڴ�DC���飺author��������ʦ
1��BOOL LoadBitmap(UINT nBitmapID,CDC* pDC = NULL)
����Դ�а��գ���λͼID����λͼ
2��BOOL LoadFile(LPCTSTR sFile, CDC* pDC = NULL)
��exe�ⲿ����ͼƬ������LoadImage��
3��BOOL Create(int cx, int cy, CDC* pDC = NULL)
�����հ�λͼ��Ĭ����ȫ�ڣ�
4���ܹ���4�ֹ��캯������������3�ֻ��пչ��죺
CMemoryDC(UINT nBitmapID)//����Դ����λͼ���������
CMemoryDC(LPCTSTR sFile, CDC* pDC = NULL)//��exe�ⲿ����
CMemoryDC(int cx, int cy, CDC* pDC=NULL)//ָ���߿����հ�λͼ

5��void MakeRgn(CRgn& r,COLORREF col)
����͸������
6��int GetWidth() const
int GetHeight() const
����ػ�ȡͼƬ�߿�
7��
͸����ʾ��BitTrans��StrecthTrans
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
					r1.CreateRectRgn(i, j, i + 1, j + 1);//1x1 ����
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
		int nXDest,		// Ŀ�����X
		int nYDest,		// Ŀ�����Y
		int nWidthDest,	// Ŀ����
		int nHeightDest,// Ŀ��߶�
		CDC* pDC,		// Ŀ��DC
		int nXSrc,		// ��Դ���X
		int nYSrc,		// ��Դ���Y
		COLORREF crTrans// ͸��ɫ
	)
	{
		CMemoryDC dcImage(nWidthDest, nHeightDest, pDC);//��ʱDC
		CBitmap bmpMask;
		bmpMask.CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);            // ������ɫ����λͼ
		CDC dcMask;//����DC 
		dcMask.CreateCompatibleDC(pDC);
		dcMask.SelectObject(bmpMask);
		//������λͼ���ڴ�DC�е�λͼ����������ʱDC��
		dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, this, nXSrc, nYSrc, SRCCOPY);

		// ������ʱDC��͸��ɫ
		dcImage.SetBkColor(crTrans);
		//����DC��͸������Ϊ��ɫ��������Ϊ��ɫ
		dcMask.BitBlt(0, 0, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCCOPY);

		//��ʱDC͸������Ϊ��ɫ���������򱣳ֲ���
		dcImage.SetBkColor(RGB(0, 0, 0));
		dcImage.SetTextColor(RGB(255, 255, 255));
		dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);

		// Ŀ��DC͸�����ֱ�����Ļ���䣬�������ֱ�ɺ�ɫ
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCPAINT);
	}
	void StretchTrans(
		int nXDest,			// Ŀ�����X
		int nYDest,			// Ŀ�����Y
		int nWidthDest,     // Ŀ����
		int nHeightDest,    // Ŀ��߶�
		CDC* pDC,			// Ŀ��DC
		int nXSrc,			// ��Դ���X
		int nYSrc,			// ��Դ���Y
		int nWidthSrc,		// ��Դ���
		int nHeightSrc,		// ��Դ�߶�
		COLORREF crTrans	// ͸��ɫ
	)
	{
		CMemoryDC dcImage(nWidthDest, nHeightDest, pDC);//��ʱDC
		CBitmap bmpMask;
		// ������ɫ����λͼ
		bmpMask.CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);
		CDC dcMask;
		dcMask.CreateCompatibleDC(pDC);
		dcMask.SelectObject(bmpMask);

		// ������λͼ���ڴ�DC�е�λͼ����������ʱDC��
		if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
			dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, this, nXSrc, nYSrc, SRCCOPY);
		else
			dcImage.StretchBlt(0, 0, nWidthDest, nHeightDest,
				this, nXSrc, nYSrc, nWidthSrc, nHeightSrc, SRCCOPY);

		// ������ʱDC��͸��ɫ
		dcImage.SetBkColor(crTrans);
		//����DC��͸������Ϊ��ɫ��������Ϊ��ɫ
		dcMask.BitBlt(0, 0, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCCOPY);

		//��ʱDC͸������Ϊ��ɫ���������򱣳ֲ���
		dcImage.SetBkColor(RGB(0, 0, 0));
		dcImage.SetTextColor(RGB(255, 255, 255));
		dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);

		// Ŀ��DC͸�����ֱ�����Ļ���䣬�������ֱ�ɺ�ɫ
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
	//����һ��exe�ⲿλͼ
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
	//����һ����Դλͼ
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