
// GxxGmPlayCoreDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GxxGmPlayCore.h"
#include "GxxGmPlayCoreDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGxxGmPlayCoreDlg 对话框




CGxxGmPlayCoreDlg::CGxxGmPlayCoreDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGxxGmPlayCoreDlg::IDD, pParent)
	, player_(new GxxGmPlayer())
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGxxGmPlayCoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_URL, m_cUrl);
	DDX_Control(pDX, IDC_EDIT_SS_IP, m_cSSIp);
	DDX_Control(pDX, IDC_EDIT_SS_PORT, m_cSSPort);
	DDX_Control(pDX, IDC_EDIT_DEVID, m_cDevId);
}

BEGIN_MESSAGE_MAP(CGxxGmPlayCoreDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_PLAY, &CGxxGmPlayCoreDlg::OnBnClickedBtnPlay)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CGxxGmPlayCoreDlg::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_STOP, &CGxxGmPlayCoreDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_GET_URL, &CGxxGmPlayCoreDlg::OnBnClickedBtnGetUrl)
	ON_BN_CLICKED(IDC_BTN_CLEANUP, &CGxxGmPlayCoreDlg::OnBnClickedBtnCleanup)
END_MESSAGE_MAP()


// CGxxGmPlayCoreDlg 消息处理程序

BOOL CGxxGmPlayCoreDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//m_cUrl.SetWindowText(_T("rtsp://127.0.0.1:554/hkstv"));
	m_cUrl.SetWindowText(_T("http://127.0.0.1/live/bob.flv"));

	HWND window = NULL;
	GetDlgItem(IDC_STATIC_SCREEN, &window);
	player_->SetScreenWindow(window);

	m_cSSIp.SetWindowText(_T("127.0.0.1"));
	m_cSSPort.SetWindowText(_T("10086"));
	m_cDevId.SetWindowText(_T("110"));

	SSInit();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGxxGmPlayCoreDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGxxGmPlayCoreDlg::OnPaint()
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
HCURSOR CGxxGmPlayCoreDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGxxGmPlayCoreDlg::OnBnClickedBtnPlay()
{
	CString url;
	m_cUrl.GetWindowText(url);

	USES_CONVERSION;
	int errCode = player_->Open(T2A(url.GetBuffer(0)));
	if (errCode != 0)
	{
		MessageBox(_T("打开媒体失败！"), _T(""), 0);
		return;
	}
}

void CGxxGmPlayCoreDlg::OnBnClickedBtnPause()
{
	player_->Pause();
}

void CGxxGmPlayCoreDlg::OnBnClickedBtnStop()
{
	player_->Stop();
}


void CGxxGmPlayCoreDlg::OnBnClickedBtnGetUrl()
{
	CString sz_ssip;
	CString sz_devid;
	CString sz_ssport;

	m_cSSIp.GetWindowText(sz_ssip);
	m_cSSPort.GetWindowText(sz_ssport);
	m_cDevId.GetWindowText(sz_devid);

	USES_CONVERSION;
	GOSUN_SERVER_INFO srv_info;
	strcpy(srv_info.servIP, T2A(sz_ssip.GetBuffer(0)));
	strcpy(srv_info.username, "admin");
	strcpy(srv_info.password, "admin");
	int port = _ttoi(sz_ssport.GetBuffer(0));
	srv_info.servPort = port;

	int errCode = SSLogin(&handle, srv_info);
	if (errCode != GOSUN_SUCCESS)
	{
		// 
		return ;
	}

	SS_DEVICE_INFO dsj_info;
	ZeroMemory(&dsj_info, sizeof(SS_DEVICE_INFO));
	strcpy_s(dsj_info.devCodeid, GOSUN_CODEID_LEN, T2A(sz_devid.GetString()));
	dsj_info.channel = 1;
	strcpy_s(dsj_info.username, GOSUN_USER_INFO_LEN, "admin");
	strcpy_s(dsj_info.password, GOSUN_USER_INFO_LEN, "admin");
	dsj_info.modelID = SDK_DEV_GXX;
	dsj_info.streamType = 1;

	char url[512] = {0};
	errCode = SSGetURL(handle, url, 512, dsj_info);
	if (errCode != GOSUN_SUCCESS)
	{
		// 获取URL失败！
		return ;
	}

	m_cUrl.SetWindowText(A2T(url));
}

void CGxxGmPlayCoreDlg::OnBnClickedBtnCleanup()
{
	SSLogout(handle);
}
