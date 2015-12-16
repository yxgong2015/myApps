#pragma once


// webCtrl 对话框

class webCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(webCtrl)

public:
	webCtrl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~webCtrl();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
