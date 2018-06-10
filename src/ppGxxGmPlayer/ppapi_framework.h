#ifndef _ppapi_framework_H_
#define _ppapi_framework_H_

#include <algorithm>

#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"
#include "ppapi/cpp/input_event.h"

// When compiling natively on Windows, PostMessage can be #define-d to
// something else.
#ifdef PostMessage
#undef PostMessage
#endif

// This is a simple C++ Pepper plugin that demonstrates HandleMessage and
// PostMessage.

// This object represents one time the page says <embed>.
class MyInstance : public pp::Instance {
public:
	explicit MyInstance(PP_Instance instance)
		: pp::Instance(instance)
		, plugin_hwnd_(NULL)
	{}

	virtual ~MyInstance() {}
	 
public:
	virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]);
	virtual void DidChangeView(const pp::View& view);
	virtual void DidChangeView(const pp::Rect& position, const pp::Rect& clip);
	virtual void DidChangeFocus(bool has_focus);
	virtual bool HandleInputEvent(const pp::InputEvent& event);
	virtual void HandleMessage(const pp::Var& message_data);

public:
	HWND plugin_hwnd_;
};

#endif//_ppapi_framework_H_
 