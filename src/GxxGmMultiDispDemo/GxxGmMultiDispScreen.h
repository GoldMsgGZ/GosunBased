#pragma once


// CGxxGmMultiDispScreen �Ի���

class CGxxGmMultiDispScreen : public CDialog
{
	DECLARE_DYNAMIC(CGxxGmMultiDispScreen)

public:
	CGxxGmMultiDispScreen(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGxxGmMultiDispScreen();

// �Ի�������
	enum { IDD = IDD_DLG_MAINSCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};
