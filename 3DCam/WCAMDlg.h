#pragma once
#include "resource.h"

// CWCAMDlg �Ի���

class CWCAMDlg : public CDialog
{
	DECLARE_DYNAMIC(CWCAMDlg)

public:
	CWCAMDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWCAMDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_CAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSide2();
};
