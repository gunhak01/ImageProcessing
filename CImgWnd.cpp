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
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
	Graphics graphics(dc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);
	Color color;
	CImage bmp;
	bmp.Load(_T("image6.bmp"));
	//bmp.Load(_T("image5.png"));

	//gdi+를 사용하는 방법 
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
	//	//비트맵 리소스를 로딩한다.
	//	HBITMAP hBitmap = bmp.Detach();
	//	//status = bmp.GetHBITMAP(color, &hBitmap);
	//	//if (status == Status::Ok) {
	//	if (hBitmap) {
	//		CDC memDC;

	//		//화면 DC화 호환되는 메모리 DC를 생성한다.
	//		memDC.CreateCompatibleDC(&dc);
	//		//메모리 DC에 선택한다.
	//		HBITMAP hOldBmp = (HBITMAP) ::SelectObject(memDC.m_hDC, hBitmap);
	//		//메모리 DC에 들어있는 비트맵을 화면 DC로 복사하여 출력한다.
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
		//이미지의 시작 주소 설정 
		lpvBits = lpvBits + ((nHeight - 1) * pitch);
	}

	//이미지의 내용을 직접 변경 
	const int size = abs(nHeight * pitch);

	for (int i = 0; i < size; i++) {
		lpvBits[i] = lpvBits[i];
	}

	//gray로 변경 
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
				lpvBits, pBitmapInfo.get(), DIB_RGB_COLORS);  // SetDIBitsToDevice 를 이용해 윈도우에 영상 전 시
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
	CRect rect = CRect(x, y, x + 1000, y + 1000); // 화면 영역 설정
	return CWnd::Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rect, pParentWnd, 0);
}