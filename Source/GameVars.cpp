// Lic:
// Source/GameVars.cpp
// Game Vars
// version: 21.01.13
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
/*
* 
* Below is an as literal as possible translation of my old GameVars module from BlitzMax to C++
* As a whole not important, but I need it for my LAURA II conversion.
* 
* Back in the day, this module saved me a lot of typing work, since maps in BlitzMax were a bit of a disaster (but I was glad they were possible at all, so let's not moan too much).
*/



// Strict
//Import brl.System
#include "../Headers/QuickString.hpp"
#include "../Headers/GameVars.hpp"
#include <map> //Import BRL.Map
#include <string>
#include <iostream> //Import BRL.StandardIO
//Import BRL.Retro
// Import tricky_units.MKL_Version

//MKL_Version "Tricky's Units - GameVars.bmx", "16.05.16"
//MKL_Lic     "Tricky's Units - GameVars.bmx", "ZLib License"

namespace TrickyUnits {

	//Private
	static std::map<std::string, std::string> GM_Ref{};
	// Global GM_REF : TMap    ' This variable should have the same referrence as the var you use in the game. Just create a map and register it with VarReg

	//Public


	/*
	bbdoc : Register a TMAP for the usage of the vars.If you don't need to do anything crazy just "New TMap" for a parameter suffices. This command needs to be executed before you can use this module at all!
	*/
	bool VarReg(std::map<std::string, std::string> V) { //Function VarReg(V : TMap)
	//If Not V
	//Notify "Cannot register a Null-value"
	//Return
	//EndIf
		GM_Ref = V;
		return true;
	}

	std::map<std::string, std::string>* ReffedVar() { return &GM_Ref; } // This is new, but as the pointer is very important, I think this MAY be the better way to go!

	/*
	bbdoc : Defines var
	*/
	void VarDef(std::string K, std::string V) {
		//If Not GM_Ref Return Notify("VarDef(~q" + k + "~q,~q" + V + "~q): Cannot define with Null For referrence")
		GM_Ref[K] = V;//MapInsert GM_REF, K, V
	}

	/*
	bbdoc : Shows value in var
	*/
	std::string VarCall(std::string K, bool Debug) {
		// If Not GM_Ref Return Notify("VarCall(~q" + K + "~q): Cannot call with Null For referrence")
		if (!GM_Ref.count(K)) {
			if (Debug) std::cout << "Key \"" << K << "\" doesn't exist!\n";
			return "";
		}
		auto Ret{ GM_Ref[K] };//Local Ret$ = String(MapValueForKey(GM_REF, K))
		if (Debug) {
			std::cout << "VARCALL(\"" << K << "\") = \"" << Ret << "\"\n";
			//If Not MapContains(GM_REF, K) Print "Please note that the key does not exist!"
		}
		return Ret;
	}

	/*
	bbdoc : Converts a string by substituting all found vars into their respective values
	*/
	std::string VarStr(std::string Str) {
		auto Ret{ Str };
		for (auto IT : GM_Ref) {// Local K$ = EachIn(MapKeys(GM_Ref))
			Ret = TReplace(Ret, IT.first, IT.second);
		}
		return Ret;
	}

	/*
		bbdoc : Clears everything
		*/
	void VarClearAll() {
		GM_Ref.clear();
	}

	/*
	bbdoc : Removes var
	*/
	void VarClear(std::string K) {
		GM_Ref.erase(K); //MapRemove GM_Ref, K
	}

		/*
		bbdoc : List of all vars for use with EachIn
		*/
	std::vector<std::string> Vars() { //Function Vars : TMapEnumerator()
		std::vector<std::string> ret;
		for (auto IT : GM_Ref) ret.push_back(IT.first);
		return ret; //MapKeys(GM_Ref)
	}

		/*
		Returns : Returns the registered var map in case you need it		
		Function VarMap : TMap()
		Return GM_Ref
		End Function
		*/

		/*
		bbdoc : Counts all variables we got now
		returns : The exact number of variables
		*/
	size_t VarCount() {
		return GM_Ref.size();
		/*
	Local ret
	For Local k$ = EachIn MapKeys(GM_Ref)
	ret : +1
	Next
	Return ret
	*/
	}

		//Rem
		//bbdoc : Get a key
		//returns : The varkey on a specific index.
		//about : In the release mode you'll just get an empty string if the index is out of bounds. The debug mode will throw an error.
		//End Rem
	std::string VarKey(size_t i) {
		std::string ret{};
		size_t c{ 0 };
		//Assert c >= 0 And c <= VarCount() Else "VarKey(" + i + "): Index out of bounds"
		for (auto IT : GM_Ref) {// For Local K$ = EachIn MapKeys(GM_Ref)
			if (c == i) return IT.first;
			c++;// : +1
		}
		return "";
	}

		//Rem
		//bbdoc : All variable banes
		//returns : A string array with all variable names in it
		//EndRem
		//Function VarKeys$[]()
		//Local ret$[] = New String[VarCount()]
		//Local i = -1
		//For Local k$ = EachIn MapKeys(GM_Ref)
		//i : +1
		//ret[i] = k
		//Next
		//Return ret
		//endfunction

}