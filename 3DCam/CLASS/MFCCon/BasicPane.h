#pragma once
#include "../../WCAMDlg.h"
#include "afxcmn.h"
class CBasicPane : public CDockablePane
{
	DECLARE_DYNAMIC(CBasicPane)

public:
	CBasicPane();
	virtual ~CBasicPane();

protected:
	DECLARE_MESSAGE_MAP()
public:
//	CBasicDialog m_BasicDialog;
//	CTabDialog m_TabDialog;
	CWCAMDlg m_TabDialog;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	virtual int GetCaptionHeight()const;			//ȥ�������� 
	virtual BOOL CanBeClosed() const;				//ȥ���رհ�ť
	virtual BOOL FloatPane(CRect rectFloat, AFX_DOCK_METHOD dockMethod, bool bShow);			//ȡ������
 	virtual BOOL IsResizable() const;				//�ɷ���ڴ�С
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};


