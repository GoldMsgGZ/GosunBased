#ifndef _ffmpeg_stub_H_
#define _ffmpeg_stub_H_

#include <Windows.h>

class ffmpeg_avformat_stub;
class ffmpeg_avcodec_stub;

class ffmpeg_stub
{
public:
	ffmpeg_stub();
	~ffmpeg_stub();

public:
	int LoadFFmpeg(const char *version = NULL, const char *root_dir = NULL);
	void ReleaseFFmpeg();

public:
	ffmpeg_avformat_stub *avformat_;
	ffmpeg_avcodec_stub *avcodec_;
};

#endif//_ffmpeg_stub_H_
