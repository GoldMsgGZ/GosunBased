//////////////////////////////////////////////////////////////////////////
//
// ���Ǹ����˹�����SIP�������˳���
// ������������Windowsϵͳ��Linuxϵͳ

#include <iostream>
#include "SipStack.h"

#ifdef _DEBUG

#endif

SipSessionHandle cli_session = NULL;

typedef struct GxxGmSIPListener : public _StruSipListener
{
	// ���յ��µ�����
	EnumSipErrorCode _OnClientConnectEvent(SipServiceHandle hService, SipSessionHandle hNewSession)
	{
		if (cli_session != NULL)
		{
			std::cout<<"�Ѿ��пͻ��˽�����"<<std::endl;
			return EnumSipErrorCode::eSIP_RET_FAILURE;
		}

		std::cout<<"�����豸����"<<std::endl;
		cli_session = hNewSession;
		return EnumSipErrorCode::eSIP_RET_SUCCESS;
	}

	//�Ͽ�����
	void _OnClientDisconnectEvent(SipServiceHandle hService, SipSessionHandle hNewSession)
	{
		if (hNewSession == cli_session)
		{
			std::cout<<"�ͻ��˶Ͽ�������..."<<std::endl;
			cli_session = NULL;
		}
	}

	//���ϲ�Ļص����ô˽ӿ� ����������Ļص�����Ӧ��ص����� pData���;���
	void _OnSIPPacketEvent(SipServiceHandle hService, SipSessionHandle hNewSession, StruSipData *pData)
	{
		std::cout<<"=========================================="<<std::endl;
		std::cout<<"���յ���Ϣ��"<<std::endl;
		std::cout<<"��Ϣ���ȣ�"<<pData->iContentLength;
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

	EnumSipErrorCode err = SipService_Start(srv_handle, EnumSipConnectType::eSIP_CONNECT_UDP, "10.10.16.59", 8888);
	if (err != EnumSipErrorCode::eSIP_RET_SUCCESS)
	{
		std::cout<<"����SIP����ʧ�ܣ������룺"<<err<<std::endl;
		return 0;
	}

	std::cout<<"��������˳�..."<<std::endl;
	getchar();

	SipService_Stop(srv_handle);
	SipService_Release(srv_handle);
	return 0;
}