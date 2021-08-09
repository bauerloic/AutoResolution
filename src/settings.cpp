
#include <fstream> 
#include <iostream>

#include <windows.h>
#include <tlhelp32.h>

#include "settings.h"

#include <json/json.h>



static bool IsProcessRunning(const char *processName);
static void setResolution(resolution&, uint32_t width, uint32_t height, uint32_t frequency);

settings::settings(const DEVMODEW& currentSettings)
{
    base.width = currentSettings.dmPelsWidth;
    base.height = currentSettings.dmPelsHeight;
    base.frequency = currentSettings.dmDisplayFrequency;
}

void settings::readJson(const char* filename)
{
    programs.clear();

    // open the file
    std::ifstream file;
    file.open(filename);

    if (!file.is_open())
    {
        std::cout << "Could not open " << filename<< std::endl;
        return;
    }

    std::cout << "Parsing " << filename<< std::endl;
    
    // parse the json
    Json::Value j_root;
    file >> j_root;

    uint32_t width = j_root.get("width", 0).asUInt();
    uint32_t height = j_root.get("height", 0).asUInt();
    uint32_t frequency = j_root.get("frequency", 0).asUInt();

    std::cout << "Default settings:\n"; 

    setResolution(base, width, height, frequency);

    std::cout << std::endl;


    const Json::Value j_programs = j_root["programs"];
    
    for ( uint32_t i = 0; i < j_programs.size(); i++ ) {

        std::string name = j_programs[i].get("name", "null").asString();

        if (name != "null"){
            resolution new_res = base;
            std::cout << name << ":\n"; 
            
            width = j_programs[i].get("width", 0).asUInt();
            height = j_programs[i].get("height", 0).asUInt();
            frequency = j_programs[i].get("frequency", 0).asUInt();

            setResolution(new_res, width, height, frequency);

            std::cout << std::endl;
            program new_program(name.c_str(), new_res);
            programs.push_back(new_program);
        }
    }
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


static void setResolution(resolution& res, uint32_t width, uint32_t height, uint32_t frequency)
{
    if (width) {
        res.width = width;
        std::cout << "\tWidth : "<< width<<std::endl;
    }
    if (height) {
        res.height = height;
        std::cout << "\tHeight : "<< height<<std::endl;
    }
    if (frequency) {
        res.frequency = frequency;
        std::cout << "\tFrequency : "<< frequency<<std::endl;
    }
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


