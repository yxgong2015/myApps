// webCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GPS_serialPort.h"
#include "webCtrl.h"
#include "afxdialogex.h"


// webCtrl �Ի���

IMPLEMENT_DYNAMIC(webCtrl, CDialogEx)

webCtrl::webCtrl(CWnd* pParent /*=NULL*/)
	: CDialogEx(webCtrl::IDD, pParent)
{

}

webCtrl::~webCtrl()
{
}

void webCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(webCtrl, CDialogEx)
END_MESSAGE_MAP()


// webCtrl ��Ϣ�������
