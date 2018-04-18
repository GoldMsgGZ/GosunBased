#pragma once

// axGxxGmPlayerCtrl.h : CaxGxxGmPlayerCtrl ActiveX 控件类的声明。


// CaxGxxGmPlayerCtrl : 有关实现的信息，请参阅 axGxxGmPlayerCtrl.cpp。

class CaxGxxGmPlayerCtrl : public COleControl
{
	DECLARE_DYNCREATE(CaxGxxGmPlayerCtrl)

// 构造函数
public:
	CaxGxxGmPlayerCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CaxGxxGmPlayerCtrl();

	DECLARE_OLECREATE_EX(CaxGxxGmPlayerCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CaxGxxGmPlayerCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CaxGxxGmPlayerCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CaxGxxGmPlayerCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
	};
};

