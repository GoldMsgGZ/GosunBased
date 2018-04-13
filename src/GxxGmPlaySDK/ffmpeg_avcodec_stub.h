#ifndef _ffmpeg_avcodec_stub_H_
#define _ffmpeg_avcodec_stub_H_

#include "ffmpeg_interface_def.h"
#include "ffmpeg_interface_declare.h"
#include <Windows.h>

class ffmpeg_avcodec_stub
{
public:
	ffmpeg_avcodec_stub();
	~ffmpeg_avcodec_stub();

public:
	int Initialize(const char *lib_path);
	void Close();

public:
	FFMPEG_INTERFACE_DECLARE(avcodec_find_decoder);
	FFMPEG_INTERFACE_DECLARE(avcodec_open2);
	FFMPEG_INTERFACE_DECLARE(avcodec_close);
	FFMPEG_INTERFACE_DECLARE(av_free_packet);

public:
	HMODULE ffmpeg_avcodec_lib_;
};

#endif//_ffmpeg_avcodec_stub_H_
