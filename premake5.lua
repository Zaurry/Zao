workspace "Zao"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Zao/vendor/glfw/include"

include "Zao/vendor/glfw"

project "Zao"
	location "Zao"
	kind "SharedLib"
	language "C++"
	
	links {
		"GLFW",
		"opengl32.lib", --for windows
	}

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "zpch.h"
	pchsource "Zao/src/zpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs { 
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "off" --Sets <RuntimeLibrary> to "MultiThreaded Debug DLL" 可以使程序体积会减小
		systemversion "latest"

		defines {
			"ZAO_BUILD_DLL",
			"ZAO_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines {"ZAO_DEBUG", "ZAO_ENABLE_ASSERTS"}
		symbols "On" --for debugging

	filter "configurations:Release"
		defines "ZAO_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ZAO_DIST"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp" 
	language "C++"

	links { "Zao" }

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	defines {
		"ZAO_PLATFORM_WINDOWS"
	}

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs { 
		"Zao/vendor/spdlog/include",
		"Zao/src"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On" --Sets <RuntimeLibrary> to "MultiThreaded"
		systemversion "latest"

		defines {
			"ZAO_PLATFORM_WINDOWS"
		}

		postbuildcommands {
			"{COPYFILE} ../bin/".. outputdir .. "/Zao/Zao.dll ../bin/".. outputdir .. "/Sandbox"  --wierd path :( don't need %[] to swap the path
		}

	filter "configurations:Debug"
		defines {"ZAO_DEBUG", "ZAO_ENABLE_ASSERTS"}
		symbols "On"

	filter "configurations:Release"
		defines "ZAO_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ZAO_DIST"
		optimize "On"


