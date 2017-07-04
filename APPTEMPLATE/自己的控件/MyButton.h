#if !defined(AFX_MYBUTTON_H__99654018_DF84_4753_BD4A_DAE962A61BD6__INCLUDED_)
#define AFX_MYBUTTON_H__99654018_DF84_4753_BD4A_DAE962A61BD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyButton window

class CMyButton : public CButton
{
// Construction
public:
	CMyButton();

public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyButton();
    BOOL CMyButton::Attach(const UINT nID,CWnd* pParent)

    {

        if (!SubclassDlgItem(nID, pParent))

            return FALSE;

        return TRUE;

    }
    void SetBitmap(CString );
    CString m_strimgPath;
	// Generated message map functions
protected:
    //必需重载的函数

    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

public:

    //三种颜色分别为文字，Button Down的背景颜色，Button Up的背景颜色

    COLORREF m_TextColor, m_DownColor,m_UpColor;
//	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYBUTTON_H__99654018_DF84_4753_BD4A_DAE962A61BD6__INCLUDED_)
