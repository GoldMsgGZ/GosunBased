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
		// 服务器连接断开
		//object->notifer_->Notifer(object->GetId(), NotiferType::);
		break;
	case GOSUN_ENUM_EXCEPTION_TYPE::SDK_STREAM_CLOSED:
		// 流断开
		break;
	default:
		break;
	}
}

void CALLBACK GxxGmSSObject::MSGCallBack(void* pMsgInfo,int iMsgLen,void* pUserData)
{
	GxxGmSSObject *object = (GxxGmSSObject *)pUserData;

	// 这里需要解析XML吧
	char *xml = new char[iMsgLen + 1];
	ZeroMemory(xml, iMsgLen + 1);
	memcpy(xml, pMsgInfo, iMsgLen);

	TiXmlDocument docXml;
	const char* errXml = docXml.Parse(xml);

	if (errXml != NULL)
	{
		// 出错了
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
		// 心跳，拿设备ID，基本信息
		const char *device_id = root_element->FirstChild("info")->FirstChild("deviceid")->ToElement()->GetText();
		const char *battery = root_element->FirstChild("info")->FirstChild("alarminfo")->ToElement()->FirstChild("battery")->ToElement()->GetText();

		struct GxxGmDevHeartBeat hb;
		strcpy(hb.device_id, device_id);
		hb.battery = atof(battery);

		object->notifer_->Notifer(object->GetId(), NotiferType::HeartBeat, (const unsigned char *)&hb);
	}
	else if (strcmp(alarmtype, "gps") == 0)
	{
		// 定位，拿设备ID，定位信息
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

	// 这里开启定时器
}

GxxGmSSMgr::~GxxGmSSMgr()
{
	SSUninit();
}

int GxxGmSSMgr::Follow(const char *ip, int port)
{
	int errCode = 0;

	// 首先检查是否已经关注了对应的流媒体
	if (IsFollowed(ip, port))
		return -1;

	// 没有关注，那么我们创建一个新的流媒体对象来进行管理
	GxxGmSSObject *object = new GxxGmSSObject(total_, this);
	errCode = object->Login(ip, port);
	if (errCode == 0)
	{
		// 通知上层，关注成功，增加计数
		//struct GxxGmSSInfo ss;
		//itoa(object->GetId(), ss.ss_id, 10);
		//strcpy(ss.ip, ip);
		//itoa(port, ss.port, 10);
		//notifer_->Notifer(object->GetId(), NULL, SSMgrNotiferType::DevOnline, (const unsigned char *)&ss);
		++total_;

		// 加入列表，定时器会定期检查在线情况
	}

	return errCode;
}

void GxxGmSSMgr::UnFollow(int id)
{
	// 从map中找到对应的元素，移除掉，然后退出登录、释放内存
}

int GxxGmSSMgr::Notifer(int ss_id, enum NotiferType type, const unsigned char *data)
{
	// 其实在这里要过滤一遍，判断设备上下线
	switch (type)
	{
	case NotiferType::HeartBeat:
		// 更新心跳
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
				// 说明是新上线的
				GxxGmDevInfo info;
				itoa(ss_id, info.ss_id, 10);
				strcpy(info.dev_id, hb->device_id);
				info.picktime = GetTickCount();
				online_dev_.push_back(info);
				this->notifer_->Notifer(ss_id, hb->device_id, SSMgrNotiferType::DevOnline, NULL);
			}
			else
			{
				// 已经在线了，这里什么都不做，上面的应该更新心跳接收时间
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