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

include "Cubes/vendor/GLFW"

project "Cubes"
    location "Cubes"
    kind "SharedLib"
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "cbpch.h"
    pchsource "Cubes/src/Cubes/Utility/cbpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}"
    }

    links {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        characterset "Unicode"
        staticruntime "Off" 
        buildoptions {
            "/utf-8"
        }
        systemversion "latest"

        defines {
            "CB_PLATFORM_WINDOWS",
            "CB_BUILD_DLL",
        }

        postbuildcommands {
            "{COPYFILE} %{cfg.buildtarget.abspath} \"../bin/" .. outputdir .. "/VoxelGame/Cubes.dll\""
        }
        
    filter "configurations:Debug"
        defines "CB_DEBUG"
        runtime "Debug"  
        symbols "On"

    filter "configurations:Release"
        defines "CB_RELEASE"
        runtime "Release" 
        optimize "On"

    filter "configurations:Dist"
        defines "CB_DIST"
        runtime "Release"
        optimize "On"

project "VoxelGame"
    location "VoxelGame"
    kind "ConsoleApp"
    language "C++"

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
        "Cubes/vendor/GLFW/include"
    }

    links {
        "Cubes"
    }

    libdirs {
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
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
        symbols "On"

    filter "configurations:Release"
        defines "CB_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "CB_DIST"
        runtime "Release"
        optimize "On"
