//////////////////////////////////////////////////////////////////////////
//
// 这是高新兴国迈的SIP隧道服务端程序
// 代码力争兼容Windows系统和Linux系统

#include <iostream>
#include "SipStack.h"

#ifdef _DEBUG

#endif

SipSessionHandle cli_session = NULL;

typedef struct GxxGmSIPListener : public _StruSipListener
{
	// 接收到新的连接
	EnumSipErrorCode _OnClientConnectEvent(SipServiceHandle hService, SipSessionHandle hNewSession)
	{
		if (cli_session != NULL)
		{
			std::cout<<"已经有客户端接入了"<<std::endl;
			return EnumSipErrorCode::eSIP_RET_FAILURE;
		}

		std::cout<<"有新设备接入"<<std::endl;
		cli_session = hNewSession;
		return EnumSipErrorCode::eSIP_RET_SUCCESS;
	}

	//断开连接
	void _OnClientDisconnectEvent(SipServiceHandle hService, SipSessionHandle hNewSession)
	{
		if (hNewSession == cli_session)
		{
			std::cout<<"客户端断开了连接..."<<std::endl;
			cli_session = NULL;
		}
	}

	//给上层的回调皆用此接口 是网络请求的回调还是应答回调根据 pData类型决定
	void _OnSIPPacketEvent(SipServiceHandle hService, SipSessionHandle hNewSession, StruSipData *pData)
	{
		std::cout<<"=========================================="<<std::endl;
		std::cout<<"接收到消息："<<std::endl;
		std::cout<<"消息长度："<<pData->iContentLength;
	}
} GxxGmSIPListener;



int main(int argc, char *argv[])
{
	struct GxxGmSIPListener listener;
	SipServiceHandle srv_handle = SipService_Create(&listener);
	if (srv_handle == NULL)
	{
		std::cout<<"创建SIP服务失败！"<<std::endl;
		return 0;
	}

	EnumSipErrorCode err = SipService_Start(srv_handle, EnumSipConnectType::eSIP_CONNECT_UDP, "10.10.16.59", 8888);
	if (err != EnumSipErrorCode::eSIP_RET_SUCCESS)
	{
		std::cout<<"开启SIP服务失败！错误码："<<err<<std::endl;
		return 0;
	}

	std::cout<<"按任意键退出..."<<std::endl;
	getchar();

	SipService_Stop(srv_handle);
	SipService_Release(srv_handle);
	return 0;
}