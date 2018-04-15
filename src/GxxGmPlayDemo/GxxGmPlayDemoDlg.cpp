
// GxxGmPlayDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GxxGmPlayDemo.h"
#include "GxxGmPlayDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGxxGmPlayDemoDlg 对话框




CGxxGmPlayDemoDlg::CGxxGmPlayDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGxxGmPlayDemoDlg::IDD, pParent)
	, input_fmtctx_(NULL)
	, audio_len_(0)
	, audio_pos_(NULL)
	, audio_chunk_(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGxxGmPlayDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_URL, m_cUrl);
}

BEGIN_MESSAGE_MAP(CGxxGmPlayDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_OPEN, &CGxxGmPlayDemoDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_PLAY, &CGxxGmPlayDemoDlg::OnBnClickedBtnPlay)
END_MESSAGE_MAP()


// CGxxGmPlayDemoDlg 消息处理程序

BOOL CGxxGmPlayDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_cUrl.SetWindowText(_T("http://127.0.0.1/live/t.mp4"));

	av_register_all();
	avformat_network_init();
	avcodec_register_all();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGxxGmPlayDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGxxGmPlayDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGxxGmPlayDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGxxGmPlayDemoDlg::OnBnClickedBtnOpen()
{
	CString url;
	m_cUrl.GetWindowText(url);

	USES_CONVERSION;
	int errCode = avformat_open_input(&input_fmtctx_, T2A(url.GetBuffer(0)), NULL, NULL);
	if (errCode != 0)
	{
		TRACE("打开媒体失败！错误码：%d\n", errCode);
		return ;
	}

	avformat_find_stream_info(input_fmtctx_, NULL);

	for (int index = 0; index < input_fmtctx_->nb_streams; ++index)
	{
		if (input_fmtctx_->streams[index]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			video_index_ = index;
			video_stream_ = input_fmtctx_->streams[index];
			video_codec_ctx_ = video_stream_->codec;
			video_codec_ = avcodec_find_decoder(video_codec_ctx_->codec_id);
			if (video_codec_ == NULL)
			{
				TRACE("未找到视频解码器\n");
				break;
			}

			errCode = avcodec_open2(video_codec_ctx_, video_codec_, NULL);
			if (errCode != 0)
			{
				TRACE("打开视频解码器失败，错误码：%d\n", errCode);
				break;
			}
		}
		else if (input_fmtctx_->streams[index]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audio_index_ = index;
			audio_stream_ = input_fmtctx_->streams[index];
			audio_codec_ctx_ = audio_stream_->codec;
			audio_codec_ = avcodec_find_decoder(audio_codec_ctx_->codec_id);
			if (audio_codec_ == NULL)
			{
				TRACE("未找到音频解码器\n");
				break;
			}

			errCode = avcodec_open2(audio_codec_ctx_, audio_codec_, NULL);
			if (errCode != 0)
			{
				TRACE("打开音频解码器失败，错误码：%d\n", errCode);
				break;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// 计算帧率
	unsigned int time_scale = avio_rb32(input_fmtctx_->pb);
	//framerate_ = av_reduce(&video_stream_->avg_frame_rate.num, &video_stream_->avg_frame_rate.den, time_scale * time_scale, time_scale, INT_MAX);
	framerate_ = video_stream_->avg_frame_rate.num / video_stream_->avg_frame_rate.den;
	

	//////////////////////////////////////////////////////////////////////////
	// 开始准备图像转换相关参数
	yuv_frame_ = av_frame_alloc();

	// 根据视频长宽和图像颜色格式，计算出帧缓冲器大小，1字节对齐
	int yuv_frame_buf_size = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, video_codec_ctx_->width, video_codec_ctx_->height, 1);

	// 申请帧缓冲区
	unsigned char *yuv_frame_buf = (unsigned char *)av_malloc(yuv_frame_buf_size);

	// 填充帧，一字节对齐
	av_image_fill_arrays(yuv_frame_->data, yuv_frame_->linesize, yuv_frame_buf, AV_PIX_FMT_YUV420P, video_codec_ctx_->width, video_codec_ctx_->height, 1);

	// 获取转换上下文
	img_convert_ctx_ = sws_getContext(video_codec_ctx_->width, video_codec_ctx_->height, video_codec_ctx_->pix_fmt, video_codec_ctx_->width, video_codec_ctx_->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

	if (errCode != 0)
		return;

	//////////////////////////////////////////////////////////////////////////
	// 开始准备声音转换相关参数
#define MAX_AUDIO_FRAME_SIZE 192000

	uint64_t output_channel_layout = AV_CH_LAYOUT_STEREO;
	int output_frame_size = audio_codec_ctx_->frame_size;	// AAC是1024；MP3是1152；
	AVSampleFormat output_sample_format = AV_SAMPLE_FMT_S16;
	int output_sample_rate = audio_codec_ctx_->sample_rate;	// 44100
	int output_channels = av_get_channel_layout_nb_channels(output_channel_layout);
	audio_output_buffer_size_ = av_samples_get_buffer_size(NULL, output_channels, output_frame_size, output_sample_format, 1);

	audio_output_buffer_ = (unsigned char *)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);

	// 
	int input_channel_layout = av_get_default_channel_layout(audio_codec_ctx_->channels);

	// 
	audio_convert_context_ = swr_alloc();
	audio_convert_context_ = swr_alloc_set_opts(audio_convert_context_, output_channel_layout, output_sample_format, output_sample_rate,
		input_channel_layout, audio_codec_ctx_->sample_fmt, audio_codec_ctx_->sample_rate, 0, NULL);
	swr_init(audio_convert_context_);

	audio_spec_.freq = output_sample_rate;
	audio_spec_.format = AUDIO_S16SYS;
	audio_spec_.channels = output_channels;
	audio_spec_.silence = 0;
	audio_spec_.samples = output_frame_size;
	audio_spec_.callback = AudioFillCallback;
	audio_spec_.userdata = this;

	//////////////////////////////////////////////////////////////////////////
	// 初始化SDL渲染器
	errCode = SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (errCode != 0)
	{
		TRACE("初始化渲染器失败！错误码：%d\n", errCode);
		return ;
	}

	CWnd *p = GetDlgItem(IDC_STATIC_SCREEN);
	screen_ = p->GetSafeHwnd();
	sdl_window_ = SDL_CreateWindowFrom((void *)screen_);
	if (sdl_window_ == NULL)
	{
		TRACE("创建渲染窗口失败！");
		return ;
	}

	sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, 0);
	if (sdl_renderer_ == NULL)
	{
		TRACE("创建渲染器失败！");
		return ;
	}

	sdl_texture_ = SDL_CreateTexture(sdl_renderer_, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, video_codec_ctx_->width, video_codec_ctx_->height);
	if (sdl_texture_ == NULL)
	{
		TRACE("创建渲染纹理失败！");
		return ;
	}
}

void CGxxGmPlayDemoDlg::OnBnClickedBtnPlay()
{
	// 检查播放线程是否存在
	DWORD exit_code = 0;
	GetExitCodeThread(read_handle_, &exit_code);
	if (exit_code == STILL_ACTIVE)
	{
		// 检查当前标记，如果是暂停状态，则关闭其状态
	}
	else
	{
		framerate_event_handle_ = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (framerate_event_handle_ == NULL)
		{
			int errCode = GetLastError();
			TRACE("创建帧率控制事件失败！错误码：%d\n", errCode);
			return ;
		}

		control_handle_ = CreateThread(NULL, 0, ControlThread, this, 0, NULL);
		if (control_handle_ == NULL)
		{
			int errCode = GetLastError();
			TRACE("播放失败！启动解码控制线程失败！错误码：%d\n", errCode);
			return ;
		}

		Sleep(500);
		read_handle_ = CreateThread(NULL, 0, ReadThread, this, 0, NULL);
		if (read_handle_ == NULL)
		{
			int errCode = GetLastError();
			TRACE("播放失败！启动解码线程失败！错误码：%d\n", errCode);
			return ;
		}

		Sleep(500);
		int errCode = SDL_OpenAudio(&audio_spec_, NULL);
		if (errCode < 0)
		{
			TRACE("打开音频通道失败！");
			return ;
		}

		// 这里打开声音，如果初始化要关闭声音的话，参数改为“1”
		SDL_PauseAudio(0);
	}
}


DWORD WINAPI CGxxGmPlayDemoDlg::ReadThread(LPVOID lpParam)
{
	CGxxGmPlayDemoDlg *dlg = (CGxxGmPlayDemoDlg *)lpParam;

	while (true)
	{
		AVPacket av_packet;
		int errCode = av_read_frame(dlg->input_fmtctx_, &av_packet);
		if (errCode < 0)
			break;

		AVFrame *av_frame = av_frame_alloc();
		if (av_packet.stream_index == dlg->video_index_)
		{
			// 首先这里应当有一个事件，用于进行帧率控制
			WaitForSingleObject(dlg->framerate_event_handle_, INFINITE);

			// 开始解码
			int got_pic = 0;
			int errCode = avcodec_decode_video2(dlg->video_codec_ctx_, av_frame, &got_pic, &av_packet);
			if (errCode < 0)
			{
				TRACE("解码视频编码帧失败！错误码：%d\n", errCode);
				av_frame_free(&av_frame);
				av_free_packet(&av_packet);
				continue;
			}

			if (!got_pic)
			{
				av_frame_free(&av_frame);
				av_free_packet(&av_packet);
				continue;
			}

			// 图像转换
			sws_scale(dlg->img_convert_ctx_, (const unsigned char * const*)av_frame->data, av_frame->linesize, 0, dlg->video_codec_ctx_->height, dlg->yuv_frame_->data, dlg->yuv_frame_->linesize);

			// 渲染更新
			RECT rt;
			::GetWindowRect(dlg->screen_, &rt);

			SDL_Rect rect;
			rect.x = 0;
			rect.y = 0;
			rect.w = rt.right - rt.left;
			rect.h = rt.bottom - rt.top;

			SDL_UpdateTexture(dlg->sdl_texture_, NULL, dlg->yuv_frame_->data[0], dlg->yuv_frame_->linesize[0]);
			SDL_RenderCopy(dlg->sdl_renderer_, dlg->sdl_texture_, NULL, &rect);
			SDL_RenderPresent(dlg->sdl_renderer_);
		}
		else if (av_packet.stream_index == dlg->audio_index_)
		{
			// 解码音频编码帧
			int got_audio = 0;
			errCode = avcodec_decode_audio4(dlg->audio_codec_ctx_, av_frame, &got_audio, &av_packet);
			if (errCode < 0)
			{
				TRACE("解码音频编码帧失败！错误码：%d\n", errCode);
				av_frame_free(&av_frame);
				av_free_packet(&av_packet);
				continue;
			}

			if (!got_audio)
			{
				av_frame_free(&av_frame);
				av_free_packet(&av_packet);
				continue;
			}

			// 声音转换
			swr_convert(dlg->audio_convert_context_, &dlg->audio_output_buffer_, MAX_AUDIO_FRAME_SIZE, (const unsigned char **)av_frame->data, av_frame->nb_samples);

			while (dlg->audio_len_ > 0)
				SDL_Delay(1);

			dlg->audio_chunk_ = (unsigned char *)dlg->audio_output_buffer_;
			dlg->audio_len_ = dlg->audio_output_buffer_size_;
			dlg->audio_pos_ = dlg->audio_chunk_;
		}

		av_frame_free(&av_frame);
		av_free_packet(&av_packet);
	}

	// 线程即将退出，这里清理相关资源

	return 0;
}

DWORD WINAPI CGxxGmPlayDemoDlg::ControlThread(LPVOID lpParam)
{
	CGxxGmPlayDemoDlg *dlg = (CGxxGmPlayDemoDlg *)lpParam;

	// 计算一下平均帧率下需要Delay的时间
	int delay_time = 1000 / dlg->framerate_;
	while (true)
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		TRACE("%02d%02d%02d-%03d:过一帧...\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		SetEvent(dlg->framerate_event_handle_);
		Sleep(delay_time);		// 这里由帧率来控制
	}
}

void CGxxGmPlayDemoDlg::AudioFillCallback(void *udata, Uint8 *stream, int len)
{
	CGxxGmPlayDemoDlg *dlg = (CGxxGmPlayDemoDlg*)udata;

	SDL_memset(stream, 0, len);

	if(dlg->audio_len_ <= 0)
		return;

	len = (len > dlg->audio_len_ ? dlg->audio_len_ : len);

	SDL_MixAudio(stream, dlg->audio_pos_, len, SDL_MIX_MAXVOLUME);
	dlg->audio_pos_ += len;
	dlg->audio_len_ -= len;
}