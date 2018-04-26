#ifndef _GSMediaPlayer_stub_H_
#define _GSMediaPlayer_stub_H_

#include "GSMediaPlayer.h"

//////////////////////////////////////////////////////////////////////////
//
// ������GSMediaPlayer��һ��׮��
// Ŀ���Ƕ�̬����GSMediaPlayer_stub���ڼ���ǰ������ǰ���̵ĵ�ǰĿ¼����ΪGSMediaPlayer���ڵ�Ŀ¼
// Ȼ���������õ����ɽӿڶ�̬��������
//
// ����ȥ�е���ģ�����û�취
// ʵ���ϣ�������SDK����Ҳ�б�Ҫ��ffmpeg��׮��

/**
 * Method		GSMediaPlayer_Open
 * @brief		�ڸ����Ĵ�������ָ����ģʽ�򿪲��ſ�Ự
 * @param[in]	eMode				 ��ģʽ
 * @param[in]	stGSMediaDesc		 ý����������Ƶ���������д��������Ƶ�ɲ���
									 �ڲ�ʱ�������������������������֡�ʼ��㣬�ο�֡�ʱ�����д
 * @param[in]	hWnd				 ��ʾ����Ĵ��ھ��
 * @param[out]	pHandle				 ���ز��ž��
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Open)(EnumGSMediaPlayMode eMode,const StruGSMediaDesc &stGSMediaDesc,Int32 hWnd,GSMediaPlayHandle* pHandle);
/**
 * Method		GSMediaPlayer_Play
 * @brief		��ʼ���ţ�һ��˽ӿ���Open���ú󣬲��ܵ���
 * @param[in]	handle	 ���ſ���
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Play)(GSMediaPlayHandle handle);
/**
 * Method		GSMediaPlayer_ReversePlay
 * @brief		��ʼ���ţ��˽ӿڽ��ڻط�ģʽ�²������ã��˽ӿڵ�������Open���ú�
 * @param[in]	handle	���ſ���
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_ReversePlay)(GSMediaPlayHandle handle);
/**
 * Method		GSMediaPlayer_Pause
 * @brief		��ͣ���˽ӿڽ��ڻط�ģʽ��������
 * @param[in]	handle	���ſ���
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Pause)(GSMediaPlayHandle handle);
/**
 * Method		GSMediaPlayer_Stop
 * @brief		ֹͣ���ţ��˽ӿ���close��ͬ���˽ӿڵ��ú��ȥ��ղ��ſ��ڲ����棬��ͣ������Ⱦ������������Դ
				�˽ӿڵ��ú��������Open����ֱ��play����
 * @param[in]	handle	���ſ����
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Stop)(GSMediaPlayHandle handle);
/**
 * Method		GSMediaPlayer_Next
 * @brief		֡����ÿ����һ������һ֡�����ô˽ӿ�ʱ���˽ӿڽ��ڻط�ģʽ��������
 * @param[in]	handle	 ���ſ���
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Next)(GSMediaPlayHandle handle);
/**
 * Method		GSMediaPlayer_Back
 * @brief		֡����ÿ����һ����ǰ��һ֡�����ô˽ӿ�ʱ�������InputGopData,��gop��֡���˽ӿڽ��ڻط�ģʽ��������
 * @param[in]	handle	���ſ���
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Back)(GSMediaPlayHandle handle);
/**
 * Method		GSMediaPlayer_GetPlayedGOPKeyStamp
 * @brief		��ȡ�������֡����gop�Ĺؼ�֡ʱ�����˽ӿڻ�ȡ����ʱ��Ϊ�����ʱ��
 * @param[in]	handle	 ���ſ���
 * @param[out]	pulTimeStamp   ��ȡ�Ĺؼ�֡ʱ��
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_GetPlayedGOPKeyStamp)(GSMediaPlayHandle handle,UInt64* pulTimeStamp);
/**
 * Method		GSMediaPlayer_GetPlayedPos
 * @brief		��ȡ�������֡��ʱ�����˽ӿڻ�ȡ����ʱ��Ϊ�����ʱ��
 * @param[in]	handle	 ���ſ���
 * @param[out]	pulTimeStamp  ��ȡ�Ĳ���֡ʱ��
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_GetPlayedPos)(GSMediaPlayHandle handle,UInt64* pulTimeStamp);

/**
 * Method		GSMediaPlayer_SetPlayedPos
 * @brief		���õ�ǰ���ŵ���ʼλ��
 * @param[in]	handle   ���ſ���
 * @param[in]	ulTimeStamp	������ʼʱ���
 * @param[in]	bReleative	��Ϊtrue�����ʾulTimeStamp������ڼ�������GOP��I֡ʱ���Ĳ�ֵ������ΪԴʱ���
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_SetPlayedPos)(GSMediaPlayHandle handle,UInt64 ulTimeStamp,bool bReleative=true);
/**
 * Method		GSMediaPlayer_Close
 * @brief		�رղ��ſ������˽ӿڵ��ú����в�����Դ���ᱻ����
 * @param[in]	handle	���ſ���
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Close)(GSMediaPlayHandle handle);
/**
 * Method		GSMediaPlayer_InputData
 * @brief		���������ݵ����ſ��У��˽ӿ���Ҫ��Open�󣬲��ܵ��ã���ʵʱģʽ�£���֧�ִ˽ӿ���֡���ط�ģʽ�£����Ų�֧�ִ˽ӿ���֡
 * @param[in]	handle	 ���ſ���
 * @param[in]	pstMediaFrameData	֡����
 * @param[in]	bBlockedIfTooFast	�ڲ��ſ��ڲ����������Ƿ�������ֱ���п��пռ�洢֡
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_InputData)(GSMediaPlayHandle handle,const StruGSMediaFrameData* pstMediaFrameData,bool bBlockedIfTooFast=true);

/**
 * Method		GSMediaPlayer_InputGOPData
 * @brief		���������ݵ����ſ��У�����������GOP����
 * @param[in]	handle	 ���ž��
 * @param[in]	pstGopMediaFrameData   ֡����
 * @param[in]	nSize	  ֡����
 * @param[in]	bBlockedIfTooFast	�Ƿ�����
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_InputGOPData)(GSMediaPlayHandle handle,const StruGSMediaFrameData** pstGopMediaFrameData,int nSize,bool bBlockedIfTooFast=true);

/**
 * Method		GSMediaPlayer_PlaySound
 * @brief		������������
 * @param[in]	handle	���ſ���
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_PlaySound)(GSMediaPlayHandle handle);

/**
 * Method		GSMediaPlayer_SetVolumn
 * @brief		��������
 * @param[in]	handle	���ſ���
 * @param[in]	nVolumn	��������ֵȡ0-100��Χ
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_SetVolumn)(GSMediaPlayHandle handle,Int32 nVolumn);

/**
 * Method		GSMediaPlayer_GetVolumn
 * @brief		��ȡ����
 * @param[in]	handle	���ſ���
 * @param[out]	pnVolumn  ���ص�����
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_GetVolumn)(GSMediaPlayHandle handle,Int32* pnVolumn);

/**
 * Method		GSMediaPlayer_StopSound
 * @brief		�ر���������
 * @param[in]	handle	���ſ���
 * @return		typedef EnumGSMediaPlayerErrCode
 */
typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_StopSound)(GSMediaPlayHandle handle);



 
 
 /**
  * Method		GSMediaPlayer_SetDisplayCallback
  * @brief		������Ⱦǰ���ݻص�
  * @param[in]	handle	  ���ž��
  * @param[in]	pFuncDisplayCB	�ص�����
  * @param[in]	pUser			�û�����
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_SetDisplayCallback)(GSMediaPlayHandle handle,PFuncDisplayCB pFuncDisplayCB,void* pUser);
 /**
  * Method		GSMediaPlayer_SetBufferEmptyCallback
  * @brief		���û���Ϊ��ʱ�ص���������ʱ�ڲ������Ѿ����������»ط����˺����Ļص���ͨ�����ڲ������֪ͨ
  * @param[in]	handle	���ž��
  * @param[in]	pFuncBufferEmptyCB
  * @param[in]	pUser
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_SetBufferEmptyCallback)(GSMediaPlayHandle handle,PFuncOnBufferEmptyCB pFuncBufferEmptyCB,void* pUser);


 /**
  * Method		GSMediaPlayer_SetDrawCallback
  * @brief		ע�ửͼ�ص�����
  * @param[in]	handle	���ž��
  * @param[in]	pFuncDrawCB	  �ص��������ص�dc���ڻص���������������Ч
  * @param[in]	pUser		  �û�����
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_SetDrawCallback)(GSMediaPlayHandle handle,PFuncDrawCB pFuncDrawCB,void* pUser);


 /**
  * Method		GSMediaPlayer_SetDisplayRegion
  * @brief		���ӻ����޸���ʾ����,����ʵ�ֶര����ʾ��ֲ��Ŵ���ʾ
  * @param[in]	handle	 ���ſ���
  * @param[in]	nRegionNum	  ��ʾ������
  * @param[in]	pSrcRect	  ����ʾ��ԭͼ������
  * @param[in]	hDestWnd	  Ŀ�괰�ھ��
  * @param[in]	bEnable		  ��ʾ��رգ�true:��ʾ
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_SetDisplayRegion)(GSMediaPlayHandle handle,UInt32 nRegionNum,const StruRect &stRect,Int32 hDestWnd,bool bEnable);

 /**
  * Method		GSMediaPlayer_GetVideoSize
  * @brief		��ȡ��Ƶ֡�ֱ���
  * @param[in]	handle	���ſ���
  * @param[out]	pWidth	֡��
  * @param[out]	pHeight	֡��
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_GetVideoSize)(GSMediaPlayHandle handle,Int32 *pnWidth,Int32 *pnHeight);

 /**
  * Method		GSMediaPlayer_Fast
  * @brief		�ӱ����Žӿ�,�˽ӿڵ���ʱ������Ƶ���ڿ���״̬�����ر���Ƶ������Ҫ�ٴο�����Ƶ����Ҫ��ʾ����PlaySound
  * @param[in]	handle	���ž��
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Fast)(GSMediaPlayHandle handle);

 /**
  * Method		GSMediaPlayer_Slow
  * @brief		�������Žӿ�
  * @param[in]	handle   ���ž��
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_Slow)(GSMediaPlayHandle handle);

 /**
  * Method		GSMediaPlayer_SetPlaySpeed
  * @brief		ֱ�����ò����ٶȽӿ�
  * @param[in]	handle	 ���ž��
  * @param[in]	dSpeed   dSpeed ���ű���������1��ʾ��ţ�С��1��ʾ����
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_SetPlaySpeed)(GSMediaPlayHandle handle,double dSpeed);


 /**
  * Method		GSMediaPlayer_CapturePicture
  * @brief		ץͼ
  * @param[in]	handle	 ���ſ���
  * @param[in]	sPicFileName  �ļ����·�������Ե�ַ��
  * @param[in]	nPicType   0:bmp,1:jpeg,2:png
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_CapturePicture)(GSMediaPlayHandle handle, const char *szPicFileName,Int32 nPicType);



 /**
  * Method		GSMediaPlayer_ClearPlayBuffer
  * @brief		��ղ��Ż���
  * @param[in]	handle	   ���ſ���
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_ClearPlayBuffer)(GSMediaPlayHandle handle);

  /**
  * Method		GSMediaPlayer_ClearPlayBuffer
  * @brief		ˢ�´�����ͼ
  * @param[in]	handle	   ���ſ���
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_RefreshView)(GSMediaPlayHandle handle);

 /**
  * Method		GSMediaPlayer_SetColor	
  * @brief������Ƶ����
  * @param[in]	handle
  * @param[in]	nRegionNum	 ��ʾ����,����Ŀǰδ��
  * @param[in]	nBrightness	 ����,Ĭ��Ϊ;��Χ0-128
  * @param[in]	nContrast	 �Աȶ�,Ĭ��Ϊ;��Χ0-128
  * @param[in]	nSaturation	 ���Ͷ�,Ĭ��Ϊ;��Χ0-128 
  * @param[in]	nHue		 ɫ��,Ĭ��Ϊ;��Χ0-128
  * @return		typedef EnumGSMediaPlayerErrCode
  */
 typedef EnumGSMediaPlayerErrCode ( * _GSMediaPlayer_SetColor)(GSMediaPlayHandle handle, UInt32 nRegionNum, Int32 nBrightness, Int32 nContrast, Int32 nSaturation, Int32 nHue);

 /**
  * Method		GSMediaPlayer_GetColor	 
  * @brief		��ȡ��Ƶ����
  * @param[in]	handle
  * @param[in]	nRegionNum	  ��ʾ����,����Ŀǰδ�á�
  * @param[in]	nBrightness	  ����,Ĭ��Ϊ;��Χ0-128
  * @param[in]	nContrast	  �Աȶ�,Ĭ��Ϊ;��Χ0-128
  * @param[in]	nSaturation	  ���Ͷ�,Ĭ��Ϊ;��Χ0-128
  * @param[in]	nHue		  ɫ��,Ĭ��Ϊ;��Χ0-128
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
