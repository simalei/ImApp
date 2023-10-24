project "Example-App"
    kind "ConsoleApp"
    files {
        "src/*.cpp",
        "src/*.h"
    }
    links { "ImApp" }
    includedirs { "../../ImApp/src", "%{wks.location}/vendor/imgui" }

	targetdir "../build/bin/%{cfg.buildcfg}-%{cfg.platform}"
	objdir "../build/obj/%{cfg.buildcfg}-%{cfg.platform}"
    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        runtime "Release"
        optimize "On"
        symbols "Off"