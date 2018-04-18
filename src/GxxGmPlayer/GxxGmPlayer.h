#ifndef _GxxGmPlayer_H_
#define _GxxGmPlayer_H_

//#include "GxxGmPlaySDK.h"
//#include "GxxGmSDL2Player.h"
//#include "GSMediaPlayer.h"
//#include <Windows.h>
#include "GxxGmPlaySDKCallback.h"

class GxxGmPlaySDK;
class GxxGmSDL2Player;

class GxxGmPlayer : public GxxGmPlayerNotifer
{
public:
	GxxGmPlayer();
	~GxxGmPlayer();

public:
	int SetScreenWindow(void* window);
	bool IsBusy();
	
public:
	int Open(const char *url, bool is_real = true);
	int Play();
	int Pause();
	int Stop();
	void Close();

public:
	// 由PlaySDK上送上来
	virtual void StreamParamNotifer(unsigned int eVideoCode, unsigned int eAudioCode, unsigned int unSampleRate, unsigned int unBits, unsigned int unChannels, int nRefFrameRate, int nEnableTimeCaculate);
	virtual void StreamParamNotiferEx(AVCodecContext *video_codec_context, AVCodecContext *audio_codec_context);
	virtual void MediaFrameNotifer(/*StruGSMediaFrameData*/void *media_frame_data);
	virtual void MediaFrameNotiferEx(AVMediaType type, AVFrame *data);
	virtual void PlayerStateNotifer(enum GxxGmPlayState state);

private:
	void* screen_window_;
	unsigned int gxx_media_player_handle_;
	bool is_real_;

private:
	//GxxGmSDL2Player *sdl2_player_;

private:
	void *play_sdk_; 
	
};

#endif//_GxxGmPlayer_H_
