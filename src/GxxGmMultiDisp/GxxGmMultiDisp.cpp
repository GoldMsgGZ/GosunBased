#include "GxxGmMultiDisp.h"


//////////////////////////////////////////////////////////////////////////
//
//

GxxGmDisp::GxxGmDisp()
: is_real_mode_(true)
{

}

GxxGmDisp::~GxxGmDisp()
{

}

int GxxGmDisp::Play(const char *url, const char *play_info, bool is_real /* = true */)
{
	int errCode = 0;

	errCode = disp_player_.Open(url, is_real);
	if (errCode == 0)
	{
		is_real_mode_ = is_real;
		play_info_url_ = url;
		play_info_01_ = play_info;
	}

	return errCode;
}

int GxxGmDisp::Pause()
{
	int errCode = 0;

	errCode = disp_player_.Pause();

	return errCode;
}

int GxxGmDisp::Resume()
{
	int errCode = 0;

	return errCode;
}

int GxxGmDisp::Stop()
{
	int errCode = 0;

	errCode = disp_player_.Stop();

	return errCode;
}

//////////////////////////////////////////////////////////////////////////
//
//

GxxGmMultiDisp::GxxGmMultiDisp()
: current_disp_count_(1)
{

}

GxxGmMultiDisp::~GxxGmMultiDisp()
{

}

int GxxGmMultiDisp::Initialize(void* screen_window, int disp_rows /* = 1 */, int disp_lists /* = 1 */)
{
	int errCode = 0;

	// 首先根据传入的银幕句柄，计算出银幕区域

	// 然后根据银幕区域和行列数，计算出子窗口的宽度和高度

	return errCode;
}

void GxxGmMultiDisp::Close()
{

}

int GxxGmMultiDisp::ReDivision(int disp_rows /* = 1 */, int disp_lists /* = 1 */)
{
	int errCode = 0;

	return errCode;
}

int GxxGmMultiDisp::ChangeScreenSize(void* screen_window)
{
	int errCode = 0;

	return errCode;
}

int GxxGmMultiDisp::ChangeScreenSize(int screen_window_width, int screen_window_height)
{
	int errCode = 0;

	return errCode;
}

int GxxGmMultiDisp::GetCurrentDispCount()
{
	return current_disp_count_;
}

int GxxGmMultiDisp::Play(const char *url, const char *play_info, int disp_index /* = -1 */, bool is_real /* = true */)
{
	int errCode = 0;

	return errCode;
}

int GxxGmMultiDisp::Pause(int disp_index)
{
	int errCode = 0;

	return errCode;
}

int GxxGmMultiDisp::Resume(int disp_index)
{
	int errCode = 0;

	return errCode;
}

int GxxGmMultiDisp::Stop(int disp_index)
{
	int errCode = 0;

	return errCode;
}