#include "GxxGmHttpImp.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "libavformat\avformat.h"
#include "libavcodec\avcodec.h"
#include "libavutil\avutil.h"
#include "libavutil\samplefmt.h"
#ifdef __cplusplus
};
#endif

#include "FFmpeg2Gxx.h"
#include "GxxGmPlayBase.h"


#define _USE_GXX_
#ifndef _USE_GXX_
#define _USE_FFMPEG_
#endif//_USE_GXX_

#define USE_H264BSF



GxxGmHttpImp::GxxGmHttpImp(GxxGmPlaySDKNotifer *notifer)
: notifer_(notifer)
, is_paused_(false)
, need_stop_(false)
, read_stream_thread_handle_(NULL)
, format_ctx_(NULL)
, video_stream_index_(-1)
, audio_stream_index_(-1)
, video_stream_(NULL)
, audio_stream_(NULL)
, video_codec_ctx_(NULL)
, audio_codec_ctx_(NULL)
, video_codec_(NULL)
, audio_codec_(NULL)
{
	av_register_all();
	avformat_network_init();
	avcodec_register_all();
}

GxxGmHttpImp::~GxxGmHttpImp()
{

}

int GxxGmHttpImp::Open(const char *url)
{
	int errCode = 0;

	// 这里负责解复用，回调给上层视音频流的基本参数
	if (format_ctx_ == NULL)
	{
		errCode = avformat_open_input((AVFormatContext **)&format_ctx_, url, NULL, NULL);
		if (errCode != 0)
		{
			GxxGmPlayBase::DebugStringOutput("打开目标媒体：\"%s\"失败！错误码：%d\n", url, errCode);
			return errCode;
		}
		GxxGmPlayBase::DebugStringOutput("打开目标媒体：\"%s\"成功！错误码：%d\n", url, errCode);

		avformat_find_stream_info((AVFormatContext*)format_ctx_, NULL);

		int stream_count = ((AVFormatContext*)format_ctx_)->nb_streams;
		for (int index = 0; index < stream_count; ++index)
		{
			AVStream *st = ((AVFormatContext*)format_ctx_)->streams[index];
			if (st->codec->codec_type == AVMEDIA_TYPE_VIDEO)
			{
				video_stream_index_ = index;
				video_stream_ = (void*)st;
				video_codec_ctx_ = (void*)st->codec;

#ifdef _USE_FFMPEG_
				video_codec_ = (void*)avcodec_find_decoder(((AVCodecContext*)video_codec_ctx_)->codec_id);
				if (video_codec_ == NULL)
				{
					// 没有找到对应的视频解码器
					GxxGmPlayBase::DebugStringOutput("没有找到对应的视频解码器！解码器名称：%s\n", avcodec_get_name(((AVCodecContext*)video_codec_ctx_)->codec_id));
					break;
				}

				errCode = avcodec_open2((AVCodecContext*)video_codec_ctx_, (const AVCodec *)video_codec_, NULL);
				if (errCode != 0)
				{
					// 打开视频解码器失败
					GxxGmPlayBase::DebugStringOutput("打开视频解码器：%s 失败！错误码：%d\n", avcodec_get_name(((AVCodecContext*)video_codec_ctx_)->codec_id), errCode);
					break;
				}
#endif
			}
			else if (st->codec->codec_type == AVMEDIA_TYPE_AUDIO)
			{
				audio_stream_index_ = index;
				audio_stream_ = (void*)st;
				audio_codec_ctx_ = (void*)st->codec;

#ifdef _USE_FFMPEG_
				audio_codec_ = (void*)avcodec_find_decoder(((AVCodecContext*)audio_codec_ctx_)->codec_id);
				if (audio_codec_ == NULL)
				{
					// 没有找到对应的音频解码器
					GxxGmPlayBase::DebugStringOutput("没有找到对应的视频解码器！解码器名称：%s\n", avcodec_get_name(((AVCodecContext*)audio_codec_ctx_)->codec_id));
					break;
				}

				errCode = avcodec_open2((AVCodecContext*)audio_codec_ctx_, (const AVCodec *)audio_codec_, NULL);
				if (errCode != 0)
				{
					// 打开音频解码器失败
					GxxGmPlayBase::DebugStringOutput("打开视频解码器：%s 失败！错误码：%d\n", avcodec_get_name(((AVCodecContext*)audio_codec_ctx_)->codec_id), errCode);
					break;
				}
#endif
			}
		}

#ifdef _USE_GXX_
		eVideoCode_ = FFmpegCodecId2GxxCodecId(((AVStream *)video_stream_)->codecpar->codec_id);
		eAudioCode_ = FFmpegCodecId2GxxCodecId(((AVStream *)audio_stream_)->codecpar->codec_id);
		//unSampleRate_ = ((AVStream *)video_stream_)->codecpar->sample_rate;
		unSampleRate_ = ((AVCodecContext *)audio_codec_ctx_)->sample_rate;
		unBits_ = ((AVStream *)video_stream_)->codecpar->bits_per_raw_sample;
		//unChannels_ = ((AVStream *)video_stream_)->codecpar->channels;
		unChannels_ = ((AVCodecContext *)audio_codec_ctx_)->channels;
		nRefFrameRate_ = ((AVStream *)video_stream_)->avg_frame_rate.num / ((AVStream *)video_stream_)->avg_frame_rate.den;
		nEnableTimeCaculate_ = 0;
		GxxGmPlayBase::DebugStringOutput("eVideoCode:%d, eAudioCode:%d, unSampleRate:%d, unBits:%d, unChannels:%d, nRefFrameRate:%d, nEnableTimeCaculate:%d\n",
			eVideoCode_, eAudioCode_, unSampleRate_, unBits_, unChannels_, nRefFrameRate_, nEnableTimeCaculate_);
#endif

#ifdef _USE_FFMPEG_
		notifer_->StreamParamNotiferEx((AVCodecContext*)video_codec_ctx_, (AVCodecContext*)audio_codec_ctx_);
#else if
		notifer_->StreamParamNotifer(eVideoCode_, eAudioCode_, unSampleRate_, unBits_, unChannels_, nRefFrameRate_, nEnableTimeCaculate_);
#endif
	}

	return 0;
}

