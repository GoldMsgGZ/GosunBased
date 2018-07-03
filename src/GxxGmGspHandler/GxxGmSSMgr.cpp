#include "stdafx.h"
#include "GxxGmSSMgr.h"
#include "tinyxml.h"

GxxGmSSObject::GxxGmSSObject(int id, GxxGmSSObjectNotifer *notifer)
: id_(id)
, notifer_(notifer)
{
	SSSetExceptionCallback(GxxGmSSObject::ExceptionCallback, this);
	SSSetDevMsgCallBack(GxxGmSSObject::MSGCallBack, this);
}

GxxGmSSObject::~GxxGmSSObject()
{
	
}

int GxxGmSSObject::Login(const char *ip, int port)
{
	GOSUN_SERVER_INFO info;
	ZeroMemory(&info, sizeof(GOSUN_SERVER_INFO));
	strcpy(info.servIP, ip);
	strcpy(info.username, "admin");
	strcpy(info.password, "admin");
	info.servPort = port;

	int errCode = SSLogin(&handle_, info);
	if (errCode == GOSUN_SUCCESS)
	{
		strcpy(ip_, ip);
		port_ = port;
	}

	return errCode;
}

void GxxGmSSObject::Logout()
{
	SSLogout(handle_);
}

void CALLBACK GxxGmSSObject::ExceptionCallback(GOSUN_HANDLE pHandle, GOSUN_ENUM_EXCEPTION_TYPE type, void* pExceptionInfo, void* userData)
{
	GxxGmSSObject *object = (GxxGmSSObject *)userData;

	switch (type)
	{
	case GOSUN_ENUM_EXCEPTION_TYPE::SDK_SERV_DISCONNECT:
		// ���������ӶϿ�
		//object->notifer_->Notifer(object->GetId(), NotiferType::);
		break;
	case GOSUN_ENUM_EXCEPTION_TYPE::SDK_STREAM_CLOSED:
		// ���Ͽ�
		break;
	default:
		break;
	}
}

void CALLBACK GxxGmSSObject::MSGCallBack(void* pMsgInfo,int iMsgLen,void* pUserData)
{
	GxxGmSSObject *object = (GxxGmSSObject *)pUserData;

	// ������Ҫ����XML��
	char *xml = new char[iMsgLen + 1];
	ZeroMemory(xml, iMsgLen + 1);
	memcpy(xml, pMsgInfo, iMsgLen);

	TiXmlDocument docXml;
	const char* errXml = docXml.Parse(xml);

	if (errXml != NULL)
	{
		// ������
	}

	const TiXmlElement *root_element = docXml.RootElement();
	if (!root_element)
		return ;

	const TiXmlNode *node = root_element->FirstChild("info")->FirstChild("alarmtype");
	if (!node)
		return ;

	const TiXmlElement *alarmtype_element = node->ToElement();
	if (!alarmtype_element)
		return ;

	const char *alarmtype = alarmtype_element->GetText();
	if (!alarmtype)
		return ;

	if (strcmp(alarmtype, "status") == 0)
	{
		// ���������豸ID��������Ϣ
		const char *device_id = root_element->FirstChild("info")->FirstChild("deviceid")->ToElement()->GetText();
		const char *battery = root_element->FirstChild("info")->FirstChild("alarminfo")->ToElement()->FirstChild("battery")->ToElement()->GetText();

		struct GxxGmDevHeartBeat hb;
		strcpy(hb.device_id, device_id);
		hb.battery = atof(battery);

		object->notifer_->Notifer(object->GetId(), NotiferType::HeartBeat, (const unsigned char *)&hb);
	}
	else if (strcmp(alarmtype, "gps") == 0)
	{
		// ��λ�����豸ID����λ��Ϣ
		const char *device_id = root_element->FirstChild("info")->FirstChild("deviceid")->ToElement()->GetText();
		const char *longitude = root_element->FirstChild("info")->FirstChild("alarminfo")->ToElement()->FirstChild("longitude")->ToElement()->GetText();
		const char *latitude = root_element->FirstChild("info")->FirstChild("alarminfo")->ToElement()->FirstChild("latitude")->ToElement()->GetText();

		struct GxxGmDevLocation dl;
		strcpy(dl.device_id, device_id);
		dl.longitude = atoi(longitude);
		dl.latitude = atoi(latitude);
		object->notifer_->Notifer(object->GetId(), NotiferType::Location, (const unsigned char *)&dl);
	}
	
	Sleep(1);
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

GxxGmSSMgr::GxxGmSSMgr(GxxGmSSMgrNotifer *notifer)
: total_(0)
, notifer_(notifer)
{
	SSInit();

	// ���￪����ʱ��
}

GxxGmSSMgr::~GxxGmSSMgr()
{
	SSUninit();
}

int GxxGmSSMgr::Follow(const char *ip, int port)
{
	int errCode = 0;

	// ���ȼ���Ƿ��Ѿ���ע�˶�Ӧ����ý��
	if (IsFollowed(ip, port))
		return -1;

	// û�й�ע����ô���Ǵ���һ���µ���ý����������й���
	GxxGmSSObject *object = new GxxGmSSObject(total_, this);
	errCode = object->Login(ip, port);
	if (errCode == 0)
	{
		// ֪ͨ�ϲ㣬��ע�ɹ������Ӽ���
		//struct GxxGmSSInfo ss;
		//itoa(object->GetId(), ss.ss_id, 10);
		//strcpy(ss.ip, ip);
		//itoa(port, ss.port, 10);
		//notifer_->Notifer(object->GetId(), NULL, SSMgrNotiferType::DevOnline, (const unsigned char *)&ss);
		++total_;

		// �����б���ʱ���ᶨ�ڼ���������
	}

	return errCode;
}

void GxxGmSSMgr::UnFollow(int id)
{
	// ��map���ҵ���Ӧ��Ԫ�أ��Ƴ�����Ȼ���˳���¼���ͷ��ڴ�
}

int GxxGmSSMgr::Notifer(int ss_id, enum NotiferType type, const unsigned char *data)
{
	// ��ʵ������Ҫ����һ�飬�ж��豸������
	switch (type)
	{
	case NotiferType::HeartBeat:
		// ��������
		{
			struct GxxGmDevHeartBeat *hb = (struct GxxGmDevHeartBeat*)data;
			std::vector<GxxGmDevInfo>::iterator iter;
			bool finded = false;
			for (iter = online_dev_.begin(); iter != online_dev_.end(); ++iter)
			{
				if ((atoi(iter->ss_id) == ss_id) && (strcmp(iter->dev_id, hb->device_id) == 0))
				{
					finded = true;
					iter->picktime = GetTickCount();
					break;
				}
			}

			if (!finded)
			{
				// ˵���������ߵ�
				GxxGmDevInfo info;
				itoa(ss_id, info.ss_id, 10);
				strcpy(info.dev_id, hb->device_id);
				info.picktime = GetTickCount();
				online_dev_.push_back(info);
				this->notifer_->Notifer(ss_id, hb->device_id, SSMgrNotiferType::DevOnline, NULL);
			}
			else
			{
				// �Ѿ������ˣ�����ʲô�������������Ӧ�ø�����������ʱ��
			}
		}
		break;
	}
	
	return 0;
}

bool GxxGmSSMgr::IsFollowed(const char *ip, int port)
{
	std::map<int, GxxGmSSObject*>::iterator iter;
	for (iter = ss_list_.begin(); iter != ss_list_.end(); ++iter)
	{
		if ((strcmp(iter->second->GetIp(), ip) == 0) && (iter->second->GetPort() == port))
			return true;
	}

	return false;
}