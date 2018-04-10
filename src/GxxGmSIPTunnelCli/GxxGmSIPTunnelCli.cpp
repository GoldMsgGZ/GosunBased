//////////////////////////////////////////////////////////////////////////
//
// ���Ǹ����˹�����SIP����ͻ��˳���
// ������������Windowsϵͳ��Linuxϵͳ

#include <iostream>
#include "SipStack.h"

SipSessionHandle srv_session = NULL;

typedef struct GxxGmSIPListener : public _StruSipListener
{
	// ���յ��µ�����
	EnumSipErrorCode _OnClientConnectEvent(SipServiceHandle hService, SipSessionHandle hNewSession)
	{
		if (srv_session != NULL)
		{
			std::cout<<"�Ѿ��з���˽�����"<<std::endl;
			return EnumSipErrorCode::eSIP_RET_FAILURE;
		}

		std::cout<<"�����豸����"<<std::endl;
		srv_session = hNewSession;
		return EnumSipErrorCode::eSIP_RET_SUCCESS;
	}

	//�Ͽ�����
	void _OnClientDisconnectEvent(SipServiceHandle hService, SipSessionHandle hNewSession)
	{
		if (hNewSession == srv_session)
		{
			std::cout<<"�ͻ��˶Ͽ�������..."<<std::endl;
			srv_session = NULL;
		}
	}

	//���ϲ�Ļص����ô˽ӿ� ����������Ļص�����Ӧ��ص����� pData���;���
	void _OnSIPPacketEvent(SipServiceHandle hService, SipSessionHandle hNewSession, StruSipData *pData)
	{

	}
} GxxGmSIPListener;

int main(int argc, char *argv[])
{
	struct GxxGmSIPListener listener;
	SipServiceHandle srv_handle = SipService_Create(&listener);
	if (srv_handle == NULL)
	{
		std::cout<<"����SIP����ʧ�ܣ�"<<std::endl;
		return 0;
	}

	SipSessionHandle srv = SipService_Connect(srv_handle, EnumSipConnectType::eSIP_CONNECT_UDP, "10.10.16.59", 8888);
	if (srv == NULL)
	{
		std::cout<<"���ӵ�Զ�˷���ʧ�ܣ�"<<std::endl;
		return 0;
	}

	// ��������
	StruSipData send_data;
	send_data.eContentType = EnumSipContentType::eSIP_CONTENT_INNER;
	send_data.eDataType = EnumSipDataType::eSIP_DATA_REQUEST;
	send_data.eMethod = EnumSipMethod::eSIP_METHOD_MESSAGE;
	send_data.iContentLength = 10;
	memcpy(send_data.vContent, "12345678900987654321", send_data.iContentLength);

	StruSipData ret_data;
	EnumSipErrorCode err = SipSession_SendMessage(srv, &send_data, &ret_data, 30, NULL);
	return 0;
}