int GxxGmHttpImp::Play()
{
	int errCode = 0;

	// 启动线程，读出编码包，将编码包数据传到上层
	DWORD thread_exit_code = 0;
	GetExitCodeThread(read_stream_thread_handle_, &thread_exit_code);
	if (thread_exit_code == STILL_ACTIVE)
	{
		// 线程正在运行，那么则将暂停标志位调整为关闭
		// 这里用系统事件可能会更好
		GxxGmPlayBase::DebugStringOutput("流读取线程正在运行，将暂停标记关闭！\n");
		is_paused_ = false;
	}
	else
	{
		// 不存在线程，那么我们就新建一个线程来处理相关问题
		GxxGmPlayBase::DebugStringOutput("未检测到流读取线程，启动线程！\n");
		framerate_event_handle_ = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (framerate_event_handle_ == NULL)
		{
			errCode = GetLastError();
			return errCode;
		}

		control_thread_handle_ = CreateThread(NULL, 0, ControlThread, this, 0, NULL);
		if (control_thread_handle_ == NULL)
		{
			errCode = GetLastError();
			return errCode;
		}

		read_stream_thread_handle_ = CreateThread(NULL, 0, ReadStreamThread, this, 0, NULL);
		if (read_stream_thread_handle_ == NULL)
		{
			errCode = GetLastError();
			TerminateThread(control_thread_handle_, 4);
			return errCode;
		}
	}

	need_stop_ = false;
	return 0;
}

int GxxGmHttpImp::Pause()
{
	// 暂停读取编码包
	GxxGmPlayBase::DebugStringOutput("流读取线程正在运行，将暂停标记开启！\n");
	is_paused_ = true;
	need_stop_ = false;
	return 0;
}

int GxxGmHttpImp::Stop()
{
	// 停止读取数据包，通知退出线程
	need_stop_ = true;
	return 0;
}

void GxxGmHttpImp::Close()
{

}

