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
	int current_disp_count_;
	GxxGmDisp gxx_gm_disp_[MAX_DISP_COUNT];
};

#endif//_GxxGmMultiDisp_H_