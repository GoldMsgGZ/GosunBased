// GxxGmMultiDispScreen.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GxxGmMultiDispDemo.h"
#include "GxxGmMultiDispScreen.h"


// CGxxGmMultiDispScreen �Ի���

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


// CGxxGmMultiDispScreen ��Ϣ�������

BOOL CGxxGmMultiDispScreen::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}
void CGxxGmMultiDispScreen::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//CDialog::OnClose();
}
