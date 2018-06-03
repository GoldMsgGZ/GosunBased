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

bool GxxGmPlayer::IsRealMode()
{
	return is_real_;
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
	if (is_real_)
		return -6003;

	return ((GxxGmPlaySDK*)play_sdk_)->Pause();
}

int GxxGmPlayer::Resume()
{
	if (is_real_)
		return -6003;

	return ((GxxGmPlaySDK*)play_sdk_)->Resume();
}

int GxxGmPlayer::Stop()
{
	return ((GxxGmPlaySDK*)play_sdk_)->Stop();
}

int GxxGmPlayer::OpenAudio()
{
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_PlaySound((GSMediaPlayHandle)this->gxx_media_player_handle_);
	if (err != EnumGSMediaPlayerErrCode::GSMEDIAPLAYER_CODE_SUCCESS)
	{
		GxxGmPlayBase::DebugStringOutput("������ʧ�ܣ������룺%d\n", err);
		return err;
	}

	GxxGmPlayBase::DebugStringOutput("�������ɹ���\n");
	return 0;
}

int GxxGmPlayer::GetVolume()
{
	int volume = 0;
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_GetVolumn((GSMediaPlayHandle)this->gxx_media_player_handle_, &volume);
	if (err != EnumGSMediaPlayerErrCode::GSMEDIAPLAYER_CODE_SUCCESS)
	{
		GxxGmPlayBase::DebugStringOutput("��ȡ����ʧ�ܣ������룺%d\n", err);
		return -1;
	}

	GxxGmPlayBase::DebugStringOutput("��ȡ�����ɹ�������Ϊ��%d\n", volume);
	return volume;
}

int GxxGmPlayer::SetVolume(int volume)
{
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_SetVolumn((GSMediaPlayHandle)this->gxx_media_player_handle_, volume);
	if (err != EnumGSMediaPlayerErrCode::GSMEDIAPLAYER_CODE_SUCCESS)
	{
		GxxGmPlayBase::DebugStringOutput("��������ʧ�ܣ������룺%d\n", err);
		return err;
	}

	GxxGmPlayBase::DebugStringOutput("���������ɹ�������Ϊ��%d\n", volume);
	return err;
}

int GxxGmPlayer::CloseAudio()
{
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_StopSound((GSMediaPlayHandle)this->gxx_media_player_handle_);
	if (err != EnumGSMediaPlayerErrCode::GSMEDIAPLAYER_CODE_SUCCESS)
	{
		GxxGmPlayBase::DebugStringOutput("�ر�����ʧ�ܣ������룺%d\n", err);
		return err;
	}

	GxxGmPlayBase::DebugStringOutput("�ر������ɹ���\n");
	return err;
}

void GxxGmPlayer::Close()
{
	((GxxGmPlaySDK*)play_sdk_)->Close();
}

int GxxGmPlayer::CapturePicture(const char *save_path, int img_type)
{
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_CapturePicture((GSMediaPlayHandle)this->gxx_media_player_handle_, save_path, img_type);
	return err;
}

int GxxGmPlayer::Fast()
{
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_Fast((GSMediaPlayHandle)this->gxx_media_player_handle_);
	return err;
}

int GxxGmPlayer::Slow()
{
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_Slow((GSMediaPlayHandle)this->gxx_media_player_handle_);
	return err;
}

int GxxGmPlayer::SetPlaySpeed(double speed)
{
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_SetPlaySpeed((GSMediaPlayHandle)this->gxx_media_player_handle_, speed);
	return err;
}

int GxxGmPlayer::Next()
{
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_Next((GSMediaPlayHandle)this->gxx_media_player_handle_);
	return err;
}

int GxxGmPlayer::Back()
{
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_Back((GSMediaPlayHandle)this->gxx_media_player_handle_);
	return err;
}

int GxxGmPlayer::SetPlayPos(UInt64 pulTimeStamp)
{
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_SetPlayedPos((GSMediaPlayHandle)this->gxx_media_player_handle_, pulTimeStamp, true);
	return err;
}

int GxxGmPlayer::ClearPlayBuffer()
{
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_ClearPlayBuffer((GSMediaPlayHandle)this->gxx_media_player_handle_);
	return err;
}

int GxxGmPlayer::RefreshView()
{
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_RefreshView((GSMediaPlayHandle)this->gxx_media_player_handle_);
	return err;
}


//////////////////////////////////////////////////////////////////////////
//
//

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
		GxxGmPlayBase::DebugStringOutput("�򿪲������ʧ�ܣ������룺%d\n", err);
	}

	if (mode == EnumGSMediaPlayMode::GSPLAYMODE_RECORD)
	{
		//// ��װ���Żص�
		//err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_SetBufferEmptyCallback((GSMediaPlayHandle)this->gxx_media_player_handle_, GxxGmPlayer::_FuncOnBufferEmptyCB, this);
		//if (err != GSMEDIAPLAYER_CODE_SUCCESS)
		//{
		//	GxxGmPlayBase::DebugStringOutput("��װ������ɻص�ʧ�ܣ������룺%d\n", err);
		//}
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