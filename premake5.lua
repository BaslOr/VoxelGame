workspace "Cubes"
    configurations {
        "Debug",
        "Release",
        "Dist"
    }

    startproject "Cubes Editor"

    architecture "x64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["spdlog"] = "Cubes/vendor/spdlog/include"
IncludeDir["GLFW"] = "Cubes/vendor/GLFW/include"
IncludeDir["glad"] = "Cubes/vendor/glad/include"
IncludeDir["ImGUI"] = "Cubes/vendor/ImGUI"
IncludeDir["glm"] = "Cubes/vendor/glm"
IncludeDir["stb_image"] = "Cubes/vendor/stb_image"
IncludeDir["tiny_obj_loader"] = "Cubes/vendor/tiny_obj_loader"
IncludeDir["entt"] = "Cubes/vendor/entt"

group "Dependencies"
include "Cubes/vendor/GLFW"
include "Cubes/vendor/glad"
include "Cubes/vendor/ImGUI"
include "Cubes/vendor/stb_image"
include "Cubes/vendor/tiny_obj_loader"
include "Cubes/vendor/entt"
group ""

project "Cubes"
    location "Cubes"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on" 


    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "cbpch.h"
    pchsource "Cubes/src/cbpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.ImGUI}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.tiny_obj_loader}",
        "%{IncludeDir.entt}"
    }

    links {
        "GLFW",
        "glad",
        "ImGUI",
        "opengl32.lib",
        "stb_image",
        "tiny_obj_loader"
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
        defines {
            "CB_DEBUG",
            "CB_DEBUG_UTILS"
        }
        runtime "Debug"  
        symbols "on"

    filter "configurations:Release"
        defines {
            "CB_RELEASE",
            "CB_DEBUG_UTILS"
        }
        runtime "Release" 
        optimize "on"

    filter "configurations:Dist"
        defines "CB_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
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
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.ImGUI}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.tiny_obj_loader}",
        "%{IncludeDir.entt}"
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
        defines {
            "CB_DEBUG",
            "CB_DEBUG_UTILS"
        }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines {
            "CB_RELEASE",
            "CB_DEBUG_UTILS"
        }
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "CB_DIST"
        runtime "Release"
        optimize "on"


project "Cubes Editor"
    location "Cubes Editor"
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
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.ImGUI}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.tiny_obj_loader}",
        "%{IncludeDir.entt}"
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
        defines {
            "CB_DEBUG",
            "CB_DEBUG_UTILS"
        }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines {
            "CB_RELEASE",
            "CB_DEBUG_UTILS"
        }
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "CB_DIST"
        runtime "Release"
        optimize "on"

