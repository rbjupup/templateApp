// MaskWindow.cpp : 实现文件
//

#include "stdafx.h"
#include "MaskWindow.h"


// CMaskWindow
LPCTSTR CMaskWindow::m_lpszClassName=NULL;

IMPLEMENT_DYNAMIC(CMaskWindow, CWnd)

CMaskWindow::CMaskWindow()
{
	m_bIsBlur=FALSE;
	m_bIsMouse=FALSE;
	m_hWndControl=NULL;
	m_clrMask=0;
	m_nMaskAlpha=100;
	m_hCacheDC=NULL;
	m_hCacheBitmap=NULL;
	m_hCacheOldBitmap=NULL;
}

CMaskWindow::~CMaskWindow()
{
	DestroyMask();
}


BEGIN_MESSAGE_MAP(CMaskWindow, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_MOVE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


//创建遮罩窗口(父窗口句柄，是否模糊，是否鼠标穿透，遮罩颜色，遮罩透明度)
BOOL CMaskWindow::CreateMask(HWND hWndParent,BOOL bIsBlur,BOOL bIsMouse,HWND hWndControl,COLORREF clrMask,int nAlpha)
{
	if(hWndParent==NULL || !::IsWindow(hWndParent))
	{
		return FALSE;
	}
	//------------------------------
	DestroyMask();
	m_bIsBlur=bIsBlur;
	m_bIsMouse=bIsMouse;
	m_hWndControl=hWndControl;
	m_clrMask=clrMask;
	m_nMaskAlpha=nAlpha;
	if(m_bIsBlur)
	{
		m_bIsMouse=FALSE;
	}
	if(m_nMaskAlpha<0)
	{
		m_nMaskAlpha=0;
	}
	else if(m_nMaskAlpha>255)
	{
		m_nMaskAlpha=255;
	}
	//------------------------------
	DWORD dwStyle = WS_CHILD;
	DWORD dwExStyle = NULL;
	if(m_bIsMouse)
	{
		dwStyle = WS_POPUP;
		dwExStyle = WS_EX_LAYERED | WS_EX_TRANSPARENT;
	}

	if(m_lpszClassName==NULL)
	{
		m_lpszClassName=AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS
				,::LoadCursor (NULL, IDC_ARROW)
				,(HBRUSH)::GetStockObject (BLACK_BRUSH)
			);
	}
	if(!CWnd::CreateEx(dwExStyle,m_lpszClassName,NULL,dwStyle,0,0,0,0,hWndParent,(HMENU)NULL))
	{
		return FALSE;
	}
	//------------------------------
	AdjustPos();
	if(m_bIsMouse)
	{
		SetLayeredWindowAttributes (m_clrMask, m_nMaskAlpha, LWA_ALPHA);
	}
	else
	{
		DoEvents();
		CreateCache();
		ShowControl(SW_HIDE);
	}
    BringWindowToTop ();
	ShowWindow (SW_SHOWNOACTIVATE);
	//------------------------------
	return TRUE;

}
void CMaskWindow::DestroyMask()
{
	ShowControl(SW_SHOWNOACTIVATE);
	if(::IsWindow(m_hWnd))
	{
		::DestroyWindow(m_hWnd);
	}
	if(m_hCacheDC)
	{
		SelectObject(m_hCacheDC,m_hCacheOldBitmap);
		DeleteObject(m_hCacheBitmap);
		DeleteDC(m_hCacheDC);
		m_hCacheDC=NULL;
		m_hCacheBitmap=NULL;
		m_hCacheOldBitmap=NULL;
	}

}
//显示隐藏子控件
void CMaskWindow::ShowControl(int nCmdShow)
{
	HWND hWndOwner=::GetWindow(m_hWnd,GW_OWNER);
	if(!hWndOwner)
	{
		hWndOwner=::GetParent(m_hWnd);
	}
	//--------------------------
	if(nCmdShow==SW_HIDE)
	{
		HWND hWndChild=::GetWindow(hWndOwner,GW_CHILD);
		while(hWndChild)
		{
			if(hWndChild!=m_hWnd && hWndChild!=m_hWndControl)
			{
				if(::IsWindowVisible(hWndChild))
				{
					::ShowWindow(hWndChild,SW_HIDE);
					m_hWndChildArray.Add(hWndChild);
				}
			}
			hWndChild=::GetWindow(hWndChild,GW_HWNDNEXT);
		}
	}
	else
	{
		int nCount = m_hWndChildArray.GetCount();
		for(int i=0;i<nCount;i++)
		{
			::ShowWindow(m_hWndChildArray[i],nCmdShow);
		}
		m_hWndChildArray.RemoveAll();
	}
}
//调整位置、尺寸
void CMaskWindow::AdjustPos()
{
	if(m_hWnd==NULL || !::IsWindow(m_hWnd))
	{
		return;
	}
	//--------------------------
	HWND hWndOwner=::GetWindow(m_hWnd,GW_OWNER);
	if(!hWndOwner)
	{
		hWndOwner=::GetParent(m_hWnd);
	}
	//--------------------------
	CRect rc;
	::GetClientRect(hWndOwner,&rc);
	int x=rc.left;
	int y=rc.top + 50;
	int nWidth=rc.Width();
	int nHeight=rc.Height() - 100;
	if(m_bIsMouse)
	{
		CPoint pt(x,y);
		::ClientToScreen(hWndOwner,&pt);
		x=pt.x;
		y=pt.y;
	}
	MoveWindow(x,y, nWidth, nHeight, FALSE);
	//--------------------------
	//根据保留控件句柄设置外形
	if(m_hWndControl)
	{
		::GetWindowRect (m_hWndControl, &rc);
		CPoint pt(rc.left,rc.top);
		::ScreenToClient (hWndOwner, &pt);

		HRGN hRgn1 = CreateRectRgn (0, 0, nWidth + 1, nHeight + 1);
		HRGN hRgn2 = CreateRectRgn (pt.x, pt.y, pt.x + (rc.right - rc.left), pt.y + (rc.bottom - rc.top));
		HRGN hRgn3 = CreateRectRgn (0, 0, 0, 0);
		CombineRgn (hRgn3, hRgn1, hRgn2, RGN_XOR);
		SetWindowRgn (hRgn3, TRUE);
		DeleteObject (hRgn1);
		DeleteObject (hRgn2);
		DeleteObject (hRgn3);
	}
	else
	{
		SetWindowRgn (NULL,TRUE);
	}
}
//创建缓存
void CMaskWindow::CreateCache()
{
	HWND hWndOwner=::GetWindow(m_hWnd,GW_OWNER);
	if(!hWndOwner)
	{
		hWndOwner=::GetParent(m_hWnd);
	}
	//--------------------------
	CRect rc;
	::GetClientRect(hWndOwner,&rc);
	int nWidth=rc.Width();
	int nHeight=rc.Height();
	HDC hOwnerDC = ::GetDC (hWndOwner);

	m_hCacheDC = ::CreateCompatibleDC (hOwnerDC);
	m_hCacheBitmap = ::CreateCompatibleBitmap (hOwnerDC, nWidth, nHeight);
	m_hCacheOldBitmap = (HBITMAP)::SelectObject (m_hCacheDC, m_hCacheBitmap);

	::PrintWindow (hWndOwner, m_hCacheDC, PW_CLIENTONLY);

	//--------------------------
	if(m_bIsBlur)
	{
		HBITMAP hBlurBitmap = SetHBitmapBlur(m_hCacheBitmap);
		if(hBlurBitmap)
		{
			SelectObject (m_hCacheDC, m_hCacheOldBitmap);
			DeleteObject (m_hCacheBitmap);
			m_hCacheBitmap = hBlurBitmap;
			m_hCacheOldBitmap = (HBITMAP)SelectObject (m_hCacheDC, m_hCacheBitmap);
		}
	}
	//--------------------------
	if(m_nMaskAlpha>0)//覆盖半透明颜色层
	{
		HDC hTempDC = CreateCompatibleDC (hOwnerDC);
		HBITMAP hTempBitmap = CreateCompatibleBitmap (hOwnerDC, nWidth, nHeight);
		HBITMAP hTempOldBitmap = (HBITMAP)SelectObject (hTempDC, hTempBitmap);
		if(m_clrMask!=0)
		{
			SetBkColor (hTempDC, m_clrMask);
			ExtTextOut (hTempDC, 0, 0, ETO_OPAQUE,CRect (0, 0, nWidth, nHeight), NULL, 0, 0);
		}
		BLENDFUNCTION blend;
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = m_nMaskAlpha;  // 透明度 最大255
		blend.AlphaFormat = 0;
		AlphaBlend (m_hCacheDC, 0,0, nWidth, nHeight, hTempDC, 0,0, nWidth, nHeight, blend);
		SelectObject (hTempDC, hTempOldBitmap);
		DeleteObject (hTempBitmap);
		DeleteDC (hTempDC);
	}
	//--------------------------
	::ReleaseDC (hWndOwner, hOwnerDC);
}
//模糊位图
HBITMAP CMaskWindow::SetHBitmapBlur(HBITMAP hBitmap,int nRadius)
{
	if(!hBitmap)
		return NULL;
	if(nRadius<1)
		nRadius=2;
	nRadius = nRadius*2;
	//--------------------------
	Gdiplus::Bitmap* pSrcImage=Gdiplus::Bitmap::FromHBITMAP(hBitmap,NULL);
	if(!pSrcImage)
	{
		return NULL;
	}
	int nSrcWidth = pSrcImage->GetWidth();
	int nSrcHeight = pSrcImage->GetHeight();
	int nTempWidth = nSrcWidth / nRadius;
	int nTempHeight = nSrcHeight / nRadius;
	if(nSrcWidth<nRadius || nSrcHeight<nRadius || nTempWidth == 0 || nTempHeight == 0)
	{
		delete pSrcImage;
		return NULL;
	}
	//--------------------------
	Gdiplus::Bitmap* pTempImage=new Gdiplus::Bitmap(nTempWidth,nTempHeight,PixelFormat32bppARGB);
	if(!pTempImage)
	{
		delete pSrcImage;
		return NULL;
	}
	//--------------------------
	Gdiplus::Graphics* pGraphics = Gdiplus::Graphics::FromImage(pTempImage);
	if(pGraphics)
	{
		pGraphics->SetSmoothingMode (SmoothingModeAntiAlias);//平滑模式_抗锯齿
		pGraphics->SetCompositingQuality (CompositingQualityGammaCorrected);//混合品质_伽玛校正
		pGraphics->SetInterpolationMode (InterpolationModeHighQualityBilinear);//算法模式_高质量双线性
		pGraphics->SetPixelOffsetMode (PixelOffsetModeNone);//像素偏移模式_不偏移
		Gdiplus::RectF destRect(0, 0, nTempWidth, nTempHeight);
		pGraphics->DrawImage(pSrcImage,destRect,0, 0, nSrcWidth, nSrcHeight,Gdiplus::UnitPixel);
		delete pGraphics;
	}
	pGraphics = Gdiplus::Graphics::FromImage(pSrcImage);
	if(pGraphics)
	{
		pGraphics->SetSmoothingMode (SmoothingModeAntiAlias);//平滑模式_抗锯齿
		pGraphics->SetCompositingQuality (CompositingQualityGammaCorrected);//混合品质_伽玛校正
		pGraphics->SetInterpolationMode (InterpolationModeHighQualityBilinear);//算法模式_高质量双线性
		pGraphics->SetPixelOffsetMode (PixelOffsetModeNone);//像素偏移模式_不偏移
		Gdiplus::RectF destRect(0, 0, nSrcWidth, nSrcHeight);
		pGraphics->DrawImage(pTempImage,destRect,0, 0,nTempWidth, nTempHeight ,Gdiplus::UnitPixel);
		delete pGraphics;
	}
	//--------------------------
	HBITMAP hBlurBitmap = NULL;
	pSrcImage->GetHBITMAP(Gdiplus::Color::White,&hBlurBitmap);
	delete pSrcImage;
	delete pTempImage;
	return hBlurBitmap;
}
void CMaskWindow::OnDestroy()
{
	ShowControl(SW_SHOWNOACTIVATE);
	CWnd::OnDestroy();
}
BOOL CMaskWindow::OnEraseBkgnd(CDC* pDC)
{
	RECT rc;
	GetClientRect(&rc);
	pDC->FillSolidRect(&rc,m_clrMask);
	return TRUE;

	//return CWnd::OnEraseBkgnd(pDC);
}

void CMaskWindow::OnPaint()
{
	if(m_hCacheDC)
	{
		RECT rc;
		GetClientRect(&rc);
		CPaintDC dc(this); // device context for painting
		::BitBlt(dc.GetSafeHdc(),0,0,rc.right-rc.left,rc.bottom-rc.top,m_hCacheDC,0,0,SRCCOPY);
	}
	else
	{
		CWnd::OnPaint();
	}
}
void CMaskWindow::DoEvents()  
{  
    MSG msg;  
    while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))  
    {  
        DispatchMessage(&msg);  
        TranslateMessage(&msg);  
    }   
}  

