// axGxxGmPlayerPropPage.cpp : CaxGxxGmPlayerPropPage 属性页类的实现。

#include "stdafx.h"
#include "axGxxGmPlayer.h"
#include "axGxxGmPlayerPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CaxGxxGmPlayerPropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CaxGxxGmPlayerPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CaxGxxGmPlayerPropPage, "AXGXXGMPLAYER.axGxxGmPlayerPropPage.1",
	0x2b4c5a1c, 0x58df, 0x458a, 0xa8, 0x72, 0x45, 0x47, 0x39, 0x8, 0x4f, 0xb7)



// CaxGxxGmPlayerPropPage::CaxGxxGmPlayerPropPageFactory::UpdateRegistry -
// 添加或移除 CaxGxxGmPlayerPropPage 的系统注册表项

BOOL CaxGxxGmPlayerPropPage::CaxGxxGmPlayerPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_AXGXXGMPLAYER_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CaxGxxGmPlayerPropPage::CaxGxxGmPlayerPropPage - 构造函数

CaxGxxGmPlayerPropPage::CaxGxxGmPlayerPropPage() :
	COlePropertyPage(IDD, IDS_AXGXXGMPLAYER_PPG_CAPTION)
{
}



// CaxGxxGmPlayerPropPage::DoDataExchange - 在页和属性间移动数据

void CaxGxxGmPlayerPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CaxGxxGmPlayerPropPage 消息处理程序
