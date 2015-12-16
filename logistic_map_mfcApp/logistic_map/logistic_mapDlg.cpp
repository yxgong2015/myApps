// logistic_mapDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "logistic_map.h"
#include "logistic_mapDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define itr_time 200
#define TMR 200
#define ZP 120
#define SP 35
#define TP 5
#endif

CString lm_R, lm_x, lm_R_d, lm_x_d;
CString lm_R1, lm_R2, lm_xdd;
long double x_New=0, lm_Rtof=2, lm_xtof=0.665, x_itr[itr_time];
long double x_New_d=0, lm_Rtof_d=3, lm_xtof_d=0.665, x_itr_d[itr_time];
long double x_New_ol=0, lm_R1tof_ol=0, lm_R2tof_ol=0, lm_xtof_ol=0, x_itr_ol[itr_time];
long double compare_itr[itr_time][1], zoomMap=0, shiftY=0;
int lmFlag=0, blank_cunt = 0;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Clogistic_mapDlg 对话框


Clogistic_mapDlg::Clogistic_mapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Clogistic_mapDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clogistic_mapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_R);
	DDX_Control(pDX, IDC_EDIT2, m_Rd);
	DDX_Control(pDX, IDC_EDIT3, m_x);
	DDX_Control(pDX, IDC_EDIT4, m_xd);
	DDX_Control(pDX, IDC_ACC_MAP, m_acc_map);
	DDX_Control(pDX, IDC_CUR_MAP, m_cur_map);
	DDX_Control(pDX, IDC_EDIT5, m_R1);
	DDX_Control(pDX, IDC_EDIT6, m_R2);
	DDX_Control(pDX, IDC_EDIT7, m_xdd);
}

