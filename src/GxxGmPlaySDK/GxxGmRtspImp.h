#ifndef _GxxGmRtspImp_H_
#define _GxxGmRtspImp_H_

#include "GxxGmPlaySDKCallback.h"
#include "GSRtspStackCommonDef.h"

class GSRtspClient;

class GxxGmRtspImp
{
public:
	GxxGmRtspImp(GxxGmPlaySDKNotifer *notifer);
	~GxxGmRtspImp();

public:
	int Open(const char *url);
	int Play();
	int Pause();
	int Stop();
	void Close();

public:
	int rtsp_client_state_;

public:
	GSRtspClient *rtsp_client_;
	StruSourceMuxDescription source_mux_description_;
	
public:
	GxxGmPlaySDKNotifer *notifer_;
};

#endif//_GxxGmRtspImp_H_
