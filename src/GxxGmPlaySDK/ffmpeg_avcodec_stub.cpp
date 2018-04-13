#include "ffmpeg_avcodec_stub.h"

ffmpeg_avcodec_stub::ffmpeg_avcodec_stub()
: ffmpeg_avcodec_lib_(NULL)
{

}

ffmpeg_avcodec_stub::~ffmpeg_avcodec_stub()
{

}

int ffmpeg_avcodec_stub::Initialize(const char *lib_path)
{
	int errCode = 0;

	// º”‘ÿø‚
	ffmpeg_avcodec_lib_ = LoadLibraryA(lib_path);
	if (ffmpeg_avcodec_lib_ == NULL)
	{
		errCode = GetLastError();
		return errCode;
	}

	// ÃÓ≥‰∫Ø ˝÷∏’Î
	FFMPEG_INTERFCE(avcodec_find_decoder) = (FFMPEG_INTERFCE_TYPE(avcodec_find_decoder))GetProcAddress(ffmpeg_avcodec_lib_, "avcodec_find_decoder");
	if (FFMPEG_INTERFCE(avcodec_find_decoder) == NULL)
	{
	}

	FFMPEG_INTERFCE(avcodec_open2) = (FFMPEG_INTERFCE_TYPE(avcodec_open2))GetProcAddress(ffmpeg_avcodec_lib_, "avcodec_open2");
	FFMPEG_INTERFCE(avcodec_close) = (FFMPEG_INTERFCE_TYPE(avcodec_close))GetProcAddress(ffmpeg_avcodec_lib_, "avcodec_close");
	FFMPEG_INTERFCE(av_free_packet) = (FFMPEG_INTERFCE_TYPE(av_free_packet))GetProcAddress(ffmpeg_avcodec_lib_, "av_free_packet");

	return errCode;
}

void ffmpeg_avcodec_stub::Close()
{

}