#pragma once
#include <iostream>

template <class T>
struct Node {
	T value;
	Node* pNext;
};

template <class T>
class TStack {
	Node<T>* pFirst;

public:
	TStack() : pFirst(NULL) {}

	TStack(const TStack<T>& st) {
		Node<T>* tmpFirst = st.pFirst;
		Node<T>* pCurr, * pPrev;
		pFirst = NULL;

		while (tmpFirst != NULL)
		{
			pCurr = new Node<T>;
			pCurr->value = tmpFirst->value;
			pCurr->pNext = NULL;
			if (pFirst == NULL) {
				pFirst = pCurr;
			}
			else {
				pPrev->pNext = pCurr;
			}
			tmpFirst = tmpFirst->pNext;
			pPrev = pCurr;
		}
	}

	void Clear() {
		while (pFirst != NULL)
		{
			Node<T>* pDel = pFirst;
			pFirst = pFirst->pNext;
			delete pDel;
		}
	}

	void Push(const T& elem){
		Node<T>* newFirst = new Node<T>;
		newFirst->value = elem;
		newFirst->pNext = pFirst;
		pFirst = newFirst;
	}

	T Pop(){
		if (pFirst != NULL)
		{
			Node<T>* pDel = pFirst;
			T result = pDel->value;
			pFirst = pFirst->pNext;
			delete pDel;
			return result;
		} 
		return NULL;
	}

	T Top(){
		if (pFirst != NULL) {
			return pFirst->value;
		}
		return NULL;
	}

	~TStack(){
		while (pFirst != NULL)
		{
			Node<T>* pDel = pFirst;
			pFirst = pFirst->pNext;
			delete pDel;
		}
	}
};
