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

public:
	std::string GetUrl() { return play_info_url_; }
	std::string GetPlayInfo() { return play_info_01_; }
	void SetDeviceId(std::string dev_id) { play_info_devid_ = dev_id; }
	std::string GetDeviceId() { return play_info_devid_; }

	// 播放信息，这里很重要，我们可以用来存放设备、用户信息等
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
	/**
	 * 播放视频
	 * 参数：
	 *	@url			播放路径
	 *	@play_info		附加的播放信息，字符串
	 *	@disp_index		子窗口索引，0~最大窗口索引，-1时为自动搜索空闲的子窗口
	 *	@is_real		true 为实时模式，false 为录像模式
	 * 返回值
	 */
	int Play(const char *url, const char *play_info, int disp_index = -1, bool is_real = true);

	/**
	 * 暂停播放
	 */
	int Pause(int disp_index);

	/**
	 * 恢复播放
	 */
	int Resume(int disp_index);

	/**
	 * 停止播放
	 */
	int Stop(int disp_index);

public:
	int current_disp_count_;
	GxxGmDisp gxx_gm_disp_[MAX_DISP_COUNT];
};

#endif//_GxxGmMultiDisp_H_