
// GxxGmMediaPlayerMultiDisp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGxxGmMediaPlayerMultiDispApp:
// �йش����ʵ�֣������ GxxGmMediaPlayerMultiDisp.cpp
//

class CGxxGmMediaPlayerMultiDispApp : public CWinAppEx
{
public:
	CGxxGmMediaPlayerMultiDispApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGxxGmMediaPlayerMultiDispApp theApp;