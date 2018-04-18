
// GxxGmMultiDispDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GxxGmMultiDispDemo.h"
#include "GxxGmMultiDispDemoDlg.h"

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


// CGxxGmMultiDispDemoDlg 对话框




CGxxGmMultiDispDemoDlg::CGxxGmMultiDispDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGxxGmMultiDispDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGxxGmMultiDispDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ROW_COUNT, m_cDispRows);
	DDX_Control(pDX, IDC_COMBO_LIST_COUNT, m_cDispLists);
	DDX_Control(pDX, IDC_EDIT_WIDTH, m_cScreenWidth);
	DDX_Control(pDX, IDC_EDIT_HEIGHT, m_cScreenHeight);
	DDX_Control(pDX, IDC_EDIT_URL, m_cUrl);
	DDX_Control(pDX, IDC_EDIT_PLAY_PARAM, m_cPlayParam);
	DDX_Control(pDX, IDC_EDIT_DISP_INDEX, m_cDispIndex);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_cStateText);
}

BEGIN_MESSAGE_MAP(CGxxGmMultiDispDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_DIVISION_SUBSCREEN, &CGxxGmMultiDispDemoDlg::OnBnClickedBtnDivisionSubscreen)
	ON_BN_CLICKED(IDC_BUTTON1, &CGxxGmMultiDispDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_PLAY, &CGxxGmMultiDispDemoDlg::OnBnClickedBtnPlay)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CGxxGmMultiDispDemoDlg::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_STOP, &CGxxGmMultiDispDemoDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_RESUME, &CGxxGmMultiDispDemoDlg::OnBnClickedBtnResume)
	ON_BN_CLICKED(IDC_BTN_GET_PLAYPARAM, &CGxxGmMultiDispDemoDlg::OnBnClickedBtnGetPlayparam)
	ON_BN_CLICKED(IDC_BTN_GET_URL, &CGxxGmMultiDispDemoDlg::OnBnClickedBtnGetUrl)
	ON_BN_CLICKED(IDC_BTN_GET_PLAYPARAM3, &CGxxGmMultiDispDemoDlg::OnBnClickedBtnGetPlayparam3)
END_MESSAGE_MAP()


// CGxxGmMultiDispDemoDlg 消息处理程序

BOOL CGxxGmMultiDispDemoDlg::OnInitDialog()
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
	m_cDispRows.AddString(_T("1"));
	m_cDispRows.AddString(_T("2"));
	m_cDispRows.AddString(_T("3"));
	m_cDispRows.AddString(_T("4"));
	m_cDispRows.AddString(_T("5"));
	m_cDispRows.AddString(_T("6"));
	m_cDispRows.AddString(_T("7"));
	m_cDispRows.AddString(_T("8"));
	m_cDispRows.AddString(_T("9"));
	m_cDispRows.SetCurSel(0);

	m_cDispLists.AddString(_T("1"));
	m_cDispLists.AddString(_T("2"));
	m_cDispLists.AddString(_T("3"));
	m_cDispLists.AddString(_T("4"));
	m_cDispLists.AddString(_T("5"));
	m_cDispLists.AddString(_T("6"));
	m_cDispLists.AddString(_T("7"));
	m_cDispLists.AddString(_T("8"));
	m_cDispLists.AddString(_T("9"));
	m_cDispLists.SetCurSel(0);

	CWnd *pCwnd = GetDlgItem(IDC_STATIC_SCREEN);
	CRect rect;
	//pCwnd->GetWindowRect(&rect);
	pCwnd->GetClientRect(&rect);

	TCHAR string_width[4096] = {0};
	TCHAR string_height[4096] = {0};
	_stprintf_s(string_width, 4096, _T("%d"), rect.Width());
	_stprintf_s(string_height, 4096, _T("%d"), rect.Height());
	m_cScreenWidth.SetWindowText(string_width);
	m_cScreenHeight.SetWindowText(string_height);

	m_cUrl.SetWindowText(_T("http://127.0.0.1/live/t.mp4"));

	CButton *realmode_checkbox = (CButton *)GetDlgItem(IDC_CHECK_REALMODE);
	realmode_checkbox->SetCheck(1);

	//gxx_gm_multi_disp_.Initialize((void*)pCwnd->GetSafeHwnd());
	
	// 创建一个子窗口贴在控件上
	multi_disp_screen_.Create(IDD_DLG_MAINSCREEN, pCwnd);
	multi_disp_screen_.MoveWindow(&rect);
	multi_disp_screen_.ShowWindow(TRUE);

	gxx_gm_multi_disp_.Initialize((void*)multi_disp_screen_.GetSafeHwnd(), 4, 4);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGxxGmMultiDispDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGxxGmMultiDispDemoDlg::OnPaint()
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
HCURSOR CGxxGmMultiDispDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGxxGmMultiDispDemoDlg::OnBnClickedBtnDivisionSubscreen()
{
	// 分屏
	CString str_disp_rows;
	CString str_disp_links;

	m_cDispRows.GetWindowText(str_disp_rows);
	m_cDispLists.GetWindowText(str_disp_links);

	int disp_rows = _ttoi(str_disp_rows.GetBuffer(0));
	int disp_links = _ttoi(str_disp_links.GetBuffer(0));

	int errCode = gxx_gm_multi_disp_.ReDivision(disp_rows, disp_links);
}

