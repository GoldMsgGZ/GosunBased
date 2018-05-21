#include "GxxGmHttpImp.h"
#include "GSTypes.h"
#include "GSMediaPlayerDef.h"

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
, framerate_event_handle_(NULL)
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
				video_stream_ = (char*)st;
				video_codec_ctx_ = (char*)st->codec;

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
				audio_stream_ = (char*)st;
				audio_codec_ctx_ = (char*)st->codec;

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

	if (!read_stream_thread_.IsRunning())
	{
		bool bret = read_stream_thread_.Start(_ReadStreamThreadCallback, this);
		if (!bret)
		{
			GxxGmPlayBase::DebugStringOutput("启动视频流读取线程失败！...\n");
			Stop();
			return -1;
		}
	}

	return 0;
}

int GxxGmHttpImp::Pause()
{
	// 暂停读取编码包
	GxxGmPlayBase::DebugStringOutput("流读取线程正在运行，将暂停标记开启！\n");
	read_stream_thread_.Suspend();
	return 0;
}

int GxxGmHttpImp::Resume()
{
	read_stream_thread_.Resume();
	return 0;
}

int GxxGmHttpImp::Stop()
{
	// 停止读取数据包，通知退出线程
	read_stream_thread_.Stop();
	read_stream_thread_.Join();

	//control_thread_.Stop();
	//control_thread_.Join();

	CloseHandle(framerate_event_handle_);
	framerate_event_handle_ = NULL;

	avcodec_close(((AVCodecContext*)video_codec_ctx_));
	avcodec_close(((AVCodecContext*)audio_codec_ctx_));
	avformat_close_input(((AVFormatContext **)&format_ctx_));
	video_codec_ctx_ = NULL;
	audio_codec_ctx_ = NULL;
	format_ctx_ = NULL;

	return 0;
}

void GxxGmHttpImp::Close()
{

}



void GS_CALLBACK GxxGmHttpImp::_ReadStreamThreadCallback(GSThread &thread, void *pThreadData)
{
	GxxGmHttpImp *http_ = (GxxGmHttpImp *)pThreadData;

	GxxGmPlayBase::DebugStringOutput("已启动媒体解码线程...\n");

#ifdef USE_H264BSF
	AVBitStreamFilterContext *h264_bit_stream_filter_context = av_bitstream_filter_init("h264_mp4toannexb");
#endif

	// 这里开始组织
	int index = 0;
	AVPacket av_packet;
	enum GxxGmPlayState play_state;
	while (true)
	{
		if (thread.TestExit())
		{
			GxxGmPlayBase::DebugStringOutput("收到退出媒体解码线程通知...\n");
			play_state = GxxGmPlayState::GxxGmStateClientClosed;
			break;
		}

		GxxGmPlayBase::DebugStringOutput("准备读取媒体帧...\n");

		// 在此线程中应该不用响应线程暂停的逻辑

		// 这里需要有一个事件，或者锁来进行暂停/恢复的同步处理
		int errCode = av_read_frame((AVFormatContext*)http_->format_ctx_, &av_packet);
		if (errCode != 0)
		{
			// 到这里了基本是流读取完毕了
			play_state = GxxGmPlayState::GxxGmStatePlayEnd;
			break;
		}

		StruGSMediaFrameData media_frame;
		media_frame.PresentationTimestamp = av_packet.pts;

		AVFrame *av_frame = av_frame_alloc();
		if (av_packet.stream_index == http_->video_stream_index_)
		{
			// 这里是做帧率控制的
			//WaitForSingleObject(http_->framerate_event_handle_, INFINITE);

#ifdef USE_H264BSF
			if (http_->eVideoCode_ == GS_CODEID_ST_H264)
			{
				// 这里需要判断，如果是H264编码，我们就需要用过滤器进行过滤
				av_bitstream_filter_filter(h264_bit_stream_filter_context, (AVCodecContext*)http_->video_codec_ctx_, NULL, &av_packet.data, &av_packet.size, av_packet.data, av_packet.size, 0);
			}
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

			if (http_->eAudioCode_ == GS_CODEID_AUDIO_ST_AAC)
			{
				// 这里需要增加adts头部
			}

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

#ifdef USE_H264BSF
	if (http_->eVideoCode_ == GS_CODEID_ST_H264)
	{
		av_bitstream_filter_close(h264_bit_stream_filter_context);
	}
#endif

	// 上报播放状态
	// 这里也不上报了，因为
	//http_->notifer_->PlayerStateNotifer(play_state);

	GxxGmPlayBase::DebugStringOutput("准备退出媒体帧读取线程...\n");
}

void GS_CALLBACK GxxGmHttpImp::_ControlThreadCallback(GSThread &thread, void *pThreadData)
{
	GxxGmHttpImp *http_ = (GxxGmHttpImp *)pThreadData;

	// 计算一下平均帧率下需要Delay的时间
	int delay_time = 1000 / http_->nRefFrameRate_;
	while (true)
	{
		if (thread.TestExit())
			break;

		SYSTEMTIME st;
		GetLocalTime(&st);
		GxxGmPlayBase::DebugStringOutput("%02d%02d%02d-%03d:过一帧...\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		SetEvent(http_->framerate_event_handle_);
		Sleep(delay_time);		// 这里由帧率来控制
	}
}