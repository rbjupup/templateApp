
// APPTEMPLATEDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "APPTEMPLATE.h"
#include "APPTEMPLATEDlg.h"
#include "afxdialogex.h"
#include "�Լ��Ŀؼ�\\MaskWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAPPTEMPLATEDlg �Ի���




CAPPTEMPLATEDlg::CAPPTEMPLATEDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAPPTEMPLATEDlg::IDD, pParent),
    m_nHeight(GetSystemMetrics(SM_CYSCREEN)/3*2),
    m_nWidgth(GetSystemMetrics(SM_CXSCREEN)/3*2),
    m_movedlg(NULL),
    m_strshow("test")
{
//	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_imageSetDlg == NULL;
}

void CAPPTEMPLATEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAPPTEMPLATEDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BUTTONtestself, &CAPPTEMPLATEDlg::OnBnClickedButtontest)
    ON_BN_CLICKED(IDC_BUTTONmoveButton, &CAPPTEMPLATEDlg::OnBnClickedmoveButton)
    ON_BN_CLICKED(IDC_BUTTONcamStatu, &CAPPTEMPLATEDlg::OnBnClickedStatuCam)
	ON_BN_CLICKED(IDC_BUTTONImgSet, &CAPPTEMPLATEDlg::OnBnClickedSetCam)
	ON_BN_CLICKED(IDC_BUTTONReturnMainFrame, &CAPPTEMPLATEDlg::OnBnClickedReturnMainFrame)
    ON_BN_CLICKED(IDC_BUTTONOpenCam, &CAPPTEMPLATEDlg::OnBnClickedStartGrab)
    ON_WM_CTLCOLOR()
ON_WM_CTLCOLOR()
ON_WM_MOVE()
END_MESSAGE_MAP()


// CAPPTEMPLATEDlg ��Ϣ�������

BOOL CAPPTEMPLATEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    DWORD dwStyle = GetStyle();//��ȡ����ʽ    
    DWORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE| WS_SYSMENU |WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;    
    dwNewStyle&=dwStyle;//��λ�뽫����ʽȥ��    
    SetWindowLong(m_hWnd,GWL_STYLE,dwNewStyle);//���ó��µ���ʽ    
    DWORD dwExStyle = GetExStyle();//��ȡ����չ��ʽ    
    DWORD dwNewExStyle = WS_EX_LEFT |WS_EX_LTRREADING |WS_EX_RIGHTSCROLLBAR;    
    dwNewExStyle&=dwExStyle;//��λ�뽫����չ��ʽȥ��    
    SetWindowLong(m_hWnd,GWL_EXSTYLE,dwNewExStyle);//�����µ���չ��ʽ    
    SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_FRAMECHANGED);//����windows���ҵ���ʽ�ı��ˣ�����λ�úʹ�С����ԭ�����䣡    
    int m_cx = GetSystemMetrics(SM_CXSCREEN);//��Ļ���ؿ��  
    int m_cy = GetSystemMetrics(SM_CYSCREEN);//��Ļ���ظ߶�  
    SetWindowPos(NULL, 0, 0, m_nWidgth, m_nHeight, 0); 

    //��ʼ���رհ�ť
    m_btnCloss.SetBitmap("res\\bitmap1.bmp");
    m_btnCloss.Create("", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP|BS_OWNERDRAW, CRect(m_nWidgth - 40,10,m_nWidgth - 10,40), this,IDC_BUTTONtestself);

    m_btnsmallest.SetBitmap("pic\\test.png");
    m_btnsmallest.Create("",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW ,CRect(0,0,1,4),this,IDC_BUTTONmoveButton);
    
    //��ʼ��logo������
    m_logoAndName.Create("����������", WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(30,5,130,35), this);
    //OnBnClickedmoveButton();
    //��ʼ�����״̬��ť
    m_btnOpenCam.Create("�����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP|BS_OWNERDRAW, CRect(0,0.7*m_nHeight,m_nWidgth / 3,0.8*m_nHeight), this,IDC_BUTTONOpenCam);
    m_btnImgSet.Create("��������", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP|BS_OWNERDRAW, CRect(m_nWidgth/3,0.7*m_nHeight,m_nWidgth /3 * 2,0.8*m_nHeight), this,IDC_BUTTONImgSet);
    m_btncamStatu.Create("�������״̬", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP|BS_OWNERDRAW, CRect(m_nWidgth/3*2,0.7*m_nHeight,m_nWidgth,0.8*m_nHeight), this,IDC_BUTTONcamStatu);

    m_btnSetImageDown.SetBitmap("pic\\camset.bmp");
    m_btnSetImageDown.Create("111",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP|BS_OWNERDRAW,CRect(0,m_nHeight - 50,m_nWidgth/5,m_nHeight),this,IDC_BUTTONReturnMainFrame);

	m_btnSetImageDown1.SetBitmap("pic\\camsetn.bmp");
	m_btnSetImageDown1.Create("112",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP|BS_OWNERDRAW,CRect(1*m_nWidgth/5,m_nHeight - 50,2*m_nWidgth/5,m_nHeight),this,IDC_BUTTONImgSet);

	m_btnSetImageDown2.SetBitmap("pic\\camsetn.bmp");
	m_btnSetImageDown2.Create("113",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP|BS_OWNERDRAW,CRect(2*m_nWidgth/5,m_nHeight - 50,3*m_nWidgth/5,m_nHeight),this,IDC_BUTTONImgSet);

	m_btnSetImageDown3.SetBitmap("pic\\camsetn.bmp");
	m_btnSetImageDown3.Create("114",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP|BS_OWNERDRAW,CRect(3*m_nWidgth/5,m_nHeight - 50,4*m_nWidgth/5,m_nHeight),this,IDC_BUTTONImgSet);

	m_btnSetImageDown4.SetBitmap("pic\\camsetn.bmp");
	m_btnSetImageDown4.Create("115",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP|BS_OWNERDRAW,CRect(4*m_nWidgth/5,m_nHeight - 50,5*m_nWidgth/5,m_nHeight),this,IDC_BUTTONImgSet);

    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAPPTEMPLATEDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

        CImage img;                     
        CPaintDC dc(this);          
        if(!img.IsNull()) img.Destroy();  
        HRESULT result = img.Load(_T("pic\\bac.jpg")); 
        
        ::SetStretchBltMode(dc.m_hDC, HALFTONE);  
        ::SetBrushOrgEx(dc.m_hDC, 0, 0, NULL);  
        if (!img.IsNull()) img.StretchBlt(dc.m_hDC,CRect(0,0,m_nWidgth,m_nHeight));
        img.Destroy();  
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAPPTEMPLATEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAPPTEMPLATEDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
    CDialogEx::OnLButtonDown(nFlags, point);
}
// D:\project\APPTEMPLATE\APPTEMPLATE\APPTEMPLATEDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "APPTEMPLATE.h"
#include "APPTEMPLATEDlg.h"
#include "afxdialogex.h"


