
// GxxGmGspFFmpegSdl2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGxxGmGspFFmpegSdl2App:
// �йش����ʵ�֣������ GxxGmGspFFmpegSdl2.cpp
//

class CGxxGmGspFFmpegSdl2App : public CWinAppEx
{
public:
	CGxxGmGspFFmpegSdl2App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGxxGmGspFFmpegSdl2App theApp;