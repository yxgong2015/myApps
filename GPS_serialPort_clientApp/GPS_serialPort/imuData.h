#pragma once
#include "afxwin.h"


// imuData �Ի���

class imuData : public CDialogEx
{
	DECLARE_DYNAMIC(imuData)

public:
	imuData(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~imuData();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_imuData;
};