// MoveDlg �Ի���

IMPLEMENT_DYNAMIC(MoveDlg, CDialogEx)

MoveDlg::MoveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(MoveDlg::IDD, pParent)
    , m_curmsg(_T(""))
{
    m_ptOffset.x = 0;m_ptOffset.y = 0;
}

MoveDlg::~MoveDlg()
{
}

void MoveDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_STATICSHOWMSG, m_curmsg);
    DDX_Control(pDX, IDC_STATICSHOWMSG, m_textcon);
}


BEGIN_MESSAGE_MAP(MoveDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// MoveDlg ��Ϣ�������


void CAPPTEMPLATEDlg::OnMouseMove(UINT nFlags, CPoint point)
{
    CDialogEx::OnMouseMove(nFlags, point);
//     if (m_movedlg != NULL)
//     {
//         m_movedlg->DestroyWindow();
//     }

}


void MoveDlg::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    dc.FillRect(CRect(0,0,1000,1000),&CBrush(RGB(0xFF,0xFF,0xFF)));
    // TODO: �ڴ˴������Ϣ����������
    // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


BOOL MoveDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH MoveDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
    if   (nCtlColor == CTLCOLOR_STATIC )   
    {   
        pDC->SetBkMode(TRANSPARENT);   
        return   (HBRUSH)::GetStockObject(NULL_BRUSH);   
    }   
    // TODO:  �ڴ˸��� DC ���κ�����

    // TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
    return hbr;
}
void func1(){

}  
void func2(){;}  


void CAPPTEMPLATEDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    switch (nIDEvent)      
    {      
    case 1:      
        // ����յ�IDΪ1�Ķ�ʱ������Ϣ�����func1����      
        if (m_movedlg == NULL)
        {
            m_movedlg = new MoveDlg;
            m_movedlg->Create(IDD_DIALOG1,this);
            m_movedlg->ShowWindow(SW_SHOW);
        }

        m_movedlg->ShowMsg(m_strshow,m_ptDlgpos.x,m_ptDlgpos.y);    
        break;      
    case 2:      
        // ����յ�IDΪ2�Ķ�ʱ������Ϣ�����func2����      
        func2();    
        break;       
    default:      
        break;      
    }      
    CDialogEx::OnTimer(nIDEvent);
}




