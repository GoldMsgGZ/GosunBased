#pragma once

// axGxxGmPlayer.h : axGxxGmPlayer.DLL ����ͷ�ļ�

#if !defined( __AFXCTL_H__ )
#error "�ڰ������ļ�֮ǰ������afxctl.h��"
#endif

#include "resource.h"       // ������


// CaxGxxGmPlayerApp : �й�ʵ�ֵ���Ϣ������� axGxxGmPlayer.cpp��

class CaxGxxGmPlayerApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

