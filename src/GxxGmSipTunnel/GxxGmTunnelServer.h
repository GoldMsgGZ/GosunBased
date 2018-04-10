#ifndef _GxxGmTunnelServer_H_
#define _GxxGmTunnelServer_H_

#include "GxxGmSipTunnelCli.h"

class GxxGmTunnelServer : public GxxGmSipTunnelCliNotifer
{
public:
	GxxGmTunnelServer();
	~GxxGmTunnelServer();

public:
	/**
	 * ��ʼ��������������
	 * ������
	 *	@tcp_srv_ip		���ڰ󶨼�����IP�������������IP���0.0.0.0��
	 *	@tcp_srv_port	TCP�����˿�
	 *	@sip_cli_ip		SIP����ͻ���IP
	 *	@sip_cli_port	SIP����ͻ��˶˿ں�
	 *	@sip_cli_id		SIP����ͻ��˱���
	 *	@sip_srv_ip		SIP��������IP
	 *	@sip_srv_port	SIP�������˶˿ں�
	 *	@sip_srv_id		SIP�������˱���
	 */
	int Initialize(const char *tcp_srv_ip, int tcp_srv_port, const char *sip_cli_ip, int sip_cli_port, const char *sip_cli_id, const char *sip_srv_ip, int sip_srv_port, const char *sip_srv_id);
	void Close();

public:
	int Start();
	void Stop();

public:
	static DWORD WINAPI ListenThread(LPVOID lpParam);

public:
	virtual void RecvResponse(const char *response, int response_len);
};

#endif//_GxxGmTunnelServer_H_