#ifndef _GxxGmStreamRecevicer_H_
#define _GxxGmStreamRecevicer_H_

class GxxGmGSPHandler;

/**
 * 高新兴国迈编解码上下文
 */
struct GxxGmAVCodecContext
{
	// 编码ID
	enum AVCodecID codec_id;

	// 媒体类型
	enum AVMediaType codec_type;
};

/**
 * 高新兴国迈视音频流
 */
struct GxxGmAVStream
{
	GxxGmAVCodecContext *codec; 
};

/**
 * 高新兴国迈复用格式上下文
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
	 * 视频流复用信息回调
	 * 参数：
	 *	@fmtctx		复用格式上下文
	 */
	virtual int DemuxingInfo(GxxGmAVFormatContext *fmtctx) = 0;
	virtual int VideoPacket(AVPacket *pkt) = 0;
	virtual int AudioPacket(AVPacket *pkt) = 0;
};

/**
 * 高新兴国迈流接收器
 * 用于打开常用视频流，协议支持包含但不限于以下协议：
 * GSP
 * RTSP
 * 
 * 模块反馈流的视音频信息，编解码器等基本信息
 * 根据参数输出对应的ES包
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
	 * 打开URL，根据不同的协议打开URL
	 * 解复用信息会回调给观察者对应的回调接口
	 */
	int OpenURL(const char *url);
	void Close();

	/**
	 * 开始播放，开始向观察者推送编码包
	 */
	int Play();

	/**
	 * 停止播放，停止向观察者推送编码包
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
