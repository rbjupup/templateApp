
// 3DCamView.cpp : CMy3DCamView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CMy3DCamView ����/����

CMy3DCamView::CMy3DCamView()
{
	// TODO: �ڴ˴���ӹ������

}

CMy3DCamView::~CMy3DCamView()
{
}

BOOL CMy3DCamView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy3DCamView ����

void CMy3DCamView::OnDraw(CDC* /*pDC*/)
{
	CMy3DCamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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


// CMy3DCamView ���

#ifdef _DEBUG
void CMy3DCamView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3DCamView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3DCamDoc* CMy3DCamView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DCamDoc)));
	return (CMy3DCamDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy3DCamView ��Ϣ�������
