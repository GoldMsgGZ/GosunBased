#include "GSMediaPlayer_stub.h"
#include "GxxGmPlayBase.h"
#include <tchar.h>

#define REG_LOCATION	_T("SOFTWARE\\Gosuncn\\GM\\GxxGmPlayer")


GSMediaPlayer_stub::GSMediaPlayer_stub()
: GSMediaPlayerLib_(NULL)
, ptr_GSMediaPlayer_Open(NULL)
, ptr_GSMediaPlayer_Play(NULL)
, ptr_GSMediaPlayer_ReversePlay(NULL)
, ptr_GSMediaPlayer_Pause(NULL)
, ptr_GSMediaPlayer_Stop(NULL)
, ptr_GSMediaPlayer_Next(NULL)
, ptr_GSMediaPlayer_Back(NULL)
, ptr_GSMediaPlayer_GetPlayedGOPKeyStamp(NULL)
, ptr_GSMediaPlayer_GetPlayedPos(NULL)
, ptr_GSMediaPlayer_SetPlayedPos(NULL)
, ptr_GSMediaPlayer_Close(NULL)
, ptr_GSMediaPlayer_InputData(NULL)
, ptr_GSMediaPlayer_InputGOPData(NULL)
, ptr_GSMediaPlayer_PlaySound(NULL)
, ptr_GSMediaPlayer_SetVolumn(NULL)
, ptr_GSMediaPlayer_GetVolumn(NULL)
, ptr_GSMediaPlayer_StopSound(NULL)
, ptr_GSMediaPlayer_SetDisplayCallback(NULL)
, ptr_GSMediaPlayer_SetBufferEmptyCallback(NULL)
, ptr_GSMediaPlayer_SetDrawCallback(NULL)
, ptr_GSMediaPlayer_SetDisplayRegion(NULL)
, ptr_GSMediaPlayer_GetVideoSize(NULL)
, ptr_GSMediaPlayer_Fast(NULL)
, ptr_GSMediaPlayer_Slow(NULL)
, ptr_GSMediaPlayer_SetPlaySpeed(NULL)
, ptr_GSMediaPlayer_CapturePicture(NULL)
, ptr_GSMediaPlayer_ClearPlayBuffer(NULL)
, ptr_GSMediaPlayer_RefreshView(NULL)
, ptr_GSMediaPlayer_SetColor(NULL)
, ptr_GSMediaPlayer_GetColor(NULL)
{

}

GSMediaPlayer_stub::~GSMediaPlayer_stub()
{
	if (GSMediaPlayerLib_)
	{
		FreeLibrary(GSMediaPlayerLib_);
		GSMediaPlayerLib_ = NULL;
	}
}

