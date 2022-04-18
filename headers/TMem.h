#pragma once
#include "TNode.h"

struct TMem {
	TNode* pFirst, * pFree, * pLast;
};