#pragma once

#include <memory>

#define TLFORA(lst,L) for(auto L=lst.First;L;L=L.Next)
#define TLFORD(lst,L) for(auto L=lst.Last;L;L=L.Prev)

namespace TricktUnits {


	template <class MyType> class TLink;
	template <class MyType> class TList;


	template <class MyType> class TLink {
	public:		
		//std::shared_ptr < TList<MyType>> Parent{ nullptr };
		std::shared_ptr<TLink<MyType>> Prev{ nullptr };
		std::shared_ptr<TLink<MyType>> Next{ nullptr };
		MyType Obj{ nullptr };

		operator MyType() const;

		void UnLink();
	};

	template <class MyType> class TList {
		std::shared_ptr<TLink<MyType>> First{ nullptr };
		std::shared_ptr<TLink<MyType>> Last{ nullptr };

		TLink<MyType>* GetLink(int i);
		MyType Get(int i);
		MyType* GetP(int i);

		void Add(MyType O);
		void AddFirst(MyType O);
		bool Insert(int i, MyType O);
	};

	template<class MyType> inline TLink<MyType>::operator MyType() const { return Obj; }

	template<class MyType>	inline void TLink<MyType>::UnLink() {
		if (Prev) Prev.Next = Next;
		if (Next) Next.Prev = Prev;
	}

	template<class MyType> inline TLink<MyType>* TList<MyType>::GetLink(int i) {
		if (i == 0)
			return First;
		if (i > 0) {
			for(std::shared_ptr<TLink<MyType>>* lnk=this->First;lnk;lnk=lnk->Next) {
				if (!i--) return lnk->get();
			}
		}
		if (i < 0) {
			for (std::shared_ptr<TLink<MyType>>* lnk = this->First; lnk; lnk = lnk->Next) {
				if (i++>=0) return lnk->get();
			}

		}
	}

	template<class MyType> inline MyType TList<MyType>::Get(int i) { return GetLink(i)->Obj; }
	template<class MyType> inline MyType* TList<MyType>::GetP(int i) { return &(GetLink(i)->Obj); }

	template<class MyType> inline void TList<MyType>::Add(MyType O) {
		auto NL = std::make_shared<TLink<MyType>>();
		NL.Prev = Last;
		if (Last) Last->Next = NL;
		Last = NL;		
	}

	template<class MyType> 	inline void TList<MyType>::AddFirst(MyType O) {
		auto NL = std::make_shared<TLink<MyType>>();
		NL.Next = First;
		if (First) First->Prev = NL;
		First = NL;
	}

	template<class MyType> inline bool TList<MyType>::Insert(int i, MyType O) {
		auto WL{ GetLink(i) };
		if (!WL) return false;
		auto NL = std::make_shared<TLink<MyType>>();
		NL->Prev = WL->Prev;
		NL->Next = WL;
		WL->Prev = NL;
		NL->Prev->Next = NL;
		return true;
	}

}