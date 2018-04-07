#include "GxxGmSDL2Player.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "libavformat\avformat.h"
#include "libavcodec\avcodec.h"
#include "libavutil\avutil.h"
#include "libavutil\imgutils.h"
#include "libswscale\swscale.h"
#ifdef __cplusplus
};
#endif


FrameDataCache::FrameDataCache()
{
	InitializeCriticalSection(&section_);
}

FrameDataCache::~FrameDataCache()
{
	DeleteCriticalSection(&section_);
}

int FrameDataCache::push(AVMediaType type, AVFrame *data)
{
	// �����ڽ�֡����֮ǰ������һ�µ�ǰ�Ѿ��������Ƶ֡������
	// ����ο�ֵ���£�
	// ���ǰ��ջ���15����Ƶ����Ƶ֡��Ϊ30֡������
	// ������ǻ���30 * 15 = 450֡��Ƶ֡
	// ������������е��������ģ����Ǵֱ�һ�㣬ֱ�ӽ���������10��Ҳ�ʹ���Ƶ֡���������໺�治��3���ӵ���Ƶ
	EnterCriticalSection(&section_);

	// ������֡������150֡ʱ������
	while (true)
	{
		int frame_count = frame_queue_.size();
		if (frame_count > 150)
			Sleep(1000);
		else
			break;
	}

	FrameData *framedata = new FrameData;
	framedata->type_ = type;
	framedata->data_ = data;

	frame_queue_.push_back(framedata);

	LeaveCriticalSection(&section_);
	return 0;
}

FrameData* FrameDataCache::pop()
{
	EnterCriticalSection(&section_);

	// �������ж��Ƿ�Ϊ��
	if (frame_queue_.empty())
		return NULL;

	FrameData *data = frame_queue_.front();
	frame_queue_.pop_front();

	LeaveCriticalSection(&section_);
	return data;
}



GxxGmSDL2Player::GxxGmSDL2Player()
: window_(NULL)
, renderer_(NULL)
, texture_(NULL)
, video_frame_yuv_(NULL)
, image_convert_context_(NULL)
{

}

GxxGmSDL2Player::~GxxGmSDL2Player()
{

}

int GxxGmSDL2Player::Initialize(HWND screen)
{
	int errCode = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
	if (errCode != 0)
		return errCode;

	window_ = SDL_CreateWindowFrom(screen);
	if (window_ == NULL)
		return -1;

	renderer_ = SDL_CreateRenderer(window_, -1, 0);
	if (renderer_ == NULL)
		return -2;

	RECT rt;
	GetWindowRect(screen, &rt);
	screen_width_ = rt.right - rt.left;
	screen_height_ = rt.bottom - rt.top;
	texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, screen_width_, screen_height_);
	if (texture_ == NULL)
		return -3;

	framerate_control_event_ = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (framerate_control_event_ == NULL)
		return -4;

	return 0;
}

int GxxGmSDL2Player::SetMediaInfo(int width, int height, AVPixelFormat pixfmt, int channel_layout, int audio_frame_size, AVSampleFormat samplefmt, int sample_rate)
{
	// ��׼����Ƶͼ��ת����ص�����
	video_img_width_ = width;
	video_img_height_ = height;
	video_frame_yuv_ = av_frame_alloc();
	int video_frame_yuv_buffer_size = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, video_img_width_, video_img_height_, 1);
	unsigned char *video_frame_yuv_buffer = (unsigned char *)av_malloc(video_frame_yuv_buffer_size);
	av_image_fill_arrays(video_frame_yuv_->data, video_frame_yuv_->linesize, video_frame_yuv_buffer, AV_PIX_FMT_YUV420P, video_img_width_, video_img_height_, 1);

	image_convert_context_ = sws_getContext(video_img_width_, video_img_height_, pixfmt, screen_width_, screen_height_, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

	// ������Ƶ��ص�����
	return 0;
}

int GxxGmSDL2Player::Play()
{
	// ����߳�û���������������̣߳��ֱ�����Ⱦ�����̺߳��¼�����(ͬ��)�߳�
	// ����߳������ˣ��򴥷�����¼�
	DWORD exit_code_ = 0;
	GetExitCodeThread(render_thread_handle_, &exit_code_);
	if (exit_code_ != STILL_ACTIVE)
	{
		render_thread_handle_ = CreateThread(NULL, 0, RenderThread, this, 0, NULL);
	}

	GetExitCodeThread(control_thread_handle_, &exit_code_);
	if (exit_code_ != STILL_ACTIVE)
	{
		control_thread_handle_ = CreateThread(NULL, 0, ControlThread, this, 0, NULL);
	}

	if ((render_thread_handle_ == NULL) || (control_thread_handle_ == NULL))
		return -1;

	return 0;
}

int GxxGmSDL2Player::Pause()
{
	return 0;
}

int GxxGmSDL2Player::Stop()
{
	return 0;
}

int GxxGmSDL2Player::InputFrameData(AVMediaType type, AVFrame *data)
{
	// ��֡���ݲ������
	return frame_cache_.push(type, data);
}

DWORD WINAPI GxxGmSDL2Player::RenderThread(LPVOID lpParam)
{
	GxxGmSDL2Player *player_ = (GxxGmSDL2Player *)lpParam;

	while (true)
	{
		// �ȴ������¼�
		//WaitForSingleObject(player_->framerate_control_event_, INFINITE);

		// �ӻ�����ȡ��֡����
		FrameData *data = player_->frame_cache_.pop();
		if (data->type_ == AVMEDIA_TYPE_VIDEO)
		{
			// ͼ���ʽת��
			sws_scale(player_->image_convert_context_, (const unsigned char * const*)data->data_->data, data->data_->linesize, 0, player_->video_img_height_, player_->video_frame_yuv_->data, player_->video_frame_yuv_->linesize);

			// ��Ⱦ
			SDL_Rect rect;
			rect.x = 0;
			rect.y = 0;
			rect.w = player_->screen_width_;
			rect.h = player_->screen_height_;

			SDL_UpdateTexture(player_->texture_, NULL, player_->video_frame_yuv_->data[0], player_->video_frame_yuv_->linesize[0]);
			SDL_RenderCopy(player_->renderer_, player_->texture_, NULL, &rect);
			SDL_RenderPresent(player_->renderer_);
		}
		else if (data->type_ == AVMEDIA_TYPE_AUDIO)
		{
			// ��Ƶת��
		}

		av_frame_free(&data->data_);
	}

	return 0;
}

DWORD WINAPI GxxGmSDL2Player::ControlThread(LPVOID lpParam)
{
	GxxGmSDL2Player *player_ = (GxxGmSDL2Player *)lpParam;

	return 0;
}
