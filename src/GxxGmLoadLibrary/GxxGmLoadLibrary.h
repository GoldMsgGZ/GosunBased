
// GxxGmLoadLibrary.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGxxGmLoadLibraryApp:
// �йش����ʵ�֣������ GxxGmLoadLibrary.cpp
//

class CGxxGmLoadLibraryApp : public CWinAppEx
{
public:
	CGxxGmLoadLibraryApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGxxGmLoadLibraryApp theApp;