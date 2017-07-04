// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "MyButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyButton

CMyButton::CMyButton()
{
    m_DownColor = m_UpColor =RGB(0,0,0);//初始化设为黑色
}

CMyButton::~CMyButton()
{
}


/////////////////////////////////////////////////////////////////////////////
// CMyButton message handlers


void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    CDC dc;

    dc.Attach(lpDrawItemStruct->hDC);//得到绘制的设备环境CDC

    VERIFY(lpDrawItemStruct->CtlType==ODT_BUTTON);

    //得当Button上文字,这里的步骤是:1,先得到在资源里编辑的按钮的文字,

    //然后将此文字重新绘制到按钮上,

    //同时将此文字的背景色设为透明,这样,按钮上仅会显示文字
    const int bufSize = 512;

    TCHAR buffer[bufSize];

    GetWindowText(buffer, bufSize);

    int size=strlen(buffer);//得到长度

    DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);//绘制文字


    SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);//透明


    CImage m_btnimg;
    if(!m_btnimg.IsNull()) m_btnimg.Destroy();  
    HRESULT result = m_btnimg.Load(m_strimgPath); 
    if (result != 0)
    {
        return;
    }

    HBITMAP hbitmap = m_btnimg.Detach();  
    CBitmap cBitmap;  
    BITMAP bitmap;  
    cBitmap.Attach(hbitmap);  
    cBitmap.GetBitmap(&bitmap);  
    if ( cBitmap.GetSafeHandle() )  
    {  
        CDC tmpdc;  
        tmpdc.CreateCompatibleDC(&dc);  
        CBitmap *pOldBitmap = tmpdc.SelectObject(&cBitmap);  

        int nXOriginDest    = 0;  
        int nYOriginDest    = 0;  
        int nWidthDest  = 0;  
        int hHeightDest     = 0;  
        CRect winrect;
        GetWindowRect(winrect);
        nXOriginDest = 0;// 目标X偏移  
        nYOriginDest = 0;// 目标Y偏移  
        nWidthDest   = winrect.right - winrect.left;// 目标宽度  
        hHeightDest  = winrect.bottom - winrect.top;// 目标高度  

        ::TransparentBlt(dc.m_hDC,nXOriginDest,nYOriginDest,nWidthDest,hHeightDest,  
            tmpdc.m_hDC,0,0,bitmap.bmWidth,bitmap.bmHeight,RGB(255,255,255));//白色作为透明色  
        tmpdc.SelectObject(pOldBitmap);  
        tmpdc.DeleteDC();  
    }  

// 
//     ::SetStretchBltMode(dc.m_hDC, HALFTONE);  
//     ::SetBrushOrgEx(dc.m_hDC, 0, 0, NULL);  
//     CRect winrect;
//     GetWindowRect(winrect);
//     if (!m_btnimg.IsNull()) m_btnimg.StretchBlt(dc.m_hDC,CRect(0,0,winrect.right - winrect.left,winrect.bottom - winrect.top));
//     m_btnimg.Destroy();  


// 
//     if (lpDrawItemStruct->itemState&ODS_SELECTED)//当按下按钮时的处理
// 
//     {////重绘整个控制
// 
//         CBrush brush(m_DownColor);
// 
//         dc.FillRect(&(lpDrawItemStruct->rcItem),&brush);//利用画刷brush，填充矩形框
// 
//         //因为这里进行了重绘,所以文字也要重绘
// 
//         DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);
// 
//         SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);
// 
//     }
// 
//     else//当按钮不操作或者弹起时
// 
//     {
// 
//         CBrush brush(m_UpColor);
// 
//         dc.FillRect(&(lpDrawItemStruct->rcItem),&brush);//
// 
//         DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);
// 
//         SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);
// 
//     }
// 
//     if ((lpDrawItemStruct->itemState&ODS_SELECTED)&&(lpDrawItemStruct->itemAction &(ODA_SELECT|ODA_DRAWENTIRE)))
// 
//     {//选中了本控件,高亮边框
// 
//         COLORREF fc=RGB(255-GetRValue(m_UpColor),255-GetGValue(m_UpColor),255-GetBValue(m_UpColor));
// 
//         CBrush brush(fc);
// 
//         dc.FrameRect(&(lpDrawItemStruct->rcItem),&brush);//用画刷brush，填充矩形边框
// 
//     }
// 
    if (!(lpDrawItemStruct->itemState &ODS_SELECTED) &&(lpDrawItemStruct->itemAction & ODA_SELECT))

    {

        CBrush brush(m_UpColor); //控制的选中状态结束,去掉边框

        dc.FrameRect(&lpDrawItemStruct->rcItem,&brush);

        dc.Detach();
    }
}

void CMyButton::SetBitmap(CString path)
{
    m_strimgPath = path;
}


