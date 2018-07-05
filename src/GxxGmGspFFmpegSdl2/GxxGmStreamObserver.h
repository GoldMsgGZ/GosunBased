#ifndef _GxxGmStreamObserver_H_
#define _GxxGmStreamObserver_H_

struct VIDEO_INFO
{
	int codec_;			// ��������ֵ�ο�ffmpeg
	int frame_rate_;	// ֡��
};

struct AUDIO_INFO
{
	int codec_;			// ������
	int sample_rate_;	// ������
	int channel_;		// ������
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
	// �⸴����Ϣ
	virtual void DemuxingInfo(struct VIDEO_INFO *video_info, struct AUDIO_INFO *audio_info) = 0;

	// ý��������Ϣ
	virtual void MediaData(const void *data, int data_len, const struct EXTRA_INFO *extra) = 0;
};

#endif//_GxxGmStreamObserver_H_