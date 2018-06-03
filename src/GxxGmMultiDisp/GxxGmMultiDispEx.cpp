#include "GxxGmMultiDispEx.h"
#include "..\GxxGmPlayBase\GxxGmPlayBase.h"
#include "..\GxxGmPlayer\GxxGmPlayer.h"
#include "GxxGmMultiDispMsgId.h"
#include <Windows.h>
#include <WindowsX.h>


GxxGmDispEx::GxxGmDispEx()
: disp_hwnd_(0)
, father_hwnd_(0)
, row_index_(0)
, list_index_(0)
, player_(new GxxGmPlayer())
, is_real_(false)
, old_proc_(0)
{

}

GxxGmDispEx::~GxxGmDispEx()
{
	SetWindowLongPtr((HWND)disp_hwnd_, GWLP_WNDPROC, (LPARAM)(WNDPROC)old_proc_);

	disp_hwnd_   = 0;
	father_hwnd_ = 0;
	row_index_	 = 0;
	list_index_  = 0;
	old_proc_	 = 0;
}

void GxxGmDispEx::Attach(int self_hwnd, int father_hwnd)
{
	disp_hwnd_ = self_hwnd;
	father_hwnd_ = father_hwnd;
	player_->SetScreenWindow((void*)disp_hwnd_);

	// 
	old_proc_ = (long)(WNDPROC)SetWindowLongPtr((HWND)disp_hwnd_, GWLP_WNDPROC, (LPARAM)(WNDPROC)GxxGmDispEx::WinProc);
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
		// ���沥����Ϣ
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
	int errCode = player_->Resume();
	return 0;
}

int GxxGmDispEx::Stop()
{
	player_->Stop();
	play_info_.clear();
	url_.clear();
	return 0;
}

int GxxGmDispEx::OpenAudio()
{
	int errCode = player_->OpenAudio();
	return errCode;
}

int GxxGmDispEx::SetVolume(int volume)
{
	int errCode = player_->SetVolume(volume);
	return errCode;
}

int GxxGmDispEx::GetVolume()
{
	return player_->GetVolume();
}

int GxxGmDispEx::CloseAudio()
{
	int errCode = player_->CloseAudio();
	return errCode;
}

int GxxGmDispEx::CapturePicture(const char *save_path, int img_type)
{
	// δʵ��
	int errCode = player_->CapturePicture(save_path, img_type);
	return errCode;
}

int GxxGmDispEx::Fast()
{
	int errCode = player_->Fast();
	return errCode;
}

int GxxGmDispEx::Slow()
{
	int errCode = player_->Slow();
	return errCode;
}

int GxxGmDispEx::SetPlaySpeed(double speed)
{
	int errCode = player_->SetPlaySpeed(speed);
	return errCode;
}

int GxxGmDispEx::Next()
{
	int errCode = player_->Next();
	return errCode;
}

int GxxGmDispEx::Back()
{
	int errCode = player_->Back();
	return errCode;
}

int GxxGmDispEx::SetPlayPos(unsigned __int64 pulTimeStamp)
{
	int errCode = player_->SetPlayPos(pulTimeStamp);
	return errCode;
}

int GxxGmDispEx::ClearPlayBuffer()
{
	int errCode = player_->ClearPlayBuffer();
	return errCode;
}

int GxxGmDispEx::RefreshView()
{
	int errCode = player_->RefreshView();
	return errCode;
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
	return player_->IsRealMode();
}

