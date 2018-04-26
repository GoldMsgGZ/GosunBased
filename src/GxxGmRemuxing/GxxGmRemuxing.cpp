// GxxGmRemuxing.cpp : �������̨Ӧ�ó������ڵ㡣
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
		printf("�÷�: %s input output\n\n���������ڷ�װת�������漰��Ƶת�룬��Ƶ����ת��", argv[0]);
		system("pause");
		return 0;
	}

	const char *input_file = argv[1];
	const char *output_file = argv[2];

	av_register_all();
	avformat_network_init();

	//////////////////////////////////////////////////////////////////////////
	//
	// Ԥ���������ļ�

	int errCode = 0;

	// ���Դ������ļ�
	AVFormatContext *input_fmtctx_ = NULL;
	int errCode = avformat_open_input(&input_fmtctx_, input_file, NULL, NULL);
	if (errCode < 0)
	{
		printf("���ļ�%dʧ�ܣ������룺%d\n", errCode);
		errCode = AVERROR_UNKNOWN;
		goto end;
	}

	errCode = avformat_find_stream_info(input_fmtctx_, NULL);
	if (errCode < 0)
	{
		printf("��������Ϣʧ�ܣ������룺%d\n", errCode);
		errCode = AVERROR_UNKNOWN;
		goto end;
	}

	// �����ļ���Ϣ
	av_dump_format(input_fmtctx_, 0, input_file, 0);

	//////////////////////////////////////////////////////////////////////////
	//
	// Ԥ��������ļ�

	AVFormatContext *output_fmtctx_ = NULL;
	avformat_alloc_output_context2(&output_fmtctx_, NULL, NULL, output_file);
	if (!output_fmtctx_)
	{
		printf("��������ļ������Ķ���ʧ�ܣ�\n");
		errCode = AVERROR_UNKNOWN;
		goto end;
	}

	int *stream_mapping = NULL;
	int stream_mapping_size = input_fmtctx_->nb_streams;
	stream_mapping = av_mallocz_array(stream_mapping_size, sizeof(*stream_mapping));
	if (!stream_mapping)
	{
		printf("�����ڴ�ʧ�ܣ�\n");
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

