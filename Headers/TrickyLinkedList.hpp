// Lic:
// Headers/TrickyLinkedList.hpp
// Linked List (header)
// version: 22.10.26
// Copyright (C) 2022 Jeroen P. Broks
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
// This file does not require a .cpp file, as this is entirely template based

#pragma once

#undef DEBUG_TLIST

#include <memory>

#define TLFORA(lst,L) if(lst.First) for(auto L=lst.First;L;L=L->Next)
#define TLFORD(lst,L) if(list.Last) for(auto L=lst.Last;L;L=L->Prev)


#ifdef DEBUG_TLIST
#include <iostream>
#define TL_CHAT(ABC) std::cout << "\x1b[32mLinked List Debug> \x1b[0m"<<ABC<<std::endl
#else
#define TL_CHAT(ABC)
#endif

namespace TrickyUnits {




	template <class MyType> class TLink;
	template <class MyType> class TList;


	template <class MyType> class TLink {
	public:		
		//std::shared_ptr < TList<MyType>> Parent{ nullptr };
		std::shared_ptr<TLink<MyType>> Prev{ nullptr };
		std::shared_ptr<TLink<MyType>> Next{ nullptr };
		MyType Obj{ };
		TList<MyType>* Parent;


		//operator MyType() const;

		void UnLink();
	};

	template <class MyType> class TList {
	public:
		std::shared_ptr<TLink<MyType>> First{ nullptr };
		std::shared_ptr<TLink<MyType>> Last{ nullptr };

		TLink<MyType>* GetLink(int i);
		MyType Get(int i);
		MyType* GetP(int i);
		MyType operator[](int i);

		void Delete(int i);

		void Add(MyType O);
		void AddFirst(MyType O);
		bool Insert(int i, MyType O);
		TList<MyType>& operator+=(MyType O);
	};

	//template<class MyType> inline TLink<MyType>::operator MyType() const { return Obj; }

	template<class MyType>	inline void TLink<MyType>::UnLink() {
		if (Prev) Prev->Next = Next; else Parent->First = Next;
		if (Next) Next->Prev = Prev; else Parent->Last = Prev;
	}

	template<class MyType> inline TLink<MyType>* TList<MyType>::GetLink(int i) {
		if (i == 0)
			return First.get();
		if (i > 0) {
			for(std::shared_ptr<TLink<MyType>> lnk=this->First;lnk;lnk=lnk->Next) {
				if (!i--) return lnk.get();
			}
		}
		if (i < 0) {
			for (std::shared_ptr<TLink<MyType>> lnk = this->First; lnk; lnk = lnk->Next) {
				if (i++>=0) return lnk.get();
			}

		}
	}

	template<class MyType> inline MyType TList<MyType>::Get(int i) { return GetLink(i)->Obj; }
	template<class MyType> inline MyType* TList<MyType>::GetP(int i) { return &(GetLink(i)->Obj); }

	template<class MyType> inline MyType TList<MyType>::operator[](int i) {	return Get(i);	}

	template<class MyType>	inline void TList<MyType>::Delete(int i) {
		GetLink(i)->UnLink();
	}

	template<class MyType> inline void TList<MyType>::Add(MyType O) {
		TL_CHAT("Adding: " << O);
		auto NL = std::make_shared<TLink<MyType>>();
		NL->Parent = this;
		TL_CHAT("-> Value");
		NL->Obj = O;
		TL_CHAT("-> Link prev");
		NL->Prev = Last;
		TL_CHAT("-> Link Last");
		if (Last) Last->Next = NL;
		if (!First) First = NL;
		TL_CHAT("-> Set Last");
		Last = NL;		
	}

	template<class MyType> 	inline void TList<MyType>::AddFirst(MyType O) {
		auto NL = std::make_shared<TLink<MyType>>();
		NL->Obj=O;
		NL->Next = First;
		if (First) First->Prev = NL;
		First = NL;
		if (!Last) Last = NL;
	}

	template<class MyType> inline bool TList<MyType>::Insert(int i, MyType O) {
		auto WL{ GetLink(i) };
		if (!WL) return false;
		auto NL = std::make_shared<TLink<MyType>>();
		NL->Obj = O;
		NL->Prev = WL->Prev;
		NL->Next = WL;
		WL->Prev = NL;
		NL->Prev->Next = NL;
		return true;
	}

	template<class MyType>	inline TList<MyType>& TList<MyType>::operator+=(MyType O) {
		Add(O);
		return *this;
	}

}