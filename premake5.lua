workspace "ImApp"
    configurations { "Debug", "Release" }
    platforms { "Win64" }
    language "C++"
    cppdialect "C++17"

    filter "platforms:Win64"
        architecture "x86_64"

    filter "platforms:Win32"
        architecture "x86"

project "ImApp"
	kind "StaticLib"
	files { "src/**.h", "src/**.cpp" }
	targetdir "build/bin/%{cfg.buildcfg}-%{cfg.platform}"
	objdir "build/obj/%{cfg.buildcfg}-%{cfg.platform}"

    includedirs { "%{wks.location}/vendor/imgui", "%{wks.location}/vendor/glfw/include", "%{wks.location}/vendor/stb" }
    links { "imgui", "glfw", "opengl32" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		runtime "Release"
		optimize "On"
        symbols "Off"

group "Dependencies"
    include "vendor/scripts/imgui.lua"
    include "vendor/scripts/glfw.lua"
    
    

group "Example"
    include "example"