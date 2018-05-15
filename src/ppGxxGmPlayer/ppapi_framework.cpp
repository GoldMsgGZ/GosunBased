#include "ppapi_framework.h"
#include "..\GxxGmPlayBase\GxxGmPlayBase.h"


void MyInstance::DidChangeView(const pp::View& view)
{
	pp::Rect view_rect = view.GetRect();
	GxxGmPlayBase::DebugStringOutput("[ppGxxGmPlayer.dll] MyInstance::DidChangeView(const pp::View& view) 接口被调用，view_rect=(%d, %d, %d, %d)\n", view_rect.x(), view_rect.y(), view_rect.width(), view_rect.height());
}

void MyInstance::DidChangeView(const pp::Rect& position, const pp::Rect& clip)
{
	GxxGmPlayBase::DebugStringOutput("[ppGxxGmPlayer.dll] MyInstance::DidChangeView(const pp::Rect& position, const pp::Rect& clip) 接口被调用，position=(%d, %d, %d, %d), clip=(%d, %d, %d, %d)\n",
		position.x(), position.y(), position.width(), position.height(), clip.x(), clip.y(), clip.width(), clip.height());
}

void MyInstance::DidChangeFocus(bool has_focus)
{
	GxxGmPlayBase::DebugStringOutput("[ppGxxGmPlayer.dll] MyInstance::DidChangeFocus(bool has_focus) 接口被调用，has_focus = %s\n", has_focus ? "true" : "false");
}

bool MyInstance::HandleInputEvent(const pp::InputEvent& event)
{
	char dbgmsg[4096] = {0};

	PP_InputEvent_Type event_type = event.GetType();
	PP_TimeTicks event_time = event.GetTimeStamp();
	uint32_t event_modifiers = event.GetModifiers();

	switch (event_type)
	{
	case PP_INPUTEVENT_TYPE_UNDEFINED:
		break;
	case PP_INPUTEVENT_TYPE_MOUSEDOWN:
		{
			// 鼠标按下
			pp::MouseInputEvent mouse_event(event);	

			PP_InputEvent_MouseButton mouse_button = mouse_event.GetButton();	// 获取鼠标按下的具体是哪个案件
			int32_t mouse_click_count = mouse_event.GetClickCount();			// 获取鼠标按下的次数
			pp::Point mouse_point = mouse_event.GetPosition();					// 获取鼠标位置

			sprintf_s(dbgmsg, 4096, "鼠标按下, mouse_button:%d, mouse_click_count:%d, mouse_point:(%d, %d)\n", mouse_button, mouse_click_count, mouse_point.x(), mouse_point.y());
		}
		break;
	case PP_INPUTEVENT_TYPE_MOUSEUP:
		{
			// 鼠标弹起
		}
		break;
	case PP_INPUTEVENT_TYPE_MOUSEMOVE:
		{
			// 鼠标移动
		}
		break;
	case PP_INPUTEVENT_TYPE_MOUSEENTER:
		{
			// 鼠标进入
		}
		break;
	case PP_INPUTEVENT_TYPE_MOUSELEAVE:
		{
			// 鼠标移出
		}
		break;
	case PP_INPUTEVENT_TYPE_WHEEL:
		{
			// 滚轮滚动
		}
		break;
	case PP_INPUTEVENT_TYPE_RAWKEYDOWN:
		break;
	case PP_INPUTEVENT_TYPE_KEYDOWN:
		{
			// 键盘按下
		}
		break;
	case PP_INPUTEVENT_TYPE_KEYUP:
		{
			// 键盘弹起
		}
		break;
	case PP_INPUTEVENT_TYPE_CHAR:
		{
			// 输入字符
		}
		break;
	case PP_INPUTEVENT_TYPE_CONTEXTMENU:
		break;
	case PP_INPUTEVENT_TYPE_IME_COMPOSITION_START:
		break;
	case PP_INPUTEVENT_TYPE_IME_COMPOSITION_UPDATE:
		break;
	case PP_INPUTEVENT_TYPE_IME_COMPOSITION_END:
		break;
	case PP_INPUTEVENT_TYPE_IME_TEXT:
		break;
	case PP_INPUTEVENT_TYPE_TOUCHSTART:
		break;
	case PP_INPUTEVENT_TYPE_TOUCHMOVE:
		break;
	case PP_INPUTEVENT_TYPE_TOUCHEND:
		break;
	case PP_INPUTEVENT_TYPE_TOUCHCANCEL:
		break;
	default:
		break;
	}

	GxxGmPlayBase::DebugStringOutput("[ppGxxGmPlayer.dll] MyInstance::HandleInputEvent(const pp::InputEvent& event) 接口被调用，event_type:%d, event_time:%f, event_modifiers:%d\n", event_type, event_time, event_modifiers);
	return true;
}

// HandleMessage gets invoked when postMessage is called on the DOM element
// associated with this plugin instance.
// In this case, if we are given a string, we'll post a message back to
// JavaScript indicating whether or not that string is a palindrome.
void MyInstance::HandleMessage(const pp::Var& message_data) {
	if (message_data.is_string()) {
		std::string string_copy(message_data.AsString());
		std::reverse(string_copy.begin(), string_copy.end());
		bool is_palindrome(message_data.AsString() == string_copy);

		if (is_palindrome)
		{
			GxxGmPlayBase::DebugStringOutput("[ppGxxGmPlayer.dll] 接收到页面传入的数据：%s\n", string_copy.c_str());
		}

		PostMessage(pp::Var(is_palindrome));
	}
}

// This object is the global object representing this plugin library as long
// as it is loaded.
class MyModule : public pp::Module {
public:
	MyModule() : pp::Module() {}
	virtual ~MyModule() {}

	// Override CreateInstance to create your customized Instance object.
	// 重载CreateInstance()接口，用于创建我们自己的实例对象
	virtual pp::Instance* CreateInstance(PP_Instance instance) {
		pp::Instance *inst = new MyInstance(instance);
		if (inst == NULL)
			GxxGmPlayBase::DebugStringOutput("[ppGxxGmPlayer.dll] 创建插件实例失败！\n");
		else
			GxxGmPlayBase::DebugStringOutput("[ppGxxGmPlayer.dll] 创建插件实例成功！实例句柄：%d\n", instance);

		return inst;
	}
};

namespace pp {

	// Factory function for your specialization of the Module object.
	// 工厂函数，Chrome浏览器会调用此接口创建ppapi模块对象
	Module* CreateModule() {
		return new MyModule();
	}

}  // namespace pp