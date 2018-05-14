#include "Plugin.h"
#include <windowsX.h>
#include "npruntime.h"


CPlugin *global_plugin_ = NULL;

static NPObject *sWindowObj;

//////////////////////////////////////////////////////////////////////////
//
// 首先实现四个函数
// 这四个函数都在pluginbase.h(81)中有定义
// 
// 以下函数需要在每个指定的插件中被实现
// 首先是创建或销毁基类派生出来的对象
//
//		nsPluginInstanceBase * NS_NewPluginInstance(nsPluginCreateData * aCreateDataStruct);
//		void NS_DestroyPluginInstance(nsPluginInstanceBase * aPlugin);
//
// 全局插件初始化或销毁
// 
//		NPError NS_PluginInitialize();
//		void NS_PluginShutdown();
// 

NPError NS_PluginInitialize()
{
	// 这里啥都不干
	// 我想这里的实现应该不是单纯的空函数
	return NPERR_NO_ERROR;
}

void NS_PluginShutdown()
{
	// 这里啥都不干
}

nsPluginInstanceBase * NS_NewPluginInstance(nsPluginCreateData * aCreateDataStruct)
{
	if(!aCreateDataStruct)
		return NULL;

	global_plugin_ = new CPlugin(aCreateDataStruct->instance);

	// NPAPI默认创建的是Windowed插件
	// 我们要创建winless插件，则需要将 bWindowed 手动设置为 FALSE
	BOOL bWindowed = TRUE;
	NPN_SetValue(aCreateDataStruct->instance, NPPVpluginTransparentBool, (void *)bWindowed);

	return global_plugin_;
}

void NS_DestroyPluginInstance(nsPluginInstanceBase * aPlugin)
{
	if(aPlugin)
		delete (CPlugin *)aPlugin;
}


//////////////////////////////////////////////////////////////////////////
//
// 这里处理与JavaScript交互的部分

void ScriptablePluginObjectBase::Invalidate()
{
}

bool ScriptablePluginObjectBase::HasMethod(NPIdentifier name)
{
	return false;
}

bool ScriptablePluginObjectBase::Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

bool ScriptablePluginObjectBase::InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

bool ScriptablePluginObjectBase::HasProperty(NPIdentifier name)
{
	return false;
}

bool ScriptablePluginObjectBase::GetProperty(NPIdentifier name, NPVariant *result)
{
	return false;
}

bool ScriptablePluginObjectBase::SetProperty(NPIdentifier name, const NPVariant *value)
{
	//if (name == sBar_id) {
	//	printf ("bar set\n");
	//	return true;
	//}

	return false;
}

bool ScriptablePluginObjectBase::RemoveProperty(NPIdentifier name)
{
	return false;
}

bool ScriptablePluginObjectBase::Enumerate(NPIdentifier **identifier, uint32_t *count)
{
	return false;
}

bool ScriptablePluginObjectBase::Construct(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

// static
void ScriptablePluginObjectBase::_Deallocate(NPObject *npobj)
{
	// Call the virtual destructor.
	delete (ScriptablePluginObjectBase *)npobj;
}

// static
void ScriptablePluginObjectBase::_Invalidate(NPObject *npobj)
{
	((ScriptablePluginObjectBase *)npobj)->Invalidate();
}

// static
bool ScriptablePluginObjectBase::_HasMethod(NPObject *npobj, NPIdentifier name)
{
	return ((ScriptablePluginObjectBase *)npobj)->HasMethod(name);
}

// static
bool ScriptablePluginObjectBase::_Invoke(NPObject *npobj, NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return ((ScriptablePluginObjectBase *)npobj)->Invoke(name, args, argCount, result);
}

// static
bool ScriptablePluginObjectBase::_InvokeDefault(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return ((ScriptablePluginObjectBase *)npobj)->InvokeDefault(args, argCount, result);
}

// static
bool ScriptablePluginObjectBase::_HasProperty(NPObject * npobj, NPIdentifier name)
{
	return ((ScriptablePluginObjectBase *)npobj)->HasProperty(name);
}

// static
bool ScriptablePluginObjectBase::_GetProperty(NPObject *npobj, NPIdentifier name, NPVariant *result)
{
	return ((ScriptablePluginObjectBase *)npobj)->GetProperty(name, result);
}

// static
bool ScriptablePluginObjectBase::_SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value)
{
	return ((ScriptablePluginObjectBase *)npobj)->SetProperty(name, value);
}

// static
bool ScriptablePluginObjectBase::_RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return ((ScriptablePluginObjectBase *)npobj)->RemoveProperty(name);
}

