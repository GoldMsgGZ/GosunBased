#ifndef _GxxGmSipTunnelSrv_H_
#define _GxxGmSipTunnelSrv_H_

#include "eXosip2/eXosip.h"
#include <iostream>
#include <string>
#include <WinSock.h>

class GxxGmSipTunnelSrvNotifer
{
public:
	virtual void RecvRequest(const char *request, int request_len) = 0;
};

class GxxGmSipTunnelSrv
{
public:
	GxxGmSipTunnelSrv(GxxGmSipTunnelSrvNotifer *notifer);
	~GxxGmSipTunnelSrv();

public:
	int Initialize(const char *srv_ip, int srv_port, const char *srv_id, const char *cli_ip, int cli_port, const char *cli_id);
	void Close();

public:
	int SendResponse(const char *response, int response_len);

public:
	static DWORD WINAPI MessageThread(LPVOID lpParam);
	HANDLE message_thread_handle_;

public:
	eXosip_t *sip_context_;
	GxxGmSipTunnelSrvNotifer *notifer_;

	std::string srv_ip_;
	int srv_port_;
	std::string srv_id_;

	std::string cli_ip_;
	int cli_port_;
	std::string cli_id_;
};

#endif//_GxxGmSipTunnelSrv_H_
