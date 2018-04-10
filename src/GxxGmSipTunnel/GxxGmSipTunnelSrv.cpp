#include "GxxGmSipTunnelSrv.h"

GxxGmSipTunnelSrv::GxxGmSipTunnelSrv(GxxGmSipTunnelSrvNotifer *notifer)
: notifer_(notifer)
, sip_context_(eXosip_malloc())
, message_thread_handle_(NULL)
, is_need_stop_(false)
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

	// ��ʼ��
	int errCode = eXosip_init(sip_context_);
	if (errCode != 0)
		return errCode;

	// ����
	errCode = eXosip_listen_addr(sip_context_, IPPROTO_UDP, srv_ip_.c_str(), srv_port_, AF_INET, 0);
	if (errCode != 0)
		return errCode;

	// �����̣߳����ڽ��տͻ��˷���������
	is_need_stop_ = false;
	message_thread_handle_ = CreateThread(NULL, 0, MessageThread, this, 0, NULL);
	if (message_thread_handle_ == NULL)
		errCode = GetLastError();
	
	return errCode;
}

void GxxGmSipTunnelSrv::Close()
{
	// ����ֹͣ�̵߳���Ϣ
	is_need_stop_ = true;
}

int GxxGmSipTunnelSrv::SendResponse(const char *response, int response_len)
{
	// ����SIPԴ��Ŀ�ĵ�ַ
	char dest_call[4096] = {0};
	sprintf_s(dest_call, 4096, "sip:%s@%s:%d", cli_id_.c_str(), cli_ip_.c_str(), cli_port_);

	char src_call[4096] = {0};
	sprintf_s(src_call, 4096, "sip:%s@%s:%d", srv_id_.c_str(), srv_ip_.c_str(), srv_port_);

	osip_message_t *message = NULL;
	eXosip_message_build_request(sip_context_, &message, "MESSAGE", dest_call, src_call, NULL);

	osip_message_set_body(message, response, response_len);

	osip_message_set_content_type(message, "text/xml");
	int errCode = eXosip_message_send_request(sip_context_, message);

	return 0;
}

DWORD WINAPI GxxGmSipTunnelSrv::MessageThread(LPVOID lpParam)
{
	GxxGmSipTunnelSrv *srv = (GxxGmSipTunnelSrv *)lpParam;

	while (true)
	{
		// ����Ƿ񴥷���ֹͣ��־
		if (srv->is_need_stop_)
			break;

		// �ȴ��¼���50������һ��
		eXosip_event_t *je = eXosip_event_wait(srv->sip_context_, 0, 50);

		//Э��ջ���д����,��������δ֪
		eXosip_lock(srv->sip_context_);
		eXosip_default_action(srv->sip_context_, je);
		eXosip_automatic_refresh(srv->sip_context_);
		eXosip_unlock(srv->sip_context_);

		//û�н��յ���Ϣ
		if (je == NULL)
			continue;

		// �յ���Ϣ��
		switch (je->type)
		{
		case EXOSIP_MESSAGE_NEW:
			// ����Ϣ����
			if (MSG_IS_MESSAGE(je->request))
			{
				// ��ʾ��Ϣ
				osip_body_t *body = NULL;
				osip_message_get_body(je->request, 0, &body);
				
				srv->notifer_->RecvRequest(body->body, body->length);

				// Ӧ�𣬱�ʾ�Ѿ��յ�
				osip_message_t *answer = NULL;
				eXosip_message_build_answer(srv->sip_context_, je->tid, 200, &answer);
				eXosip_message_send_answer(srv->sip_context_, je->tid, 200, answer);
			}
			break;
		default:
			break;
		}
	}

	eXosip_quit(srv->sip_context_);
	return 0;
}