#include <iostream>
#include "GxxGmRtspImp.h"
#include "GsRtspClient.h"

void StateChangedCallback(RtspClientState state, void* clientData)
{
	int errCode = 0;

	GxxGmRtspImp *rtsp_client = (GxxGmRtspImp *)clientData;

	RtspRequestInfo reqInfo;
	rtsp_client->rtsp_client_->GetRtspRequestInfo(&reqInfo);

	// ״̬�ı�ص�
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
			// ֻ�е����ص�stateΪReadyʱ���ܺ�����ý��Դ����Ĳ���
			// ֻ�е���ȡý��Դ������Ϣ�ɹ����ط���,��ý��Դ����Ĳ������ܳɹ����������еĲ���������Ч
			bool ret = rtsp_client->rtsp_client_->GetMediaSourceDescription(&rtsp_client->source_mux_description_);

			// ��ȡý��Դ������Ϣ
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

	// ���������Ϣ����ûص������ϲ㴫��״̬��Ϣ
	rtsp_client->rtsp_client_state_ = (int)state;
}

void DataReceivedCallback(StruGSFrameDataEx* frameHeader, void* clientData)
{
	GxxGmRtspImp *rtsp_client = (GxxGmRtspImp *)clientData;
	char *pFrame = NULL;

	// ���ûص��������ϲ㣬���Ӧ�û��ӵ����ſ�����
	char msg[4096] = {0};
	sprintf_s(msg, 4096, "�������ͣ�%d\tPTS:%d\t�����򳤶�:%d\t����ƫ��:%d\n",
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
		frame_data.VideoFrameInfo.Width = 0;	// ����Ӧ����д���Ŵ��ڵĿ��
		frame_data.VideoFrameInfo.Height = 0;	// ����Ӧ����д���Ŵ��ڵĸ߶�
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

	// ���Ϸ���
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

	// ���ûص��������ϲ�
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

	// ��֯������Ϣ
	// �����û������������ȡ��������ʱû����
	RtspRequestInfo req_info;
	strcpy_s(req_info.RequestUrl, GSRTSP_NAME_MAX_LENGTH, url);
	req_info.ConnectMode = RtspConnectMode::RtpOverRtsp;

	// �����ͻ��˶���ע��ص�
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
	// ��������ӿڵ�ʱ��ʵ�����Ѿ��õ�����صĲ�����
	// ������ʵӦ�ð�ý������ص��������SDK
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