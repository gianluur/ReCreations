// @file os.hpp

#pragma once

#include "utilities/types.h"

#ifndef RECREATION_ONLY
    #if defined(OS_WINDOWS)
        #include <windows.h>
    #elif defined(OS_LINUX) || defined(OS_UNIX) || defined(OS_APPLE)
        #include <unistd.h>
        #include <sys/types.h>
        #include <sys/stat.h>
        #include <fcntl.h>
    #endif
#endif

namespace os {
    namespace io {

    } // namespace io

    namespace file {

    } // namespace file

    namespace directory {

    } // namespace directory

    namespace process {
        int exit(const int code) {
            #ifndef RECREATION_ONLY
                #if defined(OS_WINDOWS)
                    ::ExitProcess(static_cast<UINT>(code));
                #else
                    ::_exit(code);
                #endif
            #endif
        }
    } // namespace process

    namespace thread {

    } // namespace thread

    namespace path {

    } // namespace path

    namespace env {

    } // namespace env

    namespace system {
        
    } // namespace system

    namespace network {

    } // namespace net

    namespace memory {

    } //namespace memory

} // namespace os