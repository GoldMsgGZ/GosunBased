// GxxGmImageBurn.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <objbase.h>

#import "C:\\Windows\\SysWOW64\\imapi2.dll"

#pragma comment(lib, "ole32.lib")

typedef HRESULT (__stdcall * _DllGetClassObject) (REFCLSID, REFIID, void**);   
_DllGetClassObject ptr_DllGetClassObject = NULL;  

int _tmain(int argc, _TCHAR* argv[])
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	
	CLSID imapi2_clsid;
	HRESULT hret = CLSIDFromProgID(OLESTR("IMAPI2.MsftDiscMaster2"), &imapi2_clsid);
	if (hret != S_OK)
	{
		printf("获取 IMAPI2 COM对象的CLSID失败！错误码：0x%08d", hret);
		return 0;
	}

	// 接下来开始提取对应的Interface
	HMODULE hMod = LoadLibraryA("imapi2.dll");
	if (hMod == NULL)
	{
		printf("imapi2.dll失败！错误码：%d\n", GetLastError());
		return -1;
	}

	ptr_DllGetClassObject = (_DllGetClassObject)GetProcAddress(hMod, "DllGetClassObject");
	if (ptr_DllGetClassObject == NULL)
	{
		printf("未找到DllGetClassObject接口！错误码：%d\n", GetLastError());
		return -1;
	}

	// 创建工厂
	IClassFactory *ptr_Factory = NULL;
	hret = ptr_DllGetClassObject(imapi2_clsid, IID_IClassFactory, (void **)&pcf);
	if (FAILED(hr) || (ptr_Factory == NULL))
	{
		printf("创建COM工厂失败！错误码：0x%08d\n", hret);
		return -1;
	}

	// 创建实例


	CoUninitialize();
	return 0;
}

