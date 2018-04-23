#ifndef _GxxGmMultiDisp_H_
#define _GxxGmMultiDisp_H_

#include <string>
#include "..\GxxGmPlayer\GxxGmPlayer.h"

//////////////////////////////////////////////////////////////////////////
//
//

class GxxGmDisp
{
public:
	GxxGmDisp();
	~GxxGmDisp();

public:
	void SetDispControl(void* disp, int left, int top, int right, int bottom);
	void SetBackgroundImage(const char *imgpath);
	void UpdateDispRect(int left, int top, int right, int bottom);

public:
	void ShowDispWindow(int left, int top, int right, int bottom, bool is_show = true);
	bool IsBusy();

public:
	int Play(const char *url, const char *play_info, bool is_real = true);
	int Pause();
	int Resume();
	int Stop();

public:
	// ������
	GxxGmPlayer disp_player_;

	// ��ʾ��������
	// ��������Ļ������ʱ�򣬽�����ʵ�����ǲ���������
	// ��ɲ��������󽻻�����²�������Ⱦ����ʾ����
	void* disp_control_;

public:
	std::string GetUrl() { return play_info_url_; }
	std::string GetPlayInfo() { return play_info_01_; }
	void SetDeviceId(std::string dev_id) { play_info_devid_ = dev_id; }
	std::string GetDeviceId() { return play_info_devid_; }

	// ������Ϣ���������Ҫ�����ǿ�����������豸���û���Ϣ��
	std::string play_info_url_;
	std::string play_info_devid_;
	std::string play_info_01_;
	std::string play_info_02_;
	std::string play_info_03_;
	std::string play_info_04_;
	std::string play_info_05_;
	std::string play_info_06_;
	std::string play_info_07_;
	std::string play_info_08_;
	std::string play_info_09_;
	std::string play_info_10_;

public:
	bool is_real_mode_;

public:
	int disp_left_;
	int disp_right_;
	int disp_top_;
	int disp_bottom_;
};

//////////////////////////////////////////////////////////////////////////
//
// �����Ƕ��������࣬��Ҫʵ�����¹��ܣ�
//	* ���ݴ���Ĵ��ھ�������ղ������з�������
//	* ����ÿһ�������Ŀ��Ʋ���
//	* ��ʵ�ֽ��������Ĺ���
//	* �ܼ�¼ÿһ�������Ĳ�����Ϣ���������ŵ����ĸ��豸����Ϣ����Ϣ��ÿ���չ��
//	* ����ѯ����

// �������������Ƕ�Ϊ 9��9 = 81 ��
#define MAX_DISP_COUNT	81

class GxxGmMultiDisp
{
public:
	GxxGmMultiDisp();
	~GxxGmMultiDisp();

public:
	// ��ʼ������������
	int Initialize(void* screen_window, int disp_rows = 1, int disp_lists = 1);
	void Close();

public:
	// �ط���
	int ReDivision(int disp_rows = 1, int disp_lists = 1);
	// �������Ŵ��ڴ�С
	int ChangeScreenSize(void* screen_window);
	int ChangeScreenSize(int screen_window_width, int screen_window_height);

public:
	// ��ȡ��ǰ��������
	int GetCurrentDispCount();

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

public:
	std::string GetPlayInfo(int disp_index);
	std::string GetUrl(int disp_index);
	std::string GetDeviceId(int disp_index);

	void SetDeviceId(std::string device_id, int disp_index);

public:
	int screen_width_;
	int screen_height_;
	void* pCwnd_;

public:
	int disp_lists_;
	int disp_rows_;
	int current_disp_count_;
	GxxGmDisp gxx_gm_disp_[MAX_DISP_COUNT];
};

extern GxxGmMultiDisp gxx_gm_multi_disp_player_;

#endif//_GxxGmMultiDisp_H_