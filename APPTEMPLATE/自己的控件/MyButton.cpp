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
    m_DownColor = m_UpColor =RGB(0,0,0);//��ʼ����Ϊ��ɫ
}

CMyButton::~CMyButton()
{
}


/////////////////////////////////////////////////////////////////////////////
// CMyButton message handlers


void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    CDC dc;

    dc.Attach(lpDrawItemStruct->hDC);//�õ����Ƶ��豸����CDC

    VERIFY(lpDrawItemStruct->CtlType==ODT_BUTTON);

    //�õ�Button������,����Ĳ�����:1,�ȵõ�����Դ��༭�İ�ť������,

    //Ȼ�󽫴��������»��Ƶ���ť��,

    //ͬʱ�������ֵı���ɫ��Ϊ͸��,����,��ť�Ͻ�����ʾ����
    const int bufSize = 512;

    TCHAR buffer[bufSize];

    GetWindowText(buffer, bufSize);

    int size=strlen(buffer);//�õ�����

    DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);//��������


    SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);//͸��


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
        nXOriginDest = 0;// Ŀ��Xƫ��  
        nYOriginDest = 0;// Ŀ��Yƫ��  
        nWidthDest   = winrect.right - winrect.left;// Ŀ����  
        hHeightDest  = winrect.bottom - winrect.top;// Ŀ��߶�  

        ::TransparentBlt(dc.m_hDC,nXOriginDest,nYOriginDest,nWidthDest,hHeightDest,  
            tmpdc.m_hDC,0,0,bitmap.bmWidth,bitmap.bmHeight,RGB(255,255,255));//��ɫ��Ϊ͸��ɫ  
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
//     if (lpDrawItemStruct->itemState&ODS_SELECTED)//�����°�ťʱ�Ĵ���
// 
//     {////�ػ���������
// 
//         CBrush brush(m_DownColor);
// 
//         dc.FillRect(&(lpDrawItemStruct->rcItem),&brush);//���û�ˢbrush�������ο�
// 
//         //��Ϊ����������ػ�,��������ҲҪ�ػ�
// 
//         DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);
// 
//         SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);
// 
//     }
// 
//     else//����ť���������ߵ���ʱ
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
//     {//ѡ���˱��ؼ�,�����߿�
// 
//         COLORREF fc=RGB(255-GetRValue(m_UpColor),255-GetGValue(m_UpColor),255-GetBValue(m_UpColor));
// 
//         CBrush brush(fc);
// 
//         dc.FrameRect(&(lpDrawItemStruct->rcItem),&brush);//�û�ˢbrush�������α߿�
// 
//     }
// 
    if (!(lpDrawItemStruct->itemState &ODS_SELECTED) &&(lpDrawItemStruct->itemAction & ODA_SELECT))

    {

        CBrush brush(m_UpColor); //���Ƶ�ѡ��״̬����,ȥ���߿�

        dc.FrameRect(&lpDrawItemStruct->rcItem,&brush);

        dc.Detach();
    }
}

void CMyButton::SetBitmap(CString path)
{
    m_strimgPath = path;
}


