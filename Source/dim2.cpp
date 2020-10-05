// Lic:
// Source/dim2.cpp
// dim2
// version: 20.10.06
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
#include <iostream>
#include <dim2.hpp>


namespace TrickyUnits {
	
	using namespace std;

	template<class t2dim>
	void dim2<t2dim>::Paniek(std::string msg) {
		if (!PanicDim2) {
			cout << "\x1b[31mERROR\x7\x1b[0m " << msg << "\n";
			exit(100);
		}
		PanicDim2(msg);
		exit(100);
	}
	template<class t2dim>
	inline dim2<t2dim>::dim2(int s1, int s2, bool autodispose) {
		siz1 = s1;
		siz2 = s2;
		suicidal = autodispose;
		TrueArray = new t2dim[siz1 * siz2];
	}

	template<class t2dim>
	dim2<t2dim>::dim2(int s1, int s2, t2dim cleanwithvalue, bool autodispose) {
		siz1 = s1;
		siz2 = s2;
		suicidal = autodispose;
		TrueArray = new t2dim[siz1 * siz2];
		for (int i = 0; i < siz1 * siz2; ++1) TrueArray[i] = cleanwithvalue;
	}

	template<class t2dim>
	dim2<t2dim>::~dim2() {
		if (suicidal) Dispose();
	}

	template<class t2dim>
	void dim2<t2dim>::Dispose() {
		if (TrueArray) delete[] TrueArray;
		TrueArray = NULL;
	}

	template<class t2dim>
	void dim2<t2dim>::Value(int d1, int d2, t2dim v) {
		if (d1 < 0 || d1 >= siz1) Paniek("Dimension #1 out of bounds!");
		if (d2 < 0 || d2 >= siz2) Paniek("Dimension #2 out of bounds!");
		TrueArray[d1 + (d2 * siz1)] = v;
	}

	template<class t2dim>
	t2dim dim2<t2dim>::Value(int d1, int d2) {
		if (d1 < 0 || d1 >= siz1) Paniek("Dimension #1 out of bounds!");
		if (d2 < 0 || d2 >= siz2) Paniek("Dimension #2 out of bounds!");
		return TrueArray[d1 + (d2 * siz1)];
	}

}