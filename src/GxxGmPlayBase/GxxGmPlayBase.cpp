#include "GxxGmPlayBase.h"
#include <Windows.h>
#include <iostream>
#include <objbase.h>
#include <tchar.h>
#include <DbgHelp.h>

#pragma comment(lib, "Dbghelp.lib")

using namespace std;

#define DEBUG_OUTPUT_BUFFER_LENGTH	10240

//////////////////////////////////////////////////////////////////////////
//
// ������Ϣ���

void GxxGmPlayBase::DebugStringOutput(const char *format, ...)
{
	va_list argvs;
	char *value = new char[DEBUG_OUTPUT_BUFFER_LENGTH];
	ZeroMemory(value, sizeof(char) * DEBUG_OUTPUT_BUFFER_LENGTH);
	va_start(argvs, format);
	int n = vsprintf_s(value, DEBUG_OUTPUT_BUFFER_LENGTH, format, argvs);
	OutputDebugStringA(value);
	printf(value);
	va_end(argvs);

	delete [] value;
}

void GxxGmPlayBase::DebugStringOutput(const wchar_t *format, ...)
{
	va_list argvs;
	wchar_t *value = new wchar_t[DEBUG_OUTPUT_BUFFER_LENGTH];
	ZeroMemory(value, sizeof(wchar_t) * DEBUG_OUTPUT_BUFFER_LENGTH);
	va_start(argvs, format);
	int n = vswprintf_s(value, DEBUG_OUTPUT_BUFFER_LENGTH, format, argvs);
	OutputDebugStringW(value);
	wprintf(value);
	va_end(argvs);

	delete [] value;
}

//////////////////////////////////////////////////////////////////////////
//
//

TCHAR g_MiniDumpPath[MAX_PATH] = {0};

LONG CreateDumpFile(EXCEPTION_POINTERS *aException)  
{
	if (_tcslen(g_MiniDumpPath) <= 0)
		return -1;

	// ����Dump�ļ�
	HANDLE hDumpFile = CreateFile(g_MiniDumpPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hDumpFile == INVALID_HANDLE_VALUE)
		return -2;

	// Dump��Ϣ
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = aException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;  

	// д��Dump�ļ�����
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);

	CloseHandle(hDumpFile);

	return 0;
}

void GxxGmPlayBase::SetupMiniDumpMonitor(const char *aMiniDumpSavePath)
{
	// �����ñ���·��
	if (strlen(aMiniDumpSavePath) <= 0)
		return ;

#ifdef UNICODE
	MultiByteToWideChar(CP_ACP, 0, aMiniDumpSavePath, -1, g_MiniDumpPath, MAX_PATH);
#else
	_tcscpy_s(g_MiniDumpPath, MAX_PATH, aMiniDumpSavePath);
#endif

	// ע��Dump�ص�
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)CreateDumpFile);

	return ;
}

void GxxGmPlayBase::SetupMiniDumpMonitor(const wchar_t *aMiniDumpSavePath)
{
	// �����ñ���·��
	if (wcslen(aMiniDumpSavePath) <= 0)
		return ;

#ifdef UNICODE
	_tcscpy_s(g_MiniDumpPath, MAX_PATH, aMiniDumpSavePath);
#else
	WideCharToMultiByte(CP_ACP, 0, aMiniDumpSavePath, -1, g_MiniDumpPath, MAX_PATH, NULL, NULL);
#endif

	// ע��Dump�ص�
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)CreateDumpFile);

	return ;
}