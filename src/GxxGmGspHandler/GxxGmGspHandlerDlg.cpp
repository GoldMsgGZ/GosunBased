
// GxxGmGspHandlerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GxxGmGspHandler.h"
#include "GxxGmGspHandlerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGxxGmGspHandlerDlg �Ի���




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


// CGxxGmGspHandlerDlg ��Ϣ�������

BOOL CGxxGmGspHandlerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_cSSIp.SetWindowText(_T("127.0.0.1"));
	m_cSSPort.SetWindowText(_T("10086"));

	m_cSSList.InsertColumn(0, _T("��ý��id"), 0, 50);
	m_cSSList.InsertColumn(1, _T("��ý��IP"), 0, 100);
	m_cSSList.InsertColumn(2, _T("��ý��˿�"), 0, 50);
	m_cSSList.InsertColumn(3, _T("��ý��״̬"), 0, 80);

	m_cDevList.InsertColumn(0, _T("�豸���"), 0, 100);
	m_cDevList.InsertColumn(1, _T("�豸����"), 0, 100);
	m_cDevList.InsertColumn(2, _T("������ý��"), 0, 100);

	CWnd *pcwnd = GetDlgItem(IDC_STATIC_SCREEN);
	m_cScreen = pcwnd->GetSafeHwnd();

	m_cSound = GetDlgItem(IDC_CHECK_SOUND);
	m_cRecord = GetDlgItem(IDC_CHECK_RECORD);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGxxGmGspHandlerDlg::OnPaint()
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
HCURSOR CGxxGmGspHandlerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGxxGmGspHandlerDlg::OnBnClickedBtnFollow()
{
	// ��¼��ָ������ý�������
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
	// �ǳ�ָ������ý�������
}

void CGxxGmGspHandlerDlg::OnBnClickedBtnPlay()
{
	// ����ʵʱ��
}

void CGxxGmGspHandlerDlg::OnBnClickedBtnStop()
{
	// ֹͣ����ʵʱ��
}

void CGxxGmGspHandlerDlg::OnBnClickedCheckSound()
{
	// ������
}

void CGxxGmGspHandlerDlg::OnBnClickedCheckRecord()
{
	// ��ʼ¼��
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