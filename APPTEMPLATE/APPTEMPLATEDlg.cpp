
// APPTEMPLATEDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "APPTEMPLATE.h"
#include "APPTEMPLATEDlg.h"
#include "afxdialogex.h"
#include "自己的控件\\MaskWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAPPTEMPLATEDlg 对话框




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


// CAPPTEMPLATEDlg 消息处理程序

BOOL CAPPTEMPLATEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    DWORD dwStyle = GetStyle();//获取旧样式    
    DWORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE| WS_SYSMENU |WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;    
    dwNewStyle&=dwStyle;//按位与将旧样式去掉    
    SetWindowLong(m_hWnd,GWL_STYLE,dwNewStyle);//设置成新的样式    
    DWORD dwExStyle = GetExStyle();//获取旧扩展样式    
    DWORD dwNewExStyle = WS_EX_LEFT |WS_EX_LTRREADING |WS_EX_RIGHTSCROLLBAR;    
    dwNewExStyle&=dwExStyle;//按位与将旧扩展样式去掉    
    SetWindowLong(m_hWnd,GWL_EXSTYLE,dwNewExStyle);//设置新的扩展样式    
    SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_FRAMECHANGED);//告诉windows：我的样式改变了，窗口位置和大小保持原来不变！    
    int m_cx = GetSystemMetrics(SM_CXSCREEN);//屏幕像素宽度  
    int m_cy = GetSystemMetrics(SM_CYSCREEN);//屏幕像素高度  
    SetWindowPos(NULL, 0, 0, m_nWidgth, m_nHeight, 0); 

    //初始化关闭按钮
    m_btnCloss.SetBitmap("res\\bitmap1.bmp");
    m_btnCloss.Create("", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP|BS_OWNERDRAW, CRect(m_nWidgth - 40,10,m_nWidgth - 10,40), this,IDC_BUTTONtestself);

    m_btnsmallest.SetBitmap("pic\\test.png");
    m_btnsmallest.Create("",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW ,CRect(0,0,1,4),this,IDC_BUTTONmoveButton);
    
    //初始化logo和名字
    m_logoAndName.Create("相机测试软件", WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(30,5,130,35), this);
    //OnBnClickedmoveButton();
    //初始化相机状态按钮
    m_btnOpenCam.Create("打开相机", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP|BS_OWNERDRAW, CRect(0,0.7*m_nHeight,m_nWidgth / 3,0.8*m_nHeight), this,IDC_BUTTONOpenCam);
    m_btnImgSet.Create("参数设置", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP|BS_OWNERDRAW, CRect(m_nWidgth/3,0.7*m_nHeight,m_nWidgth /3 * 2,0.8*m_nHeight), this,IDC_BUTTONImgSet);
    m_btncamStatu.Create("相机连接状态", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP|BS_OWNERDRAW, CRect(m_nWidgth/3*2,0.7*m_nHeight,m_nWidgth,0.8*m_nHeight), this,IDC_BUTTONcamStatu);

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

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAPPTEMPLATEDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAPPTEMPLATEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAPPTEMPLATEDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
    CDialogEx::OnLButtonDown(nFlags, point);
}
// D:\project\APPTEMPLATE\APPTEMPLATE\APPTEMPLATEDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "APPTEMPLATE.h"
#include "APPTEMPLATEDlg.h"
#include "afxdialogex.h"


// MoveDlg 对话框

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


// MoveDlg 消息处理程序


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
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CDialogEx::OnPaint()
}


BOOL MoveDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}


HBRUSH MoveDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
    if   (nCtlColor == CTLCOLOR_STATIC )   
    {   
        pDC->SetBkMode(TRANSPARENT);   
        return   (HBRUSH)::GetStockObject(NULL_BRUSH);   
    }   
    // TODO:  在此更改 DC 的任何特性

    // TODO:  如果默认的不是所需画笔，则返回另一个画笔
    return hbr;
}
void func1(){

}  
void func2(){;}  


void CAPPTEMPLATEDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    switch (nIDEvent)      
    {      
    case 1:      
        // 如果收到ID为1的定时器的消息则调用func1函数      
        if (m_movedlg == NULL)
        {
            m_movedlg = new MoveDlg;
            m_movedlg->Create(IDD_DIALOG1,this);
            m_movedlg->ShowWindow(SW_SHOW);
        }

        m_movedlg->ShowMsg(m_strshow,m_ptDlgpos.x,m_ptDlgpos.y);    
        break;      
    case 2:      
        // 如果收到ID为2的定时器的消息则调用func2函数      
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
    // TODO: 在此处添加消息处理程序代码
}

void CAPPTEMPLATEDlg::OnBnClickedButtontest()
{
    OnOK();
}
void CAPPTEMPLATEDlg::OnBnClickedmoveButton()
{
    BOOL bIsBlur=FALSE;//是否模糊
    BOOL bIsMouse=TRUE;//是否鼠标穿透
    HWND hWndControl=NULL;//保留控件句柄
    m_MaskWindow.CreateMask(m_hWnd,bIsBlur,bIsMouse,hWndControl,RGB(65,105,225),40);
}

void CAPPTEMPLATEDlg::OnBnClickedStatuCam()
{
//    AfxMessageBox("ip");
//    BOOL bIsBlur=FALSE;//是否模糊
//    BOOL bIsMouse=TRUE;//是否鼠标穿透
//    HWND hWndControl=NULL;//保留控件句柄
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
// D:\project\APPTEMPLATE\APPTEMPLATE\APPTEMPLATEDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "APPTEMPLATE.h"
#include "APPTEMPLATEDlg.h"
#include "afxdialogex.h"


// ImageSetDialog 对话框

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
//调整位置、尺寸
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
    //根据保留控件句柄设置外形
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


// ImageSetDialog 消息处理程序


BOOL ImageSetDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    CButton button;
    button.Create("button", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
        CRect(0,0,50,40), this,IDC_BUTTONtestself);
    // TODO:  在此添加额外的初始化

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}




void ImageSetDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    theApp.dlg.OnLButtonDown(nFlags,point);
    CDialogEx::OnLButtonDown(nFlags, point);
}


void ImageSetDialog::OnBnClickedButton1()
{
	OnOK();
	// TODO: 在此添加控件通知处理程序代码
}


void ImageSetDialog::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

// 		// 绘制图标
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
