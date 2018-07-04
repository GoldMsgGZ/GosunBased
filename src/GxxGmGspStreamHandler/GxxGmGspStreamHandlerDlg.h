
// GxxGmGspStreamHandlerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include "StreamServerSDK.h"
#include "PSFormat.h"


// CGxxGmGspStreamHandlerDlg �Ի���
class CGxxGmGspStreamHandlerDlg : public CDialog
{
// ����
public:
	CGxxGmGspStreamHandlerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GXXGMGSPSTREAMHANDLER_DIALOG };

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
	CEdit m_cDevId;
	CString devid;

	GOSUN_SERV_HANDLE handle_;
	GS_MpegPSHandle ps_handle_;

	afx_msg void OnBnClickedButtonHandler();
	afx_msg void OnBnClickedButtonLogin();
};
