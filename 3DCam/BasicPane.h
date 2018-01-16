#pragma once
#include "TabDialog.h"
//#include "BasicDialog.h"
// CBasicPane

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
	CTabDialog m_TabDialog;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	virtual int GetCaptionHeight()const;			//去掉标题栏 
	virtual BOOL CanBeClosed() const;				//去掉关闭按钮
	virtual BOOL FloatPane(CRect rectFloat, AFX_DOCK_METHOD dockMethod, bool bShow);			//取消浮动
 	virtual BOOL IsResizable() const;				//可否调节大小
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};


