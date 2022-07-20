workspace "MScProject"
    configurations{"Debug", "Release"}
    startproject "MScProject"

    filter "configurations:Debug"
        defines {"DEBUG", "DEBUG_SHADER"}
        symbols "On"

    filter "configurations:Release"
        defines {"RELEASE"}
        optimize "Speed"
        flags { "LinkTimeOptimization" }

project "MScProject"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++11"
        architecture "x86_64"
    
    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    sysincludedirs{"Include/", "libs/glad/include/", "libs/glfw/include/","libs/glm/", "libs/imgui/"}

    files {"Source/**.cpp"}
    files {"Shader/*.vert", "Shader/*.frag"}
    files {"Include/**.hpp"}

    links {"GLFW", "GLM", "GLAD", "ImGui"}

    filter {"system:Linux", "action:gmake"}
        links {"dl", "X11", "pthread"}
    

    filter {"system:windows", "action:vs2022"}
        flags         { "MultiProcessorCompile", "NoMinimalRebuild" }
        linkoptions   { "/ignore:4099" }      -- Ignore library pdb warnings when running in debug


    filter {"system:macosx", "action:xcode4"}
        toolset "clang"

        links { "IOKit.framework",
                "Cocoa.framework",
                "CoreFoundation.framework",
                "OpenGL.framework",
                "SystemConfiguration.framework",
                "CoreVideo.framework" }


    filter {}

include "libs/glfw.lua"
include "libs/glad.lua"
include "libs/glm.lua"
include "libs/imgui.lua"