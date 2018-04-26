// GxxGmRemuxing.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libswresample/swresample.h"
#include "libavutil/avutil.h"
#include "libavutil/timestamp.h"
#ifdef __cplusplus
};
#endif


int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 3) {
		printf("用法: %s input output\n\n本程序用于封装转换，不涉及视频转码，音频按需转换", argv[0]);
		system("pause");
		return 0;
	}

	const char *input_file = argv[1];
	const char *output_file = argv[2];

	av_register_all();
	avformat_network_init();

	//////////////////////////////////////////////////////////////////////////
	//
	// 预处理输入文件

	int errCode = 0;

	// 尝试打开输入文件
	AVFormatContext *input_fmtctx_ = NULL;
	int errCode = avformat_open_input(&input_fmtctx_, input_file, NULL, NULL);
	if (errCode < 0)
	{
		printf("打开文件%d失败！错误码：%d\n", errCode);
		errCode = AVERROR_UNKNOWN;
		goto end;
	}

	errCode = avformat_find_stream_info(input_fmtctx_, NULL);
	if (errCode < 0)
	{
		printf("查找流信息失败！错误码：%d\n", errCode);
		errCode = AVERROR_UNKNOWN;
		goto end;
	}

	// 输入文件信息
	av_dump_format(input_fmtctx_, 0, input_file, 0);

	//////////////////////////////////////////////////////////////////////////
	//
	// 预处理输出文件

	AVFormatContext *output_fmtctx_ = NULL;
	avformat_alloc_output_context2(&output_fmtctx_, NULL, NULL, output_file);
	if (!output_fmtctx_)
	{
		printf("申请输出文件上下文对象失败！\n");
		errCode = AVERROR_UNKNOWN;
		goto end;
	}

	int *stream_mapping = NULL;
	int stream_mapping_size = input_fmtctx_->nb_streams;
	stream_mapping = av_mallocz_array(stream_mapping_size, sizeof(*stream_mapping));
	if (!stream_mapping)
	{
		printf("申请内存失败！\n");
		errCode = AVERROR(ENOMEM);
		goto end;
	}

	AVOutputFormat *ofmt = output_fmtctx_->oformat;

	for (int index = 0; index < input_fmtctx_->nb_streams; ++index)
	{
	}

end:

	return 0;
}

