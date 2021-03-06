-- premake5.lua
workspace "AutoResolution"
    configurations { "Debug" }

project "AutoResolution"
    kind "WindowedApp"
    language "C++"
    location "%{wks.location}"
    targetdir "%{wks.location}"
    objdir "build/%{cfg.buildcfg}/obj"
    

    filter "Debug"
        symbols "On"
        defines { "DEBUG" }
   
    filter {}

    defines { 
    }

    files { 
        "src/main.cpp", 
        "src/settings.cpp", 
    }

    includedirs { "src/",
                    }

    buildoptions {
        "-Wall -fno-exceptions"
    }

    linkoptions {
        "-lUser32 -lKernel32 -static-libstdc++ -static-libgcc -static -lpthread"
    }

    links {
        "jsoncpp"
    }
