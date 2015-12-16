
// logistic_mapDlg.h : ͷ�ļ�
//

#pragma once
#include <windows.h>
#include "afxwin.h"

// Clogistic_mapDlg �Ի���
class Clogistic_mapDlg : public CDialogEx
{
// ����
public:
	Clogistic_mapDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LOGISTIC_MAP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	static UINT MainThread(LPVOID lParam);//�̺߳���
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
