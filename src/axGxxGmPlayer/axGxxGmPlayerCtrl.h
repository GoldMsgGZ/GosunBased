#pragma once

// axGxxGmPlayerCtrl.h : CaxGxxGmPlayerCtrl ActiveX �ؼ����������


// CaxGxxGmPlayerCtrl : �й�ʵ�ֵ���Ϣ������� axGxxGmPlayerCtrl.cpp��

class CaxGxxGmPlayerCtrl : public COleControl
{
	DECLARE_DYNCREATE(CaxGxxGmPlayerCtrl)

// ���캯��
public:
	CaxGxxGmPlayerCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CaxGxxGmPlayerCtrl();

	DECLARE_OLECREATE_EX(CaxGxxGmPlayerCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CaxGxxGmPlayerCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CaxGxxGmPlayerCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CaxGxxGmPlayerCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
	};
};

