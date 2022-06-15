
#if _MSC_VER > 1000
#pragma once
#include <afxwin.h>
#endif // _MSC_VER > 1000
// RectWnd.h : header file
//

/************************************************************************/
/* ViewŬ���� ���� �θ��� �ڽ� ������									*/
/* 1. CWnd ���															*/
/* 2. Create() ������													*/
/* 3. ȣ���� Ŭ�������� ��ü ���� ��, Crate() ȣ��                      */
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
	virtual BOOL Create(int x, int y, CWnd* pParentWnd); // �Լ� ������
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImgWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(RectWnd)
	afx_msg void OnPaint(); // ��� ����
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#endif // !defined(AFX_RECTWND_H__B44ED4F0_2E49_4015_92BD_AF44A5168F65__INCLUDED_)