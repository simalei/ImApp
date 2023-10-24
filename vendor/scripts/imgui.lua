project "imgui"
	kind "StaticLib"
	targetdir "%{wks.location}/build/vendor/%{prj.name}/bin"
	objdir "%{wks.location}/build/vendor/%{prj.name}/obj"
	includedirs { "../imgui", "../glfw/include", "../imgui/misc/cpp" }
	files
	{
		"../imgui/*.h",
		"../imgui/*.cpp",
		"../imgui/backends/imgui_impl_glfw.cpp",
		"../imgui/backends/imgui_impl_glfw.h",
		"../imgui/backends/imgui_impl_opengl2.cpp",
		"../imgui/backends/imgui_impl_opengl2.h",
        "../imgui/misc/cpp/*.cpp",
        "../imgui/misc/cpp/*.h"
	}
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		symbols "Off"