#ifndef _GxxGmPlaySDKCallback_H_
#define _GxxGmPlaySDKCallback_H_

//#include "GSTypes.h"
//#include "GSMediaPlayerDef.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "libavformat\avformat.h"
#include "libavcodec\avcodec.h"
#include "libavutil\avutil.h"
#ifdef __cplusplus
};
#endif

class GxxGmPlaySDKNotifer
{
public:
	// 此通知在解复用的时候被每个协议处理模块调用并上报
	virtual void StreamParamNotifer(unsigned int eVideoCode, unsigned int eAudioCode, unsigned int unSampleRate, unsigned int unBits, unsigned int unChannels, int nRefFrameRate, int nEnableTimeCaculate) = 0;

	virtual void StreamParamNotiferEx(AVCodecContext *video_codec_context, AVCodecContext *audio_codec_context) = 0;
	
	// 此通知在读取到视频帧的时候上送上来，最终会调用高新兴播放器进行解码渲染播放
	virtual void MediaFrameNotifer(/*StruGSMediaFrameData*/void *media_frame_data) = 0;
	
	// 此通知在读取到视频帧的时候上送上来，最终会调用FFmpeg进行解码，使用SDL2进行渲染播放
	virtual void MediaFrameNotiferEx(AVMediaType type, AVFrame *data) = 0;
};

class GxxGmPlayerNotifer
{
public:
	// 此通知在解复用的时候被每个协议处理模块调用并上报
	virtual void StreamParamNotifer(unsigned int eVideoCode, unsigned int eAudioCode, unsigned int unSampleRate, unsigned int unBits, unsigned int unChannels, int nRefFrameRate, int nEnableTimeCaculate) = 0;

	virtual void StreamParamNotiferEx(AVCodecContext *video_codec_context, AVCodecContext *audio_codec_context) = 0;
	
	// 此通知在读取到视频帧的时候上送上来，最终会调用高新兴播放器进行解码渲染播放
	virtual void MediaFrameNotifer(/*StruGSMediaFrameData*/void *media_frame_data) = 0;

	// 此通知在读取到视频帧的时候上送上来，最终会调用FFmpeg进行解码，使用SDL2进行渲染播放
	virtual void MediaFrameNotiferEx(AVMediaType type, AVFrame *data) = 0;
};

#endif//_GxxGmPlaySDKCallback_H_
