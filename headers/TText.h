#pragma once
#include "TNode.h"
#include "TStack.h"
#include <fstream>

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

	void InsNextLine(char str[]) {
		if (pCurr) {
			TNode* n = new TNode(str);
			n->pNext = pCurr->pNext;
			pCurr->pNext = n;
		}
	}

	void InsNextSection(char str[]) {
		if (pCurr) {
			TNode* n = new TNode(str);
			n->pDown = pCurr->pNext;
			pCurr->pNext = n;
		}
	}

	void InsDownLine(char str[]) {
		if (pCurr) {
			TNode* n = new TNode(str);
			n->pNext = pCurr->pDown;
			pCurr->pDown = n;
		}
	}

	void InsDownSection(char str[]) {
		if (pCurr) {
			TNode* n = new TNode(str);
			n->pDown  = pCurr->pDown;
			pCurr->pDown = n;
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

};