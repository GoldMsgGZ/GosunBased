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

	// ���︺��⸴�ã��ص����ϲ�����Ƶ���Ļ�������
	if (format_ctx_ == NULL)
	{
		errCode = avformat_open_input((AVFormatContext **)&format_ctx_, url, NULL, NULL);
		if (errCode != 0)
		{
			GxxGmPlayBase::DebugStringOutput("��Ŀ��ý�壺\"%s\"ʧ�ܣ������룺%d\n", url, errCode);
			return errCode;
		}
		GxxGmPlayBase::DebugStringOutput("��Ŀ��ý�壺\"%s\"�ɹ��������룺%d\n", url, errCode);

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
					// û���ҵ���Ӧ����Ƶ������
					GxxGmPlayBase::DebugStringOutput("û���ҵ���Ӧ����Ƶ�����������������ƣ�%s\n", avcodec_get_name(((AVCodecContext*)video_codec_ctx_)->codec_id));
					break;
				}

				errCode = avcodec_open2((AVCodecContext*)video_codec_ctx_, (const AVCodec *)video_codec_, NULL);
				if (errCode != 0)
				{
					// ����Ƶ������ʧ��
					GxxGmPlayBase::DebugStringOutput("����Ƶ��������%s ʧ�ܣ������룺%d\n", avcodec_get_name(((AVCodecContext*)video_codec_ctx_)->codec_id), errCode);
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
					// û���ҵ���Ӧ����Ƶ������
					GxxGmPlayBase::DebugStringOutput("û���ҵ���Ӧ����Ƶ�����������������ƣ�%s\n", avcodec_get_name(((AVCodecContext*)audio_codec_ctx_)->codec_id));
					break;
				}

				errCode = avcodec_open2((AVCodecContext*)audio_codec_ctx_, (const AVCodec *)audio_codec_, NULL);
				if (errCode != 0)
				{
					// ����Ƶ������ʧ��
					GxxGmPlayBase::DebugStringOutput("����Ƶ��������%s ʧ�ܣ������룺%d\n", avcodec_get_name(((AVCodecContext*)audio_codec_ctx_)->codec_id), errCode);
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
			GxxGmPlayBase::DebugStringOutput("������Ƶ����ȡ�߳�ʧ�ܣ�...\n");
			Stop();
			return -1;
		}
	}

	return 0;
}

int GxxGmHttpImp::Pause()
{
	// ��ͣ��ȡ�����
	GxxGmPlayBase::DebugStringOutput("����ȡ�߳��������У�����ͣ��ǿ�����\n");
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
	// ֹͣ��ȡ���ݰ���֪ͨ�˳��߳�
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

	GxxGmPlayBase::DebugStringOutput("������ý������߳�...\n");

#ifdef USE_H264BSF
	AVBitStreamFilterContext *h264_bit_stream_filter_context = av_bitstream_filter_init("h264_mp4toannexb");
#endif

	// ���￪ʼ��֯
	int index = 0;
	AVPacket av_packet;
	enum GxxGmPlayState play_state;
	while (true)
	{
		if (thread.TestExit())
		{
			GxxGmPlayBase::DebugStringOutput("�յ��˳�ý������߳�֪ͨ...\n");
			play_state = GxxGmPlayState::GxxGmStateClientClosed;
			break;
		}

		GxxGmPlayBase::DebugStringOutput("׼����ȡý��֡...\n");

		// �ڴ��߳���Ӧ�ò�����Ӧ�߳���ͣ���߼�

		// ������Ҫ��һ���¼�����������������ͣ/�ָ���ͬ������
		int errCode = av_read_frame((AVFormatContext*)http_->format_ctx_, &av_packet);
		if (errCode != 0)
		{
			// �������˻���������ȡ�����
			play_state = GxxGmPlayState::GxxGmStatePlayEnd;
			break;
		}

		StruGSMediaFrameData media_frame;
		media_frame.PresentationTimestamp = av_packet.pts;

		AVFrame *av_frame = av_frame_alloc();
		if (av_packet.stream_index == http_->video_stream_index_)
		{
			// ��������֡�ʿ��Ƶ�
			//WaitForSingleObject(http_->framerate_event_handle_, INFINITE);

#ifdef USE_H264BSF
			if (http_->eVideoCode_ == GS_CODEID_ST_H264)
			{
				// ������Ҫ�жϣ������H264���룬���Ǿ���Ҫ�ù��������й���
				av_bitstream_filter_filter(h264_bit_stream_filter_context, (AVCodecContext*)http_->video_codec_ctx_, NULL, &av_packet.data, &av_packet.size, av_packet.data, av_packet.size, 0);
			}
#endif

#ifdef _USE_FFMPEG_
			int got_pic = 0;
			errCode = avcodec_decode_video2((AVCodecContext*)http_->video_codec_ctx_, av_frame, &got_pic, &av_packet);
			if (errCode != 0)
				GxxGmPlayBase::DebugStringOutput("������Ƶ֡ʧ�ܣ������룺%d...\n", errCode);

			if (got_pic)
			{
				GxxGmPlayBase::DebugStringOutput("����Ƶ֡���벥����...\n");
				http_->notifer_->MediaFrameNotiferEx(AVMediaType::AVMEDIA_TYPE_VIDEO, av_frame);
				GxxGmPlayBase::DebugStringOutput("����Ƶ֡���벥�������...\n");
			}
#else
			// ������Ƶ֡
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
				// ������Ҫ����adtsͷ��
			}

			// ������Ƶ֡
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

	// �ϱ�����״̬
	// ����Ҳ���ϱ��ˣ���Ϊ
	//http_->notifer_->PlayerStateNotifer(play_state);

	GxxGmPlayBase::DebugStringOutput("׼���˳�ý��֡��ȡ�߳�...\n");
}

void GS_CALLBACK GxxGmHttpImp::_ControlThreadCallback(GSThread &thread, void *pThreadData)
{
	GxxGmHttpImp *http_ = (GxxGmHttpImp *)pThreadData;

	// ����һ��ƽ��֡������ҪDelay��ʱ��
	int delay_time = 1000 / http_->nRefFrameRate_;
	while (true)
	{
		if (thread.TestExit())
			break;

		SYSTEMTIME st;
		GetLocalTime(&st);
		GxxGmPlayBase::DebugStringOutput("%02d%02d%02d-%03d:��һ֡...\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		SetEvent(http_->framerate_event_handle_);
		Sleep(delay_time);		// ������֡��������
	}
}