#include "FFmpeg2Gxx.h"

EnumGSCodeID FFmpegCodecId2GxxCodecId(AVCodecID codecid)
{
	EnumGSCodeID gxx_codec_id;
	if((AV_CODEC_ID_FIRST_AUDIO <= codecid)	&& (codecid < AV_CODEC_ID_ADPCM_IMA_QT))
	{
		gxx_codec_id = GS_CODEID_AUDIO_ST_PCM; 
		return gxx_codec_id;
	}

	switch(codecid)
	{
		//ÊÓÆµ
	case AV_CODEC_ID_H264:
		gxx_codec_id = GS_CODEID_ST_H264;
		break;
	case AV_CODEC_ID_MPEG4:
		gxx_codec_id = GS_CODEID_ST_MP4;
		break;
	case AV_CODEC_ID_H263:
	case AV_CODEC_ID_H263I:
	case AV_CODEC_ID_H263P:
		gxx_codec_id = GS_CODEID_ST_H263;
		break;
	case AV_CODEC_ID_MPEG2VIDEO:
		gxx_codec_id = GS_CODEID_ST_MPEG2;
		break;
	case AV_CODEC_ID_MPEG1VIDEO:
		gxx_codec_id = GS_CODEID_ST_MPEG1;
		break;
	case AV_CODEC_ID_MSMPEG4V1:
		gxx_codec_id = GS_CODEID_FCC_MPEG4;
		break;
	case AV_CODEC_ID_MSMPEG4V2:
	case AV_CODEC_ID_MSMPEG4V3:
		gxx_codec_id = GS_CODEID_MS_MPEG4;
		break;
	case AV_CODEC_ID_HEVC:
		gxx_codec_id = GS_CODEID_ST_H265;	
		break;
	case AV_CODEC_ID_MJPEG: 
		gxx_codec_id = GS_CODEID_ST_MJPG;
		break;
	case AV_CODEC_ID_FLV1:
		gxx_codec_id = GS_CODEID_ST_FLV1;
		break;
	case AV_CODEC_ID_WMV1:
		gxx_codec_id = GS_CODEID_ST_WMV1;
		break;
	case AV_CODEC_ID_WMV2:
		gxx_codec_id = GS_CODEID_ST_WMV2; 
		break;
	case AV_CODEC_ID_WMV3:
		gxx_codec_id = GS_CODEID_ST_WMV3; 
		break;

		//ÒôÆµ
	case AV_CODEC_ID_MP3:    
		gxx_codec_id = GS_CODEID_ST_MP3;
		break;
	case AV_CODEC_ID_AAC: 
		gxx_codec_id = GS_CODEID_AUDIO_ST_AAC;
		break;
	case AV_CODEC_ID_PCM_ALAW:
		gxx_codec_id = GS_CODEID_AUDIO_ST_G711A;
		break;
	case AV_CODEC_ID_PCM_MULAW:
		gxx_codec_id = GS_CODEID_AUDIO_ST_G711U;
		break;
	case AV_CODEC_ID_ADPCM_G722:
		gxx_codec_id = GS_CODEID_AUDIO_ST_G722;
		break;
	case AV_CODEC_ID_G723_1: 
		gxx_codec_id = GS_CODEID_AUDIO_ST_G721;
		break;
	case AV_CODEC_ID_ADPCM_G726:
		gxx_codec_id = GS_CODEID_AUDIO_ST_G726;
		break;
	case AV_CODEC_ID_G729: 
		gxx_codec_id = GS_CODEID_AUDIO_ST_G729;
		break;
	case AV_CODEC_ID_WMAV1:
		gxx_codec_id = GS_CODEID_AUDIO_ST_WMA1;
		break;
	case AV_CODEC_ID_WMAV2:
		gxx_codec_id = GS_CODEID_AUDIO_ST_WMA2;
		break;
	default:
		gxx_codec_id = GS_CODEID_NONE;
		break;
	}

	return gxx_codec_id;
}

