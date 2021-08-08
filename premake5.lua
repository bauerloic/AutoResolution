-- premake5.lua
workspace "AutoResolution"
    configurations { "Debug" }

project "AutoResolution"
    kind "ConsoleApp"
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
    }

    includedirs { "src/",
                    }

    buildoptions {
        "-Wall -fno-exceptions"
    }

    linkoptions {
        "-lUser32"
    }

    links {
    }
