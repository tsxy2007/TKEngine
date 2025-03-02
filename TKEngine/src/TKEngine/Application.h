#pragma once
#include "Core.h"
#include "Events/Event.h"

namespace TK
{
	class TK_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	Application* CreateApplication(); 
}

