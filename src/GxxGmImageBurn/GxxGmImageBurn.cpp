// GxxGmImageBurn.cpp : �������̨Ӧ�ó������ڵ㡣
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
		printf("��ȡ IMAPI2 COM�����CLSIDʧ�ܣ������룺0x%08d", hret);
		return 0;
	}

	// ��������ʼ��ȡ��Ӧ��Interface
	HMODULE hMod = LoadLibraryA("imapi2.dll");
	if (hMod == NULL)
	{
		printf("imapi2.dllʧ�ܣ������룺%d\n", GetLastError());
		return -1;
	}

	ptr_DllGetClassObject = (_DllGetClassObject)GetProcAddress(hMod, "DllGetClassObject");
	if (ptr_DllGetClassObject == NULL)
	{
		printf("δ�ҵ�DllGetClassObject�ӿڣ������룺%d\n", GetLastError());
		return -1;
	}

	// ��������
	IClassFactory *ptr_Factory = NULL;
	hret = ptr_DllGetClassObject(imapi2_clsid, IID_IClassFactory, (void **)&pcf);
	if (FAILED(hr) || (ptr_Factory == NULL))
	{
		printf("����COM����ʧ�ܣ������룺0x%08d\n", hret);
		return -1;
	}

	// ����ʵ��


	CoUninitialize();
	return 0;
}

