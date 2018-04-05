#include "FFmpeg2Gxx.h"

EnumGSCodeID FFmpegCodecId2GxxCodecId(enum AVCodecID codecid)
{
	EnumGSCodeID gxx_codec_id = EnumGSCodeID::GS_CODEID_NONE;

	switch (codecid)
	{
	case AV_CODEC_ID_MPEG1VIDEO:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_ST_MPEG1;
		break;
	case AV_CODEC_ID_MPEG2TS:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_ST_MPEG2;
		break;
	case AV_CODEC_ID_MSMPEG4V1:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_MS_MPEG4;
		break;
	case AV_CODEC_ID_H263:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_ST_H263;
		break;
	case AV_CODEC_ID_H264:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_ST_H264;
		break;
	case AV_CODEC_ID_H265:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_ST_H265;
		break;
	case AV_CODEC_ID_MJPEG:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_ST_MJPG;
		break;
	case AV_CODEC_ID_FLV1:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_ST_FLV1;
		break;
	case AV_CODEC_ID_WMV1:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_ST_WMV1;
		break;
	case AV_CODEC_ID_WMV2:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_ST_WMV2;
		break;
	case AV_CODEC_ID_WMV3:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_ST_WMV3;
		break;
	case AV_CODEC_ID_MP3:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_ST_MP3;
		break;
	case AV_CODEC_ID_PCM_ALAW:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_AUDIO_ST_G711A;
		break;
	case AV_CODEC_ID_PCM_MULAW:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_AUDIO_ST_G711U;
		break;
	case AV_CODEC_ID_G723_1:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_AUDIO_ST_G723;
		break;
	case AV_CODEC_ID_ADPCM_G722:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_AUDIO_ST_G722;
		break;
	case AV_CODEC_ID_G729:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_AUDIO_ST_G729;
		break;
	case AV_CODEC_ID_AAC:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_AUDIO_ST_AAC;
		break;
	case AV_CODEC_ID_AMR_NB:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_AUDIO_ST_AMR;
		break;
	case AV_CODEC_ID_WMAV1:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_AUDIO_ST_WMA1;
		break;
	case AV_CODEC_ID_WMAV2:
		gxx_codec_id = EnumGSCodeID::GS_CODEID_AUDIO_ST_WMA2;
		break;
	default:
		break;
	}

	return gxx_codec_id;
}