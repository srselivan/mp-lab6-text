#pragma once
#include <iostream>
#include <string>

// Node( pNext | pDown | str )
//		 |		 |
//		 |		 |
//		 |		 -------> Node at lower level
//		 v
// Node at same level

struct TNode {
	char str[81];
	TNode *pNext, *pDown;

	TNode (char* _str = NULL, TNode *_pNext = NULL, TNode* _pDown = NULL) {
		pNext = _pNext;
		pDown = _pDown;
		if (_str == NULL) {
			str[0] = '\0';
		}
		else {
			strcpy_s(str, _str);
		}
	}
};

