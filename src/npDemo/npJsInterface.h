#ifndef _npJsInterface_H_
#define _npJsInterface_H_

#include "pluginbase.h"
#include "Plugin.h"

//////////////////////////////////////////////////////////////////////////
//
// 这里定义提供给Javascript使用的接口

//void __stdcall NPAPI_GetVersion(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_GetVersion(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_Initialize(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_SetDispCount(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_Play(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_Pause(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_Resume(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_Stop(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_GetPlayInfo(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_GetPlayingURL(const NPVariant *args, uint32_t argCount, NPVariant *result);
//void __stdcall NPAPI_Initialize(const NPVariant *args, uint32_t argCount, NPVariant *result);

#endif//_npJsInterface_H_