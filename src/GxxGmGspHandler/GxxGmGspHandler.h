
// GxxGmGspHandler.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGxxGmGspHandlerApp:
// �йش����ʵ�֣������ GxxGmGspHandler.cpp
//

class CGxxGmGspHandlerApp : public CWinAppEx
{
public:
	CGxxGmGspHandlerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGxxGmGspHandlerApp theApp;