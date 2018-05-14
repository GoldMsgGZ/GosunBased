#include "Plugin.h"
#include <windowsX.h>
#include "npruntime.h"


CPlugin *global_plugin_ = NULL;

static NPObject *sWindowObj;

//////////////////////////////////////////////////////////////////////////
//
// ����ʵ���ĸ�����
// ���ĸ���������pluginbase.h(81)���ж���
// 
// ���º�����Ҫ��ÿ��ָ���Ĳ���б�ʵ��
// �����Ǵ��������ٻ������������Ķ���
//
//		nsPluginInstanceBase * NS_NewPluginInstance(nsPluginCreateData * aCreateDataStruct);
//		void NS_DestroyPluginInstance(nsPluginInstanceBase * aPlugin);
//
// ȫ�ֲ����ʼ��������
// 
//		NPError NS_PluginInitialize();
//		void NS_PluginShutdown();
// 

NPError NS_PluginInitialize()
{
	// ����ɶ������
	// ���������ʵ��Ӧ�ò��ǵ����Ŀպ���
	return NPERR_NO_ERROR;
}

void NS_PluginShutdown()
{
	// ����ɶ������
}

nsPluginInstanceBase * NS_NewPluginInstance(nsPluginCreateData * aCreateDataStruct)
{
	if(!aCreateDataStruct)
		return NULL;

	global_plugin_ = new CPlugin(aCreateDataStruct->instance);

	// NPAPIĬ�ϴ�������Windowed���
	// ����Ҫ����winless���������Ҫ�� bWindowed �ֶ�����Ϊ FALSE
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
// ���ﴦ����JavaScript�����Ĳ���

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
// NPAPI ����� Javascript �����ӿڶ���

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
//	MessageBox(NULL, "�ȴ����������", "����", 0);
//#endif
	// ���������ӿ�ӳ��
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
				// �ҵ���Ӧ�Ĵ�����
				// �������Ե�ʱ�򣬹̶���һ��������ȥ����������
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
	// ����������ĵ���
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
					// ���ﴦ��Js���ò���Ľӿ�
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
// �������ľ���ʵ��

// ��Ϣ��Ӧ����
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
	GxxGmPlayBase::DebugStringOutput("����һ���������\n");
	NPN_GetValue(m_pNPInstance, NPNVWindowNPObject, &sWindowObj);

	// ���ﶨ��������ŵĽӿ�
}

CPlugin::~CPlugin(void)
{
	// �ͷ�Js����
	GxxGmPlayBase::DebugStringOutput("�ͷ�һ���������\n");
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

	// ���������໯�������Ϳ��Զ���Ϣ���д������ڴ����л�����
	lpOldProc = (WNDPROC)SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LPARAM)(WNDPROC)PluginWinProc);

	// �������� Plugin ��������������Ϳ����ٴ��ڴ����з��� Plugin ������
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
	// ����������ָ��
	m_Window = pNPWindow;
	return NPERR_NO_ERROR;
}

NPObject * CPlugin::GetScriptableObject()
{
	// ��������� NPObject �������½�һ��
	if (!m_pScriptableObject) {
		m_pScriptableObject = NPN_CreateObject(m_pNPInstance, GET_NPOBJECT_CLASS(ScriptablePluginObject));
	}

	// ��ȡ����ֵ
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
			GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] ���� MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
			// ��������Ҫ����������ΪRGB(25,25,25)
			// global_plugin_->DrawBkColor(hWnd);
		}
		break;
	case WM_ERASEBKGND:
		{
			// 0x0014
			// �����ڱ������뱻����ʱ (����,���ڵ��ƶ�,���ڵĴ�С�ĸı�)�ŷ���
			//GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] ���ڱ������뱻���� MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
			//global_plugin_->DrawBkColor(hWnd);
		}
		break;
	case WM_SHOWWINDOW:
		{
			// 0x0018
			// ��������ʾ������Ϣ
			GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] ��ʾ���� MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
		}
		break;
	case WM_SETCURSOR:
		{
			// 0x0020
			//GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] ���ù��λ�� MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
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
			GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] �����Ӵ��� MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
		}
		break;
	case WM_WINDOWPOSCHANGING:
		{
			// 0x0046
			GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] ����λ�ø��� MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
			global_plugin_->DrawBkColor(hWnd);
		}
		break;
	case WM_NCHITTEST:
		{
			// 0x0084
			// ������ƶ���������������ʱ�򷢳�
			//GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] ����ƶ����� MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
		}
		break;
	case WM_NCPAINT:
		{
			// 0x0085
			//GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] ���ƿͻ�����������(������������˵�����) MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
		}
		break;
	case WM_CTLCOLORSTATIC:
		{
			// 0x0138
			//GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] ��̬�ؼ���ɫ���� MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
		}
		break;
	case WM_MOUSEMOVE:
		{
			// 0x0200
			//GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] ����ƶ� MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);

			// ��ȡ��ǰ������꣬�ж����ĸ��Ӵ��ڷ�Χ��
		}
		break;
	case WM_LBUTTONDOWN:
		{
			// 0x0201
			GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] ���������� MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
			
			
		}
		break;
	case WM_LBUTTONUP:
		{
			// 0x0202
			//GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] ���������� MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
		}
		break;
	case WM_PARENTNOTIFY:
		{
			// 0x0210
			switch (wParam)
			{
			case WM_LBUTTONDOWN:
				{
					// ��ȡ��ǰ������꣬�ж����ĸ��Ӵ��ڷ�Χ��
					// ���õ�ǰ��Ծ����Ϊ�ô��ڣ������Ʊ߿�
					//int mouse_pos_x = GET_X_LPARAM(lParam);
					//int mouse_pos_y = GET_Y_LPARAM(lParam);
					int mouse_pos_x = GET_WM_PARENTNOTIFY_X(wParam, lParam);
					int mouse_pos_y = GET_WM_PARENTNOTIFY_Y(wParam, lParam);
					HWND disp_hwnd = GET_WM_PARENTNOTIFY_HWNDCHILD(wParam, lParam);

					GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] ���Ӵ���(%d)�����������£����꣺(%d, %d) MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", (int)disp_hwnd, mouse_pos_x, mouse_pos_y, msg, wParam, lParam);
				}
				break;
			default:
				{
					GxxGmPlayBase::DebugStringOutput("[npGxxGmPlayer MESSAGE] �Ӵ��ڱ�����,���� MSG:0x%04x, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
				}
			}
		}
		break;
	//case MSG_PAINT_ACTIVE_FRAME:
	//	{
	//		// ȡ������
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