
// GPS_serialPort.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGPS_serialPortApp:
// �йش����ʵ�֣������ GPS_serialPort.cpp
//

class CGPS_serialPortApp : public CWinApp
{
public:
	CGPS_serialPortApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGPS_serialPortApp theApp;