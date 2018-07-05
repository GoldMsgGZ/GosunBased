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
	// �⸴����Ϣ
	virtual void DemuxingInfo(struct VIDEO_INFO *video_info, struct AUDIO_INFO *audio_info);

	// ý��������Ϣ
	virtual void MediaData(const void *data, int data_len, const void *extra, int extra_len);

public:
	// ������Ҫ������Ƶ�������
};

#endif//_GxxGmPlayer_H_
