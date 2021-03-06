// axGxxGmPlayer.cpp : CaxGxxGmPlayerApp 和 DLL 注册的实现。

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



// CaxGxxGmPlayerApp::InitInstance - DLL 初始化

BOOL CaxGxxGmPlayerApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CaxGxxGmPlayerApp::ExitInstance - DLL 终止

int CaxGxxGmPlayerApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
