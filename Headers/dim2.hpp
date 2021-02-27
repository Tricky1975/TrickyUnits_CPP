// Lic:
// Headers/dim2.hpp
// dim2
// version: 21.02.27
// Copyright (C) 2021 Jeroen P. Broks
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

namespace TrickyUnits {
	typedef void(*dim2panic) (std::string msg);

	dim2panic PanicDim2=NULL;

	template <class t2dim> class dim2 {
	private:
		dim2* TrueArray;
		int siz1;
		int siz2;
		bool suicidal;
		void Paniek(std::string msg);
	public:
		
		dim2(int s1, int s2, bool autodispose = false);
		dim2(int s1, int s2, t2dim cleanwithvalue, bool autodispose = false);
		~dim2();

		

		void Dispose();

		void Value(int d1, int d2, t2dim v);
		t2dim Value(int d1, int d2);

	};


}