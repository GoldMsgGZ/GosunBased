#include <iostream>
#include "GxxGmRtspImp.h"
#include "GsRtspClient.h"

void StateChangedCallback(RtspClientState state, void* clientData)
{
	int errCode = 0;

	GxxGmRtspImp *rtsp_client = (GxxGmRtspImp *)clientData;

	RtspRequestInfo reqInfo;
	rtsp_client->rtsp_client_->GetRtspRequestInfo(&reqInfo);

	// 状态改变回调
	switch (state)
	{
	case UnAuthorized:
		OutputDebugStringA("UnAuthorized\n");
		break;
	case DescribeError:
		OutputDebugStringA("DescribeError\n");
		break;
	case SetupError:
		OutputDebugStringA("SetupError\n");
		break;
	case PlayError:
		OutputDebugStringA("PlayError\n");
		break;
	case Ready:
		OutputDebugStringA("Ready\n");
		{
			// 只有当返回的state为Ready时才能后续对媒体源请求的操作
			// 只有当获取媒体源描述信息成功返回返回,对媒体源请求的操作才能成功，否则所有的操作请求都无效
			bool ret = rtsp_client->rtsp_client_->GetMediaSourceDescription(&rtsp_client->source_mux_description_);

			// 获取媒体源描述信息
			if (ret)
			{
				errCode = rtsp_client->Play();
				if (errCode == 0)
					printf("Play Success\r\n");
				else
					printf("Play Failed\r\n");
			}
		}
		break;
	case Playing:
		OutputDebugStringA("Playing\n");
		break;
	case Pause:
		OutputDebugStringA("Pause\n");
		break;
	case ServerTerminated:
		OutputDebugStringA("ServerTerminated\n");
		break;
	case PlayEnd:
		OutputDebugStringA("PlayEnd\n");
		break;
	case StreamTimeout:
		OutputDebugStringA("StreamTimeout\n");
		break;
	case ClientClosed:
		OutputDebugStringA("ClientClosed\n");
		break;
	case ServerRefused:
		OutputDebugStringA("ServerRefused\n");
		break;
	case OnvifUploadUnsupport:
		OutputDebugStringA("OnvifUploadUnsupport\n");
		break;
	default:
		break;
	}

	// 处理相关信息后调用回调，向上层传递状态信息
	rtsp_client->rtsp_client_state_ = (int)state;
}

void DataReceivedCallback(StruGSFrameDataEx* frameHeader, void* clientData)
{
	GxxGmRtspImp *rtsp_client = (GxxGmRtspImp *)clientData;
	char *pFrame = NULL;

	// 调用回调，传到上层，最后应该会扔到播放库里面
	char msg[4096] = {0};
	sprintf_s(msg, 4096, "编码类型：%d\tPTS:%d\t数据域长度:%d\t数据偏移:%d\n",
		frameHeader->FrameCodecType, frameHeader->Duration,
		frameHeader->FrameHeader.iLenght, frameHeader->FrameDataOffset);
	OutputDebugStringA(msg);

	StruGSMediaFrameData frame_data;
	frame_data.MediaType = (EnumGSMediaType)frameHeader->FrameHeader.eMediaType;
	frame_data.CodecType = frameHeader->FrameCodecType;
	frame_data.PresentationTimestamp = frameHeader->FrameHeader.iTimeStamp;

	switch (frame_data.MediaType)
	{
	case EnumGSMediaType::GS_MEDIA_TYPE_VIDEO:
		frame_data.VideoFrameInfo.Width = 0;	// 这里应该填写播放窗口的宽度
		frame_data.VideoFrameInfo.Height = 0;	// 这里应该填写播放窗口的高度
		frame_data.VideoFrameInfo.IsKeyFrame = frameHeader->FrameHeader.bKey;
		frame_data.VideoFrameInfo.FrameLength[0] = frameHeader->FrameHeader.iLenght;

		pFrame = new char[frameHeader->FrameHeader.iLenght];
		memcpy(pFrame, (char *)frameHeader->FrameDataBuffer, frameHeader->FrameHeader.iLenght);
		frame_data.VideoFrameInfo.FrameBuffer[0] = pFrame;
		break;
	case EnumGSMediaType::GS_MEDIA_TYPE_AUDIO:
		break;
	default:
		break;
	}

	// 往上发送
	rtsp_client->notifer_->MediaFrameNotifer(&frame_data);

	if (pFrame != NULL)
	{
		delete [] pFrame;
		pFrame = NULL;
	}
}

