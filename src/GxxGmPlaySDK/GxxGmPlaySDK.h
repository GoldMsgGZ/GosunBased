#ifndef _GxxGmPlaySDK_H_
#define _GxxGmPlaySDK_H_

#include "GxxGmPlaySDKCallback.h"

class GxxGmGspImp;
class GxxGmRtspImp;
class GxxGmHttpImp;


class GxxGmPlaySDK : public GxxGmPlaySDKNotifer
{
public:
	GxxGmPlaySDK(GxxGmPlayerNotifer *notifer);
	~GxxGmPlaySDK();

public:
	bool IsBusy();

public:
	int Open(const char *url, bool is_real);
	int Play();
	int Pause();
	int Resume();
	int Stop();
	void Close();

public:
	// 此通知在解复用的时候被每个协议处理模块调用并上报
	virtual void StreamParamNotifer(unsigned int eVideoCode, unsigned int eAudioCode, unsigned int unSampleRate, unsigned int unBits, unsigned int unChannels, int nRefFrameRate, int nEnableTimeCaculate);
	virtual void StreamParamNotiferEx(AVCodecContext *video_codec_context, AVCodecContext *audio_codec_context);
	virtual void MediaFrameNotifer(/*StruGSMediaFrameData*/void *media_frame_data);
	virtual void MediaFrameNotiferEx(AVMediaType type, AVFrame *data);
	virtual void PlayerStateNotifer(enum GxxGmPlayState state);

private:
	GxxGmGspImp *gsp_;
	GxxGmRtspImp *rtsp_;
	GxxGmHttpImp *http_;
	int protocol_type_;
	bool is_busy_;

private:
	GxxGmPlayerNotifer *notifer_;
};

#endif//_GxxGmPlaySDK_H_
