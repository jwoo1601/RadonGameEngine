-- Radon-Specific Configurations --
ProjectDir = "Projects";
IncludeDir = "Include";
SourceDir = "Source";
    PublicDir = "Public";
    PrivateDir = "Private";
ObjectDir = "Intermediate";
BinaryDir = "Binaries";
LibraryDir = "Libraries";

SourceExtensions = { "**.h", "**.cpp", "**.hpp", "**.inl" };

function AsPath(...)
    local args, pathString = {...}, "";

    for i, v in ipairs(args) do
        if i == 1 then
            pathString = v;
        else
            pathString = pathString .. "/" .. v;
        end
    end

    return pathString;
end

function ListSourceDir(projectName)
    local sourcePath = AsPath(SourceDir, projectName);
    --[[local publicSourcePath = AsPath(sourcePath, PublicDir)
    local privateSourcePath = AsPath(sourcePath, PrivateDir);]]--

    local fileList = { };
   --[[ for i, v in ipairs(SourceExtensions) do
        fileList[i] = AsPath(publicSourcePath, SourceExtensions[i]);
    end
    local SourceExtensionsSize = #SourceExtensions;
    for i, v in ipairs(SourceExtensions) do
        fileList[i + #SourceExtensions] = AsPath(privateSourcePath, SourceExtensions[i]);
    end ]]--

    for i, v in ipairs(SourceExtensions) do
        fileList[i] = AsPath(sourcePath, v);
    end

    return fileList;
end
-----------------------------------

workspace "Radon"

    configurations { "Debug", "Release" }
    platforms { "Win32", "Win64", "Mac", "Linux" }
    startproject "Launch"

    architecture "x86"

    BinaryPath = AsPath(BinaryDir, "%{prj.name}", "%{cfg.platform}", "%{cfg.buildcfg}");
    -- Binaries/Win32|Win64|Mac/Debug|Release
    targetdir (BinaryPath)
    targetprefix "Radon"
    -- Intermediate/Win32|Win64|Mac/Debug|Release
    objdir (ObjectDir)

    libdirs
    {
        AsPath(LibraryDir, "**")
    }

    includedirs
    {
        AsPath(SourceDir, "%{prj.name}", "**")
    }

    files (ListSourceDir "%{prj.name}")

    -- sets the current system as Windows if the target platform is Win32 or Win64
    filter "platforms:Win*"
        system "windows"
    -- sets the current system as Mac OS X if the target platform is Mac
    filter "platforms:Mac"
        system "macosx"

    -- removes Mac and Llinux from the target platforms if the current system is Windows
    filter "system:windows"
        removeplatforms { "Mac", "Linux" }
    -- removes Win32, Win64 and Linux from the current target platforms if the current system is Mac
    filter "system:macosx"
        removeplatforms { "Win*", "Linux" }
     -- removes Win32, Win64, and Mac from the target platforms if the current system is Linux
    filter "system:linux"
        removeplatforms { "Win*", "Mac" }
    
    -- sets the current architecture to x86 if the current platform is Win32
    filter "platforms:Win32"
        architecture "x86"
    -- sets the current architecture to x86_64 if the current platform is Win64
    filter "platforms:Win64"
        architecture "x64" --x86_64?

    -- sets debug macros
    filter "configurations:Debug"
        defines
        {
            "DEBUG=1",
            "RELEASE=0"
        }
        symbols "On"
    -- sets release macros
    filter "configurations:Release"
        defines
        {
            "DEBUG=0",
            "RELEASE=1"
        }
        optimize "On"

    -- sets binary type macros
    filter "kind:ConsoleApp"
        defines { "RADON_CONSOLE_APP" }
    filter "kind:WindowedApp"
        defines { "RADON_WINDOWED_APP" }
    filter "kind:SharedLib"
        defines { "RADON_SHARED_LIBRARY" }
    filter "kind:StaticLib"
        defines { "RADON_STATIC_LIBRARY" }


    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "10.0.17763.0"

        defines
        {
            "PLATFORM_WINDOWS"
        }

    filter "system:macosx"
        cppdialect "gnu++17"

        defines
        {
            "PLATFORM_MAC"
        }

    filter "system:linux"
        cppdialect "gnu++17"

        defines
        {
            "PLATFORM_LINUX"
        }

    
    project "Core"
        location (ProjectDir)
        kind "SharedLib"
        language "C++"

        includedirs
        {
            AsPath(LibraryDir, "**", IncludeDir ,"**"),
            -- Includes Radon/Launch
            AsPath(SourceDir, "Launch", "Public", "**")
        }

        --links { "" }

        -- Source/Core/** -> Source/**
        vpaths
        {
            [AsPath(SourceDir, "*")] = AsPath(SourceDir, "Core", "**");
        }

        defines
        {
            "RADON_CORE"
        }

        postbuildcommands
        {
            --(AsPath("{COPY} %{cfg.buildtarget.relpath} ../Binaries", BinaryPath))
        }


    project "Launch"
        language "C++"
        kind "WindowedApp"
        location (ProjectDir)

        includedirs
        {
            AsPath(LibraryDir, "**", IncludeDir ,"**"),
            -- Includes Radon/Core
            AsPath(SourceDir, "Core", PublicDir),
            AsPath(SourceDir, "Core", PublicDir, "**"),
        }

        links
        {
            -- Requires Radon/Core
            --"Core"
        }

        -- Source/Launch/** -> Source/**
        vpaths
        {
            [AsPath(SourceDir, "*")] = AsPath(SourceDir, "Launch", "**");
        }

        defines
        {
            "RADON_LAUNCH"
        }


    project "UnitTest"
        language "C++"
        kind "ConsoleApp"
        location (ProjectDir)

        removeconfigurations "Release"

        includedirs
        {
            AsPath(LibraryDir, "**", IncludeDir ,"**"),
            -- Includes Radon/Core
            AsPath(SourceDir, "Core", PublicDir),
            AsPath(SourceDir, "Core", PublicDir, "**"),
            -- Includes Radon/Launch
            AsPath(SourceDir, "Launch", PublicDir),
            AsPath(SourceDir, "Launch", PublicDir, "**"),
        }        

        links
        {
            "Core"
        }

        libdirs
        {
            AsPath(BinaryDir, "Core", "%{cfg.platform}", "%{cfg.buildcfg}")
        }

        -- Source/Core/** -> Source/**
        vpaths
        {
            [AsPath(SourceDir, "*")] = AsPath(SourceDir, "UnitTest", "**");
        }

        defines
        {
            "RADON_UNITTEST"
        }