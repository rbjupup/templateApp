
// 3DCamView.cpp : CMy3DCamView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "3DCam.h"
#endif

#include "3DCamDoc.h"
#include "3DCamView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy3DCamView

IMPLEMENT_DYNCREATE(CMy3DCamView, CView)

BEGIN_MESSAGE_MAP(CMy3DCamView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMy3DCamView 构造/析构

CMy3DCamView::CMy3DCamView()
{
	// TODO: 在此处添加构造代码

}

CMy3DCamView::~CMy3DCamView()
{
}

BOOL CMy3DCamView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy3DCamView 绘制

void CMy3DCamView::OnDraw(CDC* /*pDC*/)
{
	CMy3DCamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CMy3DCamView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy3DCamView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy3DCamView 诊断

#ifdef _DEBUG
void CMy3DCamView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3DCamView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3DCamDoc* CMy3DCamView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DCamDoc)));
	return (CMy3DCamDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy3DCamView 消息处理程序
