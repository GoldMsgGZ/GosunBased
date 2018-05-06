// GxxGmRemuxing.cpp : �������̨Ӧ�ó������ڵ㡣
//
// �����ر�˵��һ�£�MP4�ļ����Խ�AVI��MJPEG���븴�õ���ʽ�У�������Ƶ��PCM��Ҫת��ΪAAC
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libswresample/swresample.h"
#include "libavutil/avutil.h"
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
	errCode = avformat_open_input(&input_fmtctx_, input_file, NULL, NULL);
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

	AVOutputFormat *ofmt = output_fmtctx_->oformat;

	//////////////////////////////////////////////////////////////////////////
	AVStream *video_stream = NULL;
	AVStream *audio_stream = NULL;
	int video_index = -1;
	int audio_index = -1;

	AVStream *video_output_stream = NULL;
	AVStream *audio_output_stream = NULL;

	AVCodecContext *audio_output_codecctx_ = NULL;
	AVCodec *audio_encoder_ = NULL;

	AVCodecContext *audio_input_codecctx_ = NULL;
	AVCodec *audio_decoder_ = NULL;

	AVFrame *audio_frame_ = NULL;
	int buffer_size = 0;
	uint8_t *frame_buffer = NULL;

	for (int index = 0; index < input_fmtctx_->nb_streams; ++index)
	{
		AVStream *in_stream = input_fmtctx_->streams[index];
		AVCodecParameters *in_codecpar = in_stream->codecpar;

		if (in_codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			video_index = index;
			video_stream = in_stream;

			// �������copy��ԭ��������Ϣ������codec��һ�������
			video_output_stream = avformat_new_stream(output_fmtctx_, NULL);
			if (video_output_stream == NULL)
			{
				printf("������Ƶ�����ʧ�ܣ�\n");
				errCode = AVERROR_UNKNOWN;
				goto end;
			}

			// ���Ʋ���
			errCode = avcodec_parameters_copy(video_output_stream->codecpar, in_codecpar);
			if (errCode < 0)
			{
				printf("����������ʧ�ܣ�\n");
				errCode = AVERROR_UNKNOWN;
				goto end;
			}

			video_output_stream->codecpar->codec_tag = 0;
		}
		else if (in_codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audio_index = index;
			audio_stream = in_stream;

			audio_input_codecctx_ = audio_stream->codec;

			//////////////////////////////////////////////////////////////////////////
			// ���������
			audio_output_stream = avformat_new_stream(output_fmtctx_, NULL);
			if (audio_output_stream == NULL)
			{
				printf("������Ƶ�����ʧ�ܣ�\n");
				errCode = AVERROR_UNKNOWN;
				goto end;
			}

			// ���Ʋ���
			errCode = avcodec_parameters_copy(audio_output_stream->codecpar, in_codecpar);
			if (errCode < 0)
			{
				printf("����������ʧ�ܣ�\n");
				errCode = AVERROR_UNKNOWN;
				goto end;
			}

			audio_output_stream->codecpar->codec_tag = 0;

		}
	}

	av_dump_format(output_fmtctx_, 0, output_file, 1);

	//////////////////////////////////////////////////////////////////////////
	if (!(output_fmtctx_->flags & AVFMT_NOFILE))
	{
		errCode = avio_open(&output_fmtctx_->pb, output_file, AVIO_FLAG_WRITE);
		if (errCode < 0)
		{
			printf("��������ļ�ʧ�ܣ�\n");
			goto end;
		}
	}

	errCode = avformat_write_header(output_fmtctx_, NULL);
	if (errCode < 0)
	{
		printf("д���ļ�ͷʧ�ܣ�\n");
		goto end;
	}

	while (true)
	{
		AVPacket pkt;
		errCode = av_read_frame(input_fmtctx_, &pkt);
		if (errCode < 0)
			break;

		AVStream *in_stream = input_fmtctx_->streams[pkt.stream_index];
		AVStream *out_stream = output_fmtctx_->streams[pkt.stream_index];
		
		//
		pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
		pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
		pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
		pkt.pos = -1;

		errCode = av_interleaved_write_frame(output_fmtctx_, &pkt);
		if (errCode < 0)
		{
			printf("д��֡ʧ�ܣ�\n");
			goto end;
		}

		av_packet_unref(&pkt);
	}

	av_write_trailer(output_fmtctx_);

end:

	avformat_close_input(&input_fmtctx_);

	if (output_fmtctx_ && !(output_fmtctx_->flags & AVFMT_NOFILE))
		avio_closep(&output_fmtctx_->pb);
	avformat_free_context(output_fmtctx_);

	if (errCode < 0 && errCode != AVERROR_EOF)
	{
		//printf("�����˴���%s\n", (av_err2str(errCode)));
		return 1;
	}

	return 0;
}

