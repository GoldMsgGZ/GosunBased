#ifndef _GxxGmCodec_H_
#define _GxxGmCodec_H_


/**
 *
 */
class GxxGmCodec
{
public:
	GxxGmCodec();
	~GxxGmCodec();

	// 解码部分
public:
	/**
	 * 准备解码，需要传入视音频编码信息
	 */
	int PrepareDecode();

	// 编码部分
public:
	/**
	 * 准备编码，需要传入视音频编码信息
	 */
	int PrepareEncode();

};

#endif//_GxxGmCodec_H_
