#ifndef _ffmpeg_avformat_stub_H_
#define _ffmpeg_avformat_stub_H_

#include "ffmpeg_interface_def.h"
#include "ffmpeg_interface_declare.h"
#include <Windows.h>

class ffmpeg_avformat_stub
{
public:
	ffmpeg_avformat_stub();
	~ffmpeg_avformat_stub();

public:
	int Initialize(const char *lib_path);
	void Close();

public:
	FFMPEG_INTERFACE_DECLARE(av_register_all);
	FFMPEG_INTERFACE_DECLARE(avformat_network_init);
	FFMPEG_INTERFACE_DECLARE(avformat_network_deinit);
	FFMPEG_INTERFACE_DECLARE(avformat_open_input);
	FFMPEG_INTERFACE_DECLARE(avformat_close_input);
	FFMPEG_INTERFACE_DECLARE(avformat_find_stream_info);
	FFMPEG_INTERFACE_DECLARE(av_seek_frame);
	FFMPEG_INTERFACE_DECLARE(av_read_frame);

public:
	HMODULE ffmpeg_avformat_lib_;
};

#endif//_ffmpeg_avformat_stub_H_
