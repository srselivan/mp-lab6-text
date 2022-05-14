#pragma once
#include "TStack.h"
#include "TNode.h"
#include <fstream>


class TText {
	TNode* pFirst, * pCurr;
	TStack<TNode*> st;

	void PrintTab(int count) {
		while (count--)	std::cout << "	";
	}
	void PrintCurr(const TNode* p) {
		if (p == pCurr)	std::cout << ">";
	}

	TNode* CopyNode(TNode* p) {
		TNode* pN = NULL, * pD = NULL;
		if (p->pNext) pN = CopyNode(p->pNext);
		if (p->pDown) pD = CopyNode(p->pDown);
		TNode* result;
		result = new TNode(p->str, pN, pD);
		return result;
	}

	TNode* ReadRec(std::ifstream& ifs) {
		TNode* pHead = NULL, * tmp = NULL;
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

	void PrintRec(TNode* p, int countTab) {
		if (p) {
			PrintTab(countTab);
			PrintCurr(p);
			std::cout << p->str << std::endl;
			if (p->pDown)
			{
				PrintTab(++countTab);
				std::cout << "{\n";

				PrintRec(p->pDown, countTab);

				PrintTab(countTab--);
				std::cout << "}\n";
			}
			PrintRec(p->pNext, countTab);
		}
	}

	void FPrintRec(TNode* p, std::ofstream& ofs) {
		if (p) {
			ofs << p->str << std::endl;
			if (p->pDown)
			{
				ofs << "{\n";
				FPrintRec(p->pDown, ofs);
				ofs << "}\n";
			}
			FPrintRec(p->pNext, ofs);
		}
	}

public:
	TText() : pFirst(NULL), pCurr(NULL) {}

	TText(TNode*p) : pFirst(p), pCurr(NULL){}

	TText* Copy() {
		return new TText(CopyNode(pFirst));
	}

	void GoNextLine() {
		if (pCurr && pCurr->pNext) {
			st.Push(pCurr);
			pCurr = pCurr->pNext;
		}
	}

	void GoDownLine() {
		if (pCurr && pCurr->pDown) {
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

	void Read(char* fn) {
		std::ifstream ifs(fn);
		pFirst = ReadRec(ifs);
	}

	void Print() {
		int countTab = 0;
		PrintRec(pFirst, countTab);
	}

	void FPrint(std::ofstream& ofs) {
		FPrintRec(pFirst, ofs);
	}

	void Reset() {
		st.Clear();
		pCurr = pFirst;
		st.Push(pCurr);
		if (pCurr) {
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
		if (pCurr != pFirst && pCurr) {
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