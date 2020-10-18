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
