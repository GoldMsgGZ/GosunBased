
// GxxGmPlayDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGxxGmPlayDemoApp:
// �йش����ʵ�֣������ GxxGmPlayDemo.cpp
//

class CGxxGmPlayDemoApp : public CWinAppEx
{
public:
	CGxxGmPlayDemoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGxxGmPlayDemoApp theApp;