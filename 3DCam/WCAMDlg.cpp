// WCAMDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3DCam.h"
#include "WCAMDlg.h"
#include "afxdialogex.h"


// CWCAMDlg 对话框

IMPLEMENT_DYNAMIC(CWCAMDlg, CDialog)

CWCAMDlg::CWCAMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWCAMDlg::IDD, pParent)
{

}

CWCAMDlg::~CWCAMDlg()
{
}

void CWCAMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWCAMDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SIDE2, &CWCAMDlg::OnBnClickedButtonSide2)
END_MESSAGE_MAP()


// CWCAMDlg 消息处理程序


void CWCAMDlg::OnBnClickedButtonSide2()
{
	// TODO: 在此添加控件通知处理程序代码
}
