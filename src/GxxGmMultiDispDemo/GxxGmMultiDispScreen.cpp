// GxxGmMultiDispScreen.cpp : 实现文件
//

#include "stdafx.h"
#include "GxxGmMultiDispDemo.h"
#include "GxxGmMultiDispScreen.h"


// CGxxGmMultiDispScreen 对话框

IMPLEMENT_DYNAMIC(CGxxGmMultiDispScreen, CDialog)

CGxxGmMultiDispScreen::CGxxGmMultiDispScreen(CWnd* pParent /*=NULL*/)
	: CDialog(CGxxGmMultiDispScreen::IDD, pParent)
{

}

CGxxGmMultiDispScreen::~CGxxGmMultiDispScreen()
{
}

void CGxxGmMultiDispScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGxxGmMultiDispScreen, CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CGxxGmMultiDispScreen 消息处理程序

BOOL CGxxGmMultiDispScreen::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}
void CGxxGmMultiDispScreen::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialog::OnClose();
}
