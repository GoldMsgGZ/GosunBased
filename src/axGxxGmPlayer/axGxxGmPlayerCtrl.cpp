// axGxxGmPlayerCtrl.cpp : CaxGxxGmPlayerCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "axGxxGmPlayer.h"
#include "axGxxGmPlayerCtrl.h"
#include "axGxxGmPlayerPropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CaxGxxGmPlayerCtrl, COleControl)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CaxGxxGmPlayerCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// ����ӳ��

BEGIN_DISPATCH_MAP(CaxGxxGmPlayerCtrl, COleControl)
	DISP_FUNCTION_ID(CaxGxxGmPlayerCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(CaxGxxGmPlayerCtrl, COleControl)
END_EVENT_MAP()



// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CaxGxxGmPlayerCtrl, 1)
	PROPPAGEID(CaxGxxGmPlayerPropPage::guid)
END_PROPPAGEIDS(CaxGxxGmPlayerCtrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CaxGxxGmPlayerCtrl, "AXGXXGMPLAYER.axGxxGmPlayerCtrl.1",
	0x6d262904, 0x18a7, 0x4f97, 0xb9, 0x99, 0x66, 0x28, 0xbf, 0x44, 0x24, 0x17)



// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CaxGxxGmPlayerCtrl, _tlid, _wVerMajor, _wVerMinor)



// �ӿ� ID

const IID BASED_CODE IID_DaxGxxGmPlayer =
		{ 0x4D340EB7, 0x7199, 0x42CF, { 0x86, 0xC2, 0xBE, 0xE3, 0xC, 0x3D, 0xF, 0x2A } };
const IID BASED_CODE IID_DaxGxxGmPlayerEvents =
		{ 0x9563F9B4, 0x8690, 0x45EB, { 0xB2, 0x37, 0xBB, 0x66, 0xD7, 0xAD, 0x6F, 0xF7 } };



// �ؼ�������Ϣ

static const DWORD BASED_CODE _dwaxGxxGmPlayerOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CaxGxxGmPlayerCtrl, IDS_AXGXXGMPLAYER, _dwaxGxxGmPlayerOleMisc)



// CaxGxxGmPlayerCtrl::CaxGxxGmPlayerCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CaxGxxGmPlayerCtrl ��ϵͳע�����

BOOL CaxGxxGmPlayerCtrl::CaxGxxGmPlayerCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_AXGXXGMPLAYER,
			IDB_AXGXXGMPLAYER,
			afxRegApartmentThreading,
			_dwaxGxxGmPlayerOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CaxGxxGmPlayerCtrl::CaxGxxGmPlayerCtrl - ���캯��

CaxGxxGmPlayerCtrl::CaxGxxGmPlayerCtrl()
{
	InitializeIIDs(&IID_DaxGxxGmPlayer, &IID_DaxGxxGmPlayerEvents);
	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
}



// CaxGxxGmPlayerCtrl::~CaxGxxGmPlayerCtrl - ��������

CaxGxxGmPlayerCtrl::~CaxGxxGmPlayerCtrl()
{
	// TODO: �ڴ�����ؼ���ʵ�����ݡ�
}



// CaxGxxGmPlayerCtrl::OnDraw - ��ͼ����

void CaxGxxGmPlayerCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}



// CaxGxxGmPlayerCtrl::DoPropExchange - �־���֧��

void CaxGxxGmPlayerCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}



// CaxGxxGmPlayerCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CaxGxxGmPlayerCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}



// CaxGxxGmPlayerCtrl::AboutBox - ���û���ʾ�����ڡ���

void CaxGxxGmPlayerCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_AXGXXGMPLAYER);
	dlgAbout.DoModal();
}



// CaxGxxGmPlayerCtrl ��Ϣ�������
