
// GxxGmGspStreamHandlerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GxxGmGspStreamHandler.h"
#include "GxxGmGspStreamHandlerDlg.h"



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


// CGxxGmGspStreamHandlerDlg �Ի���




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


// CGxxGmGspStreamHandlerDlg ��Ϣ�������

BOOL CGxxGmGspStreamHandlerDlg::OnInitDialog()
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
	SSInit();

	m_cDevId.SetWindowText(_T("123456"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGxxGmGspStreamHandlerDlg::OnPaint()
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
	sprintf(msg, "��Ƶ���룺%d ��Ƶ���룺%d ֡���ͣ�%d ֡�ʣ�%d ʱ���%d.%d\n", video_codec_id, audio_codec_id, frame_type, frame_rate, time1, time2);
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

	// �����⸴����Ϣ

	errCode = SSPlay(stream_handle_);
	if (errCode != GOSUN_SUCCESS)
		return ;
}

void CGxxGmGspStreamHandlerDlg::OnBnClickedButtonLogin()
{
	

	// ���ӵ�������
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