#ifndef _WIN64
int __stdcall GxxGmDispEx::WinProc(int hwnd, unsigned int msg, unsigned int wParam, long lParam)
#else
int __stdcall GxxGmDispEx::WinProc(__int64 hwnd, unsigned int msg, unsigned __int64 wParam, __int64 lParam)
#endif
{
	int errCode = 0;

	switch (msg)
	{
	case WM_PAINT:
		{
			// 0x000F
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint((HWND)hwnd, &ps);

			RECT rc;
			GetClientRect((HWND)hwnd, &rc);

			HBRUSH frame_brush;
			HBRUSH bkguard_brush = CreateSolidBrush(RGB(25, 25, 25));
			if ((wParam == 0) || (wParam == MSG_PAINT_NORMAL_FRAME))
				frame_brush = CreateSolidBrush(RGB(25, 25, 25));//CreateSolidBrush(RGB(30, 140, 250));
			else if (wParam == MSG_PAINT_ACTIVE_FRAME)
				frame_brush = CreateSolidBrush(RGB(30, 140, 250));

			FillRect(hDC, &rc, bkguard_brush);
			FrameRect(hDC, &rc, frame_brush);

			EndPaint((HWND)hwnd, &ps);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			// 0x0201
			int mouse_pos_x = GET_X_LPARAM(lParam);
			int mouse_pos_y = GET_Y_LPARAM(lParam);
			GxxGmPlayBase::DebugStringOutput("[GxxGmDispEx MESSAGE] ���� %d ���������£����꣺(%d, %d) MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", hwnd, mouse_pos_x, mouse_pos_y, msg, wParam, lParam);

			// ֪ͨ�ϲ㣬���ĵ�ǰ��Ծ����
			//BOOL bret = PostMessage((HWND)father_hwnd_, (UINT)MSG_PAINT_ACTIVE_FRAME, (WPARAM)hwnd, (LPARAM)0);
			//if (!bret)
			//	GxxGmPlayBase::DebugStringOutput("[GxxGmDispEx MESSAGE] ���� %d ���������£����꣺(%d, %d) ���ͻ��ƻ�Ծ������Ϣʧ�ܣ� MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", hwnd, mouse_pos_x, mouse_pos_y, msg, wParam, lParam);
			//else
			//	GxxGmPlayBase::DebugStringOutput("[GxxGmDispEx MESSAGE] ���� %d ���������£����꣺(%d, %d) ���ͻ��ƻ�Ծ������Ϣ�ɹ��� MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", hwnd, mouse_pos_x, mouse_pos_y, msg, wParam, lParam);
		}
		break;
	default:
		break;
	}
	
	return DefWindowProc((HWND)hwnd, msg, wParam, lParam);
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
	MessageBoxA(NULL, "GxxGmMultiDispEx���캯�� >>> �ȴ�����������", "����", 0);
#endif
}

GxxGmMultiDispEx::~GxxGmMultiDispEx()
{
	current_disp_count_ = 0;
}

int GxxGmMultiDispEx::Init(int screen_hwnd, int row_count, int list_count)
{
	int errCode = 0;

	// ���ݴ���Ĵ��ھ��������Ļ��Χ�������������Ļ���
	screen_hwnd_ = screen_hwnd;
	RECT screen_rect;
	BOOL bret = ::GetWindowRect((HWND)screen_hwnd_, &screen_rect);
	if (!bret) {
		errCode = GetLastError();
		GxxGmPlayBase::DebugStringOutput("��ȡ��Ļ��Χʧ�ܣ������룺%d\n", errCode);
		return errCode;
	}

	screen_width_ = screen_rect.right - screen_rect.left;
	screen_height_ = screen_rect.bottom - screen_rect.top;

	// ִ�з���
	errCode = ReDivision(row_count, list_count);

	return errCode;
}

int GxxGmMultiDispEx::ReDivision(int row_count, int list_count)
{
	int errCode = 0;

	// �ȼ���Ƿ��Ѿ���ʼ���ˣ���Ȼ����Ĳ���������Ч��

	// ���¼���
	row_count_ = row_count;
	list_count_ = list_count;
	current_disp_count_ = row_count_ * list_count_;

	// �����ÿһ�������Ŀ��
	int average_disp_width = screen_width_ / list_count;
	int average_disp_height = screen_height_ / row_count;

	// �Ȱ����������������Ѿ�Attach�˵Ŀؼ�������
	for (int index = 0; index < MAX_DISP_COUNT_EX; ++index)
	{
		gxx_gm_disp_ex_[index].ShowWindow(SW_HIDE);
	}

	// �����������շ���������ʼ����STATIC������Ϊ��ʾ����
	for (int row_index = 0; row_index < row_count; ++row_index)
	{
		for (int list_index = 0; list_index < list_count; ++list_index)
		{
			// �������������������㷨���Ǻ�����
			int disp_index = row_index * row_count_ + list_index;

			// ��������
			int disp_left	= list_index * average_disp_width;
			int disp_top	= row_index	 * average_disp_height;
			int disp_right	= disp_left  + average_disp_width;
			int disp_bottom = disp_top   + average_disp_height;

			GxxGmPlayBase::DebugStringOutput("����������%02d\tx:%d\ty:%d\twidth:%d\theight:%d\n", disp_index, disp_left, disp_top, average_disp_width, average_disp_height);

			if (!gxx_gm_disp_ex_[disp_index].IsAttached())
			{
				HWND disp_hwnd = ::CreateWindowA("STATIC", "������ʾ����", WS_CHILD|WS_VISIBLE|SS_NOTIFY|SS_SUNKEN|SS_BITMAP, 
					disp_left, disp_top, average_disp_width, average_disp_height, (HWND)screen_hwnd_,
					NULL, NULL, NULL);

				if (disp_hwnd == NULL)
				{
					errCode = GetLastError();
					GxxGmPlayBase::DebugStringOutput("��������ʧ�ܣ������룺%d\n", errCode);
					return errCode;
				}

				GxxGmPlayBase::DebugStringOutput("�������� %d �ɹ������ھ��Ϊ��%d\n", disp_index, (int)disp_hwnd);

				// �����������͸����
				gxx_gm_disp_ex_[disp_index].Attach((int)disp_hwnd, (int)screen_hwnd_);

				// ���÷�������
				gxx_gm_disp_ex_[disp_index].SetLocation(row_index, list_index);

				// �����Ƿ���Ҫ����һ����Ϣ�����������ڴ����Ӧ���Ӵ�����Ϣ
			}
			

			// �ƶ�����
			gxx_gm_disp_ex_[disp_index].MoveWindow(disp_left, disp_top, average_disp_width, average_disp_height);

			// ��ʾ����
			gxx_gm_disp_ex_[disp_index].ShowWindow(SW_SHOW);
		}
	}

	// ��󣬽����б����ص��ģ����ڲ��ŵķ���ֹͣ����
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
		// ����Ŀ���ȥ����һ������������ֵ
		// �����жϴ��������ֵ�Ƿ��ǿ��õģ������������Χ�ڣ�����ָ���ķ����ǿ��еģ�
		if (IsAvaliableDisp(disp_index))
			real_disp_index = disp_index;
		else
		{
			// ����ֵ������
			return -6003;
		}
	}
	else if (disp_index <= 0)
	{
		// Ѱ��һ�����еĲ��Ŵ���
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
	// ��鵱ǰ�����Ƿ��ڷ�Χ��
	// �ȼ�鲥��ģʽ�������ʵʱģʽ���Ͳ�֧����ͣ�ӿ�
	return gxx_gm_disp_ex_[disp_index].Pause();
}

