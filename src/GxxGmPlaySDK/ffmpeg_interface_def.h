#ifndef _ffmpeg_avformat_interface_def_H_
#define _ffmpeg_avformat_interface_def_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "libavformat\avformat.h"
#ifdef __cplusplus
};
#endif

//////////////////////////////////////////////////////////////////////////
//
// avformat.h

typedef void (__cdecl *_av_register_all)(void);
typedef int (__cdecl *_avformat_network_init)(void);
typedef int (__cdecl *_avformat_network_deinit)(void);

typedef int (__cdecl *_avformat_open_input)(AVFormatContext **ps, const char *url, AVInputFormat *fmt, AVDictionary **options);
typedef void (__cdecl *_avformat_close_input)(AVFormatContext **s);

typedef int (__cdecl *_avformat_find_stream_info)(AVFormatContext *ic, AVDictionary **options);

typedef int (__cdecl *_av_seek_frame)(AVFormatContext *s, int stream_index, int64_t timestamp, int flags);
typedef int (__cdecl *_av_read_frame)(AVFormatContext *s, AVPacket *pkt);

//////////////////////////////////////////////////////////////////////////
//
// avcodec.h

typedef AVCodec* (__cdecl *_avcodec_find_decoder)(enum AVCodecID id);
typedef int (__cdecl *_avcodec_open2)(AVCodecContext *avctx, const AVCodec *codec, AVDictionary **options);
typedef int (__cdecl *_avcodec_close)(AVCodecContext *avctx);
typedef void (__cdecl *_av_free_packet)(AVPacket *pkt);

//////////////////////////////////////////////////////////////////////////
//
// avutil.h

#endif//_ffmpeg_avformat_interface_def_H_
