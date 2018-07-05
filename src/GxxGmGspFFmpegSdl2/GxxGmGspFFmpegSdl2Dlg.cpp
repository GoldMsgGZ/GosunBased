
// GxxGmGspFFmpegSdl2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GxxGmGspFFmpegSdl2.h"
#include "GxxGmGspFFmpegSdl2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGxxGmGspFFmpegSdl2Dlg 对话框




CGxxGmGspFFmpegSdl2Dlg::CGxxGmGspFFmpegSdl2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGxxGmGspFFmpegSdl2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGxxGmGspFFmpegSdl2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SSIP, m_cSSIp);
	DDX_Control(pDX, IDC_EDIT_SSPORT, m_cSSPort);
	DDX_Control(pDX, IDC_EDIT_DEVID, m_cDevId);
	DDX_Control(pDX, IDC_CHECK_SPEAK, m_cSpeak);
	DDX_Control(pDX, IDC_LIST_LOG, m_cLog);
}

BEGIN_MESSAGE_MAP(CGxxGmGspFFmpegSdl2Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CGxxGmGspFFmpegSdl2Dlg::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDC_BTN_PLAY, &CGxxGmGspFFmpegSdl2Dlg::OnBnClickedBtnPlay)
	ON_BN_CLICKED(IDC_BTN_STOP, &CGxxGmGspFFmpegSdl2Dlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_CHECK_SPEAK, &CGxxGmGspFFmpegSdl2Dlg::OnBnClickedCheckSpeak)
END_MESSAGE_MAP()


// CGxxGmGspFFmpegSdl2Dlg 消息处理程序

BOOL CGxxGmGspFFmpegSdl2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_cSSIp.SetWindowText(_T("127.0.0.1"));
	m_cSSPort.SetWindowText(_T("10086"));
	m_cDevId.SetWindowText(_T("110"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGxxGmGspFFmpegSdl2Dlg::OnPaint()
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
HCURSOR CGxxGmGspFFmpegSdl2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGxxGmGspFFmpegSdl2Dlg::WriteLog(const char *log)
{
	USES_CONVERSION;
	m_cLog.AddString(A2T(log));
	int c = m_cLog.GetCount();
	m_cLog.SetCurSel(c);
}

void CGxxGmGspFFmpegSdl2Dlg::OnBnClickedBtnLogin()
{
	CString str_ip, str_port;
	m_cSSIp.GetWindowText(str_ip);
	m_cSSPort.GetWindowText(str_port);

	USES_CONVERSION;
	const char *ip = T2A(str_ip.GetBuffer(0));
	unsigned short port = _ttoi(str_port.GetBuffer(0));

	int errCode = client.Login(ip, port);
	if (errCode != 0)
	{
		WriteLog("登录到流媒体服务器失败！");
		return ;
	}
	else
		WriteLog("登录到流媒体服务器成功！");
}

void CGxxGmGspFFmpegSdl2Dlg::OnBnClickedBtnPlay()
{
	CString str_id;
	m_cDevId.GetWindowText(str_id);

	USES_CONVERSION;
	int errCode = client.Play(T2A(str_id.GetBuffer(0)));
	if (errCode != 0)
	{
		WriteLog("点流失败！");
		return ;
	}
	else
		WriteLog("点流成功！");
}

void CGxxGmGspFFmpegSdl2Dlg::OnBnClickedBtnStop()
{
	client.Stop();
}

void CGxxGmGspFFmpegSdl2Dlg::OnBnClickedCheckSpeak()
{
	int checked = m_cSpeak.GetCheck();

	if (checked)
	{
		// 被选中了，调用
	}
	else
	{
		// 没选中
	}
}
