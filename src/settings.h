#include <string>
#include <vector>
#include <stdint.h>

#include <windows.h>

struct resolution {
    uint32_t width, height, frequency;
};

class program {
public:
    program(const char* _executable, const resolution& _res) : exec(_executable), res(_res) {}
    bool isRunning(void) const;
    const resolution& getResolution(void) const { return res;}
    const char* getName(void) const {return exec.c_str();}

private:
    std::string exec;
    resolution res;
};

class settings {
public:
    settings(const DEVMODEW&);

    void readJson(const char* filename);
    const program* getCurrent(void) const;
    const resolution& getDefaultResolution(void) const {return base;}

private:
    resolution base;
    std::vector<program> programs;
};