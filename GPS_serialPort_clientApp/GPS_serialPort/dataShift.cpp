// dataShift.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GPS_serialPort.h"
#include "dataShift.h"
#include "afxdialogex.h"


// dataShift �Ի���

IMPLEMENT_DYNAMIC(dataShift, CDialogEx)

dataShift::dataShift(CWnd* pParent /*=NULL*/)
	: CDialogEx(dataShift::IDD, pParent)
{

}

dataShift::~dataShift()
{
}

void dataShift::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_DS, m_ds);
}


BEGIN_MESSAGE_MAP(dataShift, CDialogEx)
	ON_BN_CLICKED(IDOK, &dataShift::OnBnClickedOk)
	ON_WM_TIMER()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// dataShift ��Ϣ�������
void dataShift::dataShiftWin(CDC *pDC, CRect &winSize)
{
	CBrush newBrush, *oldBrush;

	CWnd *pWnd = GetDlgItem(IDC_STATIC_DS);
	pWnd->GetClientRect(&winSize);

	newBrush.CreateSolidBrush(RGB(255,255,255));   
	oldBrush = pDC->SelectObject(&newBrush);   
	pDC->Rectangle(winSize);   
	pDC->SelectObject(oldBrush);   
	newBrush.DeleteObject();

	ReleaseDC(pDC);
}


void dataShift::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRect rectPicture;
	m_ds.GetClientRect(&rectPicture);
	dataShiftWin(m_ds.GetDC(),rectPicture);

	SetTimer(1, 1000, NULL);
}

void dataShift::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rectPicture1;
	m_ds.GetClientRect(&rectPicture1);
	dataShiftMap(m_ds.GetDC(),rectPicture1);

	CDialogEx::OnTimer(nIDEvent);
}
