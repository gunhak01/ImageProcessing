// ImageProcessingEditDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessing.h"
#include "ImageProcessingEditDlg.h"
#include "afxdialogex.h"

#include <memory>
#include <gdiplus.h>
#include <atlImage.h>
#include <wingdi.h>
using namespace Gdiplus;
using namespace std;
// ImageProcessingEditDlg 대화 상자

IMPLEMENT_DYNAMIC(ImageProcessingEditDlg, CDialogEx)

ImageProcessingEditDlg::ImageProcessingEditDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGE_EDIT, pParent)
{

}

ImageProcessingEditDlg::~ImageProcessingEditDlg()
{
}

void ImageProcessingEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ImageProcessingEditDlg, CDialogEx)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// ImageProcessingEditDlg 메시지 처리기


BOOL ImageProcessingEditDlg::OnInitDialog()
{
	//dialog에 view 올리기
	//m_pEditView = new ImageProcessingEditView;
	//m_pEditView->Create(NULL, L"", WS_CHILD | WS_VISIBLE, CRect(0, 0, 1000, 2000), this, 50001);
	//m_pEditView->OnInitialUpdate();

	m_imgWnd.Create(10, 10, this);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void ImageProcessingEditDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//delete m_pEditView;
}
