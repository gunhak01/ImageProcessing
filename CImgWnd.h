
#if _MSC_VER > 1000
#pragma once
#include <afxwin.h>
#endif // _MSC_VER > 1000
// RectWnd.h : header file
//

/************************************************************************/
/* View클래스 에서 부르는 자식 윈도우									*/
/* 1. CWnd 상속															*/
/* 2. Create() 재정의													*/
/* 3. 호출측 클래스에서 객체 생성 후, Crate() 호출                      */
/************************************************************************/

/////////////////////////////////////////////////////////////////////////////
// RectWnd window

class CImgWnd : public CWnd
{
	// Construction
public:
	CImgWnd();

	// Attributes
private:
	BOOL m_bIsSetFocus;

	// Operations
public:

	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(RectWnd)
public:
	virtual BOOL Create(int x, int y, CWnd* pParentWnd); // 함수 재정의
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImgWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(RectWnd)
	afx_msg void OnPaint(); // 출력 내용
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#endif // !defined(AFX_RECTWND_H__B44ED4F0_2E49_4015_92BD_AF44A5168F65__INCLUDED_)