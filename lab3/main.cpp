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






/*	<им€_входного_файла>, <им€_выходного_файла>: формат файлов : PGM P5; ширина и высота берутс€ из <им€_входного_файла>;
	<градиент>: 0 - используем входную картинку, 1 - рисуем горизонтальный градиент(0 - 255) (ширина и высота берутс€ из <им€_входного_файла>);
	<дизеринг> -алгоритм дизеринга :
	0 Ц Ќет дизеринга;
	1 Ц Ordered(8x8);
	2 Ц Random;
	3 Ц FloydЦSteinberg;
	4 Ц Jarvis, Judice, Ninke;
	5 - Sierra(Sierra - 3);
	6 - Atkinson;
	7 - Halftone(4x4, orthogonal);
	<битность> -битность результата дизеринга(1..8);
	<гамма>: 0 - sRGB гамма, иначе - обычна€ гамма с указанным значением.
*/