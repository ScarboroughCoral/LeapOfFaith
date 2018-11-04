#pragma once
#include <afxwin.h>
/*
À´×ÔCSDN²©¿Í£ºhttps://blog.csdn.net/tashengjinsheng/article/details/62889923#commentBox
*/
CBitmap * BmpRotate(CBitmap* cBmp, float Angle)
{
	BITMAP bmp;
	cBmp->GetBitmap(&bmp);
	BYTE *pBits = new BYTE[bmp.bmWidthBytes*bmp.bmHeight], *TempBits = new BYTE[bmp.bmWidthBytes*bmp.bmHeight];
	cBmp->GetBitmapBits(bmp.bmWidthBytes*bmp.bmHeight, pBits);
	Angle = Angle * 3.1415926 / 180;
	int interval = bmp.bmWidthBytes / bmp.bmWidth;
	double rx0 = bmp.bmWidth*0.5;
	double ry0 = bmp.bmHeight*0.5;

	for (int j = 0; j < bmp.bmHeight; j++)
	{
		for (int i = 0; i < bmp.bmWidth; i++)
		{
			for (int k = 0; k < interval; k++)
			{
				TempBits[i*bmp.bmWidthBytes + j * interval + k] = 0xff;
			}
		}
	}
	for (int j = 0; j < bmp.bmHeight; j++)
	{
		for (int i = 0; i < bmp.bmWidth; i++)
		{

			int tempI, tempJ;
			tempI = (i - rx0)*cos(Angle) + (j - ry0)*sin(Angle) + rx0;
			tempJ = -(i - rx0)*sin(Angle) + (j - ry0)*cos(Angle) + ry0;
			if (tempI > 0 && tempI < bmp.bmWidth)
				if (tempJ > 0 && tempJ < bmp.bmHeight)
				{
					for (int m = 0; m < interval; m++)
						TempBits[i*bmp.bmWidthBytes + j * interval + m] = pBits[tempI*bmp.bmWidthBytes + interval * tempJ + m];
				}
		}
	}
	CBitmap *m_bitmap;
	m_bitmap = new CBitmap;
	m_bitmap->CreateBitmapIndirect(&bmp);
	m_bitmap->SetBitmapBits(bmp.bmWidthBytes*bmp.bmHeight, TempBits);
	delete pBits;
	delete TempBits;
	return m_bitmap;
}