#include "npJsInterface.h"
#include "GxxGmPlayBase.h"
#include "GxxGmMultiDispEx.h"

extern NPNetscapeFuncs NPNFuncs;

#define PLUGIN_VERSION	"5.0.0.1"

void __stdcall NPAPI_GetVersion(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	char *output_buffer = (char *)NPNFuncs.memalloc(strlen(PLUGIN_VERSION) + 1);
	if (!output_buffer)
		return ;

	strcpy(output_buffer, PLUGIN_VERSION);
	STRINGZ_TO_NPVARIANT(output_buffer, *result);
}

void __stdcall NPAPI_Initialize(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	if (argCount != 2)
	{
		GxxGmPlayBase::DebugStringOutput("NPAPI_Initialize() argCount = %d\n", argCount);
		return ;
	}

	int disp_rows = NPVARIANT_TO_INT32(args[0]);
	int disp_lines = NPVARIANT_TO_INT32(args[1]);
	GxxGmPlayBase::DebugStringOutput("NPAPI_Initialize() disp_rows = %d, disp_lines = %d\n", disp_rows, disp_lines);

	// 初始化播放器
	int errCode = 0;
	errCode = global_plugin_->multi_disp_ex_->Init((int)global_plugin_->m_hWnd, disp_rows, disp_lines);
	if (errCode != 0)
		GxxGmPlayBase::DebugStringOutput("GxxGmMultiDispEx::Init() failed... errCode = %d\n", errCode);
}

void __stdcall NPAPI_SetDispCount(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	if (argCount != 2)
	{
		GxxGmPlayBase::DebugStringOutput("NPAPI_SetDispCount() argCount = %d\n", argCount);
		return ;
	}

	int h_count = NPVARIANT_TO_INT32(args[0]);
	int v_count = NPVARIANT_TO_INT32(args[1]);
	GxxGmPlayBase::DebugStringOutput("NPAPI_SetDispCount() v_count = %d, h_count = %d\n", v_count, h_count);

	int errCode = 0;
	errCode = global_plugin_->multi_disp_ex_->ReDivision(v_count, h_count);
	if (errCode != 0)
		GxxGmPlayBase::DebugStringOutput("GxxGmMultiDispEx::ReDivision() failed... errCode = %d\n", errCode);
}

void __stdcall NPAPI_Play(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	if (argCount != 4)
	{
		GxxGmPlayBase::DebugStringOutput("NPAPI_Play() argCount = %d\n", argCount);
		return ;
	}

	char url[4096] = {0};
	NPString np_url = NPVARIANT_TO_STRING(args[0]);
	memcpy_s(url, 4096, np_url.UTF8Characters, np_url.UTF8Length);

	char play_info[4096] = {0};
	NPString np_play_info = NPVARIANT_TO_STRING(args[1]);
	memcpy_s(play_info, 4096, np_play_info.UTF8Characters, np_play_info.UTF8Length);

	int disp_index = NPVARIANT_TO_INT32(args[2]);
	int is_real_mode_int = NPVARIANT_TO_INT32(args[3]);

	bool is_real_mode = false;
	if (is_real_mode_int != 0)
		is_real_mode = true;

	GxxGmPlayBase::DebugStringOutput("NPAPI_Play() url = %s, play_info = %s, disp_index = %d\n", url, play_info, disp_index);

	int errCode = 0;

	errCode = global_plugin_->multi_disp_ex_->Play(url, play_info, disp_index, is_real_mode);
	if (errCode != 0)
		GxxGmPlayBase::DebugStringOutput("GxxGmMultiDispEx::Play() failed... errCode = %d\n", errCode);
}

void __stdcall NPAPI_Pause(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	int disp_index = NPVARIANT_TO_INT32(args[0]);
	GxxGmPlayBase::DebugStringOutput("GxxGmMultiDisp::Pause() disp_index = %d\n", disp_index);

 	int errCode = global_plugin_->multi_disp_ex_->Pause(disp_index);
 	if (errCode != 0)
 		GxxGmPlayBase::DebugStringOutput("GxxGmMultiDispEx::Pause() failed... errCode = %d\n", errCode);
}

