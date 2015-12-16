
// logistic_mapDlg.h : 头文件
//

#pragma once
#include <windows.h>
#include "afxwin.h"

// Clogistic_mapDlg 对话框
class Clogistic_mapDlg : public CDialogEx
{
// 构造
public:
	Clogistic_mapDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LOGISTIC_MAP_DIALOG };

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

	static UINT MainThread(LPVOID lParam);//线程函数
	static UINT AuxThread(LPVOID lParam);
	
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void blank_Map(CDC *pDC, CRect &rectPicture);
	void accumulated_Map(CDC *pDC, CRect &rectPicture);
	void current_Map(CDC *pDC, CRect &rectPicture);
	CEdit m_R;
	CEdit m_Rd;
	CEdit m_x;
	CEdit m_xd;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton3();
	CStatic m_acc_map;
	CStatic m_cur_map;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton1();
	CEdit m_R1;
	CEdit m_R2;
	CEdit m_xdd;
	CRect rectPicture;  
};
