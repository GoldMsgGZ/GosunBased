
// GxxGmMultiDispDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GxxGmMultiDispDemo.h"
#include "GxxGmMultiDispDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CGxxGmMultiDispDemoDlg �Ի���




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
	DDX_Control(pDX, IDC_EDIT2, m_cUrl);
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
END_MESSAGE_MAP()


// CGxxGmMultiDispDemoDlg ��Ϣ�������

BOOL CGxxGmMultiDispDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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
	pCwnd->GetWindowRect(&rect);

	TCHAR string_width[4096] = {0};
	TCHAR string_height[4096] = {0};
	_stprintf_s(string_width, 4096, _T("%d"), rect.Width());
	_stprintf_s(string_height, 4096, _T("%d"), rect.Height());
	m_cScreenWidth.SetWindowText(string_width);
	m_cScreenHeight.SetWindowText(string_height);

	m_cUrl.SetWindowText(_T("http://127.0.0.1/live/t.mp4"));

	gxx_gm_multi_disp_.Initialize((void*)pCwnd->GetSafeHwnd());

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGxxGmMultiDispDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGxxGmMultiDispDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGxxGmMultiDispDemoDlg::OnBnClickedBtnDivisionSubscreen()
{
	// ����
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
	// �������Ŵ��ڴ�С
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
	CString url;
	m_cUrl.GetWindowText(url);

	USES_CONVERSION;
	const char * play_info = "{ deviceid : \"00000000000000000001\", userid : \"000001\", username : \"JuZhang\" }";
	int errCode = gxx_gm_multi_disp_.Play(T2A(url.GetBuffer(0)), play_info);
}

void CGxxGmMultiDispDemoDlg::OnBnClickedBtnPause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CGxxGmMultiDispDemoDlg::OnBnClickedBtnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
