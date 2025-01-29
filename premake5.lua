workspace "VoxelGame"
    configurations {
        "Debug",
        "Release",
        "Dist"
    }

    startproject "VoxelGame"

    architecture "x64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Cubes"
    location "Cubes"
    kind "SharedLib"
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
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
            symbols "On"

        filter "configurations:Release"
            defines "CB_RELEASE"
            optimize "On"

        filter "configurations:Dist"
            defines "CB_DIST"
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
        "Cubes/vendor/spdlog/include"
    }

    links "Cubes"

    filter "system:windows"
        cppdialect  "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "CB_PLATFORM_WINDOWS"
        }

        filter "configurations:Debug"
            defines "CB_DEBUG"
            symbols "On"

        filter "configurations:Release"
            defines "CB_RELEASE"
            optimize "On"

        filter "configurations:Dist"
            defines "CB_DIST"
            optimize "On"