
// GxxGmPlayCore.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGxxGmPlayCoreApp:
// �йش����ʵ�֣������ GxxGmPlayCore.cpp
//

class CGxxGmPlayCoreApp : public CWinAppEx
{
public:
	CGxxGmPlayCoreApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGxxGmPlayCoreApp theApp;