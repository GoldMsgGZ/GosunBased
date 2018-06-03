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
	// ��
	int Open(const char *url, bool is_real = true);
	// ����
	int Play();
	// ��ͣ
	int Pause();
	// �ָ�
	int Resume();
	// ֹͣ
	int Stop();

	// ������
	int OpenAudio();
	// ��������
	int SetVolume(int volume);
	// ��ȡ����
	int GetVolume();
	// �ر�����
	int CloseAudio();

	void Close();

	// ��ͼ
	int CapturePicture(const char *save_path, int img_type);
	// ���
	int Fast();
	// ����
	int Slow();
	// ���ڲ����ٶ�
	int SetPlaySpeed(double speed);
	// ֡��
	int Next();
	// ֡��
	int Back();
	// ���õ�ǰ���ŵ���ʼλ��
	int SetPlayPos(unsigned __int64 pulTimeStamp);
	// ��ղ��Ż���
	int ClearPlayBuffer();
	// ˢ�´�����ͼ
	int RefreshView();

public:
	//static void __stdcall _FuncOnBufferEmptyCB(EnumGSMediaType eMediaType,UInt64 ulLatestPlayed,UInt64 ulLatestedPlayedKey,void* pUser);

public:
	// ��PlaySDK��������
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
