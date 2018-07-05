#ifndef _GxxGmPlayer_H_
#define _GxxGmPlayer_H_

#include "GxxGmStreamObserver.h"

class GxxGmPlayerSdl2 : public GxxGmStreamObserver
{
public:
	GxxGmPlayerSdl2();
	~GxxGmPlayerSdl2();

public:
	int Init();
	void Uninit();

public:
	// 解复用信息
	virtual void DemuxingInfo(struct VIDEO_INFO *video_info, struct AUDIO_INFO *audio_info);

	// 媒体数据信息
	virtual void MediaData(const void *data, int data_len, const void *extra, int extra_len);

public:
	// 这里需要有视音频缓冲队列
};

#endif//_GxxGmPlayer_H_
