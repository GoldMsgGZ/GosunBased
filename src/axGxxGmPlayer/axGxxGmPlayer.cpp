// axGxxGmPlayer.cpp : CaxGxxGmPlayerApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "axGxxGmPlayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CaxGxxGmPlayerApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x2E3A279F, 0x5861, 0x424D, { 0xA8, 0x6F, 0x35, 0x45, 0x61, 0x6E, 0xD1, 0xC7 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CaxGxxGmPlayerApp::InitInstance - DLL ��ʼ��

BOOL CaxGxxGmPlayerApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CaxGxxGmPlayerApp::ExitInstance - DLL ��ֹ

int CaxGxxGmPlayerApp::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
