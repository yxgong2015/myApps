/* ---------------------------------------------------------- *
 * Last modification date: 2015/09/18 12:36 - by: Xiaoxi Gong *
 * ---------------------------------------------------------- *
*/

// GPS_serialPortDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "GPS_serialPort.h"
#include "GPS_serialPortDlg.h"
#include "afxdialogex.h"
#include "webpage.h"
#include "dataShift.h"
#include "imuData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "afxmt.h"


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


// CGPS_serialPortDlg 对话框




CGPS_serialPortDlg::CGPS_serialPortDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGPS_serialPortDlg::IDD, pParent)
	, m_Receive(_T(""))
	, m_Send(_T(""))
	, m_GNRMC(_T(""))
	, m_ct(0)
	, m_imu(_T(""))
	, m_ctA(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGPS_serialPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Receive);
	DDX_Text(pDX, IDC_EDIT2, m_Send);
	DDX_Control(pDX, IDC_COMBO1, m_COM1);
	DDX_Control(pDX, IDC_COMBO2, m_COM2);
	DDX_Control(pDX, IDC_MSCOMM1, m_SerialPort);
	DDX_Control(pDX, IDC_EDIT1, m_ReceiveCtrl);
	DDX_Text(pDX, IDC_EDIT3, m_GNRMC);
	DDX_Control(pDX, IDC_EDIT3, m_GNRMCctrl);
	DDX_Text(pDX, IDC_EDIT4, m_ct);
	//DDX_Control(pDX, IDC_EXPLORER1, m_web);
	DDX_Text(pDX, IDC_EDIT5, m_imu);
	DDX_Text(pDX, IDC_EDIT6, m_ctA);
}

BEGIN_MESSAGE_MAP(CGPS_serialPortDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CGPS_serialPortDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CGPS_serialPortDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &CGPS_serialPortDlg::OnBnClickedButtonClean)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CGPS_serialPortDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON1, &CGPS_serialPortDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGPS_serialPortDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CGPS_serialPortDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CGPS_serialPortDlg 消息处理程序

BOOL CGPS_serialPortDlg::OnInitDialog()
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

	//----- Initiate serial port -----//
	CString str;
	int i;
	for(i=0;i<15;i++)
	{
		str.Format(_T("com %d"),i+1);
		m_COM1.InsertString(i,str);
	}
	m_COM1.SetCurSel(13);//预置COM口 0~11

	//波特率选择组合框
	CString str1[]={_T("300"),_T("600"),_T("1200"),_T("2400"),_T("4800"),_T("9600"),
		            _T("19200"),_T("38400"),_T("43000"),_T("56000"),_T("57600"),_T("115200")};
	for(int i=0;i<12;i++)
	{
		int judge_tf=m_COM2.AddString(str1[i]);
		if((judge_tf==CB_ERR)||(judge_tf==CB_ERRSPACE))
			MessageBox(_T("build baud error!"));
	}
	m_COM2.SetCurSel(11);//预置波特率为"9600" 0~11

	//----- -------------------- -----//

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGPS_serialPortDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGPS_serialPortDlg::OnPaint()
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
HCURSOR CGPS_serialPortDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*void CGPS_serialPortDlg::OnBnClickedOk()
{
	AfxBeginThread(MainThread, NULL);
}*/

/*UINT CGPS_serialPortDlg::MainThread(LPVOID pParam)
{
	while(1)
	{

	}
}*/

void CGPS_serialPortDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str,str1,n;					//定义字符串
	GetDlgItemText(IDC_BUTTON_OPEN,str);
	CWnd *h1;
	h1=GetDlgItem(IDC_BUTTON_OPEN);		//指向控件的caption
	
	if(!m_SerialPort.get_PortOpen())
	{
		m_COM2.GetLBText(m_COM2.GetCurSel(),str1);//取得所选的字符串，并存放在str1里面
		str1=str1+','+'n'+','+'8'+','+'1';			//这句话很关键
		
		m_SerialPort.put_CommPort((m_COM1.GetCurSel()+1));	//选择串口
		m_SerialPort.put_InputMode(1);			//设置输入方式为二进制方式
		m_SerialPort.put_Settings(str1);		//波特率为（波特率组Á合框）无校验，8数据位，1个停止位
		m_SerialPort.put_InputLen(1024);		//设置当前接收区数据长度为1024
		m_SerialPort.put_RThreshold(1);			//缓冲区一个字符引发事件
		m_SerialPort.put_RTSEnable(1);			//设置RT允许
			
		m_SerialPort.put_PortOpen(true);		//打开串口

		if(m_SerialPort.get_PortOpen())
		{
			str=_T("close COM");
			UpdateData(true);
			h1->SetWindowText(str);			//改变按钮名称为"关闭串口"
		}		
	}	
	
	else 
	{
		m_SerialPort.put_PortOpen(false);
		if(str!=_T("open COM"))
		{
			str=_T("open COM");
			UpdateData(true);
			h1->SetWindowText(str);			//改变按钮名称为打开串口
		}
	}

}

