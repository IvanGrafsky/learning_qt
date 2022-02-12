#include "sysinfo.h"
#include <QtGlobal>

#ifdef Q_OS_LINUX
    #include <sysinfolinux.h>
#endif

SysInfo& SysInfo::instance(){
    #ifdef Q_OS_LINUX
        static SysInfoLinux singleton;
    #endif

    return singleton;
}

SysInfo::SysInfo()
{

}

SysInfo::~SysInfo()
{

}
