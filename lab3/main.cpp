#include <iostream>
#include <string>
#include "P5.h"



using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 7) {
		cerr << "N E argoments" << endl;
		return 1;
	}

	string fin = string(argv[1]);
	string fout = string(argv[2]);
	double gamma;
	bool sRGB = false;
	bool grad = false;
	int dis_algo = 0;
	int bit = 0;
	try {
		//grad = (bool)argv[3];
		if (argv[3] != "0") {
			grad = false;
		}
		else {
			grad = true;
		}
		dis_algo = (int)(*argv[4] - '0');
		bit = (int)(*argv[5] - '0');
		if (string(argv[6]) == "0")
		{
			gamma = 3.0;
			sRGB = true;
		}
		else {

			gamma = stold(argv[6]);
		}
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
		return 1;
	}
	//std::cout << grad << " " << dis_algo << " " << bit << " " << gamma;

	try {
		P5 image(fin, grad, gamma, sRGB);
		image.dither(bit, dis_algo, gamma);
		try {
			image.write(fout, gamma, sRGB, bit);
		}
		catch (const exception& e) {
			cerr << e.what() << endl;
			return 1;
		}
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
		return 1;
	}




	return 0;
}






/*	<���_��������_�����>, <���_���������_�����>: ������ ������ : PGM P5; ������ � ������ ������� �� <���_��������_�����>;
	<��������>: 0 - ���������� ������� ��������, 1 - ������ �������������� ��������(0 - 255) (������ � ������ ������� �� <���_��������_�����>);
	<��������> -�������� ��������� :
	0 � ��� ���������;
	1 � Ordered(8x8);
	2 � Random;
	3 � Floyd�Steinberg;
	4 � Jarvis, Judice, Ninke;
	5 - Sierra(Sierra - 3);
	6 - Atkinson;
	7 - Halftone(4x4, orthogonal);
	<��������> -�������� ���������� ���������(1..8);
	<�����>: 0 - sRGB �����, ����� - ������� ����� � ��������� ���������.
*/