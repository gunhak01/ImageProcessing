#include "pch.h"
#include "CImgWnd.h"
#include "ImageProcessing.h"

//#include "stdafx.h"
//#include "publicCWnd.h"

#include <memory>
#include <gdiplus.h>
#include <atlImage.h>
#include <wingdi.h>
using namespace Gdiplus;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RectWnd

CImgWnd::CImgWnd()
	: m_bIsSetFocus(FALSE)
{
}

CImgWnd::~CImgWnd()
{
}


BEGIN_MESSAGE_MAP(CImgWnd, CWnd)
	//{{AFX_MSG_MAP(RectWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// RectWnd message handlers

void CImgWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CView::OnPaint()��(��) ȣ������ ���ʽÿ�.
	Graphics graphics(dc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);
	Color color;
	CImage bmp;
	bmp.Load(_T("image6.bmp"));
	//bmp.Load(_T("image5.png"));

	//gdi+�� ����ϴ� ��� 
	//Bitmap bmp(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_Sample));
	//CachedBitmap cachedbmp(&bmp, &graphics);
	int nWidth = bmp.GetWidth();
	int nHeight = bmp.GetHeight();

	CString strTmp = _T("");
	LARGE_INTEGER	lnFreq, lnStart, lnEnd, lnResult;
	::QueryPerformanceFrequency(&lnFreq);


	//::QueryPerformanceCounter(&lnStart);
	//graphics.DrawCachedBitmap(&cachedbmp, bmp.GetWidth() + 20, 10);
	//::QueryPerformanceCounter(&lnEnd);
	//lnResult.QuadPart = (lnEnd.QuadPart - lnStart.QuadPart) * 1000000 / lnFreq.QuadPart;
	//strTmp.Format(_T("DrawCachedBitmap() counter %u"), lnResult.QuadPart);
	//dc.TextOut(bmp.GetWidth() + 20, 10, strTmp);
	Status status = Status::GenericError;

	//::QueryPerformanceCounter(&lnStart);
	//{
	//	//��Ʈ�� ���ҽ��� �ε��Ѵ�.
	//	HBITMAP hBitmap = bmp.Detach();
	//	//status = bmp.GetHBITMAP(color, &hBitmap);
	//	//if (status == Status::Ok) {
	//	if (hBitmap) {
	//		CDC memDC;

	//		//ȭ�� DCȭ ȣȯ�Ǵ� �޸� DC�� �����Ѵ�.
	//		memDC.CreateCompatibleDC(&dc);
	//		//�޸� DC�� �����Ѵ�.
	//		HBITMAP hOldBmp = (HBITMAP) ::SelectObject(memDC.m_hDC, hBitmap);
	//		//�޸� DC�� ����ִ� ��Ʈ���� ȭ�� DC�� �����Ͽ� ����Ѵ�.
	//		BitBlt(dc.m_hDC, nWidth * 2 + 20, 10, nWidth, nHeight, memDC.m_hDC, 0, 0, SRCCOPY);

	//		::SelectObject(memDC.m_hDC, hOldBmp);

	//		::DeleteObject(hBitmap);
	//	}
	//}
	//::QueryPerformanceCounter(&lnEnd);
	//lnResult.QuadPart = (lnEnd.QuadPart - lnStart.QuadPart) * 1000000 / lnFreq.QuadPart;
	//strTmp.Format(_T("BitBlt() counter %u:%d"), lnResult.QuadPart, status);
	//dc.TextOut(nWidth*2 + 20, 10, strTmp);

	int pitch = bmp.GetPitch();
	BYTE* lpvBits = (BYTE*)bmp.GetBits();
	if (pitch < 0) {
		//�̹����� ���� �ּ� ���� 
		lpvBits = lpvBits + ((nHeight - 1) * pitch);
	}

	//�̹����� ������ ���� ���� 
	const int size = abs(nHeight * pitch);

	for (int i = 0; i < size; i++) {
		lpvBits[i] = lpvBits[i];
	}

	//gray�� ���� 
	//for (int i = 0; i < size; i++) {
	//	lpvBits[i] = 0x80;
	//}

	//gray scale
	//for (int i = 0; i < size; i = i+3) {
	//	unsigned char gray = (lpvBits[i] + lpvBits[i+1] + lpvBits[i+2]) / 3;
	//	lpvBits[i] = gray;
	//	lpvBits[i+1] = gray;
	//	lpvBits[i+2] = gray;
	//}

	//50% 
	//for (int i = 0; i < size; i++) {
	//	lpvBits[i] = lpvBits[i] * 0.5;
	//}

	::QueryPerformanceCounter(&lnStart);
	{

		shared_ptr<BITMAPINFO> pBitmapInfo((BITMAPINFO*)malloc(sizeof(BITMAPINFO)));
		if (pBitmapInfo) {
			pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			pBitmapInfo->bmiHeader.biWidth = nWidth;
			pBitmapInfo->bmiHeader.biHeight = nHeight;
			pBitmapInfo->bmiHeader.biPlanes = 1;
			pBitmapInfo->bmiHeader.biBitCount = 24;
			pBitmapInfo->bmiHeader.biCompression = BI_RGB;
			pBitmapInfo->bmiHeader.biSizeImage = 0;
			pBitmapInfo->bmiHeader.biClrImportant = 0;
			pBitmapInfo->bmiHeader.biClrUsed = 0;
			pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
			pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;

			SetDIBitsToDevice(dc.m_hDC,
				0, 30, nWidth, nHeight,
				0, 0, 0, nHeight,
				lpvBits, pBitmapInfo.get(), DIB_RGB_COLORS);  // SetDIBitsToDevice �� �̿��� �����쿡 ���� �� ��
		}
	}

	::QueryPerformanceCounter(&lnEnd);
	lnResult.QuadPart = (lnEnd.QuadPart - lnStart.QuadPart) * 1000000 / lnFreq.QuadPart;
	strTmp.Format(_T("SetDIBitsToDevice() counter %u"), lnResult.QuadPart);
	dc.TextOut(0, 10, strTmp);

	::QueryPerformanceCounter(&lnStart);
	bmp.Draw(dc.m_hDC, 0, 460, nWidth, nHeight);
	::QueryPerformanceCounter(&lnEnd);
	lnResult.QuadPart = (lnEnd.QuadPart - lnStart.QuadPart) * 1000000 / lnFreq.QuadPart;
	strTmp.Format(_T("DrawImage() counter %u"), lnResult.QuadPart);
	dc.TextOut(10, 430, strTmp);
}

BOOL CImgWnd::Create(int x, int y, CWnd* pParentWnd)
{
	CRect rect = CRect(x, y, x + 1000, y + 1000); // ȭ�� ���� ����
	return CWnd::Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rect, pParentWnd, 0);
}