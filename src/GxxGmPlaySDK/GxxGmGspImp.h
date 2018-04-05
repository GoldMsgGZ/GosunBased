#ifndef _GxxGmGspImp_H_
#define _GxxGmGspImp_H_

#include "GxxGmPlaySDKCallback.h"

class GxxGmGspImp
{
public:
	GxxGmGspImp(GxxGmPlaySDKNotifer *notifer);
	~GxxGmGspImp();

public:
	int Open(const char *url);
	int Play();
	int Pause();
	int Stop();
	void Close();

private:
	void* stream_handle_;

public:
	GxxGmPlaySDKNotifer *notifer_;
	bool is_paused_;
};

#endif//_GxxGmGspImp_H_
