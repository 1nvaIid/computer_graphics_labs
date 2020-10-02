#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "P5.h"

using namespace std;

int main(int argc, char* argv[]) {
	setlocale(0, "");
	string fin = string(argv[1]);
	string fout = string(argv[2]);
/*	int class_numb;

	try {
		class_numb = stoi(argv[3]);
	}
	catch (const exception& e) {
		cerr << "input errors";
		return 1;
	}
*/


	if (argc != 3) {
		std::cerr << "Wrong number of arguments: " << argc;
		return 1;
	}



	try {
		P5_image image(fin);
		image.akoefs();
		image.write(fout);

	}
	catch (const exception& e) {
		cerr << "input errors 2";
		return 1;
	}



	return 0;
}