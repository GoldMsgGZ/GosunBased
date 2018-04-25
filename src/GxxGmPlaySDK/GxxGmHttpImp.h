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

	//static DWORD WINAPI ReadStreamThread(LPVOID lpParam);
	//static DWORD WINAPI ControlThread(LPVOID lpParam);

public:
	GxxGmPlaySDKNotifer *notifer_;
	//bool is_paused_;
	//bool need_stop_;
	//HANDLE read_stream_thread_handle_;
	//HANDLE control_thread_handle_;
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
	void* format_ctx_;

	// 流序号
	int video_stream_index_;
	int audio_stream_index_;

	// 流实体
	void* video_stream_;
	void* audio_stream_;

	// 解码器上下文
	void* video_codec_ctx_;
	void* audio_codec_ctx_;

	// 解码器
	void* video_codec_;
	void* audio_codec_;

	// 解码器ID
	UInt32 video_codec_id_;
	UInt32 audio_codec_id_;
};

#endif//_GxxGmHttpImp_H_
