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
	// �⸴����Ϣ
	virtual void DemuxingInfo(struct VIDEO_INFO *video_info, struct AUDIO_INFO *audio_info);

	// ý��������Ϣ
	virtual void MediaData(const void *data, int data_len, const void *extra, int extra_len);

public:
	// ������Ҫ������Ƶ������У����������Ҫ�Ǹ�������ʷ��Ƶ���л���ͬ���õģ�ʵʱģʽ����

public:
	// �������
	GxxGmCodec *codec_;

public:
	// ����������
	SDL_Window *screen_;
	// ������Ⱦ��
	SDL_Renderer *screen_renderer_;
	// ���������������û�б�Ҫ�ŵ�ȫ���ϣ�
	SDL_Texture *screen_texture_;

	void *screen_hwnd_;
	int screen_width_;
	int screen_height_;
};

#endif//_GxxGmPlayer_H_