DWORD WINAPI GxxGmHttpImp::ReadStreamThread(LPVOID lpParam)
{
	GxxGmHttpImp *http_ = (GxxGmHttpImp *)lpParam;
	GxxGmPlayBase::DebugStringOutput("已启动媒体解码线程...\n");

#ifdef USE_H264BSF
	AVBitStreamFilterContext *h264_bit_stream_filter_context = av_bitstream_filter_init("h264_mp4toannexb");
#endif

	// 这里开始组织
	int index = 0;
	AVPacket av_packet;
	while (true)
	{
		GxxGmPlayBase::DebugStringOutput("准备读取媒体帧...\n");

		// 这里使用了一个非常低劣的手段来实现暂停
		while (true)
		{
			if (http_->is_paused_)
			{
				if (http_->need_stop_)
					break;

				Sleep(1);
				continue;
			}
			else
				break;
		}

		if (http_->need_stop_)
			break;

		// 这里需要有一个事件，或者锁来进行暂停/恢复的同步处理
		int errCode = av_read_frame((AVFormatContext*)http_->format_ctx_, &av_packet);
		if (errCode != 0)
			break;

		StruGSMediaFrameData media_frame;
		media_frame.PresentationTimestamp = av_packet.pts;

		AVFrame *av_frame = av_frame_alloc();
		if (av_packet.stream_index == http_->video_stream_index_)
		{
			WaitForSingleObject(http_->framerate_event_handle_, INFINITE);

#ifdef USE_H264BSF
			av_bitstream_filter_filter(h264_bit_stream_filter_context, (AVCodecContext*)http_->video_codec_ctx_, NULL, &av_packet.data, &av_packet.size, av_packet.data, av_packet.size, 0);
#endif

#ifdef _USE_FFMPEG_
			int got_pic = 0;
			errCode = avcodec_decode_video2((AVCodecContext*)http_->video_codec_ctx_, av_frame, &got_pic, &av_packet);
			if (errCode != 0)
				GxxGmPlayBase::DebugStringOutput("解码视频帧失败！错误码：%d...\n", errCode);
			
			if (got_pic)
			{
				GxxGmPlayBase::DebugStringOutput("将视频帧塞入播放器...\n");
				http_->notifer_->MediaFrameNotiferEx(AVMediaType::AVMEDIA_TYPE_VIDEO, av_frame);
				GxxGmPlayBase::DebugStringOutput("将视频帧塞入播放器完成...\n");
			}
#else
			// 这是视频帧
			media_frame.MediaType = EnumGSMediaType::GS_MEDIA_TYPE_VIDEO;
			media_frame.CodecType = (EnumGSCodeID)http_->eVideoCode_;
			media_frame.VideoFrameInfo.Width = ((AVStream*)http_->video_stream_)->codecpar->width;
			media_frame.VideoFrameInfo.Height = ((AVStream*)http_->video_stream_)->codecpar->height;
			media_frame.VideoFrameInfo.IsKeyFrame = av_packet.flags & AV_PKT_FLAG_KEY;
			media_frame.VideoFrameInfo.FrameLength[0] = av_packet.size;
			media_frame.VideoFrameInfo.FrameBuffer[0] = (char*)av_packet.data;
#endif
		}
		else if (av_packet.stream_index == http_->audio_stream_index_)
		{
#ifdef _USE_FFMPEG_
			int got_data = 0;
			avcodec_decode_audio4((AVCodecContext*)http_->audio_codec_ctx_, av_frame, &got_data, &av_packet);
			if (got_data)
			{
				http_->notifer_->MediaFrameNotiferEx(AVMediaType::AVMEDIA_TYPE_AUDIO, av_frame);
			}
#else
			// 这是音频帧
			media_frame.MediaType = EnumGSMediaType::GS_MEDIA_TYPE_AUDIO;
			media_frame.CodecType = (EnumGSCodeID)http_->eAudioCode_;
			media_frame.AudioFrameInfo.SampleRate = http_->unSampleRate_;
			media_frame.AudioFrameInfo.Bits = http_->unBits_;
			media_frame.AudioFrameInfo.Channels = http_->unChannels_;
#endif
		}

#ifdef _USE_GXX_
		http_->notifer_->MediaFrameNotifer(&media_frame);
#endif

		av_free_packet(&av_packet);
		++index;
	}

	http_->need_stop_ = false;
#ifdef USE_H264BSF
	av_bitstream_filter_close(h264_bit_stream_filter_context);
#endif
	avcodec_close(((AVCodecContext*)http_->video_codec_ctx_));
	avcodec_close(((AVCodecContext*)http_->audio_codec_ctx_));
	avformat_close_input(((AVFormatContext **)&http_->format_ctx_));
	http_->video_codec_ctx_ = NULL;
	http_->audio_codec_ctx_ = NULL;
	http_->format_ctx_ = NULL;
	GxxGmPlayBase::DebugStringOutput("准备退出媒体帧读取线程...\n");
	return 0;
}

DWORD WINAPI GxxGmHttpImp::ControlThread(LPVOID lpParam)
{
	GxxGmHttpImp *http_ = (GxxGmHttpImp *)lpParam;

	// 计算一下平均帧率下需要Delay的时间
	int delay_time = 1000 / http_->nRefFrameRate_;
	while (true)
	{
		if (http_->need_stop_)
			break;

		SYSTEMTIME st;
		GetLocalTime(&st);
		GxxGmPlayBase::DebugStringOutput("%02d%02d%02d-%03d:过一帧...\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		SetEvent(http_->framerate_event_handle_);
		Sleep(delay_time);		// 这里由帧率来控制
	}

	return 0;
}