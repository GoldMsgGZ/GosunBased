
// GxxGmGspFFmpegSdl2Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#include "GxxGmStreamServerClient.h"


// CGxxGmGspFFmpegSdl2Dlg 对话框
class CGxxGmGspFFmpegSdl2Dlg : public CDialog
{
// 构造
public:
	CGxxGmGspFFmpegSdl2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GXXGMGSPFFMPEGSDL2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
