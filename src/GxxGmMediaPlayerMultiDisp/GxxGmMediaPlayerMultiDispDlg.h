
// GxxGmMediaPlayerMultiDispDlg.h : ͷ�ļ�
//

#pragma once

#include "GSMediaPlayer.h"

// CGxxGmMediaPlayerMultiDispDlg �Ի���
class CGxxGmMediaPlayerMultiDispDlg : public CDialog
{
// ����
public:
	CGxxGmMediaPlayerMultiDispDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GXXGMMEDIAPLAYERMULTIDISP_DIALOG };

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
};
