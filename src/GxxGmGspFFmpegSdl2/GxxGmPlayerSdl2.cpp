#include "stdafx.h"
#include "GxxGmPlayerSdl2.h"
#include "GxxGmCodec.h"
#include <Windows.h>

GxxGmPlayerSdl2::GxxGmPlayerSdl2()
: codec_(new GxxGmCodec())
, screen_(NULL)
, screen_renderer_(NULL)
, screen_hwnd_(NULL)
, screen_width_(0)
, screen_height_(0)
{

}

GxxGmPlayerSdl2::~GxxGmPlayerSdl2()
{

}

int GxxGmPlayerSdl2::Init(void* hwnd, int screen_width, int screen_height)
{
	int errCode = 0;

	// SDL2的一些初始化工作
	if (hwnd == NULL)
		screen_ = SDL_CreateWindow("GxxGmPlayer_V1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_OPENGL);
	else
		screen_ = SDL_CreateWindowFrom(hwnd);
	
	if (screen_ == NULL)
		return -1;
	
	// 获取当前系统版本，如果是XP/2003，则用软件渲染（SDL_RENDERER_SOFTWARE）
	// 如果是Vista及以上，则用硬件加速（SDL_RENDERER_ACCELERATED）
	// 还可以选择与显示器刷新频率同步（SDL_RENDERER_PRESENTVSYNC）
	OSVERSIONINFO os_version;
	GetVersionEx(&os_version);
	if (os_version.dwMajorVersion > 5) {
		// Vista及以上
		screen_renderer_ = SDL_CreateRenderer(screen_, -1, SDL_RENDERER_ACCELERATED);
	} else {
		screen_renderer_ = SDL_CreateRenderer(screen_, -1, SDL_RENDERER_SOFTWARE);
	}
	
	if (screen_renderer_ == NULL)
	{
		SDL_DestroyWindow(screen_);
		screen_ = NULL;

		return -2;
	}

	return errCode;
}

void GxxGmPlayerSdl2::Uninit()
{
	screen_hwnd_ = NULL;
	screen_width_ = 0;
	screen_height_ = 0;

	if (screen_renderer_)
	{
		SDL_DestroyRenderer(screen_renderer_);
		screen_renderer_ = NULL;
	}

	if (screen_)
	{
		SDL_DestroyWindow(screen_);
		screen_ = NULL;
	}

	if (codec_)
	{
		delete codec_;
		codec_ = NULL;
	}
}

void GxxGmPlayerSdl2::DemuxingInfo(struct VIDEO_INFO *video_info, struct AUDIO_INFO *audio_info)
{
	// 
	codec_->PrepareDecode();
}

void GxxGmPlayerSdl2::MediaData(const void *data, int data_len, const void *extra, int extra_len)
{

}