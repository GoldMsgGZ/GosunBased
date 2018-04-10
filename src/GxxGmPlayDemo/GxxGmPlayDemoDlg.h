
// GxxGmPlayDemoDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#include "SDL.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libavutil/avutil.h"
#include "libavutil/imgutils.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
#ifdef __cplusplus
	};
#endif

// CGxxGmPlayDemoDlg 对话框
class CGxxGmPlayDemoDlg : public CDialog
{
// 构造
public:
	CGxxGmPlayDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GXXGMPLAYDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_cUrl;

public:
	// 输入媒体对象
	AVFormatContext *input_fmtctx_;

	// 视频流相关参数
	int video_index_;
	AVStream *video_stream_;
	AVCodecContext *video_codec_ctx_;
	AVCodec *video_codec_;
	int framerate_;	// 帧率，用于控制视频播放

	// 音频流相关参数
	int audio_index_;
	AVStream *audio_stream_;
	AVCodecContext *audio_codec_ctx_;
	AVCodec *audio_codec_;

public:
	// 视频相关转换参数
	AVFrame *yuv_frame_;
	struct SwsContext *img_convert_ctx_;

	// 音频相关转换参数
	int audio_output_buffer_size_;
	unsigned char *audio_output_buffer_;
	struct SwrContext *audio_convert_context_;

public:
	SDL_Window *sdl_window_;
	SDL_Renderer *sdl_renderer_;
	SDL_Texture *sdl_texture_;
	HWND screen_;

	SDL_AudioSpec audio_spec_;

public:
	static DWORD WINAPI ReadThread(LPVOID lpParam);
	HANDLE read_handle_;
	HANDLE framerate_event_handle_;

	static DWORD WINAPI ControlThread(LPVOID lpParam);
	HANDLE control_handle_;

	static void __cdecl AudioFillCallback(void *udata, Uint8 *stream, int len);
	int audio_len_;
	unsigned char *audio_pos_;
	unsigned char *audio_chunk_;

public:
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnPlay();
};
