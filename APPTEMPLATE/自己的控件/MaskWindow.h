//=========================================
//���ִ���ʵ����
//By����ѧ��(�ᴳ����)
//=========================================
#pragma once

#include <gdiplus.h>
#include <afxtempl.h>

class CMaskWindow : public CWnd
{
	DECLARE_DYNAMIC(CMaskWindow)
public:
	CMaskWindow();
	virtual ~CMaskWindow();
public:
	//�������ִ���(�����ھ�����Ƿ�ģ�����Ƿ���괩͸�������ؼ������������ɫ������͸����)
	BOOL CreateMask(HWND hWndParent,BOOL bIsBlur,BOOL bIsMouse,HWND hWndControl,COLORREF clrMask=0,int nAlpha=150);
	//��������
	void DestroyMask();
	//����λ�á��ߴ�
	void AdjustPos();
private:
	static void DoEvents();
private:
	//��������
	void CreateCache();
	//��ʾ�����ӿؼ�
	void ShowControl(int nCmdShow);
	//ģ��λͼ
	static HBITMAP SetHBitmapBlur(HBITMAP hBitmap,int nRadius=2);

private:
	BOOL m_bIsBlur;
	BOOL m_bIsMouse;
	HWND m_hWndControl;
	COLORREF m_clrMask;
	int m_nMaskAlpha;
	HDC m_hCacheDC;
	HBITMAP m_hCacheBitmap;
	HBITMAP m_hCacheOldBitmap;
	static LPCTSTR m_lpszClassName;
	CArray<HWND,HWND> m_hWndChildArray;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
public:
	afx_msg void OnDestroy();
};


