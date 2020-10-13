#include "P5.h"

P5_image::P5_image(string filename) {
	//cc = class_numb;
	ifstream fin(filename, ios::binary);
	if (!fin.is_open()) {
		cerr << "Can't open file";
		exit(1);
	}
	char c, c1;
	try {
		fin >> c >> c1;
		fin >> width >> height >> depth;
	}
	catch (const exception& e) {
		cerr << "Wrong Header";
		exit(1);
	}
	if (depth > 255 && width < 0 && height < 0 && depth <= 0) {
		cerr << "Wrong Header";
		exit(1);
	}

	if (c != 'P' || c1 != '5') {
		cout << c << " " << c1;

		cerr << "Wrong Header";
		exit(1);
	}

	fin.read(&c, 1);
	try {
		data.assign(height, vector<double>(width));
		newdata.assign(height, vector<double>(width));
		count.assign(height, vector<int>(width));
	}
	catch (const exception& e) {
		cerr << "troubles with memory";
		exit(1);
	}

	//check header;


	char color_bw;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (fin.eof()) {
				fin.close();
				throw runtime_error("N E pixels");
			}
			fin.read(&color_bw, 1);
			data[i][j] = (double)((unsigned char)color_bw);
		}

	fin.close();
}


void P5_image::write(string filename) {
	ofstream fout(filename, ios::binary);
	if (!fout.is_open()) {
		throw runtime_error("Can't open output file");
	}
	//fout << "P5\n" << width << ' ' << height << '\n' << depth << '\n';
	fout << "P5\n" << -start_x + end_x << ' ' << -start_y + end_y << '\n' << depth << '\n';
	unsigned char press_f;

	for (int i = start_y; i < end_y; i++) {
		for (int j = start_x; j < end_x; j++) {
			press_f = (int)newdata[i][j];
			//cout << press_f << " ";
			fout << press_f;

		}
	}
	
	fout.flush();
	fout.close();
}


void P5_image::akoefs() {
	double Xc, Yc;
	double sum_xT = 0, sum_T = 0, sum_yT = 0;
	double B = 0, C = 0, D = 0, M = 0, K = 10;
	double mu, omega;
	double x_plus, y_plus;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			sum_T += data[y][x];
			sum_xT += data[y][x] * x;
			sum_yT += data[y][x] * y;
		}
	}
	// cout << sum_T << " " << sum_xT << " " << sum_yT;
	Xc = sum_xT / sum_T;
	Yc = sum_yT / sum_T;
	cout << "Линейное смещение центра тяжести вдоль оси абсцисс: " << Xc << endl;
	cout << "Линейное смещение центра тяжести вдоль оси ординат: " << Yc << endl;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			B += data[y][x] * ((x - Xc) * (x - Xc) - (y - Yc) * (y - Yc));
			C += data[y][x] * 2 * (x - Xc) * (y - Yc);
			D += data[y][x] * ((x - Xc) * (x - Xc) + (y - Yc) * (y - Yc));
		}
	}
	//cout << B << " " << C << " " << D;
	mu = sqrt((D + sqrt(C * C + B * B)) / (D - sqrt(C * C + B * B)));
	omega = 0.5 * atan2(C, B);
	cout << "Направление центрированного изображения: " << omega << endl;
	cout << "Величина сжатия:" << mu << endl;
	float minx = 0, maxx = 0;
	float miny = 0, maxy = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			x_plus = (1 / mu) * ((x - Xc) * cos(-omega) - (y - Yc) * sin(-omega)) * cos(omega) - ((x - Xc) * sin(-omega) + (y - Yc) * cos(-omega)) * sin(omega);
			y_plus = (1 / mu) * ((x - Xc) * cos(-omega) - (y - Yc) * sin(-omega)) * sin(omega) + ((x - Xc) * sin(-omega) + (y - Yc) * cos(-omega)) * cos(omega);
			//cout << x_plus << y_plus << endl;
			M += data[y][x] * sqrt(x_plus * x_plus + y_plus * y_plus) / (K * sum_T);
			/*if (x_plus < minx) {
				minx = x_plus;
			}
			if (x_plus > maxx) {
				maxx = x_plus;
			}
			if (y_plus < miny) {
				miny = y_plus;
			}
			if (y_plus > maxy) {
				maxy = y_plus;
			}*/
		}
	}
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			x_plus = ((1 / mu) * ((x - Xc) * cos(-omega) - (y - Yc) * sin(-omega)) * cos(omega) - ((x - Xc) * sin(-omega) + (y - Yc) * cos(-omega)) * sin(omega)) / M;
			y_plus = ((1 / mu) * ((x - Xc) * cos(-omega) - (y - Yc) * sin(-omega)) * sin(omega) + ((x - Xc) * sin(-omega) + (y - Yc) * cos(-omega)) * cos(omega)) / M;
			//cout << x_plus << y_plus << endl;
			newdata[(int)y_plus + 200][(int)x_plus + 200] += data[y][x];
			count[(int)y_plus + 200][(int)x_plus + 200] += 1;
			if (x_plus < minx) {
				minx = x_plus;
			}
			if (x_plus > maxx) {
				maxx = x_plus;
			}
			if (y_plus < miny) {
				miny = y_plus;
			}
			if (y_plus > maxy) {
				maxy = y_plus;
			}

			//M += data[y][x] * sqrt(x_plus * x_plus + y_plus * y_plus) / (K * sum_T);
		}
	}
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (count[y][x] != 0)
			{
				newdata[y][x] = newdata[y][x] / count[y][x];
			}
		}
	}
	start_x = minx + 200, start_y = miny + 200, end_x = maxx + 200, end_y = maxy + 200;
	/*cout << 200 + minx << endl;
	cout << 200 + maxx << endl;
	cout << 200 + miny << endl;
	cout << 200 + maxy << endl;*/
	cout << "Равномерное масштабирование:" << M << endl;
}