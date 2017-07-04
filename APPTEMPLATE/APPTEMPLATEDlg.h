
// APPTEMPLATEDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "�Լ��Ŀؼ�\\MyButton.h"
#include "�Լ��Ŀؼ�\\MaskWindow.h"
// MoveDlg �Ի���

class MoveDlg : public CDialogEx
{
    DECLARE_DYNAMIC(MoveDlg)

public:
    MoveDlg(CWnd* pParent = NULL);   // ��׼���캯��
    virtual ~MoveDlg();

    CPoint m_ptOffset;
    void ShowMsg(CString msg,int x,int y){
        m_curmsg = msg;
        UpdateData(false);
        SetWindowPos(NULL, x + 10 + m_ptOffset.x, y + 10 + m_ptOffset.y,msg.GetLength()*10,30, 0);
    }
    // �Ի�������
    enum { IDD = IDD_DIALOG1 };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    DECLARE_MESSAGE_MAP()
public:
    CString m_curmsg;
    afx_msg void OnPaint();
    virtual BOOL OnInitDialog();
    CStatic m_textcon;
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

// ImageSetDialog �Ի���

class ImageSetDialog : public CDialogEx
{
    DECLARE_DYNAMIC(ImageSetDialog)

public:
    ImageSetDialog(CWnd* pParent = NULL);   // ��׼���캯��
    virtual ~ImageSetDialog();

    // �Ի�������
    enum { IDD = IDD_DIALOGCONFIG };
    bool CreateImageSetDDlg(HWND hWndParent);
    int m_width;
    int m_height;
    void AdjustPos();
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    DECLARE_MESSAGE_MAP()

public:
    virtual BOOL OnInitDialog();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnPaint();
};


// CAPPTEMPLATEDlg �Ի���
class CAPPTEMPLATEDlg : public CDialogEx
{
// ����
public:
	CAPPTEMPLATEDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_APPTEMPLATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

    CMaskWindow m_MaskWindow;


/****************************************************************************
ģ����ƵĲ���,���ڴ��ڴ���֮ǰ���ú�
****************************************************************************/
public:
    int m_nWidgth;
    int m_nHeight;
    //��������,������ʾ��Ϣ
    MoveDlg *m_movedlg;
    CPoint  m_ptDlgpos;
    CString m_strshow;
    //��ť
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



