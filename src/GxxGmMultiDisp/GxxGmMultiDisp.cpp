#include "GxxGmMultiDisp.h"
#include <afxwin.h>

#include "GxxGmStatic.h"


//////////////////////////////////////////////////////////////////////////
//
//

GxxGmDisp::GxxGmDisp()
: is_real_mode_(true)
, disp_control_(NULL)
{

}

GxxGmDisp::~GxxGmDisp()
{

}

void GxxGmDisp::SetDispControl(void* disp, int left, int top, int right, int bottom)
{
	disp_control_ = disp;
	disp_player_.SetScreenWindow((HWND)disp_control_);

	disp_left_ = left;
	disp_right_ = right;
	disp_top_ = top;
	disp_bottom_ = bottom;
}

void GxxGmDisp::SetBackgroundImage(const char *imgpath)
{
	// ���ȼ���ͼƬ

	// Ȼ����Ƶ���ʾ����
}

void GxxGmDisp::ShowDispWindow(int left, int top, int right, int bottom, bool is_show /* = true */)
{
	if (!disp_control_)
		return ;

	disp_left_ = left;
	disp_right_ = right;
	disp_top_ = top;
	disp_bottom_ = bottom;

	CWnd *pCwnd = CWnd::FromHandle((HWND)disp_control_);

	if (is_show)
	{
		// ����ͨ��Rect�������ǲ��Ե�
		// �������Ҫ����������
		RECT rect;
		rect.left	= disp_left_;
		rect.right	= disp_right_;
		rect.top	= disp_top_;
		rect.bottom	= disp_bottom_;

		pCwnd->MoveWindow(&rect);
		pCwnd->ShowWindow(SW_SHOW);
		pCwnd->SetWindowText(_T("This is a display screen ..."));
	}
	else
		pCwnd->ShowWindow(SW_HIDE);
}

bool GxxGmDisp::IsBusy()
{
	return disp_player_.IsBusy();
}

