#ifndef _GSMediaPlayer_stub_H_
#define _GSMediaPlayer_stub_H_

#include "GSMediaPlayer.h"

//////////////////////////////////////////////////////////////////////////
//
// 本类是GSMediaPlayer的一个桩类
// 目的是动态加载GSMediaPlayer_stub，在加载前，将当前进程的当前目录设置为GSMediaPlayer所在的目录
// 然后将我们所用的若干接口动态导出调用
//
// 看上去有点恶心，但是没办法
// 实际上，播放器SDK里面也有必要做ffmpeg的桩类

/**
 * Method		GSMediaPlayer_Open
 * @brief		在给定的窗口上以指定的模式打开播放库会话
 * @param[in]	eMode				 打开模式
 * @param[in]	stGSMediaDesc		 媒体描述，视频编码必须填写，若无音频可不填
									 内部时戳计算仅适用于裸流，若启用帧率计算，参考帧率必须填写
 * @param[in]	hWnd				 显示画面的窗口句柄
 * @param[out]	pHandle				 返回播放句柄
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Open)(EnumGSMediaPlayMode eMode,const StruGSMediaDesc &stGSMediaDesc,Int32 hWnd,GSMediaPlayHandle* pHandle);
/**
 * Method		GSMediaPlayer_Play
 * @brief		开始播放，一般此接口在Open调用后，才能调用
 * @param[in]	handle	 播放库句柄
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Play)(GSMediaPlayHandle handle);
/**
 * Method		GSMediaPlayer_ReversePlay
 * @brief		开始倒放，此接口仅在回放模式下才起作用，此接口调用需在Open调用后
 * @param[in]	handle	播放库句柄
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_ReversePlay)(GSMediaPlayHandle handle);
/**
 * Method		GSMediaPlayer_Pause
 * @brief		暂停，此接口仅在回放模式下起作用
 * @param[in]	handle	播放库句柄
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Pause)(GSMediaPlayHandle handle);
/**
 * Method		GSMediaPlayer_Stop
 * @brief		停止播放，此接口与close不同，此接口调用后会去清空播放库内部缓存，暂停解码渲染，但不销毁资源
				此接口调用后，无需调用Open，可直接play调用
 * @param[in]	handle	播放库柄句
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Stop)(GSMediaPlayHandle handle);
/**
 * Method		GSMediaPlayer_Next
 * @brief		帧进，每调用一次向后出一帧，调用此接口时，此接口仅在回放模式下起作用
 * @param[in]	handle	 播放库句柄
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Next)(GSMediaPlayHandle handle);
/**
 * Method		GSMediaPlayer_Back
 * @brief		帧进，每调用一次向前出一帧，调用此接口时，需调用InputGopData,按gop推帧，此接口仅在回放模式下起作用
 * @param[in]	handle	播放库句柄
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Back)(GSMediaPlayHandle handle);
/**
 * Method		GSMediaPlayer_GetPlayedGOPKeyStamp
 * @brief		获取最近播放帧所在gop的关键帧时戳，此接口获取到的时戳为解码后时戳
 * @param[in]	handle	 播放库句柄
 * @param[out]	pulTimeStamp   获取的关键帧时戳
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_GetPlayedGOPKeyStamp)(GSMediaPlayHandle handle,UInt64* pulTimeStamp);
/**
 * Method		GSMediaPlayer_GetPlayedPos
 * @brief		获取最近播放帧的时戳，此接口获取到的时戳为解码后时戳
 * @param[in]	handle	 播放库句柄
 * @param[out]	pulTimeStamp  获取的播放帧时戳
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_GetPlayedPos)(GSMediaPlayHandle handle,UInt64* pulTimeStamp);

/**
 * Method		GSMediaPlayer_SetPlayedPos
 * @brief		设置当前播放的起始位置
 * @param[in]	handle   播放库句柄
 * @param[in]	ulTimeStamp	播放起始时间戳
 * @param[in]	bReleative	若为true，则表示ulTimeStamp是相对于即将推入GOP的I帧时戳的差值，否则为源时间戳
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_SetPlayedPos)(GSMediaPlayHandle handle,UInt64 ulTimeStamp,bool bReleative=true);
/**
 * Method		GSMediaPlayer_Close
 * @brief		关闭播放库句柄，此接口调用后，所有播放资源将会被销毁
 * @param[in]	handle	播放库句柄
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Close)(GSMediaPlayHandle handle);
/**
 * Method		GSMediaPlayer_InputData
 * @brief		主动推数据到播放库中，此接口需要在Open后，才能调用，在实时模式下，仅支持此接口推帧，回放模式下，倒放不支持此接口推帧
 * @param[in]	handle	 播放库句柄
 * @param[in]	pstMediaFrameData	帧数据
 * @param[in]	bBlockedIfTooFast	在播放库内部缓存满后，是否阻塞，直到有空闲空间存储帧
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_InputData)(GSMediaPlayHandle handle,const StruGSMediaFrameData* pstMediaFrameData,bool bBlockedIfTooFast=true);

/**
 * Method		GSMediaPlayer_InputGOPData
 * @brief		主动推数据到播放库中，必须以完整GOP推入
 * @param[in]	handle	 播放句柄
 * @param[in]	pstGopMediaFrameData   帧数据
 * @param[in]	nSize	  帧数量
 * @param[in]	bBlockedIfTooFast	是否阻塞
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_InputGOPData)(GSMediaPlayHandle handle,const StruGSMediaFrameData** pstGopMediaFrameData,int nSize,bool bBlockedIfTooFast=true);

/**
 * Method		GSMediaPlayer_PlaySound
 * @brief		启用声音播放
 * @param[in]	handle	播放库句柄
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_PlaySound)(GSMediaPlayHandle handle);

/**
 * Method		GSMediaPlayer_SetVolumn
 * @brief		设置音量
 * @param[in]	handle	播放库句柄
 * @param[in]	nVolumn	音量，改值取0-100范围
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_SetVolumn)(GSMediaPlayHandle handle,Int32 nVolumn);

/**
 * Method		GSMediaPlayer_GetVolumn
 * @brief		获取音量
 * @param[in]	handle	播放库句柄
 * @param[out]	pnVolumn  返回的音量
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_GetVolumn)(GSMediaPlayHandle handle,Int32* pnVolumn);

/**
 * Method		GSMediaPlayer_StopSound
 * @brief		关闭声音播放
 * @param[in]	handle	播放库句柄
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_StopSound)(GSMediaPlayHandle handle);



 
 
 /**
  * Method		GSMediaPlayer_SetDisplayCallback
  * @brief		设置渲染前数据回调
  * @param[in]	handle	  播放句柄
  * @param[in]	pFuncDisplayCB	回调函数
  * @param[in]	pUser			用户数据
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_SetDisplayCallback)(GSMediaPlayHandle handle,PFuncDisplayCB pFuncDisplayCB,void* pUser);
 /**
  * Method		GSMediaPlayer_SetBufferEmptyCallback
  * @brief		设置缓存为空时回调，当播放时内部缓存已经播完的情况下回发生此函数的回调，通常用于播放完成通知
  * @param[in]	handle	播放句柄
  * @param[in]	pFuncBufferEmptyCB
  * @param[in]	pUser
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_SetBufferEmptyCallback)(GSMediaPlayHandle handle,PFuncOnBufferEmptyCB pFuncBufferEmptyCB,void* pUser);


 /**
  * Method		GSMediaPlayer_SetDrawCallback
  * @brief		注册画图回调函数
  * @param[in]	handle	播放句柄
  * @param[in]	pFuncDrawCB	  回调函数传回的dc仅在回调函数作用域中有效
  * @param[in]	pUser		  用户数据
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_SetDrawCallback)(GSMediaPlayHandle handle,PFuncDrawCB pFuncDrawCB,void* pUser);


 /**
  * Method		GSMediaPlayer_SetDisplayRegion
  * @brief		增加或者修改显示区域,可以实现多窗口显示或局部放大显示
  * @param[in]	handle	 播放库句柄
  * @param[in]	nRegionNum	  显示区域编号
  * @param[in]	pSrcRect	  待显示的原图像区域
  * @param[in]	hDestWnd	  目标窗口句柄
  * @param[in]	bEnable		  显示或关闭，true:显示
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_SetDisplayRegion)(GSMediaPlayHandle handle,UInt32 nRegionNum,const StruRect &stRect,Int32 hDestWnd,bool bEnable);

 /**
  * Method		GSMediaPlayer_GetVideoSize
  * @brief		获取视频帧分辨率
  * @param[in]	handle	播放库句柄
  * @param[out]	pWidth	帧宽
  * @param[out]	pHeight	帧高
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_GetVideoSize)(GSMediaPlayHandle handle,Int32 *pnWidth,Int32 *pnHeight);

 /**
  * Method		GSMediaPlayer_Fast
  * @brief		加倍播放接口,此接口调用时，若音频处于开启状态，则会关闭音频，若需要再次开启音频，需要显示调用PlaySound
  * @param[in]	handle	播放句柄
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Fast)(GSMediaPlayHandle handle);

 /**
  * Method		GSMediaPlayer_Slow
  * @brief		减倍播放接口
  * @param[in]	handle   播放句柄
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Slow)(GSMediaPlayHandle handle);

 /**
  * Method		GSMediaPlayer_SetPlaySpeed
  * @brief		直接设置播放速度接口
  * @param[in]	handle	 播放句柄
  * @param[in]	dSpeed   dSpeed 播放倍数，大于1表示快放，小于1表示慢放
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_SetPlaySpeed)(GSMediaPlayHandle handle,double dSpeed);


 /**
  * Method		GSMediaPlayer_CapturePicture
  * @brief		抓图
  * @param[in]	handle	 播放库句柄
  * @param[in]	sPicFileName  文件存放路径（绝对地址）
  * @param[in]	nPicType   0:bmp,1:jpeg,2:png
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_CapturePicture)(GSMediaPlayHandle handle, const char *szPicFileName,Int32 nPicType);



 /**
  * Method		GSMediaPlayer_ClearPlayBuffer
  * @brief		清空播放缓存
  * @param[in]	handle	   播放库句柄
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_ClearPlayBuffer)(GSMediaPlayHandle handle);

  /**
  * Method		GSMediaPlayer_ClearPlayBuffer
  * @brief		刷新窗口视图
  * @param[in]	handle	   播放库句柄
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_RefreshView)(GSMediaPlayHandle handle);

 /**
  * Method		GSMediaPlayer_SetColor	
  * @brief设置视频参数
  * @param[in]	handle
  * @param[in]	nRegionNum	 显示区域,这里目前未用
  * @param[in]	nBrightness	 亮度,默认为;范围0-128
  * @param[in]	nContrast	 对比度,默认为;范围0-128
  * @param[in]	nSaturation	 饱和度,默认为;范围0-128 
  * @param[in]	nHue		 色调,默认为;范围0-128
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_SetColor)(GSMediaPlayHandle handle, UInt32 nRegionNum, Int32 nBrightness, Int32 nContrast, Int32 nSaturation, Int32 nHue);

 /**
  * Method		GSMediaPlayer_GetColor	 
  * @brief		获取视频参数
  * @param[in]	handle
  * @param[in]	nRegionNum	  显示区域,这里目前未用。
  * @param[in]	nBrightness	  亮度,默认为;范围0-128
  * @param[in]	nContrast	  对比度,默认为;范围0-128
  * @param[in]	nSaturation	  饱和度,默认为;范围0-128
  * @param[in]	nHue		  色调,默认为;范围0-128
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_GetColor)(GSMediaPlayHandle handle, UInt32 nRegionNum,Int32 *nBrightness,Int32 *nContrast, Int32 *nSaturation, Int32 *nHue);

class GSMediaPlayer_stub
{
public:
	GSMediaPlayer_stub();
	~GSMediaPlayer_stub();

public:
	int Initialize();

public:
	_GSMediaPlayer_Open	ptr_GSMediaPlayer_Open;
	_GSMediaPlayer_Play ptr_GSMediaPlayer_Play;
	_GSMediaPlayer_ReversePlay ptr_GSMediaPlayer_ReversePlay;
	_GSMediaPlayer_Pause ptr_GSMediaPlayer_Pause;
	_GSMediaPlayer_Stop ptr_GSMediaPlayer_Stop;
	_GSMediaPlayer_Next ptr_GSMediaPlayer_Next;
	_GSMediaPlayer_Back ptr_GSMediaPlayer_Back;
	_GSMediaPlayer_GetPlayedGOPKeyStamp ptr_GSMediaPlayer_GetPlayedGOPKeyStamp;
	_GSMediaPlayer_GetPlayedPos ptr_GSMediaPlayer_GetPlayedPos;
	_GSMediaPlayer_SetPlayedPos ptr_GSMediaPlayer_SetPlayedPos;
	_GSMediaPlayer_Close ptr_GSMediaPlayer_Close;
	_GSMediaPlayer_InputData ptr_GSMediaPlayer_InputData;
	_GSMediaPlayer_InputGOPData ptr_GSMediaPlayer_InputGOPData;
	_GSMediaPlayer_PlaySound ptr_GSMediaPlayer_PlaySound;
	_GSMediaPlayer_SetVolumn ptr_GSMediaPlayer_SetVolumn;
	_GSMediaPlayer_GetVolumn ptr_GSMediaPlayer_GetVolumn;
	_GSMediaPlayer_StopSound ptr_GSMediaPlayer_StopSound;

	_GSMediaPlayer_SetDisplayCallback ptr_GSMediaPlayer_SetDisplayCallback;
	_GSMediaPlayer_SetBufferEmptyCallback ptr_GSMediaPlayer_SetBufferEmptyCallback;
	_GSMediaPlayer_SetDrawCallback ptr_GSMediaPlayer_SetDrawCallback;
	_GSMediaPlayer_SetDisplayRegion ptr_GSMediaPlayer_SetDisplayRegion;
	_GSMediaPlayer_GetVideoSize ptr_GSMediaPlayer_GetVideoSize;
	_GSMediaPlayer_Fast ptr_GSMediaPlayer_Fast;
	_GSMediaPlayer_Slow ptr_GSMediaPlayer_Slow;
	_GSMediaPlayer_SetPlaySpeed ptr_GSMediaPlayer_SetPlaySpeed;
	_GSMediaPlayer_CapturePicture ptr_GSMediaPlayer_CapturePicture;
	_GSMediaPlayer_ClearPlayBuffer ptr_GSMediaPlayer_ClearPlayBuffer;
	_GSMediaPlayer_RefreshView ptr_GSMediaPlayer_RefreshView;
	_GSMediaPlayer_SetColor ptr_GSMediaPlayer_SetColor;
	_GSMediaPlayer_GetColor ptr_GSMediaPlayer_GetColor;

private:
	HMODULE GSMediaPlayerLib_;
};

#endif//_GSMediaPlayer_stub_H_
