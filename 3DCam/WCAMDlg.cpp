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
END_MESSAGE_MAP()


// CWCAMDlg 消息处理程序
