#include "GxxGmTunnelServer.h"


typedef struct _CLIENT_INFO_
{
	SOCKET cli_sock_;
	SOCKADDR_IN cli_addr_;
	GxxGmTunnelServer *srv_;
	std::string cli_sock_id_;
} CLIENT_INFO, *PCLIENT_INFO;


GxxGmTunnelServer::GxxGmTunnelServer()
: listen_thread_handle_(NULL)
, is_need_stop_(false)
, sip_tunnel_cli_(NULL)
{

}

GxxGmTunnelServer::~GxxGmTunnelServer()
{

}

int GxxGmTunnelServer::Initialize(const char *tcp_srv_ip, int tcp_srv_port, const char *sip_cli_ip, int sip_cli_port, const char *sip_cli_id, const char *sip_srv_ip, int sip_srv_port, const char *sip_srv_id)
{
	// 首先开启TCP监听
	WSAData wsaData;
	int errCode = WSAStartup(MAKEWORD(1,1), &wsaData);
	if (errCode != 0)
		return errCode;

	srv_sock_ = socket(AF_INET, SOCK_STREAM, 0);
	if (srv_sock_ == INVALID_SOCKET)
	{
		errCode = WSAGetLastError();
		return errCode;
	}

	SOCKADDR_IN srv_addr;
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = tcp_srv_port;
	srv_addr.sin_addr.S_un.S_addr = inet_addr(tcp_srv_ip);

	errCode = bind(srv_sock_, (SOCKADDR*)&srv_addr, sizeof(SOCKADDR));
	if (errCode == SOCKET_ERROR)
	{
		errCode = WSAGetLastError();
		return errCode;
	}

	errCode = listen(srv_sock_, 5);
	if (errCode == SOCKET_ERROR)
	{
		errCode = WSAGetLastError();
		return errCode;
	}

	sip_tunnel_cli_ = new GxxGmSipTunnelCli(this);
	errCode = sip_tunnel_cli_->Initialize(sip_srv_ip, sip_srv_port, sip_srv_id, sip_cli_ip, sip_cli_port, sip_cli_id);

	return errCode;
}

void GxxGmTunnelServer::Close()
{
	this->Stop();
	WSACleanup();
}

int GxxGmTunnelServer::Start()
{
	int errCode = 0;

	// 启动接收线程
	DWORD exit_code = 0;
	GetExitCodeThread(listen_thread_handle_, &exit_code);
	if (exit_code == STILL_ACTIVE)
	{
		errCode = 0;
	}
	else
	{
		listen_thread_handle_ = CreateThread(NULL, 0, ListenThread, this, 0, NULL);
		if (listen_thread_handle_ == NULL)
			errCode = GetLastError();
	}

	is_need_stop_ = false;
	return errCode;
}

void GxxGmTunnelServer::Stop()
{
	is_need_stop_ = true;
}

void GxxGmTunnelServer::RecvResponse(const char *response, int response_len)
{
	int errCode = send(srv_sock_, response, response_len, 0);
	// 这里评估一下是否需要输出相关信息
}

DWORD WINAPI GxxGmTunnelServer::ListenThread(LPVOID lpParam)
{
	GxxGmTunnelServer *server = (GxxGmTunnelServer *)lpParam;

	while (true)
	{
		SOCKADDR_IN client_addr;
		SOCKET client_sock = accept(server->srv_sock_, (SOCKADDR *)&client_addr, sizeof(SOCKADDR));

		// 如果接入的是无效的客户端，跳过
		if (client_sock == INVALID_SOCKET)
			continue;

		// 有效客户端，先对客户端生成一个唯一ID，然后缓存记录
		GUID guid;
		HRESULT ret = CoCreateGuid(&guid);
		if (ret != S_OK)
			continue;

		char buffer[60] = {0};
		_snprintf(buffer, sizeof(buffer),
			"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2],
			guid.Data4[3], guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);

		server->client_connections_.insert(std::pair<SOCKET, std::string>(client_sock, buffer));

		// 每接收到一个客户端的接入请求后，都在线程池里面新建一个任务进行处理
		// 很想用Chromium那套东西来实现...
		CLIENT_INFO *client_info = new CLIENT_INFO;
		client_info->cli_sock_ = client_sock;
		client_info->cli_addr_ = client_addr;
		client_info->srv_ = server;
		client_info->cli_sock_id_ = buffer;
		CreateThread(NULL, 0, RecvClientThread, client_info, 0, NULL);
		//CreateThread(NULL, 0, SendClientThread, client_info, 0, NULL);
	}

	return 0;
}

DWORD WINAPI GxxGmTunnelServer::RecvClientThread(LPVOID lpParam)
{
	CLIENT_INFO *client_info = (CLIENT_INFO *)lpParam;

	while (true)
	{
		// 收到客户端发来的请求后，重构消息，扔给SIP隧道
		char recv_buffer[512] = {0};
		int recv_len = recv(client_info->cli_sock_, recv_buffer, 4096, 0);
		if (recv_len > 0)
		{
			// 这里重新构建消息，消息算法为：Base64(client_sock_id + message)
			client_info->srv_->sip_tunnel_cli_->SendRequest(recv_buffer, recv_len);
		}
	}

	return 0;
}