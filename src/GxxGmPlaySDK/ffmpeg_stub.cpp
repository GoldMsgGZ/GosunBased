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
	// ����򵥴ֱ�һ�������
	// �ȼ������ǰģ������·��
	return 0;
}

void ffmpeg_stub::ReleaseFFmpeg()
{

}