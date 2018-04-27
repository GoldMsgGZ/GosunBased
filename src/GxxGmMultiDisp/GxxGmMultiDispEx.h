#ifndef _GxxGmMultiDispEx_H_
#define _GxxGmMultiDispEx_H_

//////////////////////////////////////////////////////////////////////////
//
// �µĶ��������࣬������Ļ����Ļ��ֺͲ���ȫ��ͨ��HWND�������

class GxxGmDispEx
{
public:
	GxxGmDispEx();
	~GxxGmDispEx();

public:
	void Attach(int self_hwnd, int father_hwnd);

	void SetLocation(int row_index, int list_index);

	// �ƶ����ڣ����ڵ���������ʾλ��
	int MoveWindow(int x, int y, int width, int height);

	// ��ʾ���ڣ�������ʾ������
	int ShowWindow(int nCmdShow);

public:
	bool IsAttached();

private:
	// ������ʾ���
	int disp_hwnd_;
	int father_hwnd_;

	// ��������
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
//	 * ������Ƶ
//	 * ������
//	 *	@url			����·��
//	 *	@play_info		���ӵĲ�����Ϣ���ַ���
//	 *	@disp_index		�Ӵ���������0~��󴰿�������-1ʱΪ�Զ��������е��Ӵ���
//	 *	@is_real		true Ϊʵʱģʽ��false Ϊ¼��ģʽ
//	 * ����ֵ
//	 */
//	int Play(const char *url, const char *play_info, int disp_index = -1, bool is_real = true);
//
//	/**
//	 * ��ͣ����
//	 */
//	int Pause(int disp_index);
//
//	/**
//	 * �ָ�����
//	 */
//	int Resume(int disp_index);
//
//	/**
//	 * ֹͣ����
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
