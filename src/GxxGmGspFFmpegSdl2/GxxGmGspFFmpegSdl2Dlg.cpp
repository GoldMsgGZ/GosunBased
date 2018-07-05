
// GxxGmGspFFmpegSdl2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GxxGmGspFFmpegSdl2.h"
#include "GxxGmGspFFmpegSdl2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGxxGmGspFFmpegSdl2Dlg �Ի���




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


// CGxxGmGspFFmpegSdl2Dlg ��Ϣ�������

BOOL CGxxGmGspFFmpegSdl2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_cSSIp.SetWindowText(_T("127.0.0.1"));
	m_cSSPort.SetWindowText(_T("10086"));
	m_cDevId.SetWindowText(_T("110"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGxxGmGspFFmpegSdl2Dlg::OnPaint()
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
		WriteLog("��¼����ý�������ʧ�ܣ�");
		return ;
	}
	else
		WriteLog("��¼����ý��������ɹ���");
}

void CGxxGmGspFFmpegSdl2Dlg::OnBnClickedBtnPlay()
{
	CString str_id;
	m_cDevId.GetWindowText(str_id);

	USES_CONVERSION;
	int errCode = client.Play(T2A(str_id.GetBuffer(0)));
	if (errCode != 0)
	{
		WriteLog("����ʧ�ܣ�");
		return ;
	}
	else
		WriteLog("�����ɹ���");
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
		// ��ѡ���ˣ�����
	}
	else
	{
		// ûѡ��
	}
}
