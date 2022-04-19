#pragma once
#include <iostream>
//#include <string>
//#include "TText.h"

// Node( pNext | pDown | str )
//		 |		 |
//		 |		 |
//		 |		 -------> Node at lower level
//		 v
// Node at same level

struct TNode;
class TText;

struct TMem {
	TNode* pFirst, * pFree, * pLast;
};

struct TNode {
	char str[81];
	TNode *pNext, *pDown;
	static TMem mem;
	bool flag;

	TNode (char* _str = NULL, TNode *_pNext = NULL, TNode* _pDown = NULL) {
		pNext = _pNext;
		pDown = _pDown;
		if (_str == NULL) {
			str[0] = '\0';
		}
		else {
			strcpy_s(str, _str);
		}
		flag = false;
	}

	void* operator new (size_t size) {
		TNode* result = mem.pFree;
		if (mem.pFree) {
			mem.pFree = mem.pFree->pNext;
		}
		return result;
	}

	void operator delete (void* pDel) {
		if (!pDel) {
			TNode* del = (TNode*)pDel;
			TNode* pLastFree = mem.pFree;
			mem.pFree = del;
			mem.pFree->pNext = pLastFree;
		}
	}

	static void InitMem(int s = 100) {
		mem.pFirst = (TNode*) new char[sizeof(TNode) * s];
		mem.pFree = mem.pFirst;
		mem.pLast = mem.pFirst + s - 1;
		// setting pointers
		TNode* p;
		p = mem.pFirst;
		for (int i = 0; i < s - 1; i++) {
			p->pNext = p + 1; 
			p->str[0] = '\0';
			p->flag = false;
			p++;
		}
		mem.pLast->pNext = NULL;
	}

	static void CleanMem(TText& txt); /*{
		TNode* p = mem.pFree;
		while (p) {
			p->flag = true;
			p = p->pNext;
		}

		for (txt.Reset(); !txt.IsEnd(); txt.GoNext()) {
			txt.SetFlag();
		}

		p = mem.pFirst;
		while (p <= mem.pLast) {
			if (!p->flag) {
				delete p;
				p->flag = true;
			}
			p++;
		}
	}*/

	/*static void PaintFree() {

	}*/
};

