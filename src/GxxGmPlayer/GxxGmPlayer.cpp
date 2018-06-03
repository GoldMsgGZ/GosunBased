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
		GxxGmPlayBase::DebugStringOutput("打开声音失败！错误码：%d\n", err);
		return err;
	}

	GxxGmPlayBase::DebugStringOutput("打开声音成功！\n");
	return 0;
}

int GxxGmPlayer::GetVolume()
{
	int volume = 0;
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_GetVolumn((GSMediaPlayHandle)this->gxx_media_player_handle_, &volume);
	if (err != EnumGSMediaPlayerErrCode::GSMEDIAPLAYER_CODE_SUCCESS)
	{
		GxxGmPlayBase::DebugStringOutput("获取音量失败！错误码：%d\n", err);
		return -1;
	}

	GxxGmPlayBase::DebugStringOutput("获取音量成功！音量为：%d\n", volume);
	return volume;
}

int GxxGmPlayer::SetVolume(int volume)
{
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_SetVolumn((GSMediaPlayHandle)this->gxx_media_player_handle_, volume);
	if (err != EnumGSMediaPlayerErrCode::GSMEDIAPLAYER_CODE_SUCCESS)
	{
		GxxGmPlayBase::DebugStringOutput("设置音量失败！错误码：%d\n", err);
		return err;
	}

	GxxGmPlayBase::DebugStringOutput("设置音量成功！音量为：%d\n", volume);
	return err;
}

int GxxGmPlayer::CloseAudio()
{
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_StopSound((GSMediaPlayHandle)this->gxx_media_player_handle_);
	if (err != EnumGSMediaPlayerErrCode::GSMEDIAPLAYER_CODE_SUCCESS)
	{
		GxxGmPlayBase::DebugStringOutput("关闭声音失败！错误码：%d\n", err);
		return err;
	}

	GxxGmPlayBase::DebugStringOutput("关闭声音成功！\n");
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
	EnumGSMediaPlayerErrCode err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_Open(mode, media_desc, (Int32)this->screen_window_, (GSMediaPlayHandle*)&this->gxx_media_player_handle_);
	if (err != GSMEDIAPLAYER_CODE_SUCCESS)
	{
		// 调试输出相关信息
		GxxGmPlayBase::DebugStringOutput("打开播放组件失败！错误码：%d\n", err);
	}

	if (mode == EnumGSMediaPlayMode::GSPLAYMODE_RECORD)
	{
		//// 安装播放回调
		//err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_SetBufferEmptyCallback((GSMediaPlayHandle)this->gxx_media_player_handle_, GxxGmPlayer::_FuncOnBufferEmptyCB, this);
		//if (err != GSMEDIAPLAYER_CODE_SUCCESS)
		//{
		//	GxxGmPlayBase::DebugStringOutput("安装播放完成回调失败！错误码：%d\n", err);
		//}
	}

	// 播放
	err = gs_mediaplayer_stub_->ptr_GSMediaPlayer_Play((GSMediaPlayHandle)this->gxx_media_player_handle_);
	if (err != GSMEDIAPLAYER_CODE_SUCCESS)
	{
		// 调试输出相关信息
	}
}

void GxxGmPlayer::StreamParamNotiferEx(AVCodecContext *video_codec_context, AVCodecContext *audio_codec_context)
{
	//// 先初始化SDL2渲染环境
	//int errCode = sdl2_player_->Initialize(screen_window_);
	//if (errCode != 0)
	//{
	//	// 初始化失败
	//	GxxGmPlayBase::DebugStringOutput("初始化SDL2渲染播放环境失败！");
	//}

	//// 上报视音频解码上下文
	//errCode = sdl2_player_->SetMediaInfo(video_codec_context, audio_codec_context);
	//if (errCode != 0)
	//{
	//	// 初始化失败
	//}

	//sdl2_player_->Play();
}

void GxxGmPlayer::MediaFrameNotifer(/*StruGSMediaFrameData*/void *media_frame_data)
{
	StruGSMediaFrameData *data = (StruGSMediaFrameData*)media_frame_data;
	// 收到帧数据后，判断是不是视频帧，如果是，则补全视频宽高
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
	//// 首先将帧数据复制一份
	//AVFrame *av_frame = av_frame_alloc();
	//av_frame_copy(av_frame, data);

	//// 接下来将帧数据转为图像，最后渲染到播放窗口里
	//sdl2_player_->InputFrameData(type, av_frame);

	//av_frame_free(&av_frame);
}

void GxxGmPlayer::PlayerStateNotifer(enum GxxGmPlayState state)
{
	// 收到状态后执行相关操作
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
		// 播放完成了，我们调用停止接口
		Stop();
		break;
	case GxxGmStateStreamTimeOut:
		// 流超时了，我们停止播放
		Stop();
		break;
	case GxxGmStateClientClosed:
		// 客户端主动关闭的，我们停止播放
		Stop();
		break;
	case GxxGmStateServerRefused:
		// 服务器主动拒绝了，我们停止播放
		Stop();
		break;
	default:
		break;
	}
}