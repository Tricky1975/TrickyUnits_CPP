// Lic:
// Headers/Platform.hpp
// Platform (header)
// version: 22.10.26
// Copyright (C) 2021, 2022 Jeroen P. Broks
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
// EndLic
#pragma once
#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define Tricky_Windows
#ifdef _WIN64
#define Tricky_Win64
#else
#define Tricky_Win32
#endif
#elif __APPLE__
#define Tricky_Apple
#if TARGET_IPHONE_SIMULATOR
#define Tricky_iPhone_Simulator
#elif TARGET_OS_IPHONE
#define Tricky_iPhone
#elif TARGET_OS_MAC
#define Tricky_MacOs
#else
#   error "Unknown Apple platform"
#endif
#elif __linux__
#define Tricky_Linux
#elif __unix__ 
#define Tricky_Unix
#elif defined(_POSIX_VERSION)
#define Tricky_POSIX
#else
#error "Unknown compiler"
#endif		



namespace TrickyUnits {
	std::string Platform(bool g=true);
}