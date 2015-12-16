// webpage.cpp : 实现文件
//

#include "stdafx.h"
#include "GPS_serialPort.h"
#include "webpage.h"
#include "afxdialogex.h"
#include "CWebBrowser2.h"

CWebBrowser2 m_web1;
// webpage 对话框

IMPLEMENT_DYNAMIC(webpage, CDialogEx)

webpage::webpage(CWnd* pParent /*=NULL*/)
	: CDialogEx(webpage::IDD, pParent)
{

}

webpage::~webpage()
{
}

void webpage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_web1);
}


BEGIN_MESSAGE_MAP(webpage, CDialogEx)
	ON_BN_CLICKED(IDOK, &webpage::OnBnClickedOk)
END_MESSAGE_MAP()


// webpage 消息处理程序


void webpage::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// CDialogEx::OnOK();

	VARIANT vt;

	COleVariant vaUrl=_T("http://map.baidu.com/");

	m_web1.Navigate2(vaUrl,&vt,&vt,&vt,&vt);
}
