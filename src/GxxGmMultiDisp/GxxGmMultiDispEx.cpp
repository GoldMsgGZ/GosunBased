#include "GxxGmMultiDispEx.h"
#include "..\GxxGmPlayBase\GxxGmPlayBase.h"
#include "..\GxxGmPlayer\GxxGmPlayer.h"
#include <Windows.h>


GxxGmDispEx::GxxGmDispEx()
: disp_hwnd_(0)
, father_hwnd_(0)
, row_index_(0)
, list_index_(0)
, player_(new GxxGmPlayer())
, is_real_(false)
{

}

GxxGmDispEx::~GxxGmDispEx()
{
	disp_hwnd_   = 0;
	father_hwnd_ = 0;
	row_index_	 = 0;
	list_index_  = 0;
}

void GxxGmDispEx::Attach(int self_hwnd, int father_hwnd)
{
	disp_hwnd_ = self_hwnd;
	father_hwnd_ = father_hwnd;
	player_->SetScreenWindow((void*)disp_hwnd_);
}

void GxxGmDispEx::SetLocation(int row_index, int list_index)
{
	row_index_ = row_index;
	list_index_ = list_index;
}

int GxxGmDispEx::MoveWindow(int x, int y, int width, int height)
{
	if (disp_hwnd_ == 0)
		return -1;

	BOOL bret = ::MoveWindow((HWND)disp_hwnd_, x, y, width, height, TRUE);

	if (bret)
		return 0;
	else
		return GetLastError();
}

int GxxGmDispEx::ShowWindow(int nCmdShow)
{
	if (disp_hwnd_ == 0)
		return -1;

	BOOL bret = ::ShowWindow((HWND)disp_hwnd_, nCmdShow);

	if (bret)
		return 0;
	else
		return GetLastError();
}

bool GxxGmDispEx::IsAttached()
{
	if (disp_hwnd_)
		return true;
	else
		return false;
}

int GxxGmDispEx::Play(const char *url, const char *play_info, bool is_real /* = true */)
{
	int errCode = player_->Open(url, is_real);
	if (errCode == 0)
	{
		// 保存播放信息
		play_info_ = play_info;
		url_ = url;
	}

	return errCode;
}

int GxxGmDispEx::Pause()
{
	int errCode = player_->Pause();
	return errCode;
}

int GxxGmDispEx::Resume()
{
	return 0;
}

int GxxGmDispEx::Stop()
{
	player_->Stop();
	play_info_.clear();
	url_.clear();
	return 0;
}

int GxxGmDispEx::CaptureScreen()
{
	// 未实现
	return 0;
}

std::string GxxGmDispEx::GetPlayInfo()
{
	return play_info_;
}

std::string GxxGmDispEx::GetUrl()
{
	return url_;
}

std::string GxxGmDispEx::GetDeviceId()
{
	return device_id_;
}

void GxxGmDispEx::SetDeviceId(std::string device_id)
{
	device_id_ = device_id;
}

bool GxxGmDispEx::IsPlaying()
{
	return player_->IsBusy();
}

bool GxxGmDispEx::IsRealMode()
{
	return is_real_;
}


//////////////////////////////////////////////////////////////////////////
//
//

#define BASE_DISP_EX_ID		50001

GxxGmMultiDispEx::GxxGmMultiDispEx()
: current_disp_count_(0)
, gxx_gm_disp_ex_(new GxxGmDispEx[MAX_DISP_COUNT_EX])
{
#ifdef _DEBUG
	MessageBoxA(NULL, "GxxGmMultiDispEx构造函数 >>> 等待调试器接入", "调试", 0);
#endif
}

GxxGmMultiDispEx::~GxxGmMultiDispEx()
{
	current_disp_count_ = 0;
}

int GxxGmMultiDispEx::Init(int screen_hwnd, int row_count, int list_count)
{
	int errCode = 0;

	// 根据传入的窗口句柄计算银幕范围，进而计算出银幕宽高
	screen_hwnd_ = screen_hwnd;
	RECT screen_rect;
	BOOL bret = ::GetWindowRect((HWND)screen_hwnd_, &screen_rect);
	if (!bret) {
		errCode = GetLastError();
		GxxGmPlayBase::DebugStringOutput("获取银幕范围失败！错误码：%d\n", errCode);
		return errCode;
	}

	screen_width_ = screen_rect.right - screen_rect.left;
	screen_height_ = screen_rect.bottom - screen_rect.top;

	// 执行分屏
	errCode = ReDivision(row_count, list_count);

	return errCode;
}

