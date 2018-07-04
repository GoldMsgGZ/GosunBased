#ifndef _GxxGmStreamRecevicer_H_
#define _GxxGmStreamRecevicer_H_

class GxxGmGSPHandler;

/**
 * �����˹��������������
 */
struct GxxGmAVCodecContext
{
	// ����ID
	enum AVCodecID codec_id;

	// ý������
	enum AVMediaType codec_type;
};

/**
 * �����˹�������Ƶ��
 */
struct GxxGmAVStream
{
	GxxGmAVCodecContext *codec; 
};

/**
 * �����˹������ø�ʽ������
 */
struct GxxGmAVFormatContext
{
	int nb_streams;
	GxxGmAVStream *streams;
};

union GxxGmRecevicerInstance
{
	GxxGmGSPHandler *gsp_handler_;
};

class GxxGmStreamRecevicerObserver
{
public:
	/**
	 * ��Ƶ��������Ϣ�ص�
	 * ������
	 *	@fmtctx		���ø�ʽ������
	 */
	virtual int DemuxingInfo(GxxGmAVFormatContext *fmtctx) = 0;
	virtual int VideoPacket(AVPacket *pkt) = 0;
	virtual int AudioPacket(AVPacket *pkt) = 0;
};

/**
 * �����˹�����������
 * ���ڴ򿪳�����Ƶ����Э��֧�ְ���������������Э�飺
 * GSP
 * RTSP
 * 
 * ģ�鷴����������Ƶ��Ϣ����������Ȼ�����Ϣ
 * ���ݲ��������Ӧ��ES��
 */
class GxxGmStreamRecevicer
{
public:
	/**
	 *
	 */
	GxxGmStreamRecevicer(GxxGmStreamRecevicerObserver *observer);
	~GxxGmStreamRecevicer();

public:
	/**
	 * ��URL�����ݲ�ͬ��Э���URL
	 * �⸴����Ϣ��ص����۲��߶�Ӧ�Ļص��ӿ�
	 */
	int OpenURL(const char *url);
	void Close();

	/**
	 * ��ʼ���ţ���ʼ��۲������ͱ����
	 */
	int Play();

	/**
	 * ֹͣ���ţ�ֹͣ��۲������ͱ����
	 */
	void Stop();

public:
	GxxGmStreamRecevicerObserver* GetObserver() { return observer_; }
	bool IsOutput() { return is_output_; }
	

public:
	GxxGmAVStream *audio_stream_;
	GxxGmAVStream *video_stream_;

private:
	GxxGmStreamRecevicerObserver *observer_;
	bool is_output_;

private:
	union GxxGmRecevicerInstance *instance_;
};

#endif//_GxxGmStreamRecevicer_H_