void CGPS_serialPortDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(true);							//更新控件数据
	m_SerialPort.put_Output(COleVariant(m_Send));//把发送编辑框的数据发送出去
}


void CGPS_serialPortDlg::OnBnClickedButtonClean()
{
	// TODO: 在此添加控件通知处理程序代码

	m_Receive=_T("");	//给接收编辑框发送空格符
	UpdateData(false);		//更新数据
}


void CGPS_serialPortDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码

	if(m_SerialPort.get_PortOpen())
		m_SerialPort.put_PortOpen(false);
	CDialogEx::OnCancel();
}
BEGIN_EVENTSINK_MAP(CGPS_serialPortDlg, CDialogEx)
	ON_EVENT(CGPS_serialPortDlg, IDC_MSCOMM1, 1, CGPS_serialPortDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()

/*
$LAT:3959.153660 N
LOT:11622.730597 E
SPD:0.000
TIM:101406.000
BJT:18146#
*/
int pkt_sf=0,pkt_ef=0,pkt_count=0;
char str_pkt[128]={0};

int pkt_sfA=0,pkt_efA=0,pkt_countA=0;
char str_pktA[64]={0};

void CGPS_serialPortDlg::OnCommMscomm1()
{
	if(m_SerialPort.get_CommEvent()==2)
	{
		char str[1024]={0};
		long k,len;

		VARIANT InputData=m_SerialPort.get_Input();	//读缓冲区
		COleSafeArray fs;
		fs=InputData;	//VARIANT型变À量转换为COleSafeArray型变量
		len=fs.GetOneDimSize(); //得到有效数据长度

		for(k=0;k<len;k++)
		{
			fs.GetElement(&k,str+k);	//转换为BYTE型数组

			//--- group the serial data from '$' to '#' signiture ---//
			if(str[k]=='$') 
			{
				pkt_sf=1;
				pkt_ef=0;

				pkt_count=0;
			}

			if(pkt_sf==1 && pkt_ef==0)
			{
				str_pkt[pkt_count]=str[k];
				pkt_count++;

				m_ct=pkt_count;
			}

			if(pkt_sf==1 && str[k]=='#') 
			{
				pkt_sf=0;
				pkt_ef=1;

				m_GNRMC=str_pkt;
			}
			//--- ----------------------------------------------- ---//

			if(str[k]=='%') 
			{
				pkt_sfA=1;
				pkt_efA=0;

				pkt_countA=0;
			}

			if(pkt_sfA==1 && pkt_efA==0)
			{
				str_pktA[pkt_countA]=str[k];
				pkt_countA++;

				m_ctA=pkt_countA;
			}

			if(pkt_sfA==1 && str[k]=='*') 
			{
				pkt_sfA=0;
				pkt_efA=1;

				m_imu=str_pktA;
			}
			//--- ----------------------------------------------- ---//
		}

		m_Receive=str;
		UpdateData(false);

		m_ReceiveCtrl.SetSel(-1, -1);	
		this->SetDlgItemText(IDC_EDIT1,m_Receive);//将m_EditReceive内容显示到ID为IDC_EDIT1的编辑框的最后位置
		m_ReceiveCtrl.LineScroll(m_ReceiveCtrl.GetLineCount()-1,0);//将垂直滚动条滚动到最后

		m_GNRMCctrl.SetSel(-1, -1);	
		this->SetDlgItemText(IDC_EDIT3,m_GNRMC);
		m_GNRMCctrl.LineScroll(m_GNRMCctrl.GetLineCount()-1,0);
	}
}


void CGPS_serialPortDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// https://www.google.co.uk/maps/place/39°59'06.8"N+116°22'46.6"E/
	
	ShellExecute(this->m_hWnd,"open","https://www.google.co.uk/maps/place/39 59.112456N+116 22.777217E/","","", SW_SHOW);
}


void CGPS_serialPortDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	webpage *dlg1 = new webpage;  // open a new dialog of MAP
	dlg1->Create(IDD_DIALOG1); 
	dlg1->ShowWindow(SW_SHOW);
}


void CGPS_serialPortDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	dataShift *dlg2 = new dataShift;
	dlg2->Create(IDD_DIALOG2);
	dlg2->ShowWindow(SW_SHOW);

	
	imuData *dlg3 = new imuData;
	dlg3->Create(IDD_DIALOG3);
	dlg3->ShowWindow(SW_SHOW);
}


