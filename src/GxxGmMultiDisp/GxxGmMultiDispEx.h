#ifndef _GxxGmMultiDispEx_H_
#define _GxxGmMultiDispEx_H_

//////////////////////////////////////////////////////////////////////////
//
// 新的多屏管理类，对于屏幕区域的划分和操作全部通过HWND句柄进行

class GxxGmDispEx
{
public:
	GxxGmDispEx();
	~GxxGmDispEx();

public:
	void Attach(int self_hwnd, int father_hwnd);

	void SetLocation(int row_index, int list_index);

	// 移动窗口，用于调整窗口显示位置
	int MoveWindow(int x, int y, int width, int height);

	// 显示窗口，用于显示或隐藏
	int ShowWindow(int nCmdShow);

public:
	bool IsAttached();

private:
	// 分屏显示句柄
	int disp_hwnd_;
	int father_hwnd_;

	// 分屏坐标
	int row_index_;
	int list_index_;
};


#define MAX_DISP_COUNT_EX	81

class GxxGmMultiDispEx
{
public:
	GxxGmMultiDispEx();
	~GxxGmMultiDispEx();

public:
	int Init(int screen_hwnd, int row_count, int list_count);
	int ReDivision(int row_count, int list_count);

//public:
//	/**
//	 * 播放视频
//	 * 参数：
//	 *	@url			播放路径
//	 *	@play_info		附加的播放信息，字符串
//	 *	@disp_index		子窗口索引，0~最大窗口索引，-1时为自动搜索空闲的子窗口
//	 *	@is_real		true 为实时模式，false 为录像模式
//	 * 返回值
//	 */
//	int Play(const char *url, const char *play_info, int disp_index = -1, bool is_real = true);
//
//	/**
//	 * 暂停播放
//	 */
//	int Pause(int disp_index);
//
//	/**
//	 * 恢复播放
//	 */
//	int Resume(int disp_index);
//
//	/**
//	 * 停止播放
//	 */
//	int Stop(int disp_index);
//
//public:
//	std::string GetPlayInfo(int disp_index);
//	std::string GetUrl(int disp_index);
//	std::string GetDeviceId(int disp_index);
//
//	void SetDeviceId(std::string device_id, int disp_index);

public:
	int screen_hwnd_;
	int screen_width_;
	int screen_height_;

public:
	int current_disp_count_;
	int row_count_;
	int list_count_;
	GxxGmDispEx gxx_gm_disp_ex_[MAX_DISP_COUNT_EX];
};

#endif//_GxxGmMultiDispEx_H_
