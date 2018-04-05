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
	int Open(const char *url, bool is_real);
	int Play();
	int Pause();
	int Stop();
	void Close();

public:
	// 此通知在解复用的时候被每个协议处理模块调用并上报
	virtual void StreamParamNotifer(UInt32 eVideoCode, UInt32 eAudioCode, UInt32 unSampleRate, UInt32 unBits, UInt32 unChannels, Int32 nRefFrameRate, Int32 nEnableTimeCaculate);
	virtual void StreamParamNotiferEx(AVCodecContext *video_codec_context, AVCodecContext *audio_codec_context);
	virtual void MediaFrameNotifer(StruGSMediaFrameData *media_frame_data);
	virtual void MediaFrameNotiferEx(AVMediaType type, AVFrame *data);

private:
	GxxGmGspImp *gsp_;
	GxxGmRtspImp *rtsp_;
	GxxGmHttpImp *http_;
	int protocol_type_;

private:
	GxxGmPlayerNotifer *notifer_;
};

#endif//_GxxGmPlaySDK_H_