// static
bool ScriptablePluginObjectBase::_Enumerate(NPObject *npobj, NPIdentifier **identifier, uint32_t *count)
{
	return ((ScriptablePluginObjectBase *)npobj)->Enumerate(identifier, count);
}

// static
bool ScriptablePluginObjectBase::_Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return ((ScriptablePluginObjectBase *)npobj)->Construct(args, argCount, result);
}


//////////////////////////////////////////////////////////////////////////
//
//

static NPObject * AllocateConstructablePluginObject(NPP npp, NPClass *aClass)
{
	return new ConstructablePluginObject(npp);
}

DECLARE_NPOBJECT_CLASS_WITH_BASE(ConstructablePluginObject, AllocateConstructablePluginObject);

bool ConstructablePluginObject::Construct(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	GxxGmPlayBase::DebugStringOutput("Creating new ConstructablePluginObject!\n");

	NPObject *myobj = NPN_CreateObject(mNpp, GET_NPOBJECT_CLASS(ConstructablePluginObject));
	if (!myobj)
		return false;

	OBJECT_TO_NPVARIANT(myobj, *result);

	return true;
}

//////////////////////////////////////////////////////////////////////////
//
//

//////////////////////////////////////////////////////////////////////////
//
// NPAPI 插件对 Javascript 导出接口定义

JsParams js_params[] = {
	{ 0,	NULL,	"GetVersion",					NPAPI_GetVersion,					JsFuncType_Interface	},
	{ 1,	NULL,	"Initialize",					NPAPI_Initialize,					JsFuncType_Interface	},
	{ 2,	NULL,	"SetDispCount",					NPAPI_SetDispCount,					JsFuncType_Interface	},
	{ 3,	NULL,	"Play",							NPAPI_Play,							JsFuncType_Interface	},
	{ 4,	NULL,	"Pause",						NPAPI_Pause,						JsFuncType_Interface	},
	{ 5,	NULL,	"Resume",						NPAPI_Resume,						JsFuncType_Interface	},
	{ 6,	NULL,	"Stop",							NPAPI_Stop,							JsFuncType_Interface	},
	{ 7,	NULL,	"StopAll",						NPAPI_StopAll,						JsFuncType_Interface	},
	{ 8,	NULL,	"GetPlayInfo",					NPAPI_GetPlayInfo,					JsFuncType_Interface	},
	{ 9,	NULL,	"GetPlayingURL",				NPAPI_GetPlayingURL,				JsFuncType_Interface	},
	{ 10,	NULL,	"PlayCallback",					NPAPI_PlayCallback,					JsFuncType_Property		},
	{ 11,	NULL,	"TestPlayCallback",				NPAPI_TestPlayCallback,				JsFuncType_Interface	},
	{ -1,	NULL,	"",								NULL,								JsFuncType_None			}
};


static NPObject * AllocateScriptablePluginObject(NPP npp, NPClass *aClass)
{
	return new ScriptablePluginObject(npp);
}


DECLARE_NPOBJECT_CLASS_WITH_BASE(ScriptablePluginObject, AllocateScriptablePluginObject);

ScriptablePluginObject::ScriptablePluginObject(NPP npp)
: ScriptablePluginObjectBase(npp)
{
//#ifdef _DEBUG
//	MessageBox(NULL, "等待接入调试器", "调试", 0);
//#endif
	// 在这里做接口映射
	int index = 0;
	while(js_params[index].index_ != -1)
	{
		GxxGmPlayBase::DebugStringOutput("ScriptablePluginObject::ScriptablePluginObject() >>> Map %s Js interface...\n", js_params[index].interfaceName_);
		js_params[index].npId_ = NPN_GetStringIdentifier(js_params[index].interfaceName_);
		++index;
	}
}

bool ScriptablePluginObject::HasMethod(NPIdentifier name)
{
	bool has_method = false;

	int index = 0;
	while(js_params[index].index_ != -1)
	{
		if (js_params[index].npId_ == name)
		{
			has_method = true;
			break;
		}

		++index;
	}

	return has_method;
}

bool ScriptablePluginObject::HasProperty(NPIdentifier name)
{
	bool has_property = false;

	int index = 0;
	while(js_params[index].index_ != -1)
	{
		if (js_params[index].jsFuncType_ == JsFuncType_Property)
		{
			if (js_params[index].npId_ == name)
			{
				has_property = true;
				break;
			}
		}

		++index;
	}

	return has_property;
}

