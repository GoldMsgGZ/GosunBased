// axGxxGmPlayerPropPage.cpp : CaxGxxGmPlayerPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "axGxxGmPlayer.h"
#include "axGxxGmPlayerPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CaxGxxGmPlayerPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CaxGxxGmPlayerPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CaxGxxGmPlayerPropPage, "AXGXXGMPLAYER.axGxxGmPlayerPropPage.1",
	0x2b4c5a1c, 0x58df, 0x458a, 0xa8, 0x72, 0x45, 0x47, 0x39, 0x8, 0x4f, 0xb7)



// CaxGxxGmPlayerPropPage::CaxGxxGmPlayerPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CaxGxxGmPlayerPropPage ��ϵͳע�����

BOOL CaxGxxGmPlayerPropPage::CaxGxxGmPlayerPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_AXGXXGMPLAYER_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CaxGxxGmPlayerPropPage::CaxGxxGmPlayerPropPage - ���캯��

CaxGxxGmPlayerPropPage::CaxGxxGmPlayerPropPage() :
	COlePropertyPage(IDD, IDS_AXGXXGMPLAYER_PPG_CAPTION)
{
}



// CaxGxxGmPlayerPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CaxGxxGmPlayerPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CaxGxxGmPlayerPropPage ��Ϣ�������
