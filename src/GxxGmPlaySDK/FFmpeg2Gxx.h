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

EnumGSCodeID FFmpegCodecId2GxxCodecId(AVCodecID codecid);
AVCodecID GxxCodecId2FFmpegCodecId(EnumGSCodeID codecid);

#endif//_FFmpeg2Gxx_H_
