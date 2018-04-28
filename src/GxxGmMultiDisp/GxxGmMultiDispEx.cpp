#include "GxxGmMultiDispEx.h"
#include "..\GxxGmPlayBase\GxxGmPlayBase.h"
#include <Windows.h>

GxxGmDispEx::GxxGmDispEx()
: disp_hwnd_(0)
, father_hwnd_(0)
, row_index_(0)
, list_index_(0)
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


//////////////////////////////////////////////////////////////////////////
//
//

#define BASE_DISP_EX_ID		50001

GxxGmMultiDispEx::GxxGmMultiDispEx()
: current_disp_count_(0)
{

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
			// ��������
			int disp_index = row_index * list_index;

			// ��������
			int disp_left	= list_index * average_disp_width;
			int disp_top	= row_index	 * average_disp_height;
			int disp_right	= disp_left  + average_disp_width;
			int disp_bottom = disp_top   + average_disp_height;

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

				// �����������͸����
				gxx_gm_disp_ex_[disp_index].Attach((int)disp_hwnd, (int)screen_hwnd_);

				// ���÷�������
				gxx_gm_disp_ex_[disp_index].SetLocation(row_index, list_index);
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