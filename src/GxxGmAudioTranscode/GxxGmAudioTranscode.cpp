// GxxGmAudioTranscode.cpp : 定义控制台应用程序的入口点。
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
#ifdef __cplusplus
};
#endif

#define SOURCE_AUTIO_PATH "F:\\Downloads\\WPF_JJDown_v1.210.0\\[WPF]JJDown\\Download\\chongai.Mp3"
#define TARGET_AUDIO_PATH "chongai_audio.mkv"

const enum AVCodecID encoder_id = AV_CODEC_ID_PCM_MULAW;

int _tmain(int argc, _TCHAR* argv[])
{
	av_register_all();
	avformat_network_init();
	avcodec_register_all();

	char errstr[4096] = {0};

	// 打开音频文件
	AVFormatContext *mp3_fmtctx = NULL;
	int errCode = avformat_open_input(&mp3_fmtctx, SOURCE_AUTIO_PATH, NULL, NULL);
	if (errCode < 0)
	{
		char *errinfo = av_make_error_string(errstr, AV_ERROR_MAX_STRING_SIZE, errCode);
		std::cout<<"打开文件出错："<<errinfo<<std::endl;
		system("pause");
		return errCode;
	}

	errCode = avformat_find_stream_info(mp3_fmtctx, NULL);
	if (errCode < 0)
	{
		char *errinfo = av_make_error_string(errstr, AV_ERROR_MAX_STRING_SIZE, errCode);
		std::cout<<"查找文件信息出错："<<errinfo<<std::endl;
		system("pause");
		return errCode;
	}

	AVStream *audio_stream = NULL;
	AVStream *video_stream = NULL;
	for (int index = 0; index < mp3_fmtctx->nb_streams; ++index)
	{
		if (mp3_fmtctx->streams[index]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audio_stream = mp3_fmtctx->streams[index];
		}
		else if (mp3_fmtctx->streams[index]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			video_stream = mp3_fmtctx->streams[index];
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// 这里准备转码参数
	
	AVIOContext *output_io_context = NULL;
	errCode = avio_open(&output_io_context, TARGET_AUDIO_PATH, AVIO_FLAG_WRITE);
	if (errCode < 0)
	{
		char *errinfo = av_make_error_string(errstr, AV_ERROR_MAX_STRING_SIZE, errCode);
		std::cout<<"创建输出文件出错："<<errinfo<<std::endl;
		system("pause");
		return errCode;
	}

	AVFormatContext *output_fmtctx = avformat_alloc_context();
	if (output_fmtctx == NULL)
	{
		std::cout<<"申请输出上下文失败！"<<std::endl;
		system("pause");
		return errCode;
	}

	output_fmtctx->pb = output_io_context;

	output_fmtctx->oformat = av_guess_format(NULL, TARGET_AUDIO_PATH, NULL);

	strcpy(output_fmtctx->filename, TARGET_AUDIO_PATH);

	// 编码器信息
	AVCodec *encoder = avcodec_find_encoder(encoder_id);
	if (encoder == NULL)
	{
		std::cout<<"没有找到编码器！"<<std::endl;
		system("pause");
		return errCode;
	}

	AVStream *target_audio_stream = avformat_new_stream(output_fmtctx, NULL);
	if (target_audio_stream == NULL)
	{
		std::cout<<"申请输出流失败！"<<std::endl;
		system("pause");
		return errCode;
	}

	AVCodecContext *avctx = avcodec_alloc_context3(encoder);
	if (avctx == NULL)
	{
		std::cout<<"申请编码器上下文失败！"<<std::endl;
		system("pause");
		return errCode;
	}

	avctx->channels = 2;
	avctx->channel_layout = av_get_default_channel_layout(2);
	avctx->sample_rate = audio_stream->codec->sample_rate;
	avctx->sample_fmt = encoder->sample_fmts[0];
	avctx->bit_rate = 96000;

	target_audio_stream->time_base.den = audio_stream->codec->sample_rate;
	target_audio_stream->time_base.num = 1;

	// 有些容器需要全局头部，我们判断一下，如果需要就设置
	if (output_fmtctx->oformat->flags & AVFMT_GLOBALHEADER)
		avctx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

	// 打开编码器
	errCode = avcodec_open2(avctx, encoder, NULL);
	if (errCode < 0)
	{
		char *errinfo = av_make_error_string(errstr, AV_ERROR_MAX_STRING_SIZE, errCode);
		std::cout<<"打开编码器出错："<<errinfo<<std::endl;
		system("pause");
		return errCode;
	}

	return 0;
}

