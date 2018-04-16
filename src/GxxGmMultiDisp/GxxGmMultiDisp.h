#ifndef _GxxGmMultiDisp_H_
#define _GxxGmMultiDisp_H_


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
	int Play(const char *url, const char *play_info, bool is_real = true);
	int Pause();
	int Resume();
	int Stop();

public:
	// ������
	GxxGmPlayer disp_player_;

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
	int current_disp_count_;
	GxxGmDisp gxx_gm_disp_[MAX_DISP_COUNT];
};

#endif//_GxxGmMultiDisp_H_