#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "P5.h"

using namespace std;

int main(int argc, char* argv[]) {

	const double srgb_gamma = 2.4;
	string fin = string(argv[1]);
	string fout = string(argv[2]);
	int brightness;
	double thickness, x1, x2, y1, y2, gamma;
	//	cout << brightness << " " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << gamma<< endl;

	try {
		brightness = stoi(argv[3]);
		thickness = stold(argv[4]);
		x1 = stold(argv[5]);
		y1 = stold(argv[6]);
		x2 = stold(argv[7]);
		y2 = stold(argv[8]);
		if (argc == 10) {
			gamma = stold(argv[9]);
		}
		else {
			gamma = srgb_gamma;
		}
		if ( brightness>255) {
			cerr << "Wrong brightness ";
			return 1;
		}
		if ( thickness <= 0) {
			cerr << "Wrong thickness: "<< thickness;
			return 1;
		}
		if (brightness < 0) {
			cerr << "Wrong brightness ";
			return 1;
		}
	}
	catch (const exception& e) {
		cerr << "input errors";
		return 1;
	}



	if (argc != 10 && argc != 9) {
		std::cerr << "Wrong number of arguments: "<< argc;
		return 1;
	}

	//cout << brightness << " " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << gamma;

	try {
		P5_image image(fin, gamma, false);
		image.draw_line(brightness, x1, y1, x2, y2, gamma);
		image.write(fout,  gamma, false);
	}
	catch (const exception& e) {
		cerr << "input errors";
		return 1;
	}

	return 0;
}