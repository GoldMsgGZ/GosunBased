#ifndef _GxxGmPlayer_H_
#define _GxxGmPlayer_H_

#include "GxxGmPlaySDKCallback.h"

class GxxGmPlaySDK;
//class GxxGmSDL2Player;
class GSMediaPlayer_stub;

class GxxGmPlayer : public GxxGmPlayerNotifer
{
public:
	GxxGmPlayer();
	~GxxGmPlayer();

public:
	int SetScreenWindow(void* window);
	bool IsBusy();
	bool IsRealMode();
	
public:
	int Open(const char *url, bool is_real = true);
	int Play();
	int Pause();
	int Resume();
	int Stop();

	int OpenAudio();
	int SetVolumn(int volume);
	int GetVolumn();
	int CloseAudio();

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
	GSMediaPlayer_stub *gs_mediaplayer_stub_;

private:
	void *play_sdk_; 
	
};

#endif//_GxxGmPlayer_H_
