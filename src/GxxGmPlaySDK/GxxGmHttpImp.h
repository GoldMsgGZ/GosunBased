#ifndef _GxxGmHttpImp_H_
#define _GxxGmHttpImp_H_

#include "GxxGmPlaySDKCallback.h"
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
	int Stop();
	void Close();

public:
	static DWORD WINAPI ReadStreamThread(LPVOID lpParam);

public:
	GxxGmPlaySDKNotifer *notifer_;
	bool is_paused_;
	HANDLE read_stream_thread_handle_;

public:
	// AVFormatContext
	void* format_ctx_;

	// 流序号
	int video_stream_index_;
	int audio_stream_index_;

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
