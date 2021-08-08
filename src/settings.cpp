#include "settings.h"

#include <tlhelp32.h>

static bool IsProcessRunning(const char *processName);

settings::settings(const DEVMODEW& currentSettings)
{
    base.width = currentSettings.dmPelsWidth;
    base.height = currentSettings.dmPelsHeight;
    base.frequency = currentSettings.dmDisplayFrequency;
}

void settings::readJson(const char* filename)
{
    programs.clear();


}


const program* settings::getCurrent(void) const 
{
    for (std::vector<program>::const_iterator it = programs.begin() ; it != programs.end(); it++)
    {
        if (it->isRunning())
        {
            return it.base();
        }
    }
    return NULL;
}

bool program::isRunning(void) const
{
    return IsProcessRunning(exec.c_str());
}










/*!
\note From https://stackoverflow.com/questions/1591342/c-how-to-determine-if-a-windows-process-is-running/14751302#14751302
\brief Check if a process is running
\param [in] processName Name of process to check if is running
\returns \c True if the process is running, or \c False if the process is not running
*/
static bool IsProcessRunning(const char *processName)
{
    bool exists = false;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(snapshot, &entry))
        while (Process32Next(snapshot, &entry))
            if (strstr(entry.szExeFile, processName))
                exists = true;

    CloseHandle(snapshot);
    return exists;
}