AVCodecID GxxCodecId2FFmpegCodecId(EnumGSCodeID codecid)
{
	AVCodecID av_codec_id = AV_CODEC_ID_NONE;

	switch (codecid)
	{
	//±ê×¼ÊÓÆµ±àÂë
	case GS_CODEID_ST_MP4:
		av_codec_id = AV_CODEC_ID_MPEG4;
		break;
	case GS_CODEID_ST_H264:
		av_codec_id = AV_CODEC_ID_H264;
		break;
	case GS_CODEID_ST_SVAC:
		av_codec_id = AV_CODEC_ID_H264;
		break;
	case GS_CODEID_ST_H265:
		av_codec_id = AV_CODEC_ID_HEVC;
		break;
	case GS_CODEID_ST_H263:
		av_codec_id = AV_CODEC_ID_H263;
		break;
	case GS_CODEID_ST_MPEG2:
		av_codec_id = AV_CODEC_ID_MPEG2VIDEO;
		break;
	case GS_CODEID_ST_MPEG1:
		av_codec_id = AV_CODEC_ID_MPEG1VIDEO;
		break;
	case GS_CODEID_ST_MJPG:
		av_codec_id = AV_CODEC_ID_MJPEG;
		break;
	case GS_CODEID_FCC_MPEG4:
		av_codec_id = AV_CODEC_ID_MSMPEG4V1;
		break;
	case GS_CODEID_MS_MPEG4:
		av_codec_id = AV_CODEC_ID_MSMPEG4V2;
		break;
	case GS_CODEID_ST_FLV1:
		av_codec_id = AV_CODEC_ID_FLV1;
		break;
	case GS_CODEID_ST_WMV1:
		av_codec_id = AV_CODEC_ID_WMV1;
		break;
	case GS_CODEID_ST_WMV2:
		av_codec_id = AV_CODEC_ID_WMV2;
		break;
	case GS_CODEID_ST_WMV3:
		av_codec_id = AV_CODEC_ID_WMV3;
		break;

	//±ê×¼ÒôÆµ±àÂë
	case GS_CODEID_ST_MP3:
		av_codec_id = AV_CODEC_ID_MP3;
		break;
	case GS_CODEID_AUDIO_ST_PCM:
		av_codec_id = AV_CODEC_ID_FIRST_AUDIO;
		break;
	case GS_CODEID_AUDIO_ST_G711A:
		av_codec_id = AV_CODEC_ID_PCM_ALAW;
		break;
	case GS_CODEID_AUDIO_ST_G711U:
		av_codec_id = AV_CODEC_ID_PCM_MULAW;
		break;
	case GS_CODEID_AUDIO_ST_G721:
		av_codec_id = AV_CODEC_ID_G723_1;
		break;
	case GS_CODEID_AUDIO_ST_G722:
		av_codec_id = AV_CODEC_ID_ADPCM_G722;
		break;
	case GS_CODEID_AUDIO_ST_G723:
		av_codec_id = AV_CODEC_ID_G723_1;
		break;
	case GS_CODEID_AUDIO_ST_G726:
		av_codec_id = AV_CODEC_ID_ADPCM_G726;
		break;
	case GS_CODEID_AUDIO_ST_G729:
		av_codec_id = AV_CODEC_ID_G729;
		break;
	//case GS_CODEID_AUDIO_ST_H263:
	//	av_codec_id = AV_CODEC_ID_MPEG4;
	//	break;
	//case GS_CODEID_AUDIO_ST_SVAC:
	//	av_codec_id = AV_CODEC_ID_MPEG4;
	//	break;
	case GS_CODEID_AUDIO_ST_AAC:
		av_codec_id = AV_CODEC_ID_AAC;
		break;
	case GS_CODEID_AUDIO_ST_G726_16:
		av_codec_id = AV_CODEC_ID_ADPCM_G726;
		break;
	case GS_CODEID_AUDIO_ST_G726_24:
		av_codec_id = AV_CODEC_ID_ADPCM_G726;
		break;
	case GS_CODEID_AUDIO_ST_G726_32:
		av_codec_id = AV_CODEC_ID_ADPCM_G726;
		break;
	case GS_CODEID_AUDIO_ST_G726_40:
		av_codec_id = AV_CODEC_ID_ADPCM_G726;
		break;
	//case GS_CODEID_AUDIO_ST_OGGVORBIS:
	//	av_codec_id = AV_CODEC_ID_MPEG4;
	//	break;
	//case GS_CODEID_AUDIO_ST_AMR:
	//	av_codec_id = AV_CODEC_ID_MPEG4;
	//	break;
	case GS_CODEID_AUDIO_ST_WMA1:
		av_codec_id = AV_CODEC_ID_WMAV1;
		break;
	case GS_CODEID_AUDIO_ST_WMA2:
		av_codec_id = AV_CODEC_ID_WMAV2;
		break;
	}

	return av_codec_id;
}