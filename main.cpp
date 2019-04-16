//LABKA 2-4 v.1
#include <iostream>
#include <fstream>
#include <string>
#define NOMINMAX
#include <Windows.h>
#include "classes.h"

void putAboutStudent();

std::istream& setIStream(std::ifstream& f);
std::ostream& setOStream(std::ofstream& f);

int main() {
	system("mode con COLS=700");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

	putAboutStudent();
	
	Polynom operandA, operandB;
	try {
		// INPUT
		std::ifstream f;
		std::istream& s_inA = setIStream(f);
		s_inA >> operandA;
		std::istream& s_inB = setIStream(f);
		s_inB >> operandB;

		Polynom resultPlus = operandA + operandB;
		Polynom resultMinus = operandA - operandB;
		operandA += operandB;

		// OUTPUT
		std::ofstream g;
		std::ostream& s_outP = setOStream(g);
		s_outP << resultPlus;
		std::ostream& s_outM = setOStream(g);
		s_outM << resultMinus;
		std::ostream& s_outPE = setOStream(g);
		s_outPE << operandA;
	} catch (std::exception & ex) {
		std::cerr << "\n\t" << ex.what() << std::endl;
		system("pause");
		return -1;
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}

void putAboutStudent() {
	std::cout << "Laboratory work 2 - 4 Linked Lists" << std::endl;
	std::cout << "Group: K-14 Danilchenko Alexander" << std::endl;
	std::cout << "\t     VAR: 70" << std::endl;
}

std::istream& setIStream(std::ifstream& f) {
	if (std::cin.fail() or f.bad()) {
		std::cin.clear(); 
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	while (true) {
		short i;
		std::cout << "\n... Enter 1(kbd) or 2(file): ";
		std::cin >> i;
		if (i == 1)
			return std::cin;
		else if (i == 2) {
			std::cin.get(); // pass Enter from previous input
			while (true) {
				std::cout << "\n... Enter input filepath: ";
				std::string fN;
				getline(std::cin, fN);
				if (fN.length() == 0)
					fN = "in.txt";
				f.open(fN);
				if (f.fail())
					continue;
				return (std::istream&)f;
			}
		} else
			continue;
	}
}

std::ostream& setOStream(std::ofstream& f) {
	if (std::cin.fail() or f.bad()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	while (true) {
		short i;
		std::cout << "\n... Enter for out: 1(screen) or 2(file): ";
		std::cin >> i;
		if (i == 1)
			return std::cout;
		else if (i == 2) {
			std::cin.get(); // pass Enter from previous input
			while (true) {
				std::cout << "\n... Enter output filepath: ";
				std::string fN;
				getline(std::cin, fN);
				if (fN.length() == 0)
					fN = "out.txt";
				f.open(fN);
				if (f.fail())
					continue;
				return (std::ostream&)f;
			}
		} else
			continue;
	}
}
