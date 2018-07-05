#ifndef _GxxGmStreamServerClient_H_
#define _GxxGmStreamServerClient_H_

#include "GxxGmStreamObserver.h"

class GxxGmStreamServerClient
{
public:
	GxxGmStreamServerClient(GxxGmStreamObserver *ob);
	~GxxGmStreamServerClient();

public:
	int Login(const char *ip, unsigned short port);
	void Logout();

	int Play(const char *id);
	void Stop();

public:


public:
	void *ss_handle_;
	void *stream_handle_;
	void *ps2es_handle_;

	GxxGmStreamObserver *ob_;
};

#endif//_GxxGmStreamServerClient_H_
