#include "npJsInterface.h"
//#include "GxxGmPlayBase.h"


void __stdcall NPAPI_GetVersion(const NPVariant *args, uint32_t argCount, NPVariant *result)
{

}

void __stdcall NPAPI_Initialize(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	if (argCount != 2)
	{
		//GxxGmPlayBase::DebugStringOutput("NPAPI_Initialize() argCount = %d\n", argCount);
		return ;
	}

	int disp_rows = NPVARIANT_TO_INT32(args[0]);
	int disp_lines = NPVARIANT_TO_INT32(args[1]);

	//// ³õÊ¼»¯²¥·ÅÆ÷
	//int errCode = 0;
	//errCode = gxx_gm_multi_disp_player_.Initialize(global_plugin_->m_hWnd, disp_rows, disp_lines);
	//if (errCode != 0)
	//	GxxGmPlayBase::DebugStringOutput("GxxGmMultiDisp::Initialize() failed... errCode = %d\n", errCode);
}

void __stdcall NPAPI_SetDispCount(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	if (argCount != 2)
	{
		//GxxGmPlayBase::DebugStringOutput("NPAPI_SetDispCount() argCount = %d\n", argCount);
		return ;
	}

	int h_count = NPVARIANT_TO_INT32(args[0]);
	int v_count = NPVARIANT_TO_INT32(args[1]);

	//int errCode = 0;
	//errCode = gxx_gm_multi_disp_player_.ReDivision(v_count, h_count);

	//if (errCode != 0)
	//	GxxGmPlayBase::DebugStringOutput("GxxGmMultiDisp::Initialize() failed... errCode = %d\n", errCode);
}

void __stdcall NPAPI_Play(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	if (argCount != 4)
	{
		//GxxGmPlayBase::DebugStringOutput("NPAPI_Play() argCount = %d\n", argCount);
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
		bool is_real_mode = true;
	

	//int errCode = gxx_gm_multi_disp_player_.Play(url, play_info, disp_index, is_real_mode);

	//if (errCode != 0)
	//	GxxGmPlayBase::DebugStringOutput("GxxGmMultiDisp::Play() failed... errCode = %d\n", errCode);
}

void __stdcall NPAPI_Pause(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	int disp_index = NPVARIANT_TO_INT32(args[2]);

	//int errCode = gxx_gm_multi_disp_player_.Pause(disp_index);

	//if (errCode != 0)
	//	GxxGmPlayBase::DebugStringOutput("GxxGmMultiDisp::Pause() failed... errCode = %d\n", errCode);
}

void __stdcall NPAPI_Resume(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	int disp_index = NPVARIANT_TO_INT32(args[2]);

	//int errCode = gxx_gm_multi_disp_player_.Resume(disp_index);

	//if (errCode != 0)
	//	GxxGmPlayBase::DebugStringOutput("GxxGmMultiDisp::Resume() failed... errCode = %d\n", errCode);
}

void __stdcall NPAPI_Stop(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	int disp_index = NPVARIANT_TO_INT32(args[2]);

	//int errCode = gxx_gm_multi_disp_player_.Stop(disp_index);

	//if (errCode != 0)
	//	GxxGmPlayBase::DebugStringOutput("GxxGmMultiDisp::Stop() failed... errCode = %d\n", errCode);
}

void __stdcall NPAPI_GetPlayInfo(const NPVariant *args, uint32_t argCount, NPVariant *result)
{

}

void __stdcall NPAPI_GetPlayingURL(const NPVariant *args, uint32_t argCount, NPVariant *result)
{

}