HBRUSH CAPPTEMPLATEDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
    if   (nCtlColor == CTLCOLOR_BTN )   
    {   
        pDC->SetBkMode(TRANSPARENT);   
        return   (HBRUSH)::GetStockObject(NULL_BRUSH);   
    }  
    if   (nCtlColor == CTLCOLOR_STATIC )   
    {   
        pDC->SetBkMode(TRANSPARENT);   
        return   (HBRUSH)::GetStockObject(NULL_BRUSH);   
    }  
    return hbr;
}


void CAPPTEMPLATEDlg::OnMove(int x, int y)
{
    CDialogEx::OnMove(x, y);
	m_MaskWindow.AdjustPos();
    if(m_imageSetDlg != NULL)
        m_imageSetDlg->AdjustPos();
    // TODO: �ڴ˴������Ϣ����������
}

void CAPPTEMPLATEDlg::OnBnClickedButtontest()
{
    OnOK();
}
void CAPPTEMPLATEDlg::OnBnClickedmoveButton()
{
    BOOL bIsBlur=FALSE;//�Ƿ�ģ��
    BOOL bIsMouse=TRUE;//�Ƿ���괩͸
    HWND hWndControl=NULL;//�����ؼ����
    m_MaskWindow.CreateMask(m_hWnd,bIsBlur,bIsMouse,hWndControl,RGB(65,105,225),40);
}

void CAPPTEMPLATEDlg::OnBnClickedStatuCam()
{
//    AfxMessageBox("ip");
//    BOOL bIsBlur=FALSE;//�Ƿ�ģ��
//    BOOL bIsMouse=TRUE;//�Ƿ���괩͸
//    HWND hWndControl=NULL;//�����ؼ����
//    m_MaskWindow.CreateMask(m_hWnd,bIsBlur,bIsMouse,hWndControl,RGB(65,105,225),40);
}
void CAPPTEMPLATEDlg::OnBnClickedReturnMainFrame(){
	if (NULL != m_imageSetDlg)
	{
		delete m_imageSetDlg;
		m_imageSetDlg = NULL;
	}
}
void CAPPTEMPLATEDlg::OnBnClickedSetCam()
{
	ImageSetDialog* ptmp = NULL;
	if (NULL != m_imageSetDlg)
	{
		ptmp = m_imageSetDlg;
	}

	m_imageSetDlg = new ImageSetDialog;
	m_imageSetDlg->Create(IDD_DIALOGCONFIG,this);
//	m_imageSetDlg->SetWindowPos(NULL, 0, 50, m_nWidgth, m_nHeight - 300, 0);
	m_imageSetDlg->AdjustPos();
	m_imageSetDlg->ShowWindow(TRUE);
	Sleep(10);
	delete ptmp;
}

void CAPPTEMPLATEDlg::OnBnClickedStartGrab()
{
    AfxMessageBox("open");
}
// D:\project\APPTEMPLATE\APPTEMPLATE\APPTEMPLATEDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "APPTEMPLATE.h"
#include "APPTEMPLATEDlg.h"
#include "afxdialogex.h"


// ImageSetDialog �Ի���

IMPLEMENT_DYNAMIC(ImageSetDialog, CDialogEx)

ImageSetDialog::ImageSetDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(ImageSetDialog::IDD, pParent)
{
    m_width = 1000;
    m_height = 1000;
}

ImageSetDialog::~ImageSetDialog()
{
}

void ImageSetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ImageSetDialog, CDialogEx)
    ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &ImageSetDialog::OnBnClickedButton1)
	ON_WM_PAINT()
END_MESSAGE_MAP()
//����λ�á��ߴ�
void ImageSetDialog::AdjustPos()
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
     CPoint pt;
//     ::GetClientRect(hWndOwner,&rc);

    ::GetWindowRect(hWndOwner,&rc);
//    ::ScreenToClient(hWndOwner,&pt);
    int x=rc.left;
    int y=rc.top + 50;
    int nWidth=rc.Width();
    int nHeight=rc.Height() - 100;
	m_width = nWidth,
	m_height = nHeight;
