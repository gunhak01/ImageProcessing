#pragma once
#include "ImageProcessingEditView.h"

// ImageProcessingEditDlg 대화 상자

class ImageProcessingEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ImageProcessingEditDlg)

public:
	ImageProcessingEditDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ImageProcessingEditDlg();
	ImageProcessingEditView* m_pEditView;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGE_EDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
};
