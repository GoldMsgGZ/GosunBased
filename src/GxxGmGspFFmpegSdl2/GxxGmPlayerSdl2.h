#ifndef _GxxGmPlayer_H_
#define _GxxGmPlayer_H_

#include "GxxGmStreamObserver.h"
#include "SDL.h"

class GxxGmCodec;

class GxxGmPlayerSdl2 : public GxxGmStreamObserver
{
public:
	GxxGmPlayerSdl2();
	~GxxGmPlayerSdl2();

public:
	int Init(void* hwnd = NULL, int screen_width = 800, int screen_height = 600);
	void Uninit();

public:
	// 解复用信息
	virtual void DemuxingInfo(struct VIDEO_INFO *video_info, struct AUDIO_INFO *audio_info);

	// 媒体数据信息
	virtual void MediaData(const void *data, int data_len, const void *extra, int extra_len);

public:
	// 这里需要有视音频缓冲队列，缓冲队列主要是给播放历史视频进行话音同步用的，实时模式不用

public:
	// 编解码器
	GxxGmCodec *codec_;

public:
	// 播放器窗口
	SDL_Window *screen_;
	// 播放渲染器
	SDL_Renderer *screen_renderer_;
	// 播放纹理（这个可能没有必要放到全局上）
	SDL_Texture *screen_texture_;

	void *screen_hwnd_;
	int screen_width_;
	int screen_height_;
};

#endif//_GxxGmPlayer_H_
