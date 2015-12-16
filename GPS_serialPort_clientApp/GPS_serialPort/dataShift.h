#pragma once
#include "afxwin.h"


// dataShift 对话框

class dataShift : public CDialogEx
{
	DECLARE_DYNAMIC(dataShift)

public:
	dataShift(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~dataShift();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void dataShiftWin(CDC *dDC, CRect &winSize);
	void dataShiftMap(CDC *pDC, CRect &mapSize);
	CStatic m_ds;
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
