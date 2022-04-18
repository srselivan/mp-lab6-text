#include <iostream>
#include "headers/TStack.h"
#include "headers/TText.h"

void main() {
	TText t;
	char* str = new char[80];
	std::cin >> str;
	t.InsDownLine(str);
	std::cin >> str;
	t.InsDownLine(str);
	std::cin >> str;
	t.InsDownLine(str);
	//std::cout << t;
	t.Print();
}