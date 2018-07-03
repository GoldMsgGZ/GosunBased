
// GxxGmGspHandlerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "GxxGmSSMgr.h"


// CGxxGmGspHandlerDlg �Ի���
class CGxxGmGspHandlerDlg : public CDialog, public GxxGmSSMgrNotifer
{
// ����
public:
	CGxxGmGspHandlerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GXXGMGSPHANDLER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CEdit m_cSSIp;
	CEdit m_cSSPort;
	CListCtrl m_cSSList;
	CListCtrl m_cDevList;
	HWND m_cScreen;
	CWnd *m_cSound;
	CWnd *m_cRecord;

public:
	GxxGmSSMgr *ssmgr_;
	virtual int Notifer(int ss_id, const char *dev_id, enum SSMgrNotiferType type, const unsigned char *data);
	
public:
	afx_msg void OnBnClickedBtnFollow();
	afx_msg void OnBnClickedBtnUnfollow();
	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedCheckSound();
	afx_msg void OnBnClickedCheckRecord();
};
