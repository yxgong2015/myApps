#pragma once
#include "afxwin.h"


// imuData 对话框

class imuData : public CDialogEx
{
	DECLARE_DYNAMIC(imuData)

public:
	imuData(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~imuData();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_imuData;
};
