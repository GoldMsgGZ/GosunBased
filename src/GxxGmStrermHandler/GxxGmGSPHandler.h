#ifndef _GxxGmGSPHandler_H_
#define _GxxGmGSPHandler_H_


#include "StreamServerSDK.h"
#include "PSFormat.h"
#include "FFmpeg2Gxx.h"

class GxxGmGSPHandler
{
public:
	GxxGmGSPHandler();
	~GxxGmGSPHandler();

public:
	int OpenURL(const char *url);
	void Close();

public:
	void* GetStreamHandle() { return stream_handle_; }
	void* GetMpegPsHandle() { return mpeg_ps_handle_; }
	bool IsDemuxingOK() { return media_info_total_count_ == collected_media_info_count_ ? true : false; }

private:
	void *stream_handle_;
	void *mpeg_ps_handle_;

	int media_info_total_count_;
	int collected_media_info_count_;
};

#endif//_GxxGmGSPHandler_H_
