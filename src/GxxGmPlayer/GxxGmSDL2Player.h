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
	// ��Ⱦ�����߳�
	static DWORD WINAPI RenderThread(LPVOID lpParam);

	// ���ſ����߳�
	static DWORD WINAPI ControlThread(LPVOID lpParam);

public:
	// ��Ⱦ����ʹ�õı���
	SDL_Window *window_;
	SDL_Renderer *renderer_;
	SDL_Texture *texture_;

	// ��Ҫ���������Ƶ����
	int screen_width_;
	int screen_height_;
	int video_img_width_;
	int video_img_height_;

	// ͼ��ת��������
	AVFrame *video_frame_yuv_;
	struct SwsContext *image_convert_context_;

	HANDLE framerate_control_event_;

	// ��Ⱦ���źͲ��ſ����߳̾��
	HANDLE render_thread_handle_;
	HANDLE control_thread_handle_;

public:
	// ý��֡������
	FrameDataCache frame_cache_;
};

#endif//_GxxGmSDL2Player_H_