void ResponseReceivedCallback(StruRtspResponse* response, void* clientData)
{
	GxxGmRtspImp *rtsp_client = (GxxGmRtspImp *)clientData;

	switch (response->CmdCode)
	{
	case RTSPC_CMD_OPEN:
		OutputDebugStringA("RTSPC_CMD_OPEN\n");
		break;
	case RTSPC_CMD_PLAY:
		OutputDebugStringA("RTSPC_CMD_PLAY\n");
		break;
	case RTSPC_CMD_PAUSE:
		OutputDebugStringA("RTSPC_CMD_PAUSE\n");
		break;
	case RTSPC_CMD_TEARDOWN:
		OutputDebugStringA("RTSPC_CMD_TEARDOWN\n");
		break;
	default:
		break;
	}

	// 调用回调，传到上层
}

GxxGmRtspImp::GxxGmRtspImp(GxxGmPlaySDKNotifer *notifer)
: rtsp_client_(NULL)
, rtsp_client_state_(Unknow)
, notifer_(notifer)
{

}

GxxGmRtspImp::~GxxGmRtspImp()
{
	if (rtsp_client_ != NULL)
		delete rtsp_client_;
}

int GxxGmRtspImp::Open(const char *url)
{
	int errCode = 0;

	// 组织请求信息
	// 至于用户名密码如何提取，这里暂时没考虑
	RtspRequestInfo req_info;
	strcpy_s(req_info.RequestUrl, GSRTSP_NAME_MAX_LENGTH, url);
	req_info.ConnectMode = RtspConnectMode::RtpOverRtsp;

	// 创建客户端对象，注册回调
	rtsp_client_ = new GSRtspClient(req_info);
	rtsp_client_->SetStateChangedCallback(StateChangedCallback, this);
	rtsp_client_->SetMediaDataReceivedCallback(DataReceivedCallback, this);
	rtsp_client_->SetResponseReceivedCallback(ResponseReceivedCallback, this);

	if (rtsp_client_->Open())
		return 0;
	else
		return -1;
}

int GxxGmRtspImp::Play()
{
	// 调用这个接口的时候，实际上已经拿到流相关的参数了
	// 这里其实应该把媒体参数回调给上面的SDK
	UInt32 eVideoCode = GS_CODEID_NONE;
	UInt32 eAudioCode = GS_CODEID_NONE;
	UInt32 unSampleRate = 0;
	UInt32 unBits = 0;
	UInt32 unChannels = 0;
	Int32 nRefFrameRate = 0;
	Int32 nEnableTimeCaculate = 0;

	for (int index = 0; index < source_mux_description_.TotalSubMediaNums; ++index)
	{
#ifdef _StruGSRtspMediaDescri
		StruGSRtspMediaDescri des = source_mux_description_.SubRtspMediaDescriptions[index];
		if (des.MediaType == EnumGSMediaType::GS_MEDIA_TYPE_VIDEO)
		{
			eVideoCode = des.MediaDescri.struVideo.eCodeID;
			nRefFrameRate = des.MediaDescri.struVideo.iFrameRate;
		}
		else if (des.MediaType == EnumGSMediaType::GS_MEDIA_TYPE_AUDIO)
		{
			eAudioCode = des.MediaDescri.struAudio.eCodeID;
			unSampleRate = des.MediaDescri.struAudio.iSample;
			unBits = des.MediaDescri.struAudio.iBits;
			unChannels = des.MediaDescri.struAudio.iChannels;
		}
#else
		StruGSMediaDescri des = source_mux_description_.SubMediaDescriptions[index];
		if (des.eMediaType == EnumGSMediaType::GS_MEDIA_TYPE_VIDEO)
		{
			eVideoCode = des.unDescri.struVideo.eCodeID;
			nRefFrameRate = des.unDescri.struVideo.iFrameRate;
		}
		else if (des.eMediaType == EnumGSMediaType::GS_MEDIA_TYPE_AUDIO)
		{
			eAudioCode = des.unDescri.struAudio.eCodeID;
			unSampleRate = des.unDescri.struAudio.iSample;
			unBits = des.unDescri.struAudio.iBits;
			unChannels = des.unDescri.struAudio.iChannels;
		}
#endif
		
	}

	notifer_->StreamParamNotifer(eVideoCode, eAudioCode, unSampleRate, unBits, unChannels, nRefFrameRate, nEnableTimeCaculate);

	if (rtsp_client_->Play())
		return 0;
	else
		return -1;
}

int GxxGmRtspImp::Pause()
{
	if (rtsp_client_->Pause())
		return 0;
	else
		return -1;
}

int GxxGmRtspImp::Stop()
{
	int errCode = 0;

	rtsp_client_->TearDown();

	return errCode;
}

void GxxGmRtspImp::Close()
{

}