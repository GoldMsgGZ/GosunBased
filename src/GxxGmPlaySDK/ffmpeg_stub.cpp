#include "ffmpeg_stub.h"

ffmpeg_stub::ffmpeg_stub()
: avformat_(NULL)
, avcodec_(NULL)
{

}

ffmpeg_stub::~ffmpeg_stub()
{

}

int ffmpeg_stub::LoadFFmpeg(const char *version, const char *root_dir)
{
	// 这里简单粗暴一点来解决
	// 先计算出当前模块所在路径
	return 0;
}

void ffmpeg_stub::ReleaseFFmpeg()
{

}