bool ScriptablePluginObject::GetProperty(NPIdentifier name, NPVariant *result)
{
	VOID_TO_NPVARIANT(*result);

	return true;
}

bool ScriptablePluginObject::SetProperty(NPIdentifier name, const NPVariant *value)
{
	bool res = false;

	int index = 0;
	while(js_params[index].index_ != -1)
	{
		if (js_params[index].jsFuncType_ == JsFuncType_Property)
		{
			if (js_params[index].npId_ == name)
			{
				// 找到对应的处理函数
				// 设置属性的时候，固定传一个参数进去，不处理结果
				_Func_Js js_handler = js_params[index].jsFunc_;
				js_handler(value, 1, NULL);
				res = true;
				break;
			}
		}

		++index;
	}

	return res;
}

bool ScriptablePluginObject::Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	// 这里解决具体的调用
	bool res = false;
	int index = 0;
	while(js_params[index].index_ != -1)
	{
		if (js_params[index].npId_ == name)
		{
			switch (js_params[index].jsFuncType_)
			{
			case JsFuncType_Interface:
				{
					// 这里处理Js调用插件的接口
					_Func_Js js_handler = js_params[index].jsFunc_;
					js_handler(args, argCount, result);
					res = true;
				}
				break;
			default:
				break;
			}
			
			break;
		}

		++index;
	}

	return res;
}

bool ScriptablePluginObject::InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	GxxGmPlayBase::DebugStringOutput("ScriptablePluginObject default method called!\n");

	const char* outString = "default method return val";
	char* npOutString = (char *)NPN_MemAlloc(strlen(outString) + 1);
	if (!npOutString)
		return false;
	strcpy(npOutString, outString);
	STRINGZ_TO_NPVARIANT(npOutString, *result);

	return true;
}



//////////////////////////////////////////////////////////////////////////
//
// 插件对象的具体实现

// 消息响应函数
static LRESULT CALLBACK PluginWinProc(HWND, UINT, WPARAM, LPARAM);  
static WNDPROC lpOldProc = NULL; 

//CPlugin::CPlugin(void)
//{
//}

CPlugin::CPlugin(NPP pNPInstance)
: nsPluginInstanceBase()
, m_pNPInstance(pNPInstance)
, m_bInitialized(FALSE)
, m_hWnd(NULL)
, m_pScriptableObject(NULL)
//, m_pJsCallbackObject(NULL)
, m_pPlayCallbackObject(NULL)
, multi_disp_ex_(new GxxGmMultiDispEx())
{
	GxxGmPlayBase::DebugStringOutput("创建一个插件对象！\n");
	NPN_GetValue(m_pNPInstance, NPNVWindowNPObject, &sWindowObj);

	// 这里定义各个开放的接口
}

CPlugin::~CPlugin(void)
{
	// 释放Js对象
	GxxGmPlayBase::DebugStringOutput("释放一个插件对象！\n");
	NPN_ReleaseObject(m_pScriptableObject);
	NPN_ReleaseObject(m_pPlayCallbackObject);

	//std::vector<NPObject *>::iterator iter;
	//for (iter = global_plugin_->m_pPlayCallbackObject.begin(); iter != global_plugin_->m_pPlayCallbackObject.end(); )
	//{
	//	iter = global_plugin_->m_pPlayCallbackObject.erase(iter);
	//}
}

NPBool CPlugin::init(NPWindow* pNPWindow)
{
	m_Window = pNPWindow;
	m_hWnd = (HWND)pNPWindow->window;

	if (m_hWnd == NULL)
		return FALSE;

	// 将窗口子类化，这样就可以对消息进行处理，并在窗口中绘制了
	lpOldProc = (WNDPROC)SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LPARAM)(WNDPROC)PluginWinProc);

	// 将窗口与 Plugin 对象关联，这样就可以再窗口处理中访问 Plugin 对象了
	SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

	//int errCode = player.SetScreenWindow((void*)m_hWnd);

	m_bInitialized = TRUE;
	return TRUE;
}

void CPlugin::shut()
{
	SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LPARAM)(WNDPROC)lpOldProc);

	m_hWnd = NULL;
	m_bInitialized = FALSE;
}

NPBool CPlugin::isInitialized()
{
	return m_bInitialized;
}

NPError CPlugin::SetWindow(NPWindow* pNPWindow)
{
	// 保存插件窗口指针
	m_Window = pNPWindow;
	return NPERR_NO_ERROR;
}

