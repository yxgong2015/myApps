// imuData.cpp : 实现文件
//

#include "stdafx.h"
#include "GPS_serialPort.h"
#include "imuData.h"
#include "afxdialogex.h"


// imuData 对话框

IMPLEMENT_DYNAMIC(imuData, CDialogEx)

imuData::imuData(CWnd* pParent /*=NULL*/)
	: CDialogEx(imuData::IDD, pParent)
{

}

imuData::~imuData()
{
}

void imuData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_IMU, m_imuData);
}


BEGIN_MESSAGE_MAP(imuData, CDialogEx)
END_MESSAGE_MAP()


// imuData 消息处理程序
