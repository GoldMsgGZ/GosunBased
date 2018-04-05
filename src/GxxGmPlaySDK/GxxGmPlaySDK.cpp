#include "GxxGmPlaySDK.h"
#include "GxxGmGspImp.h"
#include "GxxGmRtspImp.h"
#include "GxxGmHttpImp.h"
#include <iostream>
#include <Windows.h>

#define GSP_PROTOCOL	"gsp://"
#define RTSP_PROTOCOL	"rtsp://"
#define HTTP_PROTOCOL	"http://"

#define PROTOCOL_TYPE_UNKNOWN	0
#define PROTOCOL_TYPE_GSP		1
#define PROTOCOL_TYPE_RTSP		2
#define PROTOCOL_TYPE_HTTP		3

GxxGmPlaySDK::GxxGmPlaySDK(GxxGmPlayerNotifer *notifer)
: gsp_(new GxxGmGspImp(this))
, rtsp_(new GxxGmRtspImp(this))
, http_(new GxxGmHttpImp(this))
, protocol_type_(PROTOCOL_TYPE_UNKNOWN)
, notifer_(notifer)
{

}

GxxGmPlaySDK::~GxxGmPlaySDK()
{
	delete gsp_;
	gsp_ = NULL;

	delete rtsp_;
	rtsp_ = NULL;

	protocol_type_ = PROTOCOL_TYPE_UNKNOWN;
}

int GxxGmPlaySDK::Open(const char *url, bool is_real)
{
	int errCode = 0;

	// 简单粗暴，直接根据协议头判断是使用gsp对象处理还是rtsp对象处理
	if (_memicmp(url, GSP_PROTOCOL, strlen(GSP_PROTOCOL)) == 0)
	{
		protocol_type_ = PROTOCOL_TYPE_GSP;
		
		errCode = gsp_->Open(url);
		if (errCode == 0)
			errCode = gsp_->Play();
	}
	else if (_memicmp(url, RTSP_PROTOCOL, strlen(RTSP_PROTOCOL)) == 0)
	{
		protocol_type_ = PROTOCOL_TYPE_RTSP;
		
		errCode = rtsp_->Open(url);
	}
	else if (_memicmp(url, HTTP_PROTOCOL, strlen(HTTP_PROTOCOL)) == 0)
	{
		protocol_type_ = PROTOCOL_TYPE_HTTP;

		errCode = http_->Open(url);
		if (errCode == 0)
			errCode = http_->Play();
	}
	else
	{
		// 未知协议
	}

	return errCode;
}

int GxxGmPlaySDK::Play()
{
	int errCode = 0;

	switch (protocol_type_)
	{
	case PROTOCOL_TYPE_GSP:
		errCode = gsp_->Play();
		break;
	case PROTOCOL_TYPE_RTSP:
		errCode = rtsp_->Play();
		break;
	case PROTOCOL_TYPE_HTTP:
		errCode = http_->Play();
		break;
	default:
		errCode = -6002;
		break;
	}

	return errCode;
}

int GxxGmPlaySDK::Pause()
{
	int errCode = 0;

	switch (protocol_type_)
	{
	case PROTOCOL_TYPE_GSP:
		errCode = gsp_->Pause();
		break;
	case PROTOCOL_TYPE_RTSP:
		errCode = rtsp_->Pause();
		break;
	case PROTOCOL_TYPE_HTTP:
		errCode = http_->Pause();
		break;
	default:
		errCode = -6002;
		break;
	}

	return errCode;
}

int GxxGmPlaySDK::Stop()
{
	int errCode = 0;

	switch (protocol_type_)
	{
	case PROTOCOL_TYPE_GSP:
		errCode = gsp_->Stop();
		break;
	case PROTOCOL_TYPE_RTSP:
		errCode = rtsp_->Stop();
		break;
	case PROTOCOL_TYPE_HTTP:
		errCode = http_->Stop();
		break;
	default:
		errCode = -6002;
		break;
	}

	return errCode;
}

void GxxGmPlaySDK::Close()
{
	switch (protocol_type_)
	{
	case PROTOCOL_TYPE_GSP:
		gsp_->Close();
		break;
	case PROTOCOL_TYPE_RTSP:
		rtsp_->Close();
		break;
	case PROTOCOL_TYPE_HTTP:
		http_->Close();
		break;
	default:
		break;
	}
}

void GxxGmPlaySDK::StreamParamNotifer(UInt32 eVideoCode, UInt32 eAudioCode, UInt32 unSampleRate, UInt32 unBits, UInt32 unChannels, Int32 nRefFrameRate, Int32 nEnableTimeCaculate)
{
	// 继续往上层传
	notifer_->StreamParamNotifer(eVideoCode, eAudioCode, unSampleRate, unBits, unChannels, nRefFrameRate, nEnableTimeCaculate);
}

void GxxGmPlaySDK::StreamParamNotiferEx(AVCodecContext *video_codec_context, AVCodecContext *audio_codec_context)
{
	notifer_->StreamParamNotiferEx(video_codec_context, audio_codec_context);
}

void GxxGmPlaySDK::MediaFrameNotifer(StruGSMediaFrameData *media_frame_data)
{
	notifer_->MediaFrameNotifer(media_frame_data);
}

void GxxGmPlaySDK::MediaFrameNotiferEx(AVMediaType type, AVFrame *data)
{
	notifer_->MediaFrameNotiferEx(type, data);
}