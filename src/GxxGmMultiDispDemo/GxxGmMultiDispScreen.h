#pragma once


// CGxxGmMultiDispScreen 对话框

class CGxxGmMultiDispScreen : public CDialog
{
	DECLARE_DYNAMIC(CGxxGmMultiDispScreen)

public:
	CGxxGmMultiDispScreen(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGxxGmMultiDispScreen();

// 对话框数据
	enum { IDD = IDD_DLG_MAINSCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};
