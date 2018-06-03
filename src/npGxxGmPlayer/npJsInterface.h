#ifndef _npJsInterface_H_
#define _npJsInterface_H_

#include "pluginbase.h"
#include "Plugin.h"

//////////////////////////////////////////////////////////////////////////
//
// 这里定义提供给Javascript使用的接口

//void __stdcall NPAPI_GetVersion(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_GetVersion(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_Initialize(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_SetDispCount(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_Play(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_Pause(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_Resume(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_Stop(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_StopAll(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_GetPlayInfo(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_GetPlayingURL(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_PlayCallback(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_TestPlayCallback(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_OpenSound(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_CloseSound(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_GetVolume(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_SetVolume(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_CapturePicture(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_Fast(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_Slow(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_SetPlaySpeed(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_Next(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_Back(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_SetPlayPos(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_ClearPlayBuffer(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_RefreshView(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);
//void __stdcall NPAPI_Initialize(NPP instance, const NPVariant *args, uint32_t argCount, NPVariant *result);

#endif//_npJsInterface_H_