#pragma once


// webpage �Ի���

class webpage : public CDialogEx
{
	DECLARE_DYNAMIC(webpage)

public:
	webpage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~webpage();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
