#pragma once
#include "resource.h"

// CWCAMDlg 对话框

class CWCAMDlg : public CDialog
{
	DECLARE_DYNAMIC(CWCAMDlg)

public:
	CWCAMDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWCAMDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_CAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSide2();
};
