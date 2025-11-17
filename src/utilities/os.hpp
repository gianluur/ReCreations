#pragma once

// === 1. Windows Detection and Headers ===
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || \
    defined(__TOS_WIN__) || defined(__WINDOWS__)
#define OS_WINDOWS

#if defined(_WIN64)
#define WINDOWS_64
#define OS_NAME "Windows 64-bit"
#else
#define WINDOWS_32
#define OS_NAME "Windows 32-bit"
#endif

// === Windows Headers ===
namespace windows {
// Keep macros local to this block
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <direct.h>    // Directory handling (_mkdir)
#include <fcntl.h>     // File control
#include <io.h>        // Low-level I/O (_open, _read, etc.)
#include <process.h>   // Process functions (_beginthread, _exec)
#include <windows.h>   // Core Win32 API
#include <winsock2.h>  // Sockets API
#include <ws2tcpip.h>  // TCP/IP extensions
}  // namespace windows

// === 2. POSIX-Compatible OS Detection and Headers ===
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__) || \
    defined(__gnu_linux__) || defined(__unix__) || defined(__unix)
#define OS_POSIX_COMPATIBLE

// --- Apple/macOS/iOS ---
#if defined(__APPLE__) || defined(__MACH__)
#define OS_MAC
#define OS_NAME "macOS"
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#define OS_IOS
#endif

// --- Linux ---
#elif defined(__linux__) || defined(__gnu_linux__)
#define OS_LINUX
#define OS_NAME "Linux"

// --- BSD variants ---
#elif defined(__FreeBSD__)
#define OS_FREEBSD
#define OS_NAME "FreeBSD"
#elif defined(__OpenBSD__)
#define OS_OPENBSD
#define OS_NAME "OpenBSD"
#else
#define OS_UNIX
#define OS_NAME "Unix"
#endif

// === POSIX Headers ===
#include <arpa/inet.h>   // Internet address manipulation
#include <dirent.h>      // Directory handling
#include <fcntl.h>       // File control flags
#include <netdb.h>       // Network DB lookups
#include <netinet/in.h>  // Internet address family
#include <pthread.h>     // POSIX threads
#include <sys/mman.h>    // Memory mapping
#include <sys/socket.h>  // Sockets
#include <sys/stat.h>    // File metadata
#include <sys/types.h>   // pid_t, size_t, etc.
#include <sys/wait.h>    // Process control
#include <unistd.h>      // Core POSIX I/O

// === 3. Unknown OS ===
#else
#define OS_UNKNOWN
#define OS_NAME "Unknown"
#endif
