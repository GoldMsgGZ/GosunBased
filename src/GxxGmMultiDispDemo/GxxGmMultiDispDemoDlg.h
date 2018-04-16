
// GxxGmMultiDispDemoDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CGxxGmMultiDispDemoDlg 对话框
class CGxxGmMultiDispDemoDlg : public CDialog
{
// 构造
public:
	CGxxGmMultiDispDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GXXGMMULTIDISPDEMO_DIALOG };

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
	CComboBox m_cDispRows;
	CComboBox m_cDispLists;
	CEdit m_cScreenWidth;
	CEdit m_cScreenHeight;
	CEdit m_cUrl;
};
