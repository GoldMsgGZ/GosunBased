// GxxGmRemuxing.cpp : 定义控制台应用程序的入口点。
//
// 这里特别说明一下，MP4文件可以将AVI的MJPEG编码复用到格式中，但是音频的PCM需要转码为AAC
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
	errCode = avformat_open_input(&input_fmtctx_, input_file, NULL, NULL);
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

			// 这里就是copy了原来的流信息，包括codec这一类的数据
			video_output_stream = avformat_new_stream(output_fmtctx_, NULL);
			if (video_output_stream == NULL)
			{
				printf("创建视频输出流失败！\n");
				errCode = AVERROR_UNKNOWN;
				goto end;
			}

			// 复制参数
			errCode = avcodec_parameters_copy(video_output_stream->codecpar, in_codecpar);
			if (errCode < 0)
			{
				printf("复制流参数失败！\n");
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
			// 创建输出流
			audio_output_stream = avformat_new_stream(output_fmtctx_, NULL);
			if (audio_output_stream == NULL)
			{
				printf("创建音频输出流失败！\n");
				errCode = AVERROR_UNKNOWN;
				goto end;
			}

			// 复制参数
			errCode = avcodec_parameters_copy(audio_output_stream->codecpar, in_codecpar);
			if (errCode < 0)
			{
				printf("复制流参数失败！\n");
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
			printf("创建输出文件失败！\n");
			goto end;
		}
	}

	errCode = avformat_write_header(output_fmtctx_, NULL);
	if (errCode < 0)
	{
		printf("写入文件头失败！\n");
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
			printf("写入帧失败！\n");
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
		//printf("发生了错误！%s\n", (av_err2str(errCode)));
		return 1;
	}

	return 0;
}