int GxxGmMultiDispEx::ReDivision(int row_count, int list_count)
{
	int errCode = 0;

	// 先检查是否已经初始化了，不然后面的操作都是无效的

	// 重新计算
	row_count_ = row_count;
	list_count_ = list_count;
	current_disp_count_ = row_count_ * list_count_;

	// 计算出每一个分屏的宽高
	int average_disp_width = screen_width_ / list_count;
	int average_disp_height = screen_height_ / row_count;

	// 先按照索引，将所有已经Attach了的控件隐藏了
	for (int index = 0; index < MAX_DISP_COUNT_EX; ++index)
	{
		gxx_gm_disp_ex_[index].ShowWindow(SW_HIDE);
	}

	// 接下来，按照分屏数，开始生成STATIC窗口作为显示窗口
	for (int row_index = 0; row_index < row_count; ++row_index)
	{
		for (int list_index = 0; list_index < list_count; ++list_index)
		{
			// 分屏索引
			int disp_index = row_index * list_index;

			// 计算坐标
			int disp_left	= list_index * average_disp_width;
			int disp_top	= row_index	 * average_disp_height;
			int disp_right	= disp_left  + average_disp_width;
			int disp_bottom = disp_top   + average_disp_height;

			if (!gxx_gm_disp_ex_[disp_index].IsAttached())
			{
				HWND disp_hwnd = ::CreateWindowA("STATIC", " ", WS_CHILD|WS_VISIBLE|SS_NOTIFY|SS_SUNKEN|SS_BITMAP, 
					disp_left, disp_top, average_disp_width, average_disp_height, (HWND)screen_hwnd_,
					NULL, NULL, NULL);

				if (disp_hwnd == NULL)
				{
					errCode = GetLastError();
					GxxGmPlayBase::DebugStringOutput("创建分屏失败！错误码：%d\n", errCode);
					return errCode;
				}

				// 保存分屏句柄和父句柄
				gxx_gm_disp_ex_[disp_index].Attach((int)disp_hwnd, (int)screen_hwnd_);

				// 设置分屏坐标
				gxx_gm_disp_ex_[disp_index].SetLocation(row_index, list_index);
			}
			

			// 移动窗口
			gxx_gm_disp_ex_[disp_index].MoveWindow(disp_left, disp_top, average_disp_width, average_disp_height);

			// 显示窗口
			gxx_gm_disp_ex_[disp_index].ShowWindow(SW_SHOW);
		}
	}

	// 最后，将所有被隐藏掉的，正在播放的分屏停止播放
	for (int index = current_disp_count_; index < MAX_DISP_COUNT_EX; ++index)
	{
		// gxx_gm_disp_ex_[index].Stop();
	}

	return errCode;
}

int GxxGmMultiDispEx::Play(const char *url, const char *play_info, int disp_index /* = -1 */, bool is_real /* = true */)
{
	int real_disp_index = -1;

	if (disp_index > -1)
	{
		// 传入的看上去像是一个正常的索引值
		// 首先判断传入的索引值是否是可用的（在最大索引范围内，并且指定的分屏是空闲的）
		if (IsAvaliableDisp(disp_index))
			real_disp_index = disp_index;
		else
		{
			// 索引值不可用
			return -6003;
		}
	}
	else if (disp_index <= 0)
	{
		// 寻找一个空闲的播放窗口
		real_disp_index = FindFreeDisp();
		if (real_disp_index < 0)
			return -6003;
	}
	else
		return -6003;
	
	return gxx_gm_disp_ex_[real_disp_index].Play(url, play_info, is_real);
}

int GxxGmMultiDispEx::Pause(int disp_index)
{
	// 检查当前索引是否在范围内
	// 先检查播放模式，如果是实时模式，就不支持暂停接口
	if (gxx_gm_disp_ex_[disp_index].IsRealMode())
		return gxx_gm_disp_ex_[disp_index].Pause();
	else
		return -6002;
}

int GxxGmMultiDispEx::Resume(int disp_index)
{
	if (gxx_gm_disp_ex_[disp_index].IsRealMode())
		return gxx_gm_disp_ex_[disp_index].Resume();
	else
		return -6002;
}

int GxxGmMultiDispEx::Stop(int disp_index)
{
	return gxx_gm_disp_ex_[disp_index].Stop();
}

int GxxGmMultiDispEx::CaptureScreen(int disp_index)
{
	if (gxx_gm_disp_ex_[disp_index].IsPlaying())
		return gxx_gm_disp_ex_[disp_index].CaptureScreen();
	else
		return -1;
}

std::string GxxGmMultiDispEx::GetPlayInfo(int disp_index)
{
	return gxx_gm_disp_ex_[disp_index].GetPlayInfo();
}

std::string GxxGmMultiDispEx::GetUrl(int disp_index)
{
	return gxx_gm_disp_ex_[disp_index].GetUrl();
}

std::string GxxGmMultiDispEx::GetDeviceId(int disp_index)
{
	return gxx_gm_disp_ex_[disp_index].GetDeviceId();
}

void GxxGmMultiDispEx::SetDeviceId(std::string device_id, int disp_index)
{
	return gxx_gm_disp_ex_[disp_index].SetDeviceId(device_id);
}




bool GxxGmMultiDispEx::IsAvaliableDisp(int disp_index)
{
	// 检查是否为可用分屏
	// 首先，检查索引号是否在可用范围内
	if ((disp_index > -1) && (disp_index < MAX_DISP_COUNT_EX))
	{
		if (!gxx_gm_disp_ex_[disp_index].IsPlaying())
			return true;
	}

	return false;
}

int GxxGmMultiDispEx::FindFreeDisp()
{
	int errCode = -1;

	for (int index = 0; index < current_disp_count_; ++index)
	{
		if (!gxx_gm_disp_ex_[index].IsPlaying())
		{
			errCode = index;
			break;
		}		
	}

	return errCode;
}