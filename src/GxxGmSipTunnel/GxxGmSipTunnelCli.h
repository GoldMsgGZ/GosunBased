#ifndef _GxxGmSipTunnelCli_H_
#define _GxxGmSipTunnelCli_H_

class GxxGmSipTunnelCliNotifer
{
public:
	virtual void RecvResponse(const char *response, int response_len) = 0;
};

class GxxGmSipTunnelCli
{
public:
	GxxGmSipTunnelCli(GxxGmSipTunnelCliNotifer *notifer);
	~GxxGmSipTunnelCli();

public:
	int Initialize(const char *srv_ip, int srv_port, const char *srv_id, const char *cli_ip, int cli_port, const char *cli_id);
	void Close();

public:
	int SendRequest(const char *request, int request_len);

public:
	eXosip_t *sip_context_;
	GxxGmSipTunnelCliNotifer *notifer_;

	std::string srv_ip_;
	int srv_port_;
	std::string srv_id_;

	std::string cli_ip_;
	int cli_port_;
	std::string cli_id_;
};

#endif//_GxxGmSipTunnelCli_H_
