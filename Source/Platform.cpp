// Lic:
// Source/Platform.cpp
// Platform
// version: 20.11.14
// Copyright (C) 2020 Jeroen P. Broks
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
#include <string>


#ifdef __APPLE__
	#include <TargetConditionals.h>
#endif

namespace TrickyUnits{
	std::string Platform(bool g) {
		#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
			if (g) return "Windows";	
			#ifdef _WIN64
				return "Win64";
			#else
				return "Win32";
			#endif
		#elif __APPLE__
			if (g) return "Apple";			
			#if TARGET_IPHONE_SIMULATOR
				return "iPhone Simulator";         
			#elif TARGET_OS_IPHONE
				return "iPhone";
		    #elif TARGET_OS_MAC
				return "MacOS";        
			#else
				#   error "Unknown Apple platform"
			#endif
		#elif __linux__
			return "Linux";
		#elif __unix__ 
			return "Unix";
		#elif defined(_POSIX_VERSION)
			return "POSIX";
		#else
		#   error "Unknown compiler"
		#endif		
	}
}