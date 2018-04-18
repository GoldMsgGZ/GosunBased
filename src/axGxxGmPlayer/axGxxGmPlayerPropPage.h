#pragma once

// axGxxGmPlayerPropPage.h : CaxGxxGmPlayerPropPage 属性页类的声明。


// CaxGxxGmPlayerPropPage : 有关实现的信息，请参阅 axGxxGmPlayerPropPage.cpp。

class CaxGxxGmPlayerPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CaxGxxGmPlayerPropPage)
	DECLARE_OLECREATE_EX(CaxGxxGmPlayerPropPage)

// 构造函数
public:
	CaxGxxGmPlayerPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_AXGXXGMPLAYER };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

