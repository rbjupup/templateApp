
// 3DCamView.h : CMy3DCamView ��Ľӿ�
//

#pragma once


class CMy3DCamView : public CView
{
protected: // �������л�����
	CMy3DCamView();
	DECLARE_DYNCREATE(CMy3DCamView)

// ����
public:
	CMy3DCamDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CMy3DCamView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 3DCamView.cpp �еĵ��԰汾
inline CMy3DCamDoc* CMy3DCamView::GetDocument() const
   { return reinterpret_cast<CMy3DCamDoc*>(m_pDocument); }
#endif

