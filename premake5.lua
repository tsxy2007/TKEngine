workspace "TKEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "TKEngine"
	location "TKEngine"
	kind "SharedLib"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"TK_PLATFORM_WINDOWS",
			"TK_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "TK_DEBUG"
		buildoptions "/utf-8"
		symbols "On"

	filter "configurations:Release"
		defines "TK_RELEASE"
		buildoptions "/utf-8"
		optimize "On"

	filter "configurations:Dist"
		defines "TK_DIST"
		buildoptions "/utf-8"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"TKEngine/vendor/spdlog/include",
		"TKEngine/src"
	}

	links
	{
		"TKEngine"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"TK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "TK_DEBUG"
		buildoptions "/utf-8"
		symbols "On"

	filter "configurations:Release"
		defines "TK_RELEASE"
		buildoptions "/utf-8"
		optimize "On"

	filter "configurations:Dist"
		defines "TK_DIST"
		buildoptions "/utf-8"
		optimize "On"