NPObject * CPlugin::GetScriptableObject()
{
	// 如果不存在 NPObject 对象，则新建一个
	if (!m_pScriptableObject) {
		m_pScriptableObject = NPN_CreateObject(m_pNPInstance, GET_NPOBJECT_CLASS(ScriptablePluginObject));
	}

	// 获取对象值
	if (m_pScriptableObject) {
		NPN_RetainObject(m_pScriptableObject);
	}

	return m_pScriptableObject;
}

void CPlugin::DrawBkColor(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	RECT rc;
	GetClientRect(hWnd, &rc);

	HBRUSH bkguard_brush = CreateSolidBrush(RGB(25, 25, 25));
	HBRUSH frame_brush = CreateSolidBrush(RGB(25, 25, 25));//CreateSolidBrush(RGB(30, 140, 250));
	FillRect(hDC, &rc, bkguard_brush);
	FrameRect(hDC, &rc, frame_brush);

	EndPaint(hWnd, &ps);
}

static LRESULT CALLBACK PluginWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
		{
			// 0x000F
			GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] 绘制 MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
			// 在这里需要将背景设置为RGB(25,25,25)
			// global_plugin_->DrawBkColor(hWnd);
		}
		break;
	case WM_ERASEBKGND:
		{
			// 0x0014
			// 当窗口背景必须被擦除时 (例如,窗口的移动,窗口的大小的改变)才发送
			//GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] 窗口背景必须被擦除 MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
			//global_plugin_->DrawBkColor(hWnd);
		}
		break;
	case WM_SHOWWINDOW:
		{
			// 0x0018
			// 发出了显示窗口消息
			GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] 显示窗口 MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
		}
		break;
	case WM_SETCURSOR:
		{
			// 0x0020
			//GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] 设置光标位置 MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
		}
		break;
	case WM_MOUSEACTIVATE:
		{
			// 0x0021
		}
		break;
	case WM_CHILDACTIVATE:
		{
			// 0x0022
			GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] 激活子窗口 MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
		}
		break;
	case WM_WINDOWPOSCHANGING:
		{
			// 0x0046
			GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] 窗口位置更改 MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
			global_plugin_->DrawBkColor(hWnd);
		}
		break;
	case WM_NCHITTEST:
		{
			// 0x0084
			// 当鼠标移动或者有鼠标键按下时候发出
			//GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] 鼠标移动或按下 MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
		}
		break;
	case WM_NCPAINT:
		{
			// 0x0085
			//GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] 绘制客户区以外区域(例如标题栏、菜单栏等) MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
		}
		break;
	case WM_CTLCOLORSTATIC:
		{
			// 0x0138
			//GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] 静态控件颜色更改 MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
		}
		break;
	case WM_MOUSEMOVE:
		{
			// 0x0200
			//GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] 鼠标移动 MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);

			// 获取当前鼠标坐标，判断在哪个子窗口范围内
		}
		break;
	case WM_LBUTTONDOWN:
		{
			// 0x0201
			GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] 鼠标左键按下 MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
			
			
		}
		break;
	case WM_LBUTTONUP:
		{
			// 0x0202
			//GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] 鼠标左键弹起 MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
		}
		break;
	case WM_PARENTNOTIFY:
		{
			// 0x0210
			switch (wParam)
			{
			case WM_LBUTTONDOWN:
				{
					// 获取当前鼠标坐标，判断在哪个子窗口范围内
					// 设置当前活跃窗口为该窗口，并绘制边框
					//int mouse_pos_x = GET_X_LPARAM(lParam);
					//int mouse_pos_y = GET_Y_LPARAM(lParam);
					int mouse_pos_x = GET_WM_PARENTNOTIFY_X(wParam, lParam);
					int mouse_pos_y = GET_WM_PARENTNOTIFY_Y(wParam, lParam);
					HWND disp_hwnd = GET_WM_PARENTNOTIFY_HWNDCHILD(wParam, lParam);

					GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] 在子窗口(%d)内鼠标左键按下，坐标：(%d, %d) MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", (int)disp_hwnd, mouse_pos_x, mouse_pos_y, msg, wParam, lParam);
				}
				break;
			default:
				{
					GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] 子窗口被建立,销毁 MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
				}
			}
		}
		break;
	//case MSG_PAINT_ACTIVE_FRAME:
	//	{
	//		// 取出索引
	//		int disp_hwnd = wParam;

	//		for (int index = 0; index < MAX_DISP_COUNT_EX; ++index)
	//		{
	//			// 
	//			if ()
	//			{
	//			}
	//		}
	//	}
	//	break;
	default:
		{
			//GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
		}
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}