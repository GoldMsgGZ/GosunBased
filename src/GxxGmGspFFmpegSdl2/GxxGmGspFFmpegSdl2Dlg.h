
// GxxGmGspFFmpegSdl2Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include "GxxGmStreamServerClient.h"


// CGxxGmGspFFmpegSdl2Dlg �Ի���
class CGxxGmGspFFmpegSdl2Dlg : public CDialog
{
// ����
public:
	CGxxGmGspFFmpegSdl2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GXXGMGSPFFMPEGSDL2_DIALOG };

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
	CEdit m_cDevId;
	CButton m_cSpeak;
	CListBox m_cLog;

	GxxGmStreamServerClient client;
	void WriteLog(const char *log);
	afx_msg void OnBnClickedBtnLogin();
	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedCheckSpeak();
};
