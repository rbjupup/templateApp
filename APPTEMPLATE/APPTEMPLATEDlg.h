
// APPTEMPLATEDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "自己的控件\\MyButton.h"
#include "自己的控件\\MaskWindow.h"
// MoveDlg 对话框

class MoveDlg : public CDialogEx
{
    DECLARE_DYNAMIC(MoveDlg)

public:
    MoveDlg(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~MoveDlg();

    CPoint m_ptOffset;
    void ShowMsg(CString msg,int x,int y){
        m_curmsg = msg;
        UpdateData(false);
        SetWindowPos(NULL, x + 10 + m_ptOffset.x, y + 10 + m_ptOffset.y,msg.GetLength()*10,30, 0);
    }
    // 对话框数据
    enum { IDD = IDD_DIALOG1 };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
public:
    CString m_curmsg;
    afx_msg void OnPaint();
    virtual BOOL OnInitDialog();
    CStatic m_textcon;
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

// ImageSetDialog 对话框

class ImageSetDialog : public CDialogEx
{
    DECLARE_DYNAMIC(ImageSetDialog)

public:
    ImageSetDialog(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~ImageSetDialog();

    // 对话框数据
    enum { IDD = IDD_DIALOGCONFIG };
    bool CreateImageSetDDlg(HWND hWndParent);
    int m_width;
    int m_height;
    void AdjustPos();
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

public:
    virtual BOOL OnInitDialog();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnPaint();
};


// CAPPTEMPLATEDlg 对话框
class CAPPTEMPLATEDlg : public CDialogEx
{
// 构造
public:
	CAPPTEMPLATEDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_APPTEMPLATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

    CMaskWindow m_MaskWindow;


/****************************************************************************
模板设计的参数,请在窗口创建之前设置好
****************************************************************************/
public:
    int m_nWidgth;
    int m_nHeight;
    //悬浮窗口,用于显示信息
    MoveDlg *m_movedlg;
    CPoint  m_ptDlgpos;
    CString m_strshow;
    //按钮
    CMyButton m_btnCloss;
    CMyButton m_btnsmallest;
    CMyButton m_btnImgSet;
    CMyButton m_btnOpenCam;
    CMyButton m_btncamStatu;
    CMyButton m_btnSetImageDown;
    CMyButton m_btnSetImageDown1;
	CMyButton m_btnSetImageDown2;
	CMyButton m_btnSetImageDown3;
	CMyButton m_btnSetImageDown4;
    CStatic   m_logoAndName;
    ImageSetDialog *m_imageSetDlg;

    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnMove(int x, int y);
    afx_msg void OnBnClickedButtontest();
    afx_msg void OnBnClickedmoveButton();
    afx_msg void OnBnClickedStatuCam();
    afx_msg void OnBnClickedSetCam();
    afx_msg void OnBnClickedStartGrab();
	afx_msg void OnBnClickedReturnMainFrame();
};



