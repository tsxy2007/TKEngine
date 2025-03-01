#pragma once
#ifdef TK_PLATFORM_WINDOWS
extern TK::Application* TK::CreateApplication(); 
int main()
{
	TK::Log::Init();
	TK_CORE_INFO("TKEngine Initialize!");
	TK::Application* app = TK::CreateApplication(); 
	app->Run();
	delete app; 
}

#else
#error TK only support Windows!
#endif // TK_PLATFORM_WINDOW
