#include <iostream>
#include "headers/TStack.h"
#include "headers/TText.h"

TMem TNode::mem;

int main() {
	TNode::InitMem();
	TText t;
	char* str = new char[80];
	std::cin >> str;
	t.InsDownLine(str);
	std::cin >> str;
	t.InsDownLine(str);
	std::cin >> str;
	t.GoDownLine();
	t.InsDownLine(str);
	//std::cout << t;
	t.Print();
	return 1;
}