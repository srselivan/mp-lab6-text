#include "../headers/TNode.h"
#include "../headers/TText.h"

TNode::TNode(char* _str, TNode* _pNext, TNode* _pDown) {
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

void* TNode::operator new (size_t size) {
	TNode* result = mem.pFree;
	if (mem.pFree) {
		mem.pFree = mem.pFree->pNext;
	}
	return result;
}

void TNode::operator delete (void* pDel) {
	if (pDel) {
		TNode* del = (TNode*)pDel;
		TNode* pLastFree = mem.pFree;
		mem.pFree = del;
		mem.pFree->pNext = pLastFree;
	}
}

void TNode::InitMem(int s) {
	mem.pFirst = (TNode*) new char[sizeof(TNode) * s];
	mem.pFree = mem.pFirst;
	mem.pLast = mem.pFirst + s - 1;
	// setting pointers
	TNode* p;
	p = mem.pFirst;
	for (int i = 0; i < s - 1; i++, p++) {
		p->pNext = p + 1;
		p->str[0] = '\0';
		p->flag = false;
	}
	mem.pLast->pNext = NULL;
}

void TNode::CleanMem(TText& txt) {
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
}

void TNode::PaintFree() {
	TNode* p;
	p = mem.pFree;
	while(p) {
		if (p->str[0] != '\0')
			std::cout << p->str << std::endl;
		p = p->pNext;
	}
}