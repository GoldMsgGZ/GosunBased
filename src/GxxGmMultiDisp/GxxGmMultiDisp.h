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
	// 播放器
	GxxGmPlayer disp_player_;
};

//////////////////////////////////////////////////////////////////////////
//
// 本类是多屏管理类，主要实现以下功能：
//	* 根据传入的窗口句柄，按照参数进行分屏划分
//	* 控制每一个分屏的控制操作
//	* 能实现交换分屏的功能
//	* 能记录每一个分屏的播放信息（包括播放的是哪个设备等信息，信息最好可扩展）
//	* 能轮询播放

// 最大分屏数，我们定为 9×9 = 81 个
#define MAX_DISP_COUNT	81

class GxxGmMultiDisp
{
public:
	GxxGmMultiDisp();
	~GxxGmMultiDisp();

public:
	// 初始化多屏管理类
	int Initialize(void* screen_window, int disp_rows = 1, int disp_lists = 1);
	void Close();

public:
	// 重分屏
	int ReDivision(int disp_rows = 1, int disp_lists = 1);
	// 调整播放窗口大小
	int ChangeScreenSize(void* screen_window);
	int ChangeScreenSize(int screen_window_width, int screen_window_height);

public:
	// 获取当前分屏数量
	int GetCurrentDispCount();

public:
	int current_disp_count_;
	GxxGmDisp gxx_gm_disp_[MAX_DISP_COUNT];
};

#endif//_GxxGmMultiDisp_H_