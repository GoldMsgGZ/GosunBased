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

GxxGmHttpImp::GxxGmHttpImp(GxxGmPlaySDKNotifer *notifer)
: notifer_(notifer)
, is_paused_(false)
, read_stream_thread_handle_(NULL)
, format_ctx_(NULL)
, video_stream_index_(-1)
, audio_stream_index_(-1)
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
	// ���︺��⸴�ã��ص����ϲ�����Ƶ���Ļ�������
	int errCode = avformat_open_input((AVFormatContext **)&format_ctx_, url, NULL, NULL);
	if (errCode != 0)
	{
		GxxGmPlayBase::DebugStringOutput("��Ŀ��ý�壺\"%s\"ʧ�ܣ������룺%d\n", url, errCode);
		return errCode;
	}

	avformat_find_stream_info((AVFormatContext*)format_ctx_, NULL);

	int stream_count = ((AVFormatContext*)format_ctx_)->nb_streams;
	for (int index = 0; index < stream_count; ++index)
	{
		AVStream *st = ((AVFormatContext*)format_ctx_)->streams[index];
		if (st->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			video_stream_index_ = index;
			video_codec_ctx_ = (void*)st->codec;

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
		}
		else if (st->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audio_stream_index_ = index;
			audio_codec_ctx_ = (void*)st->codec;

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
		}
	}

	notifer_->StreamParamNotiferEx((AVCodecContext*)video_codec_ctx_, (AVCodecContext*)audio_codec_ctx_);
	// notifer_->StreamParamNotifer(eVideoCode, eAudioCode, unSampleRate, unBits, unChannels, nRefFrameRate, nEnableTimeCaculate);

	return 0;
}

int GxxGmHttpImp::Play()
{
	// �����̣߳����������������������ݴ����ϲ�
	DWORD thread_exit_code = 0;
	GetExitCodeThread(read_stream_thread_handle_, &thread_exit_code);
	if (thread_exit_code == STILL_ACTIVE)
	{
		// �߳��������У���ô����ͣ��־λ����Ϊ�ر�
		// ������ϵͳ�¼����ܻ����
		GxxGmPlayBase::DebugStringOutput("����ȡ�߳��������У�����ͣ��ǹرգ�\n");
		is_paused_ = false;
	}
	else
	{
		// �������̣߳���ô���Ǿ��½�һ���߳��������������
		GxxGmPlayBase::DebugStringOutput("δ��⵽����ȡ�̣߳������̣߳�\n");
		read_stream_thread_handle_ = CreateThread(NULL, 0, ReadStreamThread, this, 0, NULL);
	}

	return 0;
}

int GxxGmHttpImp::Pause()
{
	// ��ͣ��ȡ�����
	GxxGmPlayBase::DebugStringOutput("����ȡ�߳��������У�����ͣ��ǿ�����\n");
	is_paused_ = true;
	return 0;
}

int GxxGmHttpImp::Stop()
{
	// ֹͣ��ȡ���ݰ���֪ͨ�˳��߳�
	return 0;
}

void GxxGmHttpImp::Close()
{

}

DWORD WINAPI GxxGmHttpImp::ReadStreamThread(LPVOID lpParam)
{
	GxxGmHttpImp *http_ = (GxxGmHttpImp *)lpParam;

	// ���￪ʼ��֯
	AVPacket av_packet;
	while (true)
	{
		GxxGmPlayBase::DebugStringOutput("׼����ȡý��֡...\n");

		// ����ʹ����һ���ǳ����ӵ��ֶ���ʵ����ͣ
		while (true)
		{
			if (http_->is_paused_)
			{
				Sleep(1);
				continue;
			}
			else
				break;
		}

		// ������Ҫ��һ���¼�����������������ͣ/�ָ���ͬ������
		int errCode = av_read_frame((AVFormatContext*)http_->format_ctx_, &av_packet);
		if (errCode != 0)
			break;

		//StruGSMediaFrameData media_frame;
		//media_frame.PresentationTimestamp = 0;//av_packet.pts;

		AVFrame *av_frame = av_frame_alloc();
		if (av_packet.stream_index == http_->video_stream_index_)
		{
#ifdef USE_FFMPEG
			int got_pic = 0;
			avcodec_decode_video2((AVCodecContext*)http_->video_codec_ctx_, av_frame, &got_pic, &av_packet);
			if (got_pic)
			{
				GxxGmPlayBase::DebugStringOutput("����Ƶ֡���벥����...\n");
				http_->notifer_->MediaFrameNotiferEx(AVMediaType::AVMEDIA_TYPE_VIDEO, av_frame);
				GxxGmPlayBase::DebugStringOutput("����Ƶ֡���벥�������...\n");
			}
#else
			//// ������Ƶ֡
			//media_frame.MediaType = EnumGSMediaType::GS_MEDIA_TYPE_VIDEO;
			//media_frame.CodecType = (EnumGSCodeID)http_->video_codec_id_;
			//media_frame.VideoFrameInfo.Width = 0;
			//media_frame.VideoFrameInfo.Height = 0;
			//media_frame.VideoFrameInfo.IsKeyFrame = true;
			//media_frame.VideoFrameInfo.FrameLength[0] = av_packet.size;
			//media_frame.VideoFrameInfo.FrameBuffer[0] = (char*)av_packet.data;
#endif
		}
		else if (av_packet.stream_index == http_->audio_stream_index_)
		{
#ifdef USE_FFMPEG
			int got_data = 0;
			avcodec_decode_audio4((AVCodecContext*)http_->audio_codec_ctx_, av_frame, &got_data, &av_packet);
			if (got_data)
			{
				http_->notifer_->MediaFrameNotiferEx(AVMediaType::AVMEDIA_TYPE_AUDIO, av_frame);
			}
#else
			//// ������Ƶ֡
			//media_frame.MediaType = EnumGSMediaType::GS_MEDIA_TYPE_AUDIO;
			//media_frame.CodecType = (EnumGSCodeID)http_->audio_codec_id_;
			//media_frame.AudioFrameInfo.SampleRate = http_->audio_sample_rate_;
			//media_frame.AudioFrameInfo.Bits = http_->audio_bits_;
			//media_frame.AudioFrameInfo.Channels = http_->audio_channels_;
#endif
		}

		av_free_packet(&av_packet);
	}

	GxxGmPlayBase::DebugStringOutput("׼���˳�ý��֡��ȡ�߳�...\n");
	return 0;
}