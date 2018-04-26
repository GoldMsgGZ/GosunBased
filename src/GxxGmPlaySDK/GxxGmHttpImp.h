#ifndef _GxxGmHttpImp_H_
#define _GxxGmHttpImp_H_

#include "GxxGmPlaySDKCallback.h"
#include "..\ext\Foundation\GSThread.h"
#include <windows.h>

class GxxGmHttpImp
{
public:
	GxxGmHttpImp(GxxGmPlaySDKNotifer *notifer);
	~GxxGmHttpImp();

public:
	int Open(const char *url);
	int Play();
	int Pause();
	int Resume();
	int Stop();
	void Close();

public:
	static void GS_CALLBACK _ReadStreamThreadCallback(GSThread &thread, void *pThreadData);
	GSThread read_stream_thread_;

	static void GS_CALLBACK _ControlThreadCallback(GSThread &thread, void *pThreadData);
	GSThread control_thread_;

public:
	GxxGmPlaySDKNotifer *notifer_;
	HANDLE framerate_event_handle_;

public:
	UInt32 eVideoCode_;
	UInt32 eAudioCode_;
	UInt32 unSampleRate_;
	UInt32 unBits_;
	UInt32 unChannels_;
	Int32 nRefFrameRate_;
	Int32 nEnableTimeCaculate_;

public:
	// AVFormatContext
	char* format_ctx_;

	// �����
	int video_stream_index_;
	int audio_stream_index_;

	// ��ʵ��
	char* video_stream_;
	char* audio_stream_;

	// ������������
	char* video_codec_ctx_;
	char* audio_codec_ctx_;

	// ������
	char* video_codec_;
	char* audio_codec_;

	// ������ID
	UInt32 video_codec_id_;
	UInt32 audio_codec_id_;
};

#endif//_GxxGmHttpImp_H_
