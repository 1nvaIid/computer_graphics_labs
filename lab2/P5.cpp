#include "P5.h"

P5_image::P5_image(string filename, double gamma, bool sRGB) {
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
	data.assign(height, vector<double>(width));

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
			data[i][j] = (double)((unsigned char)color_bw) ;
			data[i][j] = pow(data[i][j], gamma);

		}
	fin.close();
}

void P5_image::write(string filename, double gamma, bool srgb) {
	ofstream fout(filename, ios::binary);
	if (!fout.is_open()) {
		throw runtime_error("Can't open output file");
	}
	fout << "P5\n" << width << ' ' << height << '\n' << depth << '\n';

	unsigned char press_f;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			press_f = (int)pow(data[i][j], 1 / gamma);
			//cout << press_f << " ";
			fout << press_f;

		}
	}
	fout.flush();
	fout.close();
}


void P5_image::draw_line(int brightness, double wd, double x0, double y0, double x1, double y1) {
	{
		check(x0, width);
		check(x1, width);
		check(y1, height);
		check(y0, height);
		if (x0 > x1 || y0 > y1) {
			cerr << "wrong point location";
			exit(1);
		}
		int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
		int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
		int err = dx - dy, e2, x2, y2;
		float ed = dx + dy == 0 ? 1 : sqrt((float)dx * dx + (float)dy * dy);
	
		for (wd = (wd + 1) / 2; ; ) {
			setPixell(x0, y0, max(0.0, brightness * (abs(err - dx + dy) / ed - wd + 1)));
			e2 = err; x2 = x0;
			if (2 * e2 >= -dx) {
				for (e2 += dy, y2 = y0; e2 < ed * wd && (y1 != y2 || dx > dy); e2 += dx)
					setPixell(x0, y2 += sy, max(0.0, brightness * (abs(e2) / ed - wd + 1)));
				if (x0 == x1) break;
				e2 = err; err -= dy; x0 += sx;
			}
			if (2 * e2 <= dy) {
				for (e2 = dx - e2; e2 < ed * wd && (x1 != x2 || dx < dy); e2 += dy)
					setPixelr(x2 += sx, y0, max(0.0, brightness * (abs(e2) / ed - wd + 1)));
				if (y0 == y1) break;
				err += dx; y0 += sy;
			}
		}
	}
}

void P5_image::setPixel(int x, int y, double brightness) {
	try {
		data[x][y] = (brightness);
	}
	catch (const std::exception&) {

	}
}

void P5_image::setPixell(int x, int y, double brightness) {
	try {
		data[x][y] = (brightness / ( 2) + data[x + 1][y] + data[x][y - 1]) / 3;
	}
	catch (const std::exception&) {

	}
}

void P5_image::setPixelr(int x, int y, double brightness) {
	try {
		data[x][y] = (brightness / (2) + data[x - 1][y] + data[x][y + 1]) / 3;
	}
	catch (const std::exception&) {

	}
}

void P5_image::check(double a, int b) {
	if (a<0 || a>b) {
		cerr << "wrong point";
		exit(1);
	}
}