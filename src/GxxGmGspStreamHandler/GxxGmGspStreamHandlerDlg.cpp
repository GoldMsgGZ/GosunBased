
// GxxGmGspStreamHandlerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GxxGmGspStreamHandler.h"
#include "GxxGmGspStreamHandlerDlg.h"



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


// CGxxGmGspStreamHandlerDlg 对话框




CGxxGmGspStreamHandlerDlg::CGxxGmGspStreamHandlerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGxxGmGspStreamHandlerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGxxGmGspStreamHandlerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DEVID, m_cDevId);
}

BEGIN_MESSAGE_MAP(CGxxGmGspStreamHandlerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_HANDLER, &CGxxGmGspStreamHandlerDlg::OnBnClickedButtonHandler)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CGxxGmGspStreamHandlerDlg::OnBnClickedButtonLogin)
END_MESSAGE_MAP()


// CGxxGmGspStreamHandlerDlg 消息处理程序

BOOL CGxxGmGspStreamHandlerDlg::OnInitDialog()
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
	SSInit();

	m_cDevId.SetWindowText(_T("123456"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGxxGmGspStreamHandlerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGxxGmGspStreamHandlerDlg::OnPaint()
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
HCURSOR CGxxGmGspStreamHandlerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CALLBACK _StreamCallback(long lHandle, FRAME_HEADER header, char *pData, long nSize, void* userData)
{
	CGxxGmGspStreamHandlerDlg *dlg = (CGxxGmGspStreamHandlerDlg*)userData;

	EnumStreamCodeID video_codec_id = header.enStremCodeId[0];
	EnumStreamCodeID audio_codec_id = header.enStremCodeId[1];

	ENUM_FRAME_TYPE frame_type = header.type;
	int frame_rate = header.rate;
	unsigned int time1 = header.stampSec;
	unsigned int time2 = header.stampMillSec;

	char msg[409600] = {0};
	sprintf(msg, "视频编码：%d 音频编码：%d 帧类型：%d 帧率：%d 时间戳%d.%d\n", video_codec_id, audio_codec_id, frame_type, frame_rate, time1, time2);
	TRACE(msg);
}

void CGxxGmGspStreamHandlerDlg::OnBnClickedButtonHandler()
{
	USES_CONVERSION;
	m_cDevId.GetWindowText(devid);
	const char *id = T2A(devid.GetBuffer(0));

	SS_DEVICE_INFO devinfo;
	ZeroMemory(&devinfo, sizeof(SS_DEVICE_INFO));
	strcpy(devinfo.chanCodeid, id); 
	strcpy(devinfo.devCodeid, id);
	devinfo.channel = 1;
	devinfo.modelID = SDK_DEV_GXX;
	devinfo.streamType = 1;
	strcpy_s(devinfo.username, GOSUN_USER_INFO_LEN, "admin");
	strcpy_s(devinfo.password, GOSUN_USER_INFO_LEN, "admin");

	char url[512] = {0};
	int errCode = SSGetURL(handle_, url, 512, devinfo);
	if (errCode != GOSUN_SUCCESS)
		return ;

	GOSUN_STREAM_HANDLE stream_handle_ = NULL;
	SDK_StruMediaMuxDesc desc;
	errCode = SSOpenEx(url, &stream_handle_, _StreamCallback, this, &desc);
	if (errCode != GOSUN_SUCCESS)
		return ;

	// 分析解复用信息

	errCode = SSPlay(stream_handle_);
	if (errCode != GOSUN_SUCCESS)
		return ;
}

void CGxxGmGspStreamHandlerDlg::OnBnClickedButtonLogin()
{
	

	// 连接到服务器
	GOSUN_SERVER_INFO info;
	ZeroMemory(&info, sizeof(GOSUN_SERVER_INFO));
	strcpy(info.servIP, "127.0.0.1");
	strcpy(info.username, "admin");
	strcpy(info.password, "admin");
	info.servPort = 10086;

	int errCode = SSLogin(&handle_, info);
	if (errCode != GOSUN_SUCCESS)
		return ;
}