void dataShift::dataShiftMap(CDC *dDC, CRect &mapSize)
{
	CPen newPen, *oldPen;

	newPen.CreatePen(PS_SOLID,3,RGB(0,0,0));
	oldPen = dDC->SelectObject(&newPen);

	
/*
$LAT:3959.153660 N   39   59   0.153660*60
LOT:11622.730597 E   116  22   0.730597*60
SPD:0.000
TIM:101406.000
BJT:18146#
*/

	float latIntDeg=0,latIntMin=0,latIntSec=0,latIntSec_test=0;
	char latCharDeg[2],latCharMin[2],latCharSec[6],latCharSec_test[4];

	float lonIntDeg=0,lonIntMin=0,lonIntSec=0,lonIntSec_test=0;
	char lonCharDeg[3],lonCharMin[2],lonCharSec[6],lonCharSec_test[4];

	float latDegX=0,lonDegY=0, latMinX=0,lonMinY=0, latSecX=0,lonSecY=0;
	float A=1, B=1, C=1,latTestX=0,lonTestY=0;

	int spdCount=0,spdFlag=0;
	float spd=0;
	char spd_pkt[8]={0};


	for(int i=0;i<pkt_count;i++)
	{
		if(str_pkt[i-34]=='L' && str_pkt[i-33]=='A' && str_pkt[i-32]=='T')
		{
			latCharDeg[0] = str_pkt[5];
			latCharDeg[1] = str_pkt[6];
			latIntDeg = atof(latCharDeg);

			latCharMin[0] = str_pkt[7];
			latCharMin[1] = str_pkt[8];
			latIntMin = atof(latCharMin);

			latCharSec[0] = str_pkt[10];
			latCharSec[1] = str_pkt[11];
			latCharSec[2] = str_pkt[12];
			latCharSec[3] = str_pkt[13];
			latCharSec[4] = str_pkt[14];
			latCharSec[5] = str_pkt[15];
			latIntSec = atof(latCharSec);

			//--- test only ---//
			latCharSec_test[0] = str_pkt[12];
			latCharSec_test[1] = str_pkt[13];
			latCharSec_test[2] = str_pkt[14];
			latCharSec_test[3] = str_pkt[15];
			latIntSec_test = atof(latCharSec_test);
			//--- -------- ---//
		}

		if(str_pkt[i-16]=='L' && str_pkt[i-15]=='O' && str_pkt[i-14]=='T')
		{
			lonCharDeg[0] = str_pkt[24];
			lonCharDeg[1] = str_pkt[25];
			lonCharDeg[2] = str_pkt[26];
			lonIntDeg = atof(lonCharDeg);

			lonCharMin[0] = str_pkt[27];
			lonCharMin[1] = str_pkt[28];
			lonIntMin = atof(lonCharMin);

			lonCharSec[0] = str_pkt[30];
			lonCharSec[1] = str_pkt[31];
			lonCharSec[2] = str_pkt[32];
			lonCharSec[3] = str_pkt[33];
			lonCharSec[4] = str_pkt[34];
			lonCharSec[5] = str_pkt[35];
			lonIntSec = atof(lonCharSec);

			//--- test only ---//
			lonCharSec_test[0] = str_pkt[32];
			lonCharSec_test[1] = str_pkt[33];
			lonCharSec_test[2] = str_pkt[34];
			lonCharSec_test[3] = str_pkt[35];
			lonIntSec_test = atof(lonCharSec_test);
			//--- -------- ---//
		}
	}

	//--- SPD data ---//
	for(int ii=0;ii<pkt_count-20;ii++)
	{
		if(str_pkt[ii-4]=='S' && str_pkt[ii-3]=='P' && str_pkt[ii-2]=='D')
			spdFlag=1;

		if(spdFlag==1 && str_pkt[ii]=='\r')
			spdFlag=0;
			
		if(spdFlag==1)
		{
			spd_pkt[spdCount]=str_pkt[ii];
			spdCount++;
		}
	}
	spd = atof(spd_pkt);

	latDegX=latIntDeg*A*(mapSize.Width()/(90*A));
	lonDegY=lonIntDeg*A*(mapSize.Height()/(180*A));

	latMinX=latIntMin*B*(mapSize.Width()/(60*B));
	lonMinY=lonIntMin*B*(mapSize.Height()/(60*B));

	latSecX=latIntSec*0.00006*C*(mapSize.Width()/(60*C));
	lonSecY=lonIntSec*0.00006*C*(mapSize.Height()/(60*C));



	dDC->MoveTo(latDegX, lonDegY);
	dDC->LineTo(latDegX, lonDegY); 

	dDC->MoveTo(latMinX, lonMinY);
	dDC->LineTo(latMinX, lonMinY); 

	dDC->MoveTo(latSecX, lonSecY);
	dDC->LineTo(latSecX, lonSecY);

	

	dDC->SelectObject(&oldPen);
	newPen.DeleteObject();

	//------------------- SPD test --------------------//
	CPen newPen_test, *oldPen_test;

	newPen_test.CreatePen(PS_SOLID,3,RGB(0,0,255));
	oldPen_test = dDC->SelectObject(&newPen_test);

	latTestX=latIntSec_test*0.0001*(mapSize.Width());
	lonTestY=lonIntSec_test*0.0001*(mapSize.Height());

	if(spd==0.000)
	{
		dDC->MoveTo(latTestX, lonTestY);
		dDC->LineTo(latTestX, lonTestY);
	}

	dDC->SelectObject(&oldPen_test);
	newPen_test.DeleteObject();
	//------------------- ---- --------------------//

	ReleaseDC(dDC);
}

