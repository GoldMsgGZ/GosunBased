#ifndef _GxxGmPlayer_H_
#define _GxxGmPlayer_H_

#include "GxxGmPlaySDK.h"
#include "GSMediaPlayer.h"
#include <Windows.h>

class GxxGmPlaySDK;

class GxxGmPlayer : public GxxGmPlayerNotifer
{
public:
	GxxGmPlayer();
	~GxxGmPlayer();

public:
	int SetScreenWindow(HWND window);
	
public:
	int Open(const char *url, bool is_real = true);
	int Play();
	int Pause();
	int Stop();
	void Close();

public:
	// ��PlaySDK��������
	virtual void StreamParamNotifer(UInt32 eVideoCode, UInt32 eAudioCode, UInt32 unSampleRate, UInt32 unBits, UInt32 unChannels, Int32 nRefFrameRate, Int32 nEnableTimeCaculate);
	virtual void StreamParamNotiferEx(AVCodecContext *video_codec_context, AVCodecContext *audio_codec_context);
	virtual void MediaFrameNotifer(StruGSMediaFrameData *media_frame_data);
	virtual void MediaFrameNotiferEx(AVMediaType type, AVFrame *data);

private:
	HWND screen_window_;
	UInt32 gxx_media_player_handle_;
	bool is_real_;

private:
	GxxGmPlaySDK *play_sdk_; 
};

#endif//_GxxGmPlayer_H_
