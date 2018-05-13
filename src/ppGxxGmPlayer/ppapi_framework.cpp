#include "ppapi_framework.h"


void MyInstance::DidChangeView(const View& view)
{
	// 
}

void MyInstance::DidChangeView(const Rect& position, const Rect& clip)
{
	// 
}

void MyInstance::DidChangeFocus(bool has_focus)
{

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
	virtual pp::Instance* CreateInstance(PP_Instance instance) {
		return new MyInstance(instance);
	}
};

namespace pp {

	// Factory function for your specialization of the Module object.
	Module* CreateModule() {
		return new MyModule();
	}

}  // namespace pp