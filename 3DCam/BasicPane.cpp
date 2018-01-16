// BasicPane.cpp : 实现文件
//

#include "stdafx.h"
#include "Generate_Data.h"
#include "BasicPane.h"  


// CBasicPane

IMPLEMENT_DYNAMIC(CBasicPane, CDockablePane)

CBasicPane::CBasicPane()
{

}

CBasicPane::~CBasicPane()
{
}


BEGIN_MESSAGE_MAP(CBasicPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// CBasicPane 消息处理程序


int CBasicPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_TabDialog.Create(IDD_TAB_DIALOG,this);
	m_TabDialog.ShowWindow(SW_SHOW);
	return 0;
}

void CBasicPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	if(m_TabDialog.GetSafeHwnd())
	{
		CRect rct;
		GetClientRect(rct);
		m_TabDialog.MoveWindow(rct);
	}
}

void CBasicPane::OnDestroy()
{
	CDockablePane::OnDestroy();
	m_TabDialog.DestroyWindow();
}

int CBasicPane::GetCaptionHeight()const
{
	return 0;
}

BOOL CBasicPane::CanBeClosed() const 
{
	return FALSE;
}

void CBasicPane::OnRButtonDown(UINT nFlags, CPoint point)
{
	return;
	CDockablePane::OnRButtonDown(nFlags, point);
}
BOOL CBasicPane::FloatPane(CRect rectFloat, AFX_DOCK_METHOD dockMethod, bool bShow)
{
	return FALSE;
}
BOOL CBasicPane::IsResizable() const
{
	return TRUE;
}