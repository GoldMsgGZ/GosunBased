#include "GxxGmSipTunnelSrv.h"

GxxGmSipTunnelSrv::GxxGmSipTunnelSrv(GxxGmSipTunnelSrvNotifer *notifer)
: notifer_(notifer)
, sip_context_(eXosip_malloc())
, message_thread_handle_(NULL)
{

}

GxxGmSipTunnelSrv::~GxxGmSipTunnelSrv()
{

}

int GxxGmSipTunnelSrv::Initialize(const char *srv_ip, int srv_port, const char *srv_id, const char *cli_ip, int cli_port, const char *cli_id)
{
	srv_ip_ = srv_ip;
	srv_port_ = srv_port;
	srv_id_ = srv_id;

	cli_ip_ = cli_ip;
	cli_port_ = cli_port;
	cli_id_ = cli_id;

	// 初始化
	int errCode = eXosip_init(sip_context_);
	if (errCode != 0)
		return errCode;

	// 监听
	errCode = eXosip_listen_addr(sip_context_, IPPROTO_UDP, srv_ip_.c_str(), srv_port_, AF_INET, 0);
	if (errCode != 0)
		return errCode;

	// 启动线程，用于接收客户端发来的请求
	message_thread_handle_ = CreateThread(NULL, 0, MessageThread, this, 0, NULL);
	if (message_thread_handle_ == NULL)
		errCode = GetLastError();
	
	return errCode;
}

void GxxGmSipTunnelSrv::Close()
{
	// 发送停止线程的消息
}