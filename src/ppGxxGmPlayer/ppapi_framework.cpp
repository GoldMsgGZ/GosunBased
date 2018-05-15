#include "ppapi_framework.h"
#include "..\GxxGmPlayBase\GxxGmPlayBase.h"


void MyInstance::DidChangeView(const pp::View& view)
{
	pp::Rect view_rect = view.GetRect();
	GxxGmPlayBase::DebugStringOutput("[ppGxxGmPlayer.dll] MyInstance::DidChangeView(const pp::View& view) �ӿڱ����ã�view_rect=(%d, %d, %d, %d)\n", view_rect.x(), view_rect.y(), view_rect.width(), view_rect.height());
}

void MyInstance::DidChangeView(const pp::Rect& position, const pp::Rect& clip)
{
	GxxGmPlayBase::DebugStringOutput("[ppGxxGmPlayer.dll] MyInstance::DidChangeView(const pp::Rect& position, const pp::Rect& clip) �ӿڱ����ã�position=(%d, %d, %d, %d), clip=(%d, %d, %d, %d)\n",
		position.x(), position.y(), position.width(), position.height(), clip.x(), clip.y(), clip.width(), clip.height());
}

void MyInstance::DidChangeFocus(bool has_focus)
{
	GxxGmPlayBase::DebugStringOutput("[ppGxxGmPlayer.dll] MyInstance::DidChangeFocus(bool has_focus) �ӿڱ����ã�has_focus = %s\n", has_focus ? "true" : "false");
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
			// ��갴��
			pp::MouseInputEvent mouse_event(event);	

			PP_InputEvent_MouseButton mouse_button = mouse_event.GetButton();	// ��ȡ��갴�µľ������ĸ�����
			int32_t mouse_click_count = mouse_event.GetClickCount();			// ��ȡ��갴�µĴ���
			pp::Point mouse_point = mouse_event.GetPosition();					// ��ȡ���λ��

			sprintf_s(dbgmsg, 4096, "��갴��, mouse_button:%d, mouse_click_count:%d, mouse_point:(%d, %d)\n", mouse_button, mouse_click_count, mouse_point.x(), mouse_point.y());
		}
		break;
	case PP_INPUTEVENT_TYPE_MOUSEUP:
		{
			// ��굯��
		}
		break;
	case PP_INPUTEVENT_TYPE_MOUSEMOVE:
		{
			// ����ƶ�
		}
		break;
	case PP_INPUTEVENT_TYPE_MOUSEENTER:
		{
			// ������
		}
		break;
	case PP_INPUTEVENT_TYPE_MOUSELEAVE:
		{
			// ����Ƴ�
		}
		break;
	case PP_INPUTEVENT_TYPE_WHEEL:
		{
			// ���ֹ���
		}
		break;
	case PP_INPUTEVENT_TYPE_RAWKEYDOWN:
		break;
	case PP_INPUTEVENT_TYPE_KEYDOWN:
		{
			// ���̰���
		}
		break;
	case PP_INPUTEVENT_TYPE_KEYUP:
		{
			// ���̵���
		}
		break;
	case PP_INPUTEVENT_TYPE_CHAR:
		{
			// �����ַ�
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

	GxxGmPlayBase::DebugStringOutput("[ppGxxGmPlayer.dll] MyInstance::HandleInputEvent(const pp::InputEvent& event) �ӿڱ����ã�event_type:%d, event_time:%f, event_modifiers:%d\n", event_type, event_time, event_modifiers);
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
			GxxGmPlayBase::DebugStringOutput("[ppGxxGmPlayer.dll] ���յ�ҳ�洫������ݣ�%s\n", string_copy.c_str());
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
	// ����CreateInstance()�ӿڣ����ڴ��������Լ���ʵ������
	virtual pp::Instance* CreateInstance(PP_Instance instance) {
		pp::Instance *inst = new MyInstance(instance);
		if (inst == NULL)
			GxxGmPlayBase::DebugStringOutput("[ppGxxGmPlayer.dll] �������ʵ��ʧ�ܣ�\n");
		else
			GxxGmPlayBase::DebugStringOutput("[ppGxxGmPlayer.dll] �������ʵ���ɹ���ʵ�������%d\n", instance);

		return inst;
	}
};

namespace pp {

	// Factory function for your specialization of the Module object.
	// ����������Chrome���������ô˽ӿڴ���ppapiģ�����
	Module* CreateModule() {
		return new MyModule();
	}

}  // namespace pp