int GSMediaPlayer_stub::Initialize()
{
	int errCode = 0;

	// ��ע����ȡ�����װ·��
	HKEY hKey = NULL;
	LONG lret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_LOCATION, 0, KEY_QUERY_VALUE | KEY_READ, &hKey);
	if (lret != ERROR_SUCCESS)
	{
		errCode = GetLastError();
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ��ע���ʧ�ܣ������룺%d\n", errCode);
		return errCode;
	}

	TCHAR location[4096] = {0};
	DWORD location_len = 4096;
	DWORD dwType = 0;
	lret = RegQueryValueEx(hKey, _T("Location"), NULL, &dwType, (LPBYTE)location, &location_len);
	if (lret != ERROR_SUCCESS)
	{
		errCode = GetLastError();
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ��ȡע���ʧ�ܣ������룺%d\n", errCode);
		RegCloseKey(hKey);
		return errCode;
	}

	RegCloseKey(hKey);

	// ���õ�ǰ·��
	BOOL bret = SetCurrentDirectory(location);
	if (!bret)
	{
		errCode = GetLastError();
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����ʧ�ܣ������룺%d\n", errCode);
		return errCode;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	// ���￪ʼ����GSMediaPlayer��ؽӿ�

	TCHAR gsmediaplayer_path[4096] = {0};
	_tcscpy_s(gsmediaplayer_path, 4096, location);
	_tcscat_s(gsmediaplayer_path, 4096, _T("\\GSMediaPlayer.dll"));

	//HMODULE hMod = LoadLibrary(gsmediaplayer_path);
	HMODULE hMod = LoadLibraryEx(gsmediaplayer_path, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	if (hMod == NULL)
	{
		errCode = GetLastError();
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer.dllʧ�ܣ������룺%d\n", errCode);
		return errCode;
	}

	ptr_GSMediaPlayer_Open = (_GSMediaPlayer_Open)GetProcAddress(hMod, "GSMediaPlayer_Open");
	if (ptr_GSMediaPlayer_Open == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_Open()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_Play = (_GSMediaPlayer_Play)GetProcAddress(hMod, "GSMediaPlayer_Play");
	if (ptr_GSMediaPlayer_Play == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_Play()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_ReversePlay = (_GSMediaPlayer_ReversePlay)GetProcAddress(hMod, "GSMediaPlayer_ReversePlay");
	if (ptr_GSMediaPlayer_ReversePlay == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_ReversePlay()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_Pause = (_GSMediaPlayer_Pause)GetProcAddress(hMod, "GSMediaPlayer_Pause");
	if (ptr_GSMediaPlayer_Pause == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_Pause()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_Stop = (_GSMediaPlayer_Stop)GetProcAddress(hMod, "GSMediaPlayer_Stop");
	if (ptr_GSMediaPlayer_Stop == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_Stop()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_Next = (_GSMediaPlayer_Next)GetProcAddress(hMod, "GSMediaPlayer_Next");
	if (ptr_GSMediaPlayer_Next == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_Next()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_Back = (_GSMediaPlayer_Back)GetProcAddress(hMod, "GSMediaPlayer_Back");
	if (ptr_GSMediaPlayer_Back == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_Back()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_GetPlayedGOPKeyStamp = (_GSMediaPlayer_GetPlayedGOPKeyStamp)GetProcAddress(hMod, "GSMediaPlayer_GetPlayedGOPKeyStamp");
	if (ptr_GSMediaPlayer_GetPlayedGOPKeyStamp == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_GetPlayedGOPKeyStamp()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_GetPlayedPos = (_GSMediaPlayer_GetPlayedPos)GetProcAddress(hMod, "GSMediaPlayer_GetPlayedPos");
	if (ptr_GSMediaPlayer_GetPlayedPos == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_GetPlayedPos()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_SetPlayedPos = (_GSMediaPlayer_SetPlayedPos)GetProcAddress(hMod, "GSMediaPlayer_SetPlayedPos");
	if (ptr_GSMediaPlayer_SetPlayedPos == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_SetPlayedPos()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_Close = (_GSMediaPlayer_Close)GetProcAddress(hMod, "GSMediaPlayer_Close");
	if (ptr_GSMediaPlayer_Close == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����_SMediaPlayer_Close()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_InputData = (_GSMediaPlayer_InputData)GetProcAddress(hMod, "GSMediaPlayer_InputData");
	if (ptr_GSMediaPlayer_InputData == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_InputData()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_InputGOPData = (_GSMediaPlayer_InputGOPData)GetProcAddress(hMod, "GSMediaPlayer_InputGOPData");
	if (ptr_GSMediaPlayer_InputGOPData == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_InputGOPData()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_PlaySound = (_GSMediaPlayer_PlaySound)GetProcAddress(hMod, "GSMediaPlayer_PlaySound");
	if (ptr_GSMediaPlayer_PlaySound == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_PlaySound()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_SetVolumn = (_GSMediaPlayer_SetVolumn)GetProcAddress(hMod, "GSMediaPlayer_SetVolumn");
	if (ptr_GSMediaPlayer_SetVolumn == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_SetVolumn()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_GetVolumn = (_GSMediaPlayer_GetVolumn)GetProcAddress(hMod, "GSMediaPlayer_GetVolumn");
	if (ptr_GSMediaPlayer_GetVolumn == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_GetVolumn()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_StopSound = (_GSMediaPlayer_StopSound)GetProcAddress(hMod, "GSMediaPlayer_StopSound");
	if (ptr_GSMediaPlayer_StopSound == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_StopSound()������ַʧ�ܣ�\n");
		return -1;
	}

	//////////////////////////////////////////////////////////////////////////

	ptr_GSMediaPlayer_SetDisplayCallback = (_GSMediaPlayer_SetDisplayCallback)GetProcAddress(hMod, "GSMediaPlayer_SetDisplayCallback");
	if (ptr_GSMediaPlayer_SetDisplayCallback == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_SetDisplayCallback()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_SetBufferEmptyCallback = (_GSMediaPlayer_SetBufferEmptyCallback)GetProcAddress(hMod, "GSMediaPlayer_SetBufferEmptyCallback");
	if (ptr_GSMediaPlayer_SetBufferEmptyCallback == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_SetBufferEmptyCallback()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_SetDrawCallback = (_GSMediaPlayer_SetDrawCallback)GetProcAddress(hMod, "GSMediaPlayer_SetDrawCallback");
	if (ptr_GSMediaPlayer_SetDrawCallback == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_SetDrawCallback()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_SetDisplayRegion = (_GSMediaPlayer_SetDisplayRegion)GetProcAddress(hMod, "GSMediaPlayer_SetDisplayRegion");
	if (ptr_GSMediaPlayer_SetDisplayRegion == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_SetDisplayRegion()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_GetVideoSize = (_GSMediaPlayer_GetVideoSize)GetProcAddress(hMod, "GSMediaPlayer_GetVideoSize");
	if (ptr_GSMediaPlayer_GetVideoSize == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_GetVideoSize()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_Fast = (_GSMediaPlayer_Fast)GetProcAddress(hMod, "GSMediaPlayer_Fast");
	if (ptr_GSMediaPlayer_Fast == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_Fast()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_Slow = (_GSMediaPlayer_Slow)GetProcAddress(hMod, "GSMediaPlayer_Slow");
	if (ptr_GSMediaPlayer_Slow == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_Slow()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_SetPlaySpeed = (_GSMediaPlayer_SetPlaySpeed)GetProcAddress(hMod, "GSMediaPlayer_SetPlaySpeed");
	if (ptr_GSMediaPlayer_SetPlaySpeed == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_SetPlaySpeed()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_CapturePicture = (_GSMediaPlayer_CapturePicture)GetProcAddress(hMod, "GSMediaPlayer_CapturePicture");
	if (ptr_GSMediaPlayer_CapturePicture == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_CapturePicture()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_ClearPlayBuffer = (_GSMediaPlayer_ClearPlayBuffer)GetProcAddress(hMod, "GSMediaPlayer_ClearPlayBuffer");
	if (ptr_GSMediaPlayer_ClearPlayBuffer == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_ClearPlayBuffer()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_RefreshView = (_GSMediaPlayer_RefreshView)GetProcAddress(hMod, "GSMediaPlayer_RefreshView");
	if (ptr_GSMediaPlayer_RefreshView == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_RefreshView()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_SetColor = (_GSMediaPlayer_SetColor)GetProcAddress(hMod, "GSMediaPlayer_SetColor");
	if (ptr_GSMediaPlayer_SetColor == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_SetColor()������ַʧ�ܣ�\n");
		return -1;
	}

	ptr_GSMediaPlayer_GetColor = (_GSMediaPlayer_GetColor)GetProcAddress(hMod, "GSMediaPlayer_GetColor");
	if (ptr_GSMediaPlayer_GetColor == NULL)
	{
		GxxGmPlayBase::DebugStringOutput("GSMediaPlayer_stub >>> ����GSMediaPlayer_GetColor()������ַʧ�ܣ�\n");
		return -1;
	}

	return errCode;
}