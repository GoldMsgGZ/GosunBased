#include "ffmpeg_avformat_stub.h"

ffmpeg_avformat_stub::ffmpeg_avformat_stub()
: ffmpeg_avformat_lib_(NULL)
{
	
}

ffmpeg_avformat_stub::~ffmpeg_avformat_stub()
{

}

int ffmpeg_avformat_stub::Initialize(const char *lib_path)
{
	int errCode = 0;

	// º”‘ÿø‚
	ffmpeg_avformat_lib_ = LoadLibraryA(lib_path);
	if (ffmpeg_avformat_lib_ == NULL)
	{
		errCode = GetLastError();
		return errCode;
	}

	// ÃÓ≥‰∫Ø ˝÷∏’Î
	FFMPEG_INTERFCE(av_register_all) = (FFMPEG_INTERFCE_TYPE(av_register_all))GetProcAddress(ffmpeg_avformat_lib_, "av_register_all");
	if (FFMPEG_INTERFCE(av_register_all) == NULL)
	{
	}

	FFMPEG_INTERFCE(avformat_network_init) = (FFMPEG_INTERFCE_TYPE(avformat_network_init))GetProcAddress(ffmpeg_avformat_lib_, "avformat_network_init");
	FFMPEG_INTERFCE(avformat_network_deinit) = (FFMPEG_INTERFCE_TYPE(avformat_network_deinit))GetProcAddress(ffmpeg_avformat_lib_, "avformat_network_deinit");
	FFMPEG_INTERFCE(avformat_open_input) = (FFMPEG_INTERFCE_TYPE(avformat_open_input))GetProcAddress(ffmpeg_avformat_lib_, "avformat_open_input");
	FFMPEG_INTERFCE(avformat_close_input) = (FFMPEG_INTERFCE_TYPE(avformat_close_input))GetProcAddress(ffmpeg_avformat_lib_, "avformat_close_input");
	FFMPEG_INTERFCE(avformat_find_stream_info) = (FFMPEG_INTERFCE_TYPE(avformat_find_stream_info))GetProcAddress(ffmpeg_avformat_lib_, "avformat_find_stream_info");
	FFMPEG_INTERFCE(av_seek_frame) = (FFMPEG_INTERFCE_TYPE(av_seek_frame))GetProcAddress(ffmpeg_avformat_lib_, "av_seek_frame");
	FFMPEG_INTERFCE(av_read_frame) = (FFMPEG_INTERFCE_TYPE(av_read_frame))GetProcAddress(ffmpeg_avformat_lib_, "av_read_frame");

	return errCode;
}

void ffmpeg_avformat_stub::Close()
{

}