void CGxxGmMultiDispDemoDlg::OnBnClickedButton1()
{
	// 调整播放窗口大小
	CString str_screen_width;
	CString str_screen_height;

	m_cScreenWidth.GetWindowText(str_screen_width);
	m_cScreenHeight.GetWindowText(str_screen_height);

	int screen_width = _ttoi(str_screen_width.GetBuffer(0));
	int screen_height = _ttoi(str_screen_height.GetBuffer(0));

	int errCode = gxx_gm_multi_disp_.ChangeScreenSize(screen_width, screen_height);
}

void CGxxGmMultiDispDemoDlg::OnBnClickedBtnPlay()
{
	// 取URL
	CString url;
	m_cUrl.GetWindowText(url);

	// 取子窗口ID
	int disp_id = -1;
	CButton *use_id_checkbox = (CButton *)GetDlgItem(IDC_CHECK_USE_INDEX);
	if (use_id_checkbox->GetCheck() == 1)
	{
		CString id;
		m_cDispIndex.GetWindowText(id);
		disp_id = _ttoi(id.GetBuffer(0));
	}

	USES_CONVERSION;
	// 取播放参数
	CString param;
	m_cPlayParam.GetWindowText(param);
	const char * play_info = T2A(param.GetBuffer(0));

	// 取播放模式
	bool is_real = true;
	CButton *realmode_checkbox = (CButton *)GetDlgItem(IDC_CHECK_REALMODE);
	if (realmode_checkbox->GetCheck() == 0)
		is_real = false;

	// 调用播放
	int errCode = gxx_gm_multi_disp_.Play(T2A(url.GetBuffer(0)), play_info, disp_id, is_real);
}

void CGxxGmMultiDispDemoDlg::OnBnClickedBtnPause()
{
	// 取子窗口ID
	int disp_id = -1;
	CButton *use_id_checkbox = (CButton *)GetDlgItem(IDC_CHECK_USE_INDEX);
	if (use_id_checkbox->GetCheck() == 1)
	{
		CString id;
		m_cDispIndex.GetWindowText(id);
		disp_id = _ttoi(id.GetBuffer(0));
	}

	gxx_gm_multi_disp_.Pause(disp_id);
}

void CGxxGmMultiDispDemoDlg::OnBnClickedBtnStop()
{
	// 取子窗口ID
	int disp_id = -1;
	CButton *use_id_checkbox = (CButton *)GetDlgItem(IDC_CHECK_USE_INDEX);
	if (use_id_checkbox->GetCheck() == 1)
	{
		CString id;
		m_cDispIndex.GetWindowText(id);
		disp_id = _ttoi(id.GetBuffer(0));
	}

	gxx_gm_multi_disp_.Stop(disp_id);
}

void CGxxGmMultiDispDemoDlg::OnBnClickedBtnResume()
{
	// 取子窗口ID
	int disp_id = -1;
	CButton *use_id_checkbox = (CButton *)GetDlgItem(IDC_CHECK_USE_INDEX);
	if (use_id_checkbox->GetCheck() == 1)
	{
		CString id;
		m_cDispIndex.GetWindowText(id);
		disp_id = _ttoi(id.GetBuffer(0));
	}

	gxx_gm_multi_disp_.Resume(disp_id);
}

void CGxxGmMultiDispDemoDlg::OnBnClickedBtnGetPlayparam()
{
	// 取子窗口ID
	int disp_id = -1;
	CButton *use_id_checkbox = (CButton *)GetDlgItem(IDC_CHECK_USE_INDEX);
	if (use_id_checkbox->GetCheck() == 1)
	{
		CString id;
		m_cDispIndex.GetWindowText(id);
		disp_id = _ttoi(id.GetBuffer(0));
	}

	USES_CONVERSION;
	std::string play_param = gxx_gm_multi_disp_.GetPlayInfo(disp_id);
	CString result;
	result.Format(_T("播放参数为：%s"), A2T(play_param.c_str()));

	CString state_text;
	m_cStateText.GetWindowText(state_text);
	state_text.Append(_T("\r\n"));
	state_text.Append(result);
	m_cStateText.SetWindowText(state_text);
}

void CGxxGmMultiDispDemoDlg::OnBnClickedBtnGetUrl()
{
	// 取子窗口ID
	int disp_id = -1;
	CButton *use_id_checkbox = (CButton *)GetDlgItem(IDC_CHECK_USE_INDEX);
	if (use_id_checkbox->GetCheck() == 1)
	{
		CString id;
		m_cDispIndex.GetWindowText(id);
		disp_id = _ttoi(id.GetBuffer(0));
	}

	USES_CONVERSION;
	std::string url = gxx_gm_multi_disp_.GetUrl(disp_id);
	CString result;
	result.Format(_T("播放URL为：%s"), A2T(url.c_str()));

	CString state_text;
	m_cStateText.GetWindowText(state_text);
	state_text.Append(_T("\r\n"));
	state_text.Append(result);
	m_cStateText.SetWindowText(state_text);
}

void CGxxGmMultiDispDemoDlg::OnBnClickedBtnGetPlayparam3()
{
	// 取子窗口ID
	int disp_id = -1;
	CButton *use_id_checkbox = (CButton *)GetDlgItem(IDC_CHECK_USE_INDEX);
	if (use_id_checkbox->GetCheck() == 1)
	{
		CString id;
		m_cDispIndex.GetWindowText(id);
		disp_id = _ttoi(id.GetBuffer(0));
	}

	USES_CONVERSION;
	std::string deviceid = gxx_gm_multi_disp_.GetDeviceId(disp_id);
	CString result;
	result.Format(_T("设备ID为：%s"), A2T(deviceid.c_str()));

	CString state_text;
	m_cStateText.GetWindowText(state_text);
	state_text.Append(_T("\r\n"));
	state_text.Append(result);
	m_cStateText.SetWindowText(state_text);
}
