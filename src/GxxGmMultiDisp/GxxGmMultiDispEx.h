#ifndef _GxxGmMultiDispEx_H_
#define _GxxGmMultiDispEx_H_

#include <string>

class GxxGmPlayer;

//////////////////////////////////////////////////////////////////////////
//
// �µĶ��������࣬������Ļ����Ļ��ֺͲ���ȫ��ͨ��HWND�������

class GxxGmDispEx
{
public:
	GxxGmDispEx();
	~GxxGmDispEx();

public:
	void Attach(int self_hwnd, int father_hwnd);

	void SetLocation(int row_index, int list_index);

	// �ƶ����ڣ����ڵ���������ʾλ��
	int MoveWindow(int x, int y, int width, int height);

	// ��ʾ���ڣ�������ʾ������
	int ShowWindow(int nCmdShow);

public:
	bool IsAttached();

public:
	int Play(const char *url, const char *play_info, bool is_real = true);
	int Pause();
	int Resume();
	int Stop();

	int CaptureScreen();

	std::string GetPlayInfo();
	std::string GetUrl();
	std::string GetDeviceId();

	void SetDeviceId(std::string device_id);

	bool IsPlaying();
	bool IsRealMode();

private:
	// ������ʾ���
	int disp_hwnd_;
	int father_hwnd_;

	// ��������
	int row_index_;
	int list_index_;

private:
	GxxGmPlayer *player_;
	std::string play_info_;
	std::string url_;
	std::string device_id_;
	bool is_real_;
};


#define MAX_DISP_COUNT_EX	1

class GxxGmMultiDispEx
{
public:
	GxxGmMultiDispEx();
	~GxxGmMultiDispEx();

public:
	int Init(int screen_hwnd, int row_count, int list_count);
	int ReDivision(int row_count, int list_count);

public:
	/**
	 * ������Ƶ
	 * ������
	 *	@url			����·��
	 *	@play_info		���ӵĲ�����Ϣ���ַ���
	 *	@disp_index		�Ӵ���������0~��󴰿�������-1ʱΪ�Զ��������е��Ӵ���
	 *	@is_real		true Ϊʵʱģʽ��false Ϊ¼��ģʽ
	 * ����ֵ
	 */
	int Play(const char *url, const char *play_info, int disp_index = -1, bool is_real = true);

	/**
	 * ��ͣ����
	 */
	int Pause(int disp_index);

	/**
	 * �ָ�����
	 */
	int Resume(int disp_index);

	/**
	 * ֹͣ����
	 */
	int Stop(int disp_index);

	/**
	 * 
	 */
	int CaptureScreen(int disp_index);

public:
	std::string GetPlayInfo(int disp_index);
	std::string GetUrl(int disp_index);
	std::string GetDeviceId(int disp_index);

	void SetDeviceId(std::string device_id, int disp_index);

private:
	bool IsAvaliableDisp(int disp_index);
	int FindFreeDisp();

public:
	int screen_hwnd_;
	int screen_width_;
	int screen_height_;

public:
	int current_disp_count_;
	int row_count_;
	int list_count_;
	GxxGmDispEx *gxx_gm_disp_ex_;
};


#endif//_GxxGmMultiDispEx_H_