void __stdcall NPAPI_Resume(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	int disp_index = NPVARIANT_TO_INT32(args[0]);
	GxxGmPlayBase::DebugStringOutput("GxxGmMultiDisp::Resume() disp_index = %d\n", disp_index);

	int errCode = global_plugin_->multi_disp_ex_->Resume(disp_index);
	if (errCode != 0)
		GxxGmPlayBase::DebugStringOutput("GxxGmMultiDispEx::Resume() failed... errCode = %d\n", errCode);
}

void __stdcall NPAPI_Stop(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	int disp_index = NPVARIANT_TO_INT32(args[0]);
	GxxGmPlayBase::DebugStringOutput("GxxGmMultiDisp::Stop() disp_index = %d\n", disp_index);

 	int errCode = global_plugin_->multi_disp_ex_->Stop(disp_index);
 	if (errCode != 0)
 		GxxGmPlayBase::DebugStringOutput("GxxGmMultiDispEx::Stop() failed... errCode = %d\n", errCode);
}

void __stdcall NPAPI_StopAll(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	int errCode = global_plugin_->multi_disp_ex_->StopAll();
	if (errCode != 0)
		GxxGmPlayBase::DebugStringOutput("GxxGmMultiDispEx::StopAll() failed... errCode = %d\n", errCode);
}

void __stdcall NPAPI_GetPlayInfo(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	int disp_index = NPVARIANT_TO_INT32(args[0]);
	GxxGmPlayBase::DebugStringOutput("GxxGmMultiDispEx::GetPlayInfo() disp_index = %d\n", disp_index);

	std::string play_info = global_plugin_->multi_disp_ex_->GetPlayInfo(disp_index);
	if (play_info.empty())
		return ;

	char *output_buffer = (char *)NPNFuncs.memalloc(play_info.size() + 1);
	if (!output_buffer)
		return ;

	strcpy(output_buffer, play_info.c_str());
	STRINGZ_TO_NPVARIANT(output_buffer, *result);
}

void __stdcall NPAPI_GetPlayingURL(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	int disp_index = NPVARIANT_TO_INT32(args[0]);
	GxxGmPlayBase::DebugStringOutput("GxxGmMultiDispEx::GetPlayingURL() disp_index = %d\n", disp_index);

	std::string url = global_plugin_->multi_disp_ex_->GetUrl(disp_index);

	char *output_buffer = (char *)NPNFuncs.memalloc(url.size() + 1);
	if (!output_buffer)
		return ;

	strcpy(output_buffer, url.c_str());
	STRINGZ_TO_NPVARIANT(output_buffer, *result);
}


// 关于回调函数，可以参考以下资料：
// https://blog.csdn.net/rainkop/article/details/8063709
// 
void __stdcall NPAPI_PlayCallback(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	GxxGmPlayBase::DebugStringOutput("GxxGmMultiDispEx::SetPlayCallback() argCount = %d\n", argCount);

	// 
	if (global_plugin_ != NULL)
	{
		// 这里检查是否已经注册了播放回调对象
		// 其他的回调安装，在其他的安装函数中实现即可
		if (global_plugin_->m_pPlayCallbackObject == NULL)
			global_plugin_->m_pPlayCallbackObject = NPN_RetainObject(NPVARIANT_TO_OBJECT(*args));

		//NPObject *pPlayCallbackObject = NPN_RetainObject(NPVARIANT_TO_OBJECT(*args));
		//global_plugin_->m_pPlayCallbackObject.push_back(pPlayCallbackObject);
	}
}

void __stdcall NPAPI_TestPlayCallback(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	GxxGmPlayBase::DebugStringOutput("GxxGmMultiDispEx::TestPlayCallback() argCount = %d\n", argCount);

	if (global_plugin_ != NULL)
	{
		//std::vector<NPObject *>::iterator iter;
		//for (iter = global_plugin_->m_pPlayCallbackObject.begin(); iter != global_plugin_->m_pPlayCallbackObject.end(); ++iter)
		//{
		//	NPVariant result;
		//	NPN_InvokeDefault(global_plugin_->m_pNPInstance, *iter, NULL, 0, &result);
		//	NPN_ReleaseVariantValue(&result);
		//}

		NPVariant result;
		NPN_InvokeDefault(global_plugin_->m_pNPInstance, global_plugin_->m_pPlayCallbackObject, NULL, 0, &result);
		NPN_ReleaseVariantValue(&result);
	}
}