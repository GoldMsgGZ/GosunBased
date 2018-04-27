#include "GxxGmPlayer.h"
#include "GxxGmPlaySDK.h"
#include "GxxGmPlayBase.h"
#include "GSMediaPlayer.h"
#include "GSMediaPlayer_stub.h"

GxxGmPlayer::GxxGmPlayer()
: screen_window_(NULL)
, gxx_media_player_handle_(0)
//, sdl2_player_(new GxxGmSDL2Player())
, play_sdk_((void*)new GxxGmPlaySDK(this))
, is_real_(true)
, gs_mediaplayer_stub_(new GSMediaPlayer_stub())
{

}

GxxGmPlayer::~GxxGmPlayer()
{
	screen_window_ = NULL;
	if (((GxxGmPlaySDK*)play_sdk_))
		delete ((GxxGmPlaySDK*)play_sdk_);
	play_sdk_ = NULL;

	//if (sdl2_player_)
	//	delete sdl2_player_;
}

int GxxGmPlayer::SetScreenWindow(void* window)
{
	screen_window_ = window;
	
	int errCode = gs_mediaplayer_stub_->Initialize();
	if (errCode != 0)
		return errCode;

	return 0;
}

bool GxxGmPlayer::IsBusy()
{
	return ((GxxGmPlaySDK*)play_sdk_)->IsBusy();
}

int GxxGmPlayer::Open(const char *url, bool is_real /* = true */)
{
	is_real_ = is_real;
	return ((GxxGmPlaySDK*)play_sdk_)->Open(url, is_real);
}

int GxxGmPlayer::Play()
{
	return ((GxxGmPlaySDK*)play_sdk_)->Play();
}

int GxxGmPlayer::Pause()
{
	return ((GxxGmPlaySDK*)play_sdk_)->Pause();
}

int GxxGmPlayer::Stop()
{
	return ((GxxGmPlaySDK*)play_sdk_)->Stop();
}

void GxxGmPlayer::Close()
{
	((GxxGmPlaySDK*)play_sdk_)->Close();
}

void GxxGmPlayer::StreamParamNotifer(unsigned int eVideoCode, unsigned int eAudioCode, unsigned int unSampleRate, unsigned int unBits, unsigned int unChannels, int nRefFrameRate, int nEnableTimeCaculate)
{
	// ��������֯Ϊ��Ⱦ����Ҫ�����ݽṹ
	StruGSMediaDesc media_desc;
	media_desc.eVideoCode = (EnumGSCodeID)eVideoCode;
	media_desc.eAudioCode = (EnumGSCodeID)eAudioCode;
	media_desc.unSampleRate = unSampleRate;
	media_desc.unBits = unBits;
	media_desc.unChannels = unChannels;
	media_desc.nRefFrameRate = nRefFrameRate;
	media_desc.nEnableTimeCaculate = nEnableTimeCaculate;

	EnumGSMediaPlayMode mode = EnumGSMediaPlayMode::GSPLAYMODE_REAL;

	if (is_real_)
		mode = EnumGSMediaPlayMode::GSPLAYMODE_REAL;
	else
		mode = EnumGSMediaPlayMode::GSPLAYMODE_RECORD;

	// �򿪲�����
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_Open(mode, media_desc, (Int32)this->screen_window_, (GSMediaPlayHandle*)&this->gxx_media_player_handle_);
	if (err != GSMEDIAPLAYER_CODE_SUCCESS)
	{
		// ������������Ϣ
	}

	// ����
	err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_Play((GSMediaPlayHandle)this->gxx_media_player_handle_);
	if (err != GSMEDIAPLAYER_CODE_SUCCESS)
	{
		// ������������Ϣ
	}
}

void GxxGmPlayer::StreamParamNotiferEx(AVCodecContext *video_codec_context, AVCodecContext *audio_codec_context)
{
	//// �ȳ�ʼ��SDL2��Ⱦ����
	//int errCode = sdl2_player_->Initialize(screen_window_);
	//if (errCode != 0)
	//{
	//	// ��ʼ��ʧ��
	//	GxxGmPlayBase::DebugStringOutput("��ʼ��SDL2��Ⱦ���Ż���ʧ�ܣ�");
	//}

	//// �ϱ�����Ƶ����������
	//errCode = sdl2_player_->SetMediaInfo(video_codec_context, audio_codec_context);
	//if (errCode != 0)
	//{
	//	// ��ʼ��ʧ��
	//}

	//sdl2_player_->Play();
}

void GxxGmPlayer::MediaFrameNotifer(/*StruGSMediaFrameData*/void *media_frame_data)
{
	StruGSMediaFrameData *data = (StruGSMediaFrameData*)media_frame_data;
	// �յ�֡���ݺ��ж��ǲ�����Ƶ֡������ǣ���ȫ��Ƶ���
	if (data->MediaType == EnumGSMediaType::GS_MEDIA_TYPE_VIDEO)
	{
		// 
		RECT window_rect;
		GetWindowRect(((HWND)screen_window_), &window_rect);
		data->VideoFrameInfo.Width = data->VideoFrameInfo.Width == 0 ? (window_rect.right - window_rect.left) : data->VideoFrameInfo.Width;
		data->VideoFrameInfo.Height = data->VideoFrameInfo.Height == 0 ? (window_rect.bottom - window_rect.top) : data->VideoFrameInfo.Height;
	}
	else if (data->MediaType == EnumGSMediaType::GS_MEDIA_TYPE_AUDIO)
	{
		return ;
	}

	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_InputData((GSMediaPlayHandle)this->gxx_media_player_handle_, data, true);

	return ;
}

void GxxGmPlayer::MediaFrameNotiferEx(AVMediaType type, AVFrame *data)
{
	//// ���Ƚ�֡���ݸ���һ��
	//AVFrame *av_frame = av_frame_alloc();
	//av_frame_copy(av_frame, data);

	//// ��������֡����תΪͼ�������Ⱦ�����Ŵ�����
	//sdl2_player_->InputFrameData(type, av_frame);

	//av_frame_free(&av_frame);
}

void GxxGmPlayer::PlayerStateNotifer(enum GxxGmPlayState state)
{
	// �յ�״̬��ִ����ز���
	switch (state)
	{
	case GxxGmStateReady:
		break;
	case GxxGmStatePlaying:
		break;
	case GxxGmStatePause:
		break;
	case GxxGmStateServerTerminated:
		break;
	case GxxGmStatePlayEnd:
		// ��������ˣ����ǵ���ֹͣ�ӿ�
		Stop();
		break;
	case GxxGmStateStreamTimeOut:
		// ����ʱ�ˣ�����ֹͣ����
		Stop();
		break;
	case GxxGmStateClientClosed:
		// �ͻ��������رյģ�����ֹͣ����
		Stop();
		break;
	case GxxGmStateServerRefused:
		// �����������ܾ��ˣ�����ֹͣ����
		Stop();
		break;
	default:
		break;
	}
}