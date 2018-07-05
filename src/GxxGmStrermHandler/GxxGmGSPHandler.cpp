#include "GxxGmGSPHandler.h"



void CALLBACK _StreamCallback(long lHandle, FRAME_HEADER header, char *pData, long nSize, void* userData)
{
	GxxGmGSPHandler *handler = (GxxGmGSPHandler *)userData;

	// ������Ҫ�������������ӿڣ��ڽ���ص��ӿ����
	GS_MPEGPS_InputPSData(handler->GetMpegPsHandle(), (BYTE*)pData, (UInt32)nSize);
}

void CALLBACK _ESFrameReceivedCallBack(GS_MpegPSHandle handle, StruESFrameInfo const *stESFrameInfo, StruPSFrameInfo const* stPSFrameInfo, void* userData)
{
	GxxGmGSPHandler *handler = (GxxGmGSPHandler *)userData;

	// �����ж��Ƿ�����˽⸴�õ���Ϣ
	if (!handler->IsDemuxingOK())
	{
		switch (stESFrameInfo->eType)
		{
		case EnumGSMediaType::GS_MEDIA_TYPE_AUDIO:
			{

			}
			break;
		case EnumGSMediaType::GS_MEDIA_TYPE_VIDEO:
			{

			}
			break;
		default:
			break;
		}
	}

	// �����ж��Ƿ��Ѿ���ɽ⸴���ˣ�����Ѿ���ɣ�����취֪ͨ���ϲ�
}


GxxGmGSPHandler::GxxGmGSPHandler()
: stream_handle_(NULL)
, mpeg_ps_handle_(NULL)
, media_info_total_count_(0)
, collected_media_info_count_(0)
{
	//SSInit();
}

GxxGmGSPHandler::~GxxGmGSPHandler()
{
	//SSUninit();
}

int GxxGmGSPHandler::OpenURL(const char *url)
{
	int errCode = 0;

	SDK_StruMediaMuxDesc desc;
	ZeroMemory(&desc, sizeof(SDK_StruMediaMuxDesc));
	EnumStreamCodeID codeID[2];
	codeID[0] = CODEID_NONE;
	codeID[1] = CODEID_NONE;
	//errCode = SSOpenEx(url, &stream_handle_, _StreamCallback, this, &desc, false);
	errCode = SSOpen(url, &stream_handle_, _StreamCallback, this, codeID, TRAN_RTPLAY, false);
	if (errCode != GOSUN_SUCCESS)
		return errCode;

	media_info_total_count_ = desc.iMediaNum;
	// �����⸴����Ϣ
	for (int index = 0; index < media_info_total_count_; ++index)
	{
		if (desc.desc[index].mediaType == SDK_EnumMediaType::MEDIA_VIDEO)
		{
			SDK_StruVideoDescri d = desc.desc[index].mediaDesc.videoDesc;
			EnumStreamCodeID codec_id = d.eCodeID;
			//TRACE("��Ƶ���⸴�ã���Ƶ���룺%d ֡�ʣ�%d.%d\n", codec_id, d.iFrameRate, d.iFrameRate2);
		}
		else if (desc.desc[index].mediaType == SDK_EnumMediaType::MEDIA_AUDIO)
		{
			SDK_StruAudioDescri a = desc.desc[index].mediaDesc.audioDesc;
			EnumStreamCodeID codec_id = a.eCodeID;
			int bits = a.iBits;
			int channels = a.iChannels;
			int sample_rate = a.iSample;
			//TRACE("��Ƶ���⸴�ã���Ƶ���룺%d ���ʣ�%d ��������%d �����ʣ�%d\n", codec_id, bits, channels, sample_rate);
		}
	}

	EnumGS_MPEGPS_RetCode ret = GS_MPEGPS_CreatePS2ESHandle(&mpeg_ps_handle_);
	if (ret == GS_MPEGPS_Ret_Success)
	{
		// �ɹ��ˣ�ע��ص�
		ret = GS_MPEGPS_SetESFrameReceivedCallback(mpeg_ps_handle_, _ESFrameReceivedCallBack, this);
	}
	else
		errCode = ret;

	// 
	errCode = SSPlay(stream_handle_);

	return errCode;
}

void GxxGmGSPHandler::Close()
{
	SSClose(stream_handle_);
}