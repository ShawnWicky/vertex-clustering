project "tinyobjloader"
    kind "StaticLib"
    language "C++"
    cppdialect "C++11"
        architecture "x86_64"

    targetdir "../bin/%{cfg.buildcfg}"
	objdir "../obj/%{cfg.buildcfg}"

    sysincludedirs {"libs/tinyobjloader/"}

    files
    {
        "tinyobjloader/tiny_obj_loader.h",
        "tinyobjloader/tiny_obj_loader.cc"
    }

    filter "system:macosx"
    systemversion "latest"
    staticruntime "On"


filter "system:linux"
    pic "On"

    systemversion "latest"
    staticruntime "On"


filter "system:windows"
    systemversion "latest"
    staticruntime "On"

filter "configurations:Debug"
    runtime "Debug"
    symbols "on"

filter "configurations:Release"
    runtime "Release"
    optimize "on"