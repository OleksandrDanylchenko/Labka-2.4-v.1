#include <iostream>
#include <fstream>
#include <random>
#include <string>

size_t randomGenerator(size_t min, size_t max);

// get the path or name of the output file
std::string getFilePath();

int main() {
	std::cout << "How many monoms do you want?" << std::endl << ">> ";
	long long num;
	std::cin >> num;

	std::ofstream outFile;
	std::string outFilePath = getFilePath();
	outFile.open(outFilePath);
	if (outFile.fail()) {
		std::cerr << "Error Opening File" << std::endl;
		system("pause");
		return -1;
	}
	for (long long i = 0; i < num; ++i) {
		outFile << randomGenerator(0, 15) << ' ' << randomGenerator(0, 30);
		if ((i + 1) < num)
			outFile << std::endl;

	}
	system("pause");
	return 0;
}

size_t randomGenerator(size_t min, size_t max) {
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
	return dist(rng);
}

std::string getFilePath() {
	std::string outputFilePathUser = "";
	std::string outputFilePath = "";
	std::cout << "Enter the path to the output file or desirable name: ";
	std::cin.ignore();
	getline(std::cin, outputFilePathUser);
	if (outputFilePathUser[0] != 'C' && outputFilePathUser[0] != 'D') { //if user didn't provided full adress -> create a new file in the root folder
		std::string outputFilePathDefault = "D:/Studying/Programming/LABS/Labka 2-4 v.1/Labka 2-4 v.1/";
		outputFilePath += outputFilePathDefault + outputFilePathUser + ".txt";
	}
	return outputFilePath;
}
