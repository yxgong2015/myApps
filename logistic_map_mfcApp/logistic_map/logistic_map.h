
// logistic_map.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Clogistic_mapApp:
// �йش����ʵ�֣������ logistic_map.cpp
//

class Clogistic_mapApp : public CWinApp
{
public:
	Clogistic_mapApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Clogistic_mapApp theApp;