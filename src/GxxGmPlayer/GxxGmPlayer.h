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
	// 打开
	int Open(const char *url, bool is_real = true);
	// 播放
	int Play();
	// 暂停
	int Pause();
	// 恢复
	int Resume();
	// 停止
	int Stop();

	// 打开声音
	int OpenAudio();
	// 设置音量
	int SetVolume(int volume);
	// 获取音量
	int GetVolume();
	// 关闭声音
	int CloseAudio();

	void Close();

	// 截图
	int CapturePicture(const char *save_path, int img_type);
	// 快放
	int Fast();
	// 慢放
	int Slow();
	// 调节播放速度
	int SetPlaySpeed(double speed);
	// 帧进
	int Next();
	// 帧退
	int Back();
	// 设置当前播放的起始位置
	int SetPlayPos(unsigned __int64 pulTimeStamp);
	// 清空播放缓存
	int ClearPlayBuffer();
	// 刷新窗口视图
	int RefreshView();

public:
	//static void __stdcall _FuncOnBufferEmptyCB(EnumGSMediaType eMediaType,UInt64 ulLatestPlayed,UInt64 ulLatestedPlayedKey,void* pUser);

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
