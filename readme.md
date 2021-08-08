# Auto resolution changer

A light software to automatically change resolution when a program is run

## Usage
Create an `autores.json` file where the executable is launched containing the settings : 
```
{
    "width" : 3840,
    "height" : 2160,
    "frequency" : 60,

    "programs" : [
        {
            "name" : "acc",
            "width" : 3840,
            "height" : 2160,
            "frequency" : 120
        },
        {
            "name" : "mpc-hc",
            "width" : 1920,
            "height" : 1080,
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
