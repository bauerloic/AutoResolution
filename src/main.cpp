
#include <stdint.h> 
#include <string.h>
#include <iostream>

#include <windows.h>

#include "settings.h"

static DEVMODEW DefaultSettings;

static void ResolutionChange(const resolution& res)
{
    DEVMODEW newSettings = DefaultSettings;

    newSettings.dmPelsWidth = res.width;
    newSettings.dmPelsHeight = res.height;
    newSettings.dmDisplayFrequency = res.frequency;

    std::cout << "Setting " << res.width << 'x' << res.height << '@' << res.frequency << std::endl<< std::endl; 
    
    ChangeDisplaySettingsW(&newSettings, 0);
}

int main(void)
{
    DefaultSettings.dmSize = sizeof(DefaultSettings);
    EnumDisplaySettingsW(NULL, ENUM_CURRENT_SETTINGS, &DefaultSettings);

    settings s(DefaultSettings);
    s.readJson("autores.json");
    resolution default_res = s.getDefaultResolution();

    while(true)
    {
        ResolutionChange(default_res);

        const program* pRunning;
        while((pRunning = s.getCurrent()) == NULL)
            SleepEx(1000, FALSE);

        const resolution& res = pRunning->getResolution();

        std::cout << pRunning->getName()<< " running\n";

        ResolutionChange(res);

        while(pRunning->isRunning())
            SleepEx(1000, FALSE);

        std::cout << pRunning->getName()<< " quit\n";
    }

    return 0;
}