
// GxxGmPlayCoreDlg.h : 头文件
//

#pragma once

#include "GxxGmPlayer.h"
#include "afxwin.h"
#include "..\\ext\\GSStreamServerSDK\\StreamServerSDK.h"

class GxxGmPlaySDK;

// CGxxGmPlayCoreDlg 对话框
class CGxxGmPlayCoreDlg : public CDialog
{
// 构造
public:
	CGxxGmPlayCoreDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GXXGMPLAYCORE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
