#ifndef _GxxGmSDL2Player_H_
#define _GxxGmSDL2Player_H_

#include "SDL.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libavutil/avutil.h"
#ifdef __cplusplus
};
#endif

#include <list>
#include <windows.h>

typedef struct _FrameData_
{
	AVMediaType type_;
	AVFrame *data_;
} FrameData;

class FrameDataCache
{
public:
	FrameDataCache();
	~FrameDataCache();

public:
	int push(AVMediaType type, AVFrame *data);
	FrameData* pop();

public:
	std::list<FrameData*> frame_queue_;
	CRITICAL_SECTION section_;
};

class GxxGmSDL2Player
{
public:
	GxxGmSDL2Player();
	~GxxGmSDL2Player();

public:
	int Initialize(HWND screen);
	int SetMediaInfo(AVCodecContext *video_ctx, AVCodecContext *audio_ctx);
	int Play();
	int Pause();
	int Stop();
	int InputFrameData(AVMediaType type, AVFrame *data);

public:
	// 渲染播放线程
	static DWORD WINAPI RenderThread(LPVOID lpParam);

	// 播放控制线程
	static DWORD WINAPI ControlThread(LPVOID lpParam);

public:
	// 渲染播放使用的变量
	SDL_Window *window_;
	SDL_Renderer *renderer_;
	SDL_Texture *texture_;

	// 需要缓存的视音频参数
	int screen_width_;
	int screen_height_;
	int video_img_width_;
	int video_img_height_;

	// 图像转换上下文
	AVFrame *video_frame_yuv_;
	struct SwsContext *image_convert_context_;

	HANDLE framerate_control_event_;

	// 渲染播放和播放控制线程句柄
	HANDLE render_thread_handle_;
	HANDLE control_thread_handle_;

public:
	// 媒体帧缓冲区
	FrameDataCache frame_cache_;
};

#endif//_GxxGmSDL2Player_H_
