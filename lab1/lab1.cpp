#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "P6.h"
#include "P5.h"

using namespace std;

int main(int argc, char* argv[]) {

	string fin = string(argv[1]);
	string fout = string(argv[2]);
	int conv = (int)(*argv[3] - '0');

	if (argc != 4) {
		std::cerr << "Wrong number of arguments";
		return 0;
	}
	else { cout << "ok" << endl; }

	if (conv < 0 || conv >4) {
		std::cerr << "Non-existent conversion";
		return 0;
	} { cout << "ok" << endl; }

	ifstream inFile(fin, ios::binary);
	if (!inFile.is_open()) {
		std::cerr << "file isn't opened";
		return 0;
	} { cout << "ok" << endl; }

	unsigned char px[2];
	inFile >> px[0]; cout << "This is " << px[0];
	inFile >> px[1]; cout << px[1];
	try {
		if (px[1] == '5' && px[0] == 'P') {
			//cerr << "Horse1";
			P5_image image(fin);
			//cerr << "Horse2";
			switch (conv) {
			case 0:
				image.inversion();
				break;
			case 1:
				image.horizontal_reflection();
				break;
			case 2:
				image.vertical_reflection();
				break;
			case 3:
				image.rotate_right();
				break;
			case 4:
				image.rotate_left();
				break;
			}
			image.write(fout);
		}
		if (px[1] == '6' && px[0] == 'P') {
			//cerr << "Horse1";
			P6_image image(fin);
			//cerr << "Horse2";
			switch (conv) {
			case 0:
				image.inversion();
				break;
			case 1:
				image.horizontal_reflection();
				break;
			case 2:
				image.vertical_reflection();
				break;
			case 3:
				image.rotate_right();
				break;
			case 4:
				image.rotate_left();
				break;
			}
			image.write(fout);
		}
	}
	catch (const exception& e) {
		cerr << "can't create image obj";
		return 1;
	}
	

	return 0;
}