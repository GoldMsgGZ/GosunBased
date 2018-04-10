
// GxxGmPlayDemoDlg.h : ͷ�ļ�
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

// CGxxGmPlayDemoDlg �Ի���
class CGxxGmPlayDemoDlg : public CDialog
{
// ����
public:
	CGxxGmPlayDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GXXGMPLAYDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_cUrl;

public:
	// ����ý�����
	AVFormatContext *input_fmtctx_;

	// ��Ƶ����ز���
	int video_index_;
	AVStream *video_stream_;
	AVCodecContext *video_codec_ctx_;
	AVCodec *video_codec_;
	int framerate_;	// ֡�ʣ����ڿ�����Ƶ����

	// ��Ƶ����ز���
	int audio_index_;
	AVStream *audio_stream_;
	AVCodecContext *audio_codec_ctx_;
	AVCodec *audio_codec_;

public:
	// ��Ƶ���ת������
	AVFrame *yuv_frame_;
	struct SwsContext *img_convert_ctx_;

	// ��Ƶ���ת������
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
