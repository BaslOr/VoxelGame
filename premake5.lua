workspace "VoxelGame"
    configurations {
        "Debug",
        "Release",
        "Dist"
    }

    startproject "VoxelGame"

    architecture "x64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Cubes/vendor/GLFW/include"
IncludeDir["glad"] = "Cubes/vendor/glad/include"
IncludeDir["ImGUI"] = "Cubes/vendor/ImGUI"
IncludeDir["glm"] = "Cubes/vendor/glm"

include "Cubes/vendor/GLFW"
include "Cubes/vendor/glad"
include "Cubes/vendor/ImGUI"

project "Cubes"
    location "Cubes"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on" 



    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "cbpch.h"
    pchsource "Cubes/src/Cubes/cbpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.ImGUI}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.glm}"
    }

    links {
        "GLFW",
        "glad",
        "ImGUI",
        "opengl32.lib"
    }

    filter "system:windows"
        characterset "Unicode"
        buildoptions {
            "/utf-8"
        }
        systemversion "latest"

        defines {
            "CB_PLATFORM_WINDOWS",
            "CB_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }
        
    filter "configurations:Debug"
        defines "CB_DEBUG"
        runtime "Debug"  
        symbols "on"

    filter "configurations:Release"
        defines "CB_RELEASE"
        runtime "Release" 
        optimize "on"

    filter "configurations:Dist"
        defines "CB_DIST"
        runtime "Release"
        optimize "on"

project "VoxelGame"
    location "VoxelGame"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"


    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Cubes/src",
        "Cubes/vendor/spdlog/include",
        "%{IncludeDir.ImGUI}",
        "Cubes/vendor/GLFW/include",
        "%{IncludeDir.glm}"
    }

    links {
        "Cubes"
    }

    filter "system:windows"
        systemversion "latest"
        characterset "Unicode"
        buildoptions {
            "/utf-8"
        }

        defines {
            "CB_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "CB_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "CB_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "CB_DIST"
        runtime "Release"
        optimize "on"
