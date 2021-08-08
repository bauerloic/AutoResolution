
#include <cstdint> 
#include <Windows.h>


static DEVMODEA DefaultSettings;

static void ResolutionChange(uint32_t width, uint32_t height, uint32_t frequency)
{
    DEVMODEA newSettings = DefaultSettings;

    newSettings.dmPelsWidth = width;
    newSettings.dmPelsHeight = height;
    newSettings.dmDisplayFrequency = frequency;
    
    ChangeDisplaySettingsA(&newSettings, 0);
}

int main(void)
{
    EnumDisplaySettingsA(NULL, ENUM_CURRENT_SETTINGS, &DefaultSettings);

    ResolutionChange(DefaultSettings.dmPelsWidth, DefaultSettings.dmPelsHeight, 120);

    Sleep(10000);
    
    ResolutionChange(DefaultSettings.dmPelsWidth, DefaultSettings.dmPelsHeight, DefaultSettings.dmDisplayFrequency);

    return 0;
}