#include "GxxGmStreamRecevicer.h"
#include "GxxGmGSPHandler.h"

#define GSP_PROTOCOL	"gsp://"
#define RTSP_PROTOCOL	"rtsp://"
#define RTMP_PROTOCOL	"rtmp://"
#define HTTP_PROTOCOL	"http://"
#define HTTPS_PROTOCOL	"https://"


GxxGmStreamRecevicer::GxxGmStreamRecevicer(GxxGmStreamRecevicerObserver *observer)
: observer_(observer)
, is_output_(false)
, audio_stream_(NULL)
, video_stream_(NULL)
, instance_(new GxxGmRecevicerInstance)
{
	//SSInit();
}

GxxGmStreamRecevicer::~GxxGmStreamRecevicer()
{
	observer_ = NULL;
	//SSUninit();
}

int GxxGmStreamRecevicer::OpenURL(const char *url)
{
	int errCode = 0;

	// ����Ҫ�ж�Э������
	char url_lower[4096] = {0};
	strcpy_s(url_lower, 4096, url);
	_strlwr_s(url_lower);

	if (memcmp(url_lower, GSP_PROTOCOL, strlen(GSP_PROTOCOL)) == 0)
	{
		// gspЭ��
		instance_->gsp_handler_ = new GxxGmGSPHandler();
		errCode = instance_->gsp_handler_->OpenURL(url_lower);
	}
	else if (memcmp(url_lower, RTSP_PROTOCOL, strlen(RTSP_PROTOCOL)) == 0)
	{
		// rtspЭ��
	}
	else if (memcmp(url_lower, RTMP_PROTOCOL, strlen(RTMP_PROTOCOL)) == 0)
	{
		// rtmpЭ��
	}
	else if (memcmp(url_lower, HTTP_PROTOCOL, strlen(HTTP_PROTOCOL)) == 0)
	{
		// httpЭ��
	}
	else if (memcmp(url_lower, HTTPS_PROTOCOL, strlen(HTTPS_PROTOCOL)) == 0)
	{
		// httpsЭ��
	}

	return errCode;
}

void GxxGmStreamRecevicer::Close()
{
	instance_->gsp_handler_->Close();
}

int GxxGmStreamRecevicer::Play()
{
	int errCode = 0;

	is_output_ = true;

	return errCode;
}

void GxxGmStreamRecevicer::Stop()
{
	is_output_ = false;
}