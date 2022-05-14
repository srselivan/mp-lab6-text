#include "../headers/TStack.h"
#include "../headers/TText.h"
#include <conio.h>	

#define HOME	71
#define DOWN	80
#define NEXT	77
#define UP		72
#define ESC		27
#define INS		82
#define DEL		83
#define ENTER	13
#define Z		122
#define X		120
#define C		99
#define V		118
#define F		102
#define M		109
#define S		115

TMem TNode::mem;

void PrintMenu() {
	std::cout
		<< "HOME - Go fist line | RIGHT - Go next line | DOWN - Go down line | "
		<< "UP - Go previous line | INS - Delete next line" << std::endl
		<< "DEL - Delete down line | Z - Insert next line | X - Insert next section | C - Insert down line" << std::endl
		<< "V - Insert down section | M - Clean mem | F - Print free | S - Save into a file" << std::endl;
}

int main() {
	TNode::InitMem();
	TText t;
	char key;

	t.Read((char*)"../example.txt");
	t.GoFirstLine();

	do {
		system("CLS");
		PrintMenu(); 
		t.Print();
		
		char* str = new char[100];
		key = _getch();
		if (key == 0xE0) key = _getch();
		if (key == ESC) break;
		if (key != ENTER) key = _getch();
		switch (key) {
			case ENTER:
				break;
			case HOME: {
				t.GoFirstLine();
				break;
			}
			case DOWN: {
				t.GoDownLine();
				break;
			}
			case NEXT: {
				t.GoNextLine();
				break;
			}
			case UP: {
				t.GoPrevLine();
				break;
			}
			case Z: {
				std::cout << "InsNextLine: ";
				std::cin.getline(str, 100);
				t.InsNextLine(str);
				break;
			}
			case X: {
				std::cout << "InsNextSection: ";
				std::cin.getline(str, 100);
				t.InsNextSection(str);
				break;
			}
			case C: {
				std::cout << "InsDownLine: ";
				std::cin.getline(str, 100);
				t.InsDownLine(str);
				break;
			}
			case V: {
				std::cout << "InsDownSection: ";
				std::cin.getline(str, 100);
				t.InsDownSection(str);
				break;
			}
			case INS: {
				t.DelNextLine();
				break;
			}
			case DEL: {
				t.DelDownLine();
				break;
			}
			case M: {
				TNode::CleanMem(t);
				break;
			}
			case F: {
				std::cout << "Free: " << std::endl;
				TNode::PaintFree();
				std::cin.getline(str, 100);
				break;
			}
			case S: {
				std::ofstream ofs("../output.txt", std::ios::trunc);
				t.FPrint(ofs);
				break;
			}
		}

		std::cout << std::endl;
	} while (key != ESC);

	return 1;
}