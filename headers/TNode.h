#pragma once
#include <iostream>

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

	TNode(char* _str = NULL, TNode* _pNext = NULL, TNode* _pDown = NULL);
	void* operator new (size_t size);
	void operator delete (void* pDel);
	static void InitMem(int s = 100);
	static void CleanMem(TText& txt);
	static void PaintFree();
};

