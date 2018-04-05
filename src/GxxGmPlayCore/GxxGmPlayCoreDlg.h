
// GxxGmPlayCoreDlg.h : ͷ�ļ�
//

#pragma once

#include "GxxGmPlayer.h"
#include "afxwin.h"
#include "..\\ext\\GSStreamServerSDK\\StreamServerSDK.h"

class GxxGmPlaySDK;

// CGxxGmPlayCoreDlg �Ի���
class CGxxGmPlayCoreDlg : public CDialog
{
// ����
public:
	CGxxGmPlayCoreDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GXXGMPLAYCORE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	GxxGmPlayer *player_;
	CEdit m_cUrl;

	CEdit m_cSSIp;
	CEdit m_cSSPort;
	CEdit m_cDevId;

	GOSUN_SERV_HANDLE handle;

	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnBnClickedBtnStop();
	
	afx_msg void OnBnClickedBtnGetUrl();
	afx_msg void OnBnClickedBtnCleanup();
};
