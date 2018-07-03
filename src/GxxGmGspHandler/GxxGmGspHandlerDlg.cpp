
// GxxGmGspHandlerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GxxGmGspHandler.h"
#include "GxxGmGspHandlerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGxxGmGspHandlerDlg 对话框




CGxxGmGspHandlerDlg::CGxxGmGspHandlerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGxxGmGspHandlerDlg::IDD, pParent)
	, ssmgr_(new GxxGmSSMgr(this))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGxxGmGspHandlerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SS_IP, m_cSSIp);
	DDX_Control(pDX, IDC_EDIT_SS_PORT, m_cSSPort);
	DDX_Control(pDX, IDC_LIST_SS_INFO, m_cSSList);
	DDX_Control(pDX, IDC_LIST_DEV_INFO, m_cDevList);
}

BEGIN_MESSAGE_MAP(CGxxGmGspHandlerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_FOLLOW, &CGxxGmGspHandlerDlg::OnBnClickedBtnFollow)
	ON_BN_CLICKED(IDC_BTN_UNFOLLOW, &CGxxGmGspHandlerDlg::OnBnClickedBtnUnfollow)
	ON_BN_CLICKED(IDC_BTN_PLAY, &CGxxGmGspHandlerDlg::OnBnClickedBtnPlay)
	ON_BN_CLICKED(IDC_BTN_STOP, &CGxxGmGspHandlerDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_CHECK_SOUND, &CGxxGmGspHandlerDlg::OnBnClickedCheckSound)
	ON_BN_CLICKED(IDC_CHECK_RECORD, &CGxxGmGspHandlerDlg::OnBnClickedCheckRecord)
END_MESSAGE_MAP()


// CGxxGmGspHandlerDlg 消息处理程序

BOOL CGxxGmGspHandlerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_cSSIp.SetWindowText(_T("127.0.0.1"));
	m_cSSPort.SetWindowText(_T("10086"));

	m_cSSList.InsertColumn(0, _T("流媒体id"), 0, 50);
	m_cSSList.InsertColumn(1, _T("流媒体IP"), 0, 100);
	m_cSSList.InsertColumn(2, _T("流媒体端口"), 0, 50);
	m_cSSList.InsertColumn(3, _T("流媒体状态"), 0, 80);

	m_cDevList.InsertColumn(0, _T("设备编号"), 0, 100);
	m_cDevList.InsertColumn(1, _T("设备坐标"), 0, 100);
	m_cDevList.InsertColumn(2, _T("所属流媒体"), 0, 100);

	CWnd *pcwnd = GetDlgItem(IDC_STATIC_SCREEN);
	m_cScreen = pcwnd->GetSafeHwnd();

	m_cSound = GetDlgItem(IDC_CHECK_SOUND);
	m_cRecord = GetDlgItem(IDC_CHECK_RECORD);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGxxGmGspHandlerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGxxGmGspHandlerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGxxGmGspHandlerDlg::OnBnClickedBtnFollow()
{
	// 登录到指定的流媒体服务器
	CString strip;
	CString strport;

	m_cSSIp.GetWindowText(strip);
	m_cSSPort.GetWindowText(strport);

	USES_CONVERSION;
	char *ip = T2A(strip);
	int port = atoi(T2A(strport.GetBuffer(0)));

	int errCode = ssmgr_->Follow(ip, port);
	if (errCode == 0)
	{
		// 
	}
}

void CGxxGmGspHandlerDlg::OnBnClickedBtnUnfollow()
{
	// 登出指定的流媒体服务器
}

void CGxxGmGspHandlerDlg::OnBnClickedBtnPlay()
{
	// 播放实时流
}

void CGxxGmGspHandlerDlg::OnBnClickedBtnStop()
{
	// 停止播放实时流
}

void CGxxGmGspHandlerDlg::OnBnClickedCheckSound()
{
	// 打开声音
}

void CGxxGmGspHandlerDlg::OnBnClickedCheckRecord()
{
	// 开始录像
}

int CGxxGmGspHandlerDlg::Notifer(int ss_id, const char *dev_id, enum SSMgrNotiferType type, const unsigned char *data)
{
	USES_CONVERSION;
	switch (type)
	{
	case SSMgrNotiferType::DevOnline:
		{
			int count = m_cDevList.GetItemCount();
			char ss_id_str[64] = {0};
			itoa(ss_id, ss_id_str, 10);
			m_cDevList.InsertItem(count, A2T(dev_id));
			m_cDevList.SetItemText(count, 1, _T(""));
			m_cDevList.SetItemText(count, 2, A2T(ss_id_str));
		}
		break;
	case SSMgrNotiferType::DevOffline:
		{
			POSITION pos = m_cDevList.GetFirstSelectedItemPosition();
			int index = m_cDevList.GetNextSelectedItem(pos);
			m_cDevList.DeleteItem(index);
		}
		break;
	case SSMgrNotiferType::SSOnline:
		{
			struct GxxGmSSInfo *ss = (struct GxxGmSSInfo*)data;
			int count = m_cSSList.GetItemCount();
			m_cSSList.InsertItem(count, A2T(ss->ss_id));
			m_cSSList.SetItemText(count, 1, A2T(ss->ip));
			m_cSSList.SetItemText(count, 2, A2T(ss->port));
		}
		break;
	case SSMgrNotiferType::SSOffline:
		{
			//
		}
		break;
	default:
		break;
	}

	return 0;
}