int GxxGmMultiDispEx::Resume(int disp_index)
{
	return gxx_gm_disp_ex_[disp_index].Resume();
}

int GxxGmMultiDispEx::Stop(int disp_index)
{
	return gxx_gm_disp_ex_[disp_index].Stop();
}

int GxxGmMultiDispEx::StopAll()
{
	int errCode = 0;

	for (int index = 0; index < MAX_DISP_COUNT_EX; ++index)
	{
		errCode = gxx_gm_disp_ex_[index].Stop();
		if (errCode != 0)
			GxxGmPlayBase::DebugStringOutput("ֹͣ%d�ŷ���ʧ�ܣ������룺%d\n", index);
	}

	return errCode;
}

int GxxGmMultiDispEx::OpenAudio(int disp_index)
{
	return gxx_gm_disp_ex_[disp_index].OpenAudio();
}

int GxxGmMultiDispEx::SetVolume(int disp_index, int volume)
{
	return gxx_gm_disp_ex_[disp_index].SetVolume(volume);
}

int GxxGmMultiDispEx::GetVolume(int disp_index)
{
	return gxx_gm_disp_ex_[disp_index].GetVolume();
}

int GxxGmMultiDispEx::CloseAudio(int disp_index)
{
	return gxx_gm_disp_ex_[disp_index].CloseAudio();
}

int GxxGmMultiDispEx::CapturePicture(int disp_index, const char *save_path, int img_type)
{
	if (gxx_gm_disp_ex_[disp_index].IsPlaying())
		return gxx_gm_disp_ex_[disp_index].CapturePicture(save_path, img_type);
	else
		return -1;
}

int GxxGmMultiDispEx::Fast(int disp_index)
{
	return gxx_gm_disp_ex_[disp_index].Fast();
}

int GxxGmMultiDispEx::Slow(int disp_index)
{
	return gxx_gm_disp_ex_[disp_index].Slow();
}

int GxxGmMultiDispEx::SetPlaySpeed(int disp_index, double speed)
{
	return gxx_gm_disp_ex_[disp_index].SetPlaySpeed(speed);
}

int GxxGmMultiDispEx::Next(int disp_index)
{
	return gxx_gm_disp_ex_[disp_index].Next();
}

int GxxGmMultiDispEx::Back(int disp_index)
{
	return gxx_gm_disp_ex_[disp_index].Back();
}

int GxxGmMultiDispEx::SetPlayPos(int disp_index, unsigned __int64 pulTimeStamp)
{
	return gxx_gm_disp_ex_[disp_index].SetPlayPos(pulTimeStamp);
}

int GxxGmMultiDispEx::ClearPlayBuffer(int disp_index)
{
	return gxx_gm_disp_ex_[disp_index].ClearPlayBuffer();
}

int GxxGmMultiDispEx::RefreshView(int disp_index)
{
	return gxx_gm_disp_ex_[disp_index].RefreshView();
}

//////////////////////////////////////////////////////////////////////////
//
//

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
	// ����Ƿ�Ϊ���÷���
	// ���ȣ�����������Ƿ��ڿ��÷�Χ��
	if ((disp_index > -1) && (disp_index < current_disp_count_))
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