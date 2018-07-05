// GxxGmStrermHandlerDemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

#include "GxxGmStreamRecevicer.h"
#include "StreamServerSDK.h"

void CALLBACK _StreamCallback2(long lHandle, FRAME_HEADER header, char *pData, long nSize, void* userData)
{

}

class GxxGmObserver : public GxxGmStreamRecevicerObserver
{
public:
	GxxGmObserver() {}
	~GxxGmObserver() {}

public:
	/**
	 * 视频流复用信息回调
	 * 参数：
	 *	@fmtctx		复用格式上下文
	 */
	virtual int DemuxingInfo(GxxGmAVFormatContext *fmtctx)
	{
		//
		return 0;
	}

	virtual int VideoPacket(AVPacket *pkt)
	{
		//
		return 0;
	}

	virtual int AudioPacket(AVPacket *pkt)
	{
		// 
		return 0;
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	// 这里尝试使用SSSDK获取URL
	SSInit();

	// 连接到服务器
	GOSUN_SERVER_INFO info;
	ZeroMemory(&info, sizeof(GOSUN_SERVER_INFO));
	strcpy(info.servIP, "127.0.0.1");
	strcpy(info.username, "admin");
	strcpy(info.password, "admin");
	info.servPort = 10086;

	void *handle_ = NULL;
	int errCode = SSLogin(&handle_, info);
	if (errCode != GOSUN_SUCCESS)
		return 0;

	SS_DEVICE_INFO devinfo;
	ZeroMemory(&devinfo, sizeof(SS_DEVICE_INFO));
	strcpy(devinfo.chanCodeid, "110"); 
	strcpy(devinfo.devCodeid, "110");
	devinfo.channel = 1;
	devinfo.modelID = SDK_DEV_GXX;
	devinfo.streamType = 1;
	strcpy_s(devinfo.username, GOSUN_USER_INFO_LEN, "admin");
	strcpy_s(devinfo.password, GOSUN_USER_INFO_LEN, "admin");

	char url[512] = {0};
	errCode = SSGetURL(handle_, url, 512, devinfo);
	if (errCode != GOSUN_SUCCESS)
		return errCode;

	//EnumStreamCodeID codeID[2];
	//void *stream_handle_ = NULL;
	////errCode = SSOpenEx(url, &stream_handle_, _StreamCallback, this, &desc);
	//errCode = SSOpen(url, &stream_handle_, _StreamCallback2, NULL, codeID);
	//if (errCode != GOSUN_SUCCESS)
	//	return errCode;

	GxxGmObserver ob;
	GxxGmStreamRecevicer recevicer(&ob);
	errCode = recevicer.OpenURL(url);
	if (errCode != 0)
		return errCode;

	recevicer.Play();

	while (true)
	{
		Sleep(10000);
	}

	return 0;
}

