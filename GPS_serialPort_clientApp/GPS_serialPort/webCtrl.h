#pragma once


// webCtrl �Ի���

class webCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(webCtrl)

public:
	webCtrl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~webCtrl();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
