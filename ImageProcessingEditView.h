#pragma once
#include <afxwin.h>
class ImageProcessingEditView :
    public CView
{
    virtual void OnDraw(CDC* /*pDC*/);
public:
    DECLARE_MESSAGE_MAP()
//    afx_msg void OnDestroy();
    afx_msg void OnPaint();
};

