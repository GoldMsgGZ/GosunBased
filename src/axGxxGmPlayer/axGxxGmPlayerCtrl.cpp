// axGxxGmPlayerCtrl.cpp : CaxGxxGmPlayerCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "axGxxGmPlayer.h"
#include "axGxxGmPlayerCtrl.h"
#include "axGxxGmPlayerPropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CaxGxxGmPlayerCtrl, COleControl)



// 消息映射

BEGIN_MESSAGE_MAP(CaxGxxGmPlayerCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// 调度映射

BEGIN_DISPATCH_MAP(CaxGxxGmPlayerCtrl, COleControl)
	DISP_FUNCTION_ID(CaxGxxGmPlayerCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CaxGxxGmPlayerCtrl, COleControl)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CaxGxxGmPlayerCtrl, 1)
	PROPPAGEID(CaxGxxGmPlayerPropPage::guid)
END_PROPPAGEIDS(CaxGxxGmPlayerCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CaxGxxGmPlayerCtrl, "AXGXXGMPLAYER.axGxxGmPlayerCtrl.1",
	0x6d262904, 0x18a7, 0x4f97, 0xb9, 0x99, 0x66, 0x28, 0xbf, 0x44, 0x24, 0x17)



// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CaxGxxGmPlayerCtrl, _tlid, _wVerMajor, _wVerMinor)



// 接口 ID

const IID BASED_CODE IID_DaxGxxGmPlayer =
		{ 0x4D340EB7, 0x7199, 0x42CF, { 0x86, 0xC2, 0xBE, 0xE3, 0xC, 0x3D, 0xF, 0x2A } };
const IID BASED_CODE IID_DaxGxxGmPlayerEvents =
		{ 0x9563F9B4, 0x8690, 0x45EB, { 0xB2, 0x37, 0xBB, 0x66, 0xD7, 0xAD, 0x6F, 0xF7 } };



// 控件类型信息

static const DWORD BASED_CODE _dwaxGxxGmPlayerOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CaxGxxGmPlayerCtrl, IDS_AXGXXGMPLAYER, _dwaxGxxGmPlayerOleMisc)



// CaxGxxGmPlayerCtrl::CaxGxxGmPlayerCtrlFactory::UpdateRegistry -
// 添加或移除 CaxGxxGmPlayerCtrl 的系统注册表项

BOOL CaxGxxGmPlayerCtrl::CaxGxxGmPlayerCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

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



// CaxGxxGmPlayerCtrl::CaxGxxGmPlayerCtrl - 构造函数

CaxGxxGmPlayerCtrl::CaxGxxGmPlayerCtrl()
{
	InitializeIIDs(&IID_DaxGxxGmPlayer, &IID_DaxGxxGmPlayerEvents);
	// TODO: 在此初始化控件的实例数据。
}



// CaxGxxGmPlayerCtrl::~CaxGxxGmPlayerCtrl - 析构函数

CaxGxxGmPlayerCtrl::~CaxGxxGmPlayerCtrl()
{
	// TODO: 在此清理控件的实例数据。
}



// CaxGxxGmPlayerCtrl::OnDraw - 绘图函数

void CaxGxxGmPlayerCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}



// CaxGxxGmPlayerCtrl::DoPropExchange - 持久性支持

void CaxGxxGmPlayerCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}



// CaxGxxGmPlayerCtrl::OnResetState - 将控件重置为默认状态

void CaxGxxGmPlayerCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}



// CaxGxxGmPlayerCtrl::AboutBox - 向用户显示“关于”框

void CaxGxxGmPlayerCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_AXGXXGMPLAYER);
	dlgAbout.DoModal();
}



// CaxGxxGmPlayerCtrl 消息处理程序
