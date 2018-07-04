
// GxxGmGspStreamHandlerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#include "StreamServerSDK.h"
#include "PSFormat.h"


// CGxxGmGspStreamHandlerDlg 对话框
class CGxxGmGspStreamHandlerDlg : public CDialog
{
// 构造
public:
	CGxxGmGspStreamHandlerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GXXGMGSPSTREAMHANDLER_DIALOG };

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
	CEdit m_cDevId;
	CString devid;

	GOSUN_SERV_HANDLE handle_;
	GS_MpegPSHandle ps_handle_;

	afx_msg void OnBnClickedButtonHandler();
	afx_msg void OnBnClickedButtonLogin();
};
