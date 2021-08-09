# Auto resolution changer

A light software to automatically change resolution when a program is run

## Usage
Create an `autores.json` file where the executable is launched containing the settings : 
```
{
    // This part is the resolution applied when no app is running and
    // is the default for programs where values are specified. 
    // if any field is omitted, it uses what was applied when this software was launched
    "width" : 3840,
    "height" : 2160,
    "frequency" : 60,

    "programs" : [
        // list of programs, the only mandatory field is "name".
        // "name" is a part of the the executable name (mpc-hc matches mpc-hc64.exe)
        {
            "name" : "acc",
            "width" : 2560,
            "height" : 1440,
            "frequency" : 120
        },
        {
            "name" : "mpc-hc",
            "frequency" : 24
        }
    ]
}
```  


## Build dependencies 

The project uses [jsoncpp](https://github.com/open-source-parsers/jsoncpp) as the json parser. To install in msys2 :  
> pacman -S mingw-w64-x86_64-jsoncpp

## Building  
The project uses [Premake5](https://premake.github.io). To generate the Makefile simply run :  
> premake5 gmake  

Then simply run :  
> make
