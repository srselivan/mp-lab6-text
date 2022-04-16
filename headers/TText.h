#pragma once
#include "TNode.h"
#include "TStack.h"

class TText {
	TNode* pFirst, * pCurr;
	TStack<TNode*> st;

public:
	TText() : pFirst(NULL), pCurr(NULL) {}

	void GoNextLine() {
		if (pCurr) {
			st.Push(pCurr);
			pCurr = pCurr->pNext;
		}
	}

	void GoDownLine() {
		if (pCurr) {
			st.Push(pCurr);
			pCurr = pCurr->pDown;
		}
	}

	void GoPrevLine() {
		pCurr = st.Pop();
		if (!pCurr) {
			pCurr = pFirst;
		}
	}

	void GoFirstLine() {
		pCurr = pFirst;
		st.Clear();
	}
};