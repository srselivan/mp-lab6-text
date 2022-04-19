#include "../headers/TNode.h"
#include "../headers/TText.h"

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