BEGIN_MESSAGE_MAP(Clogistic_mapDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &Clogistic_mapDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &Clogistic_mapDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON9, &Clogistic_mapDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &Clogistic_mapDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDCANCEL, &Clogistic_mapDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3, &Clogistic_mapDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &Clogistic_mapDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &Clogistic_mapDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &Clogistic_mapDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &Clogistic_mapDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON1, &Clogistic_mapDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Clogistic_mapDlg 消息处理程序

BOOL Clogistic_mapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetTimer(1, TMR, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Clogistic_mapDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Clogistic_mapDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Clogistic_mapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//------------------- Plot data on screen ------------------//

void Clogistic_mapDlg::blank_Map(CDC *pDC, CRect &rectPicture)
{
	CBrush newBrush;   
	CBrush *pOldBrush; 

	newBrush.CreateSolidBrush(RGB(255,255,255));   
	pOldBrush = pDC->SelectObject(&newBrush);   
	pDC->Rectangle(rectPicture);   
	pDC->SelectObject(pOldBrush);   
	newBrush.DeleteObject();

	ReleaseDC(pDC);
}
//--------------//


void Clogistic_mapDlg::accumulated_Map(CDC *pDC, CRect &rectPicture)
{
	int now_time_p=0;
	CPen newPen_sum;       
	CPen *pOldPen_sum;
	//----------------- cumulated input ----------------//

	newPen_sum.CreatePen(PS_SOLID, 1.2, RGB(0,245,0));     
	pOldPen_sum = pDC->SelectObject(&newPen_sum);

		for(int p=0;p<itr_time;p++)
		{
			if(compare_itr[p][0] !=0 )
			{
			pDC->MoveTo(now_time_p, compare_itr[p][0]*(ZP+zoomMap)+(SP+shiftY));
			now_time_p = now_time_p + TP;
			pDC->LineTo(now_time_p, compare_itr[p][0]*(ZP+zoomMap)+(SP+shiftY)); 
			}
		}

	pDC->SelectObject(pOldPen_sum);   
	newPen_sum.DeleteObject(); 

	ReleaseDC(pDC);
}
//--------------//


void Clogistic_mapDlg::current_Map(CDC *pDC, CRect &rectPicture)
{
	int now_time=0, now_time_g=0, now_time_r=0;
	long double test;
	//------------------- input blue ------------------//
	CPen newPen, newPen_g, newPen_r;       
	CPen *pOldPen, *pOldPen_g, *pOldPen_r;

	CBrush newBrush;   
	CBrush *pOldBrush;  

	newBrush.CreateSolidBrush(RGB(255,255,255));   
	pOldBrush = pDC->SelectObject(&newBrush);   
	pDC->Rectangle(rectPicture);   
	pDC->SelectObject(pOldBrush);   
	newBrush.DeleteObject();

	newPen.CreatePen(PS_SOLID, 1.2, RGB(0,0,245));     
	pOldPen = pDC->SelectObject(&newPen);

		for(int m=0;m<itr_time;m++)
		{
			if(x_itr[m]!=0 && x_itr[m+1]!=0)
			{
			pDC->MoveTo(now_time, x_itr[m]*(ZP+zoomMap)+(SP+shiftY));
			now_time = now_time + TP;

			pDC->LineTo(now_time, x_itr[m+1]*(ZP+zoomMap)+(SP+shiftY)); 
			}
		}

	pDC->SelectObject(pOldPen);   
	newPen.DeleteObject(); 

	//------------------- input green -------------------//
	newPen_g.CreatePen(PS_SOLID, 1.2, RGB(0,245,0));     
	pOldPen_g = pDC->SelectObject(&newPen_g);

		for(int mg=0;mg<itr_time;mg++)
		{
			if(x_itr_d[mg]!=0 && x_itr_d[mg+1]!=0)
			{
			pDC->MoveTo(now_time_g, x_itr_d[mg]*(ZP+zoomMap)+(SP+shiftY));
			now_time_g = now_time_g + TP;

			pDC->LineTo(now_time_g, x_itr_d[mg+1]*(ZP+zoomMap)+(SP+shiftY)); 
			}
		}

	pDC->SelectObject(pOldPen_g);   
	newPen_g.DeleteObject(); 

	//------------------- input red -------------------//
	newPen_r.CreatePen(PS_SOLID, 1.2, RGB(245,0,0));     
	pOldPen_r = pDC->SelectObject(&newPen_r);

		for(int mr=0;mr<itr_time;mr++)
		{
			if(x_itr_ol[mr]!=0 && x_itr_ol[mr+1]!=0)
			{
			pDC->MoveTo(now_time_r, x_itr_ol[mr]*(ZP+zoomMap)+(SP+shiftY));
			test=x_itr_ol[mr]*(ZP+zoomMap)+(SP+shiftY);
			now_time_r = now_time_r + TP;

			pDC->LineTo(now_time_r, x_itr_ol[mr+1]*(ZP+zoomMap)+(SP+shiftY)); 
			}
		}

	pDC->SelectObject(pOldPen_r);   
	newPen_r.DeleteObject(); 

	ReleaseDC(pDC);
}
//--------------//


//---------------- Main thread ---------------//
UINT Clogistic_mapDlg::MainThread(LPVOID lParam)
{
	//long double test[itr_time];
	//----------------------------------------//
	while(1)
	{
		while(lmFlag == 1)
			{
			Sleep(200);
				if(lmFlag == 2)
				{
				goto out_lmf;
				}
			}
		out_lmf:
			
			//----------------------------------------//
			switch(lmFlag)
			{
			case 6:zoomMap=zoomMap+25;lmFlag=0;break; // zoom +
			case 7:zoomMap=zoomMap-25;lmFlag=0;break; // zoom -
			case 8:shiftY=shiftY-25;lmFlag=0;break; // up
			case 9:shiftY=shiftY+25;lmFlag=0;break; // down
			}

			//----------------------------------------//
			for(int cm=0;cm<itr_time;cm++)
			{
			x_New = lm_Rtof * lm_xtof * (1-lm_xtof);
			x_itr[cm] = x_New;
			lm_xtof = x_New;

			x_New_d = lm_Rtof_d * lm_xtof_d * (1-lm_xtof_d);
			x_itr_d[cm] = x_New_d;
			lm_xtof_d = x_New_d;

			x_New_ol = lm_R1tof_ol * lm_xtof_ol * (1-lm_xtof_ol) + lm_R2tof_ol * lm_xtof_ol * (1-lm_xtof_ol);
			x_itr_ol[cm] = x_New_ol;
			//test[cm] = x_New_ol;
			lm_xtof_ol = x_New_ol;
			}
			
			//----------------------------------------//
			int nn=0;

			for(int mm=0;mm<itr_time;mm++)
			{
				if(x_itr[mm] != 0)
				{
				compare_itr[nn][0] = x_itr[mm];

					if(compare_itr[nn][0] != x_itr[mm+1])
					{
					nn = nn+1;
					compare_itr[nn][0] = x_itr[mm+1];
					}	
				}
			}

	//----------------------------------------//
	while(lmFlag == 2)
		{
		Sleep(200);
			if(lmFlag == 3)
			{
			goto out_lms;
			lmFlag=0;
			}
		}
	out_lms:
	Sleep(200);
	}
}
//----------//


//----------------- Aux thread ---------------//
UINT Clogistic_mapDlg::AuxThread(LPVOID lParam)
{
	int sum=0, ct=0, comp=0;
	long double counter_itr[itr_time][2];

	while(1)
	{
		if(x_itr[comp] != 0) 
		{
			counter_itr[sum][0] = x_itr[comp];
			counter_itr[sum][1] = 0;

			for(ct=0;ct<itr_time;ct++)
			{
				if(counter_itr[sum][0] == x_itr[ct])
				{
					counter_itr[sum][1] = counter_itr[sum][1] + 1;
				}
			}

		comp = comp + 1;
		sum = sum + 1;

			if(comp == 200 || sum == 200)
			{
				comp = 0;
				sum = 0;
			}
		}		

		Sleep(200);
	}
}
//----------//


//------------------ On timer -----------------//
void Clogistic_mapDlg::OnTimer(UINT_PTR nIDEvent)
{
	m_cur_map.GetClientRect(&rectPicture); 
	current_Map(m_cur_map.GetDC(), rectPicture); 

	m_acc_map.GetClientRect(&rectPicture); 
	accumulated_Map(m_acc_map.GetDC(), rectPicture); 	

		if(blank_cunt == 0)
		{
			m_acc_map.GetClientRect(&rectPicture); 
			blank_Map(m_acc_map.GetDC(), rectPicture);
			blank_cunt = 99;
		}
	
	CDialogEx::OnTimer(nIDEvent);
}
//----------------------------//


void Clogistic_mapDlg::OnBnClickedCancel()
{
	m_R.GetWindowText(lm_R);
	m_x.GetWindowText(lm_x);
	lm_Rtof=_ttof(lm_R);
	lm_xtof=_ttof(lm_x);

	m_Rd.GetWindowText(lm_R_d);
	m_xd.GetWindowText(lm_x_d);
	lm_Rtof_d=_ttof(lm_R_d);
	lm_xtof_d=_ttof(lm_x_d);

	m_R1.GetWindowText(lm_R1);
	m_R2.GetWindowText(lm_R2);
	m_xdd.GetWindowText(lm_xdd);
	lm_R1tof_ol=_ttof(lm_R1);
	lm_R2tof_ol=_ttof(lm_R2);
	lm_xtof_ol=_ttof(lm_xdd);

	UpdateData(false);
}


//---------------------------------------//
void Clogistic_mapDlg::OnBnClickedButton3()
{
	AfxBeginThread(MainThread, this);
	//AfxBeginThread(AuxThread, this);
}


void Clogistic_mapDlg::OnBnClickedButton1()
{
	blank_cunt = 0;
}


void Clogistic_mapDlg::OnBnClickedButton2()
{
	lmFlag=1;
}


void Clogistic_mapDlg::OnBnClickedButton9()
{
	lmFlag=2;
}


void Clogistic_mapDlg::OnBnClickedButton10()
{
	lmFlag=3;
}


void Clogistic_mapDlg::OnBnClickedButton5()
{
	lmFlag=6;
}


void Clogistic_mapDlg::OnBnClickedButton6()
{
	lmFlag=7;
}


void Clogistic_mapDlg::OnBnClickedButton7()
{
	lmFlag=8;
}


void Clogistic_mapDlg::OnBnClickedButton8()
{
	lmFlag=9;
}


void Clogistic_mapDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}
//-----------------//