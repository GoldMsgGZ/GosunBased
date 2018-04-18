#include "GxxGmGspImp.h"
#include "GSTypes.h"
#include "GSMediaPlayerDef.h"
#include "StreamServerSDK.h"


void CALLBACK _ExceptionCallback(GOSUN_HANDLE pHandle, GOSUN_ENUM_EXCEPTION_TYPE type, void* pExceptionInfo, void* userData)
{
	GxxGmGspImp *gsp_ = (GxxGmGspImp *)userData;

	switch (type)
	{
	case SDK_SERV_DISCONNECT:
		gsp_->notifer_->PlayerStateNotifer();
		break;
	case SDK_STREAM_CLOSED:
		break;
	default:
		break;
	}
}

void CALLBACK _StreamCallback(long lHandle, FRAME_HEADER header, char *pData, long nSize, void* userData)
{
	GxxGmGspImp *gsp_ = (GxxGmGspImp *)userData;

	if (gsp_->is_paused_)
		return ;

	StruGSMediaFrameData gs_media_frame_data;
	ZeroMemory(&gs_media_frame_data, sizeof(StruGSMediaFrameData));
	gs_media_frame_data.MediaType = (EnumGSMediaType)header.type;
	
	if (gs_media_frame_data.MediaType == EnumGSMediaType::GS_MEDIA_TYPE_VIDEO)
	{
		gs_media_frame_data.CodecType = (EnumGSCodeID)header.enStremCodeId[0];
		gs_media_frame_data.VideoFrameInfo.Width = 0;
		gs_media_frame_data.VideoFrameInfo.Height = 0;
		gs_media_frame_data.VideoFrameInfo.FrameLength[0] = nSize;
		gs_media_frame_data.VideoFrameInfo.FrameBuffer[0] = pData;
	}
	else if (gs_media_frame_data.MediaType == EnumGSMediaType::GS_MEDIA_TYPE_AUDIO)
	{
		gs_media_frame_data.CodecType = (EnumGSCodeID)header.enStremCodeId[1];
		gs_media_frame_data.AudioFrameInfo.FrameBuffer = pData;
		gs_media_frame_data.AudioFrameInfo.FrameLength = nSize;
	}

	// 向上报
	gsp_->notifer_->MediaFrameNotifer(&gs_media_frame_data);
	
}

GxxGmGspImp::GxxGmGspImp(GxxGmPlaySDKNotifer *notifer)
: notifer_(notifer)
, is_paused_(false)
{
	SSInit();
}

GxxGmGspImp::~GxxGmGspImp()
{
	SSUninit();
}

int GxxGmGspImp::Open(const char *url)
{
	int errCode = 0;

	if (is_paused_)
	{
		is_paused_ = false;
	}
	else
	{
		SDK_StruMediaMuxDesc media_desc;
		errCode = SSOpenEx(url, (GOSUN_HANDLE*)&stream_handle_, _StreamCallback, this, &media_desc, false);
		if (errCode == GOSUN_SUCCESS)
		{
			// 将解复用后的参数信息组织好后上送
			UInt32 eVideoCode = GS_CODEID_NONE;
			UInt32 eAudioCode = GS_CODEID_NONE;
			UInt32 unSampleRate = 0;
			UInt32 unBits = 0;
			UInt32 unChannels = 0;
			Int32 nRefFrameRate = 0;
			Int32 nEnableTimeCaculate = 0;

			for (int index = 0; index < media_desc.iMediaNum; ++index)
			{
				SDK_StruMediaDesc des = media_desc.desc[index];
				if (des.mediaType == SDK_EnumMediaType::MEDIA_VIDEO)
				{
					//
					if (des.mediaDesc.videoDesc.eCodeID == GS_CODEID_GS_GUOMAI_VIPC)
						eVideoCode = GS_CODEID_GS_VIPC;
					else
						eVideoCode = des.mediaDesc.videoDesc.eCodeID;
					nRefFrameRate = des.mediaDesc.videoDesc.iFrameRate;
				}
				else if (des.mediaType == SDK_EnumMediaType::MEDIA_AUDIO)
				{
					//
					eAudioCode = des.mediaDesc.audioDesc.eCodeID;
					unSampleRate = des.mediaDesc.audioDesc.iSample;
					unBits = des.mediaDesc.audioDesc.iBits;
					unChannels = des.mediaDesc.audioDesc.iChannels;
				}
			}

			notifer_->StreamParamNotifer(eVideoCode, eAudioCode, unSampleRate, unBits, unChannels, nRefFrameRate, nEnableTimeCaculate);
		}
	}

	return errCode;
}

int GxxGmGspImp::Play()
{
	int errCode = 0;

	if (is_paused_)
		is_paused_ = false;
	else
		errCode = SSPlay((GOSUN_HANDLE)stream_handle_);

	return errCode;
}

int GxxGmGspImp::Pause()
{
	int errCode = 0;

	// 这里两种方案，一种是添加标记，在帧回调里面控制发送状态
	// 一种是直接关闭
	//errCode = SSClose((GOSUN_HANDLE)stream_handle_);
	is_paused_ = true;

	return errCode;
}

int GxxGmGspImp::Stop()
{
	int errCode = 0;

	errCode = SSClose((GOSUN_HANDLE)stream_handle_);
	is_paused_ = false;

	return errCode;
}

void GxxGmGspImp::Close()
{

}