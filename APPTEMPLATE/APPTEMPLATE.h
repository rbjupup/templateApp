
// APPTEMPLATE.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "APPTEMPLATEDlg.h"

// CAPPTEMPLATEApp:
// �йش����ʵ�֣������ APPTEMPLATE.cpp
//

class CAPPTEMPLATEApp : public CWinApp
{
public:
	CAPPTEMPLATEApp();
	CAPPTEMPLATEDlg dlg;
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAPPTEMPLATEApp theApp;