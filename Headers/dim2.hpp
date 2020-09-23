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


