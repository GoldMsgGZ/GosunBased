
// GxxGmMultiDispDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CGxxGmMultiDispDemoDlg �Ի���
class CGxxGmMultiDispDemoDlg : public CDialog
{
// ����
public:
	CGxxGmMultiDispDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GXXGMMULTIDISPDEMO_DIALOG };

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
	CComboBox m_cDispRows;
	CComboBox m_cDispLists;
	CEdit m_cScreenWidth;
	CEdit m_cScreenHeight;
	CEdit m_cUrl;
};
