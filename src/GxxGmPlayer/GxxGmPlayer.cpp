#include "GxxGmPlayer.h"
#include "GxxGmPlaySDK.h"

GxxGmPlayer::GxxGmPlayer()
: screen_window_(NULL)
, gxx_media_player_handle_(0)
, sdl2_player_(new GxxGmSDL2Player())
, play_sdk_(new GxxGmPlaySDK(this))
, is_real_(true)
{

}

GxxGmPlayer::~GxxGmPlayer()
{
	screen_window_ = NULL;
	if (play_sdk_)
		delete play_sdk_;

	if (sdl2_player_)
		delete sdl2_player_;
}

int GxxGmPlayer::SetScreenWindow(HWND window)
{
	screen_window_ = window;
	return 0;
}

int GxxGmPlayer::Open(const char *url, bool is_real /* = true */)
{
	is_real_ = is_real;
	return play_sdk_->Open(url, is_real);
}

int GxxGmPlayer::Play()
{
	return play_sdk_->Play();
}

int GxxGmPlayer::Pause()
{
	return play_sdk_->Pause();
}

int GxxGmPlayer::Stop()
{
	return play_sdk_->Stop();
}

void GxxGmPlayer::Close()
{
	play_sdk_->Close();
}

void GxxGmPlayer::StreamParamNotifer(UInt32 eVideoCode, UInt32 eAudioCode, UInt32 unSampleRate, UInt32 unBits, UInt32 unChannels, Int32 nRefFrameRate, Int32 nEnableTimeCaculate)
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
	EnumGSMediaPlayerErrCode err = GSMediaPlayer_Open(mode, media_desc, (Int32)this->screen_window_, (GSMediaPlayHandle*)&this->gxx_media_player_handle_);
	if (err != GSMEDIAPLAYER_CODE_SUCCESS)
	{
		// ������������Ϣ
	}

	// ����
	err = GSMediaPlayer_Play((GSMediaPlayHandle)this->gxx_media_player_handle_);
	if (err != GSMEDIAPLAYER_CODE_SUCCESS)
	{
		// ������������Ϣ
	}
}

void GxxGmPlayer::StreamParamNotiferEx(AVCodecContext *video_codec_context, AVCodecContext *audio_codec_context)
{
	// ��ȡ����Ҫ�Ĳ���
	
	// ��Ƶ��ز���
	int video_img_width = video_codec_context->width;
	int video_img_height = video_codec_context->height;
	AVPixelFormat video_img_pixfmt = video_codec_context->pix_fmt;

	// ��Ƶ��ز���
	int audio_channel_layout = audio_codec_context->channel_layout;
	int audio_frame_size = audio_codec_context->frame_size;
	AVSampleFormat audio_sample_fmt = audio_codec_context->sample_fmt;
	int audio_sample_rate = audio_codec_context->sample_rate;

	int errCode = sdl2_player_->Initialize(screen_window_);
	if (errCode != 0)
	{
		// ��ʼ��ʧ��
	}

	errCode = sdl2_player_->SetMediaInfo(video_img_width, video_img_height, video_img_pixfmt,
		audio_channel_layout, audio_frame_size, audio_sample_fmt, audio_sample_rate);
	if (errCode != 0)
	{
		// ��ʼ��ʧ��
	}

	sdl2_player_->Play();
}

void GxxGmPlayer::MediaFrameNotifer(StruGSMediaFrameData *media_frame_data)
{
	// �յ�֡���ݺ��ж��ǲ�����Ƶ֡������ǣ���ȫ��Ƶ���
	if (media_frame_data->MediaType == EnumGSMediaType::GS_MEDIA_TYPE_VIDEO)
	{
		// 
		RECT window_rect;
		GetWindowRect(screen_window_, &window_rect);
		media_frame_data->VideoFrameInfo.Width = window_rect.right - window_rect.left;
		media_frame_data->VideoFrameInfo.Height = window_rect.bottom - window_rect.top;
	}
	else if (media_frame_data->MediaType == EnumGSMediaType::GS_MEDIA_TYPE_AUDIO)
	{
		return ;
	}

	EnumGSMediaPlayerErrCode err = GSMediaPlayer_InputData((GSMediaPlayHandle)this->gxx_media_player_handle_, media_frame_data);

	return ;
}

void GxxGmPlayer::MediaFrameNotiferEx(AVMediaType type, AVFrame *data)
{
	// ���Ƚ�֡���ݸ���һ��
	AVFrame *av_frame = av_frame_alloc();
	av_frame_copy(av_frame, data);

	// ��������֡����תΪͼ�������Ⱦ�����Ŵ�����
	sdl2_player_->InputFrameData(type, av_frame);

	av_frame_free(&av_frame);
}