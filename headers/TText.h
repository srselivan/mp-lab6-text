#pragma once
#include "TNode.h"
#include "TStack.h"
#include <fstream>

class TText {
	TNode* pFirst, * pCurr;
	TStack<TNode*> st;

public:
	TText() : pFirst(NULL), pCurr(NULL) {}

	TText(TNode*p) : pFirst(p) {}

	/*TText* Copy() {
		return new TText();
	}*/

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

	void InsFirst(char str[]) {
		TNode* n = new TNode(str);
		pFirst = n;
		pCurr = pFirst;
	}

	void InsNextLine(char str[]) {
		if (pCurr) {
			TNode* n = new TNode(str);
			n->pNext = pCurr->pNext;
			pCurr->pNext = n;
		}
		if (!pFirst) {
			InsFirst(str);
		}
	}

	void InsNextSection(char str[]) {
		if (pCurr) {
			TNode* n = new TNode(str);
			n->pDown = pCurr->pNext;
			pCurr->pNext = n;
		}
		if (!pFirst) {
			InsFirst(str);
		}
	}

	void InsDownLine(char str[]) {
		if (pCurr) {
			TNode* n = new TNode(str);
			n->pNext = pCurr->pDown;
			pCurr->pDown = n;
		}
		if (!pFirst) {
			InsFirst(str);
		}
	}

	void InsDownSection(char str[]) {
		if (pCurr) {
			TNode* n = new TNode(str);
			n->pDown  = pCurr->pDown;
			pCurr->pDown = n;
		}
		if (!pFirst) {
			InsFirst(str);
		}
	}

	void DelNextLine() {
		if (pCurr) {
			if (pCurr->pNext) {
				TNode* n = pCurr->pNext;
				pCurr->pNext = n->pNext;
				delete n;
			}
		}
	}

	void DelDownLine() {
		if (pCurr) {
			if (pCurr->pDown) {
				TNode* n = pCurr->pDown;
				pCurr->pDown = n->pNext;
				delete n;
			}
		}
	}

	TNode* ReadRec(std::ifstream& ifs) {
		TNode* pHead, * tmp;
		char buf[81];

		while (!ifs.eof()) {
			ifs.getline(buf, 80, '\n');
			if (buf[0] == '}') {
				break;
			}
			else if (buf[0] == '{') {
				tmp->pDown = ReadRec(ifs);
			}
			else {
				TNode* p = new TNode(buf);
				if (pHead == NULL) {
					pHead = tmp = p;
				}
				else {
					tmp->pNext = p;
					tmp = p;
				}
			}
		}

		return pHead;
	}

	void Read(char* fn) {
		std::ifstream ifs(fn);
		pFirst = ReadRec(ifs);
	}

	void PrintRec(TNode* p) {
		if (p) {
			std::cout << p->str << std::endl;
			PrintRec(p->pDown);
			PrintRec(p->pNext);
		}
	}

	void Print() {
		PrintRec(pFirst);
	}

	void Reset() {
		st.Clear();
		if (pCurr) {
			pCurr = pFirst;
			st.Push(pCurr);
			if (pCurr->pNext) {
				st.Push(pCurr->pNext);
			}
			if (pCurr->pDown) {
				st.Push(pCurr->pDown);
			}
		}
	}

	void GoNext() {
		pCurr = st.Pop();
		if (pCurr != pFirst) {
			if (pCurr->pNext) {
				st.Push(pCurr->pNext);
			}
			if (pCurr->pDown) {
				st.Push(pCurr->pDown);
			}
		}
	}

	bool IsEnd() {
		return st.IsEmpty();
	}

	void SetFlag() {
		pCurr->flag = true;
	}

	friend std::ostream& operator<<(std::ostream& os, TText& text) {
		for (text.Reset(); !text.IsEnd(); text.GoNext()) {
			os << text.pCurr->str << std::endl;
		}
		return os;
	}

};