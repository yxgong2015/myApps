// imuData.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GPS_serialPort.h"
#include "imuData.h"
#include "afxdialogex.h"


// imuData �Ի���

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


// imuData ��Ϣ�������
