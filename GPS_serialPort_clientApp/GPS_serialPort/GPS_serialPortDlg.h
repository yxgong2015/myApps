
// GPS_serialPortDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"


// CGPS_serialPortDlg 对话框
class CGPS_serialPortDlg : public CDialogEx
{
// 构造
public:
	CGPS_serialPortDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GPS_SERIALPORT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//static UINT MainThread(LPVOID pParam);
	afx_msg void OnBnClickedOk();
private:
	CString m_Receive;
	CString m_Send;
	CComboBox m_COM1;
	CComboBox m_COM2;
public:
	CMscomm1 m_SerialPort;
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonClean();
	afx_msg void OnBnClickedButtonExit();
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	CEdit m_ReceiveCtrl;
	CString m_GNRMC;
	CEdit m_GNRMCctrl;
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_ct;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CString m_imu;
	int m_ctA;
};
