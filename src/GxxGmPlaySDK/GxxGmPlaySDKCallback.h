#ifndef _GxxGmPlaySDKCallback_H_
#define _GxxGmPlaySDKCallback_H_

#include "GSTypes.h"
#include "GSMediaPlayerDef.h"

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
	// ��֪ͨ�ڽ⸴�õ�ʱ��ÿ��Э�鴦��ģ����ò��ϱ�
	virtual void StreamParamNotifer(UInt32 eVideoCode, UInt32 eAudioCode, UInt32 unSampleRate, UInt32 unBits, UInt32 unChannels, Int32 nRefFrameRate, Int32 nEnableTimeCaculate) = 0;

	virtual void StreamParamNotiferEx(AVCodecContext *video_codec_context, AVCodecContext *audio_codec_context) = 0;
	
	// ��֪ͨ�ڶ�ȡ����Ƶ֡��ʱ���������������ջ���ø����˲��������н�����Ⱦ����
	virtual void MediaFrameNotifer(StruGSMediaFrameData *media_frame_data) = 0;
	
	// ��֪ͨ�ڶ�ȡ����Ƶ֡��ʱ���������������ջ����FFmpeg���н��룬ʹ��SDL2������Ⱦ����
	virtual void MediaFrameNotiferEx(AVMediaType type, AVFrame *data) = 0;
};

class GxxGmPlayerNotifer
{
public:
	// ��֪ͨ�ڽ⸴�õ�ʱ��ÿ��Э�鴦��ģ����ò��ϱ�
	virtual void StreamParamNotifer(UInt32 eVideoCode, UInt32 eAudioCode, UInt32 unSampleRate, UInt32 unBits, UInt32 unChannels, Int32 nRefFrameRate, Int32 nEnableTimeCaculate) = 0;

	virtual void StreamParamNotiferEx(AVCodecContext *video_codec_context, AVCodecContext *audio_codec_context) = 0;
	
	// ��֪ͨ�ڶ�ȡ����Ƶ֡��ʱ���������������ջ���ø����˲��������н�����Ⱦ����
	virtual void MediaFrameNotifer(StruGSMediaFrameData *media_frame_data) = 0;

	// ��֪ͨ�ڶ�ȡ����Ƶ֡��ʱ���������������ջ����FFmpeg���н��룬ʹ��SDL2������Ⱦ����
	virtual void MediaFrameNotiferEx(AVMediaType type, AVFrame *data) = 0;
};

#endif//_GxxGmPlaySDKCallback_H_
