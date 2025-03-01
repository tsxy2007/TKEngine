#include "TK.h"

class SandboxApp : public TK::Application
{
public:
	SandboxApp()
	{

	}

	~SandboxApp()
	{

	}
};

TK::Application* TK::CreateApplication()
{
	return new SandboxApp();
}