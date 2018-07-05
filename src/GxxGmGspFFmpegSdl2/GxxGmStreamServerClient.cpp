#include "stdafx.h"
#include "GxxGmStreamServerClient.h"
#include "StreamServerSDK.h"
#include "PSFormat.h"

//////////////////////////////////////////////////////////////////////////
// 前置声明
void CALLBACK _StreamCallback(long lHandle, FRAME_HEADER header, char *pData, long nSize, void* userData);
void CALLBACK _ESFrameReceivedCallBack(GS_MpegPSHandle handle, StruESFrameInfo const *stESFrameInfo, StruPSFrameInfo const* stPSFrameInfo, void* pUserData);


GxxGmStreamServerClient::GxxGmStreamServerClient(GxxGmStreamObserver *ob)
: ss_handle_(NULL)
, stream_handle_(NULL)
, ps2es_handle_(NULL)
, ob_(ob)
{
	SSInit();
}

GxxGmStreamServerClient::~GxxGmStreamServerClient()
{
	SSUninit();
}

int GxxGmStreamServerClient::Login(const char *ip, unsigned short port)
{
	GOSUN_SERVER_INFO info;
	ZeroMemory(&info, sizeof(GOSUN_SERVER_INFO));
	strcpy(info.servIP, ip);
	strcpy(info.username, "admin");
	strcpy(info.password, "admin");
	info.servPort = port;

	int errCode = SSLogin(&ss_handle_, info);
	
	return errCode;
}

void GxxGmStreamServerClient::Logout()
{
	SSLogout(ss_handle_);
	ss_handle_ = NULL;
}

int GxxGmStreamServerClient::Play(const char *id)
{
	SS_DEVICE_INFO devinfo;
	ZeroMemory(&devinfo, sizeof(SS_DEVICE_INFO));
	strcpy(devinfo.chanCodeid, id); 
	strcpy(devinfo.devCodeid, id);
	devinfo.channel = 1;
	devinfo.modelID = SDK_DEV_GXX;
	devinfo.streamType = 1;
	strcpy_s(devinfo.username, GOSUN_USER_INFO_LEN, "admin");
	strcpy_s(devinfo.password, GOSUN_USER_INFO_LEN, "admin");

	char url[512] = {0};
	int errCode = SSGetURL(ss_handle_, url, 512, devinfo);
	if (errCode != GOSUN_SUCCESS)
		return errCode;

	EnumStreamCodeID codeID[2];
	errCode = SSOpen(url, &stream_handle_, _StreamCallback, this, codeID);
	if (errCode != GOSUN_SUCCESS)
		return errCode;

	EnumGS_MPEGPS_RetCode ret = GS_MPEGPS_CreatePS2ESHandle(&ps2es_handle_);
	if (ret == GS_MPEGPS_Ret_Success)
	{
		// 成功了，注册回调
		ret = GS_MPEGPS_SetESFrameReceivedCallback(ps2es_handle_, _ESFrameReceivedCallBack, this);
	}

	return ret;
}

void GxxGmStreamServerClient::Stop()
{
	SSClose(stream_handle_);
	stream_handle_ = NULL;
}

void CALLBACK _StreamCallback(long lHandle, FRAME_HEADER header, char *pData, long nSize, void* userData)
{
	GxxGmStreamServerClient *client = (GxxGmStreamServerClient*)userData;

	GS_MPEGPS_InputPSData(client->ps2es_handle_, (BYTE*)pData, (UInt32)nSize);
}

void CALLBACK _ESFrameReceivedCallBack(GS_MpegPSHandle handle, StruESFrameInfo const *stESFrameInfo, StruPSFrameInfo const* stPSFrameInfo, void* pUserData)
{
	GxxGmStreamServerClient *client = (GxxGmStreamServerClient*)pUserData;

	EnumGSPSCodecType es_codec_id = stESFrameInfo->eCodec;
	EnumGSMediaType es_media_type = stESFrameInfo->eType;
	unsigned __int64 pts = stESFrameInfo->nPTS;

	struct EXTRA_INFO extra_info;
	extra_info.type = 
	
	// 将数据包扔给观察者
	if (client->ob_)
	{
		client->ob_->MediaData(stESFrameInfo->pBuffer, stESFrameInfo->nBufLen, )
	}
}