void GxxGmDisp::UpdateDispRect(int left, int top, int right, int bottom)
{
	RECT rect;
	rect.left	= left;
	rect.top	= top;
	rect.right	= right;
	rect.bottom = bottom;

	disp_left_ = left;
	disp_right_ = right;
	disp_top_ = top;
	disp_bottom_ = bottom;

	CWnd *pCwnd = CWnd::FromHandle((HWND)disp_control_);
	pCwnd->MoveWindow(&rect);
	pCwnd->ShowWindow(SW_SHOW);
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
, pCwnd_(NULL)
{

}

GxxGmMultiDisp::~GxxGmMultiDisp()
{

}

#define BASE_DISP_ID	40001
int GxxGmMultiDisp::Initialize(void* screen_window, int disp_rows /* = 1 */, int disp_lists /* = 1 */)
{
	int errCode = 0;

	// ���ȸ��ݴ������Ļ������������Ļ����
	RECT window_rect;
	GetWindowRect((HWND)screen_window, &window_rect);

	screen_width_ = window_rect.right - window_rect.left;
	screen_height_ = window_rect.bottom - window_rect.top;

	disp_lists_ = disp_lists;
	disp_rows_ = disp_rows;

	// Ȼ�������Ļ�������������������Ӵ��ڵĿ�Ⱥ͸߶�
	int each_disp_width = screen_width_ / disp_lists;
	int each_disp_height = screen_height_ / disp_rows;

	current_disp_count_ = disp_rows * disp_lists;
	pCwnd_ = (void*)CWnd::FromHandle((HWND)screen_window);

	// ��������ʼ�����Ӵ������꣬�����ɶ�Ӧ����ʾ�ؼ�
	// ���ν��ؼ������ֵ���Ӵ���
	int index = 0;
	for(int row_index = 0; row_index < disp_rows_; ++row_index)
	{
		for (int list_index = 0; list_index < disp_lists_; ++list_index)
		{
			int current_disp_left	= list_index * each_disp_width;
			int current_disp_top	= row_index * each_disp_height;
			int current_disp_right	= current_disp_left + each_disp_width;
			int current_disp_bottom	= current_disp_top + each_disp_height;

			RECT rect;
			rect.left	= current_disp_left;
			rect.right	= current_disp_right;
			rect.top	= current_disp_top;
			rect.bottom	= current_disp_bottom;

			//CStatic *disp = new CStatic();
			GxxGmStatic *disp = new GxxGmStatic();
			disp->Create(_T("GxxGmPlayer"), WS_CHILD | SS_NOTIFY | SS_SUNKEN, rect, (CWnd*)pCwnd_, BASE_DISP_ID + index);

			// ����ʾ����ֵ���Ӵ��ڣ�Ȼ����ʾ�Ӵ���
			gxx_gm_disp_[index].SetDispControl(disp->GetSafeHwnd(), current_disp_left, current_disp_top, current_disp_right, current_disp_bottom);
			gxx_gm_disp_[index].SetBackgroundImage(".\\res\\bkres.dll");	// ������ر���ͼ��BMPͼ��ֱ�Ӹĳ�dllͼ��
			gxx_gm_disp_[index].ShowDispWindow(current_disp_left, current_disp_top, current_disp_right, current_disp_bottom);

			++index;
		}
	}

	return errCode;
}

void GxxGmMultiDisp::Close()
{
	// ���������Ӵ���
}

int GxxGmMultiDisp::ReDivision(int disp_rows /* = 1 */, int disp_lists /* = 1 */)
{
	int errCode = 0;

	disp_lists_ = disp_lists;
	disp_rows_ = disp_rows;

	// ���¼����Ӵ��ڿ��
	int each_disp_width = screen_width_ / disp_lists;
	int each_disp_height = screen_height_ / disp_rows;

	// ���¼�����õ��Ӵ�������
	current_disp_count_ = disp_rows * disp_lists;

	// ֹͣ���в����ò������Ĳ���״̬���ݶ������������Դ�������ڱ�������
	for (int index = current_disp_count_; index < MAX_DISP_COUNT; ++index)
	{
		gxx_gm_disp_[index].Stop();
		gxx_gm_disp_[index].ShowDispWindow(0, 0, 0, 0, false);
	}

	// ���»����ӿ����Ӵ��ڵ�����
	int index = 0;
	for(int row_index = 0; row_index < disp_rows_; ++row_index)
	{
		for (int list_index = 0; list_index < disp_lists_; ++list_index)
		{
			int current_disp_left	= list_index * each_disp_width;
			int current_disp_top	= row_index * each_disp_height;
			int current_disp_right	= current_disp_left + each_disp_width;
			int current_disp_bottom	= current_disp_top + each_disp_height;

			RECT rect;
			rect.left	= current_disp_left;
			rect.right	= current_disp_right;
			rect.top	= current_disp_top;
			rect.bottom	= current_disp_bottom;

			if (!gxx_gm_disp_[index].disp_control_)
			{
				//CStatic *disp = new CStatic();
				GxxGmStatic *disp = new GxxGmStatic();
				disp->Create(_T("GxxGmPlayer"), WS_CHILD | SS_NOTIFY | SS_SUNKEN, rect, (CWnd*)pCwnd_, BASE_DISP_ID + index);

				// ����ʾ����ֵ���Ӵ��ڣ�Ȼ����ʾ�Ӵ���
				gxx_gm_disp_[index].SetDispControl(disp->GetSafeHwnd(), current_disp_left, current_disp_top, current_disp_right, current_disp_bottom);
				gxx_gm_disp_[index].SetBackgroundImage(".\\res\\bkres.dll");	// ������ر���ͼ��BMPͼ��ֱ�Ӹĳ�dllͼ��
			}
			else
			{
				// ����ʾ����ֵ���Ӵ��ڣ�Ȼ����ʾ�Ӵ���
				gxx_gm_disp_[index].UpdateDispRect(current_disp_left, current_disp_top, current_disp_right, current_disp_bottom);
			}
			
			gxx_gm_disp_[index].ShowDispWindow(current_disp_left, current_disp_top, current_disp_right, current_disp_bottom);

			++index;
		}
	}

	return errCode;
}

int GxxGmMultiDisp::ChangeScreenSize(void* screen_window)
{
	int errCode = 0;

	// ���¼�����Ļ��С
	RECT window_rect;
	GetWindowRect((HWND)screen_window, &window_rect);

	screen_width_ = window_rect.right - window_rect.left;
	screen_height_ = window_rect.bottom - window_rect.top;

	// Ȼ�������Ļ�������������������Ӵ��ڵĿ�Ⱥ͸߶�
	int each_disp_width = screen_width_ / disp_lists_;
	int each_disp_height = screen_height_ / disp_rows_;

	// ���»����ӿ����Ӵ��ڵ�����
	int index = 0;
	for(int row_index = 0; row_index < disp_rows_; ++row_index)
	{
		for (int list_index = 0; list_index < disp_lists_; ++list_index)
		{
			int current_disp_left	= list_index * each_disp_width;
			int current_disp_top	= row_index * each_disp_height;
			int current_disp_right	= current_disp_left + each_disp_width;
			int current_disp_bottom	= current_disp_top + each_disp_height;

			RECT rect;
			rect.left	= current_disp_left;
			rect.right	= current_disp_right;
			rect.top	= current_disp_top;
			rect.bottom	= current_disp_bottom;

			if (!gxx_gm_disp_[index].disp_control_)
			{
				//CStatic *disp = new CStatic();
				GxxGmStatic *disp = new GxxGmStatic();
				disp->Create(_T("GxxGmPlayer"), WS_CHILD | SS_NOTIFY | SS_SUNKEN, rect, (CWnd*)pCwnd_, BASE_DISP_ID + index);

				// ����ʾ����ֵ���Ӵ��ڣ�Ȼ����ʾ�Ӵ���
				gxx_gm_disp_[index].SetDispControl(disp->GetSafeHwnd(), current_disp_left, current_disp_top, current_disp_right, current_disp_bottom);
				gxx_gm_disp_[index].SetBackgroundImage(".\\res\\bkres.dll");	// ������ر���ͼ��BMPͼ��ֱ�Ӹĳ�dllͼ��
			}
			else
			{
				// ����ʾ����ֵ���Ӵ��ڣ�Ȼ����ʾ�Ӵ���
				gxx_gm_disp_[index].UpdateDispRect(current_disp_left, current_disp_top, current_disp_right, current_disp_bottom);
			}

			gxx_gm_disp_[index].ShowDispWindow(current_disp_left, current_disp_top, current_disp_right, current_disp_bottom);

			++index;
		}
	}

	return errCode;
}

int GxxGmMultiDisp::ChangeScreenSize(int screen_window_width, int screen_window_height)
{
	int errCode = 0;

	screen_width_ = screen_window_width;
	screen_height_ = screen_window_height;

	// ���¼�����Ļ��С
	int each_disp_width = screen_width_ / disp_lists_;
	int each_disp_height = screen_height_ / disp_rows_;

	// ���»����ӿ����Ӵ��ڵ�����
	int index = 0;
	for(int row_index = 0; row_index < disp_rows_; ++row_index)
	{
		for (int list_index = 0; list_index < disp_lists_; ++list_index)
		{
			int current_disp_left	= list_index * each_disp_width;
			int current_disp_top	= row_index * each_disp_height;
			int current_disp_right	= current_disp_left + each_disp_width;
			int current_disp_bottom	= current_disp_top + each_disp_height;

			RECT rect;
			rect.left	= current_disp_left;
			rect.right	= current_disp_right;
			rect.top	= current_disp_top;
			rect.bottom	= current_disp_bottom;

			if (!gxx_gm_disp_[index].disp_control_)
			{
				//CStatic *disp = new CStatic();
				GxxGmStatic *disp = new GxxGmStatic();
				disp->Create(_T("GxxGmPlayer"), WS_CHILD | SS_NOTIFY | SS_SUNKEN, rect, (CWnd*)pCwnd_, BASE_DISP_ID + index);

				// ����ʾ����ֵ���Ӵ��ڣ�Ȼ����ʾ�Ӵ���
				gxx_gm_disp_[index].SetDispControl(disp->GetSafeHwnd(), current_disp_left, current_disp_top, current_disp_right, current_disp_bottom);
				gxx_gm_disp_[index].SetBackgroundImage(".\\res\\bkres.dll");	// ������ر���ͼ��BMPͼ��ֱ�Ӹĳ�dllͼ��
			}
			else
			{
				// ����ʾ����ֵ���Ӵ��ڣ�Ȼ����ʾ�Ӵ���
				gxx_gm_disp_[index].UpdateDispRect(current_disp_left, current_disp_top, current_disp_right, current_disp_bottom);
			}

			gxx_gm_disp_[index].ShowDispWindow(current_disp_left, current_disp_top, current_disp_right, current_disp_bottom);

			++index;
		}
	}

	return errCode;
}

int GxxGmMultiDisp::GetCurrentDispCount()
{
	return current_disp_count_;
}

int GxxGmMultiDisp::Play(const char *url, const char *play_info, int disp_index /* = -1 */, bool is_real /* = true */)
{
	int errCode = 0;

	if (disp_index > current_disp_count_)
		return -1;

	int free_index = -1;
	if (disp_index == -1)
	{
		// ��һ�����еĲ��Ŵ���
		for (int index = 0; index < current_disp_count_; ++index)
		{
			if (!gxx_gm_disp_[index].IsBusy())
			{
				free_index = index;
				break;
			}
		}

		if (free_index != -1)
			errCode = gxx_gm_disp_[free_index].Play(url, play_info, is_real);
		else
			errCode = -6002;
	}
	else
	{
		if (gxx_gm_disp_[disp_index].IsBusy())
		{
			// ��һ�����еĲ��Ŵ���
			for (int index = 0; index < current_disp_count_; ++index)
			{
				if (!gxx_gm_disp_[index].IsBusy())
				{
					free_index = index;
					break;
				}
			}

			if (free_index != -1)
				errCode = gxx_gm_disp_[free_index].Play(url, play_info, is_real);
			else
				errCode = -6002;
		}
		else
			errCode = gxx_gm_disp_[disp_index].Play(url, play_info, is_real);
	}

	return errCode;
}

int GxxGmMultiDisp::Pause(int disp_index)
{
	int errCode = 0;

	gxx_gm_disp_[disp_index].Pause();

	return errCode;
}

int GxxGmMultiDisp::Resume(int disp_index)
{
	int errCode = 0;

	// �ݲ�֧�֣������߼�Ҫ��һ��

	return errCode;
}

int GxxGmMultiDisp::Stop(int disp_index)
{
	int errCode = 0;

	gxx_gm_disp_[disp_index].Stop();

	return errCode;
}