//     if(m_bIsMouse)
//     {
//         CPoint pt(x,y);
//         ::ClientToScreen(hWndOwner,&pt);
//         x=pt.x;
//         y=pt.y;
//     }
    MoveWindow(x,y, nWidth, nHeight, FALSE);
    //--------------------------
    //���ݱ����ؼ������������
//     if(m_hWndControl)
//     {
//         ::GetWindowRect (m_hWndControl, &rc);
//         CPoint pt(rc.left,rc.top);
//         ::ScreenToClient (hWndOwner, &pt);
// 
//         HRGN hRgn1 = CreateRectRgn (0, 0, nWidth + 1, nHeight + 1);
//         HRGN hRgn2 = CreateRectRgn (pt.x, pt.y, pt.x + (rc.right - rc.left), pt.y + (rc.bottom - rc.top));
//         HRGN hRgn3 = CreateRectRgn (0, 0, 0, 0);
//         CombineRgn (hRgn3, hRgn1, hRgn2, RGN_XOR);
//         SetWindowRgn (hRgn3, TRUE);
//         DeleteObject (hRgn1);
//         DeleteObject (hRgn2);
//         DeleteObject (hRgn3);
//     }
//     else
//     {
        SetWindowRgn (NULL,FALSE);
//    }
}
bool ImageSetDialog::CreateImageSetDDlg(HWND hWndParent)
{
    if(hWndParent==NULL || !::IsWindow(hWndParent))
    {
        return FALSE;
    }
    //------------------------------
//    DestroyMask();
//     m_bIsBlur=bIsBlur;
//     m_bIsMouse=bIsMouse;
//     m_hWndControl=hWndControl;
//     m_clrMask=clrMask;
//     m_nMaskAlpha=nAlpha;
//     if(m_bIsBlur)
//     {
//         m_bIsMouse=FALSE;
//     }
//     if(m_nMaskAlpha<0)
//     {
//         m_nMaskAlpha=0;
//     }
//     else if(m_nMaskAlpha>255)
//     {
//         m_nMaskAlpha=255;
//     }
    //------------------------------
    DWORD dwStyle = WS_CHILD;
    DWORD dwExStyle = NULL;
//     if(m_bIsMouse)
//     {
//        dwStyle = WS_POPUP;
//        dwExStyle = WS_EX_LAYERED | WS_EX_TRANSPARENT;
//    }
    static LPCTSTR m_lpszClassName;
    m_lpszClassName=AfxRegisterWndClass(WS_CHILD | WS_TABSTOP | WS_VISIBLE/*CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS*/
        ,::LoadCursor (NULL, IDC_ARROW)
        ,(HBRUSH)::GetStockObject (WHITE_BRUSH)
        );
    if(!CWnd::CreateEx(dwExStyle,m_lpszClassName,NULL,dwStyle,00,0,0,0,hWndParent,(HMENU)NULL))
    {
        return FALSE;
    }
    //------------------------------
    AdjustPos();
//     if(m_bIsMouse)
//     {
//         SetLayeredWindowAttributes (m_clrMask, m_nMaskAlpha, LWA_ALPHA);
//     }
//     else
//     {
//       DoEvents();
//        CreateCache();
//        ShowControl(SW_HIDE);
//    }
    BringWindowToTop ();
    ShowWindow (SW_SHOW/*SW_SHOWNOACTIVATE*/);
    //------------------------------
    return TRUE;

}


// ImageSetDialog ��Ϣ�������


BOOL ImageSetDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    CButton button;
    button.Create("button", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
        CRect(0,0,50,40), this,IDC_BUTTONtestself);
    // TODO:  �ڴ���Ӷ���ĳ�ʼ��

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}




void ImageSetDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    theApp.dlg.OnLButtonDown(nFlags,point);
    CDialogEx::OnLButtonDown(nFlags, point);
}


void ImageSetDialog::OnBnClickedButton1()
{
	OnOK();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void ImageSetDialog::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

// 		// ����ͼ��
// 		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CImage img;                     
		CPaintDC dc(this);          
		if(!img.IsNull()) img.Destroy();  
		HRESULT result = img.Load(_T("pic\\bac.jpg")); 

		::SetStretchBltMode(dc.m_hDC, HALFTONE);  
		::SetBrushOrgEx(dc.m_hDC, 0, -50, NULL);  
		if (!img.IsNull()) img.StretchBlt(dc.m_hDC,0,-50,this->m_width,this->m_height+100);
		img.Destroy();  
		CDialogEx::OnPaint();
	}
}
