//=========================================
//遮罩窗口实现类
//By：邓学彬(泪闯天涯)
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
	//创建遮罩窗口(父窗口句柄，是否模糊，是否鼠标穿透，保留控件句柄，遮罩颜色，遮罩透明度)
	BOOL CreateMask(HWND hWndParent,BOOL bIsBlur,BOOL bIsMouse,HWND hWndControl,COLORREF clrMask=0,int nAlpha=150);
	//销毁遮罩
	void DestroyMask();
	//调整位置、尺寸
	void AdjustPos();
private:
	static void DoEvents();
private:
	//创建缓存
	void CreateCache();
	//显示隐藏子控件
	void ShowControl(int nCmdShow);
	//模糊位图
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


