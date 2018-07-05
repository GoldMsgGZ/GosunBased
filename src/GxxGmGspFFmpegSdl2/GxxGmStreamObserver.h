#ifndef _GxxGmStreamObserver_H_
#define _GxxGmStreamObserver_H_

struct VIDEO_INFO
{
	int codec_;			// 编码器，值参考ffmpeg
	int frame_rate_;	// 帧率
};

struct AUDIO_INFO
{
	int codec_;			// 编码器
	int sample_rate_;	// 采样率
	int channel_;		// 声道数
	int bit_rate_;
};

enum GxxGmMediaType
{
	VIDEO,
	AUDIO,
	SUBTITLE
};

struct EXTRA_INFO
{
	enum GxxGmMediaType type;
	unsigned __int64 pts;
	int codec;
};

class GxxGmStreamObserver
{
public:
	// 解复用信息
	virtual void DemuxingInfo(struct VIDEO_INFO *video_info, struct AUDIO_INFO *audio_info) = 0;

	// 媒体数据信息
	virtual void MediaData(const void *data, int data_len, const struct EXTRA_INFO *extra) = 0;
};

#endif//_GxxGmStreamObserver_H_