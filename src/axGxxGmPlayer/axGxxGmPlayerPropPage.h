#pragma once

// axGxxGmPlayerPropPage.h : CaxGxxGmPlayerPropPage ����ҳ���������


// CaxGxxGmPlayerPropPage : �й�ʵ�ֵ���Ϣ������� axGxxGmPlayerPropPage.cpp��

class CaxGxxGmPlayerPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CaxGxxGmPlayerPropPage)
	DECLARE_OLECREATE_EX(CaxGxxGmPlayerPropPage)

// ���캯��
public:
	CaxGxxGmPlayerPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_AXGXXGMPLAYER };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

