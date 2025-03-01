#pragma once
#include "Core.h"

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

