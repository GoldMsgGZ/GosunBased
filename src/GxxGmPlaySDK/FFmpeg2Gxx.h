#ifndef _FFmpeg2Gxx_H_
#define _FFmpeg2Gxx_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "libavformat\avformat.h"
#include "libavcodec\avcodec.h"
#include "libavutil\avutil.h"
#ifdef __cplusplus
};
#endif

#include "GSStreamCodeID.h"

enum EnumGSCodeID FFmpegCodecId2GxxCodecId(enum AVCodecID codecid);
enum AVCodecID GxxCodecId2FFmpegCodecId(enum EnumGSCodeID codecid);

#endif//_FFmpeg2Gxx_H_
