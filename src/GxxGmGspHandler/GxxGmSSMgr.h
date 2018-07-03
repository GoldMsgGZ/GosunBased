#ifndef _GxxGmSSMgr_H_
#define _GxxGmSSMgr_H_

#include <map>
#include <vector>
#include "StreamServerSDK.h"

enum NotiferType
{
	HeartBeat,
	Location
};

struct GxxGmDevHeartBeat
{
	char device_id[64];
	double battery;
};

struct GxxGmDevLocation
{
	char device_id[64];
	double longitude;
	double latitude;
	double height;
	double direction;
	double speed;
	double radius;
};

class GxxGmSSObjectNotifer
{
public:
	virtual int Notifer(int ss_id, enum NotiferType type, const unsigned char *data) = 0;
};

class GxxGmSSObject
{
public:
	GxxGmSSObject(int id, GxxGmSSObjectNotifer *notifer);
	~GxxGmSSObject();

public:
	int GetId() { return id_; }
	const char* GetIp() { return ip_; }
	int GetPort() { return port_; }

public:
	static void CALLBACK ExceptionCallback(GOSUN_HANDLE pHandle, GOSUN_ENUM_EXCEPTION_TYPE type, void* pExceptionInfo, void* userData);
	static void CALLBACK MSGCallBack(void* pMsgInfo,int iMsgLen,void* pUserData);

public:
	int Login(const char *ip, int port);
	void Logout();

public:
	GxxGmSSObjectNotifer *notifer_;

private:
	int id_;
	char ip_[32];
	int port_;
	GOSUN_SERV_HANDLE handle_;
	
};

enum SSMgrNotiferType
{
	SSOnline,
	SSOffline,
	DevOnline,
	DevOffline
};

struct GxxGmSSInfo
{
	char ss_id[64];
	char ip[32];
	char port[32];
};

struct GxxGmDevInfo
{
	char ss_id[64];
	char dev_id[64];
	unsigned int picktime;
};

class GxxGmSSMgrNotifer
{
public:
	virtual int Notifer(int ss_id, const char *dev_id, enum SSMgrNotiferType type, const unsigned char *data) = 0;
};

class GxxGmSSMgr : public GxxGmSSObjectNotifer
{
public:
	GxxGmSSMgr(GxxGmSSMgrNotifer *notifer);
	~GxxGmSSMgr();

public:
	int Follow(const char *ip, int port);
	void UnFollow(int id);

public:
	virtual int Notifer(int ss_id, enum NotiferType type, const unsigned char *data);

private:
	bool IsFollowed(const char *ip, int port);

public:
	std::map<int, GxxGmSSObject*> ss_list_;
	int total_;

	std::vector<GxxGmDevInfo> online_dev_;

private:
	GxxGmSSMgrNotifer *notifer_;
};

#endif//_GxxGmSSMgr_H_
