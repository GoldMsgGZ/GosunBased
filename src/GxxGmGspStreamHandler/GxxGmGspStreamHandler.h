
// GxxGmGspStreamHandler.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGxxGmGspStreamHandlerApp:
// �йش����ʵ�֣������ GxxGmGspStreamHandler.cpp
//

class CGxxGmGspStreamHandlerApp : public CWinAppEx
{
public:
	CGxxGmGspStreamHandlerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGxxGmGspStreamHandlerApp theApp;