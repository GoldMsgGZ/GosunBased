//////////////////////////////////////////////////////////////////////////
//
// 这是高新兴国迈的SIP隧道客户端程序
// 代码力争兼容Windows系统和Linux系统

#include <iostream>
#include "SipStack.h"

SipSessionHandle srv_session = NULL;

typedef struct GxxGmSIPListener : public _StruSipListener
{
	// 接收到新的连接
	EnumSipErrorCode _OnClientConnectEvent(SipServiceHandle hService, SipSessionHandle hNewSession)
	{
		if (srv_session != NULL)
		{
			std::cout<<"已经有服务端接入了"<<std::endl;
			return EnumSipErrorCode::eSIP_RET_FAILURE;
		}

		std::cout<<"有新设备接入"<<std::endl;
		srv_session = hNewSession;
		return EnumSipErrorCode::eSIP_RET_SUCCESS;
	}

	//断开连接
	void _OnClientDisconnectEvent(SipServiceHandle hService, SipSessionHandle hNewSession)
	{
		if (hNewSession == srv_session)
		{
			std::cout<<"客户端断开了连接..."<<std::endl;
			srv_session = NULL;
		}
	}

	//给上层的回调皆用此接口 是网络请求的回调还是应答回调根据 pData类型决定
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
		std::cout<<"创建SIP服务失败！"<<std::endl;
		return 0;
	}

	SipSessionHandle srv = SipService_Connect(srv_handle, EnumSipConnectType::eSIP_CONNECT_UDP, "10.10.16.59", 8888);
	if (srv == NULL)
	{
		std::cout<<"连接到远端服务失败！"<<std::endl;
		return 0;
	}

	// 发送数据
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