#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <functional>
#include <random>
#include <iomanip>

class Rand_double {
public:
	Rand_double(double low, double high) : r(std::bind(std::uniform_real_distribution<>(low, high), 
													   std::default_random_engine())) {}
	double operator()() { return r(); }
private:
	std::function<double()> r;
};

size_t randomGenerator(size_t min, size_t max);

std::string getFilePath();

int main() {
	system("mode con COLS=700");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

	std::cout << "How many monoms do you want?" << std::endl << ">> ";
	long long num;
	std::cin >> num;

	std::ofstream outFile;
	std::string outFilePath = getFilePath();	
	outFile.open(outFilePath, std::fstream::out);
	if (outFile.fail()) {
		std::cerr << "Error Opening File" << std::endl;
		system("pause");
		return -1;
	}
	
	while (true) {
		char checkChar = ' ';
		std::cout << "What type of coefficients do you want? Double or Int? (D or I): ";
		std::cin >> checkChar;

		if (checkChar == 'D' or checkChar == 'd') {
			// create the random number generator:
			Rand_double rd{ 0, 99.5 };
			for (long long i = 0; i < num; ++i) {
				outFile << std::fixed << std::setprecision(1) << rd() << ' ' << randomGenerator(0, 99);
				if ((i + 1) < num)
					outFile << std::endl;
			}
			break;
		} else if (checkChar == 'I' or checkChar == 'i') {
			for (long long i = 0; i < num; ++i) {
				outFile << randomGenerator(0, 99) << ' ' << randomGenerator(0, 99);
				if ((i + 1) < num)
					outFile << std::endl;
			}
			break;
		} else continue;
	}
	system("pause");
	return 0;
}

std::string getFilePath() {
	std::string outputFilePathUser = "";
	std::string outputFilePath = "";
	std::cout << "Enter the path to the output file or desirable name: ";
	std::cin.ignore();
	getline(std::cin, outputFilePathUser);
	if (outputFilePathUser.empty())
		outputFilePath = "D:/Studying/Programming/LABS/Labka 2-4 v.1/Labka 2-4 v.1/in.txt";
	else if (outputFilePathUser[0] != 'C' && outputFilePathUser[0] != 'D') { //if user didn't provided full adress -> create a new file in the root folder
		std::string outputFilePathDefault = "D:/Studying/Programming/LABS/Labka 2-4 v.1/Labka 2-4 v.1/";
		outputFilePath += outputFilePathDefault + outputFilePathUser + ".txt";
	}
	return outputFilePath;
}

size_t randomGenerator(size_t min, size_t max) {
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
	return dist(rng);
}
