#include "GxxGmPlayer.h"
#include "GxxGmPlaySDK.h"

GxxGmPlayer::GxxGmPlayer()
: screen_window_(NULL)
, gxx_media_player_handle_(0)
, play_sdk_(new GxxGmPlaySDK(this))
, is_real_(true)
{

}

GxxGmPlayer::~GxxGmPlayer()
{
	screen_window_ = NULL;
	if (play_sdk_)
		delete play_sdk_;
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
	// 将参数组织为渲染所需要的数据结构
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

	// 打开播放器
	EnumGSMediaPlayerErrCode err = GSMediaPlayer_Open(mode, media_desc, (Int32)this->screen_window_, (GSMediaPlayHandle*)&this->gxx_media_player_handle_);
	if (err != GSMEDIAPLAYER_CODE_SUCCESS)
	{
		// 调试输出相关信息
	}

	// 播放
	err = GSMediaPlayer_Play((GSMediaPlayHandle)this->gxx_media_player_handle_);
	if (err != GSMEDIAPLAYER_CODE_SUCCESS)
	{
		// 调试输出相关信息
	}
}

void GxxGmPlayer::MediaFrameNotifer(StruGSMediaFrameData *media_frame_data)
{
	// 收到帧数据后，判断是不是视频帧，如果是，则补全视频宽高
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
	// 首先将帧数据复制一份
	AVFrame *av_frame = av_frame_alloc();
	av_frame_copy(av_frame, data);

	// 接下来将帧数据转为图像，最后渲染到播放窗口里
}