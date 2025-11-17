// @file os.hpp

#pragma once

#ifndef RECREATION_ONLY
#include "utilities/os.hpp"
#endif

namespace os {
namespace io {}  // namespace io

namespace file {}  // namespace file

namespace directory {}  // namespace directory

namespace process {
int exit(const int code);
}  // namespace process

namespace thread {}  // namespace thread

namespace path {}  // namespace path

namespace env {}  // namespace env

namespace system {}  // namespace system

namespace network {}  // namespace network

namespace memory {}  // namespace memory

}  // namespace os

inline int os::process::exit(const int code) {
#ifndef RECREATION_ONLY
#if defined(OS_WINDOWS)
  ExitProcess(static_cast<UINT>(code));

#elif defined(OS_POSIX_COMPATIBLE)
  _exit(code);
#endif
#endif
}