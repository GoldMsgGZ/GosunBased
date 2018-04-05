#ifndef _GxxGmSDL2Player_H_
#define _GxxGmSDL2Player_H_

#include "SDL.h"
#include <condition_variable>

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
	FrameData pop();

public:
	std::queue<FrameData> frame_queue_;
	CRITICAL_SECTION section_;
};

class GxxGmSDL2Player
{
public:
	GxxGmSDL2Player();
	~GxxGmSDL2Player();

public:
	int Initialize(HWND screen);
	int SetMediaInfo(int width, int height, AVPixelFormat pixfmt, int width2, int height2, int channel_layout, int audio_frame_size, AVSampleFormat samplefmt, int sample_rate);
	int Play();
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
