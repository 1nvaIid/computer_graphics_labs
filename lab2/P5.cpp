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
	try {
		data.assign(height, vector<double>(width));
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
			data[i][j] = (double)((unsigned char)color_bw) ;
			sr += (double)((unsigned char)color_bw);
//			data[i][j] = pow(data[i][j], gamma);

		}
	sr /= (height * width);
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
			press_f = (int)pow(data[i][j], 1);
			//cout << press_f << " ";
			fout << press_f;

		}
	}
	fout.flush();
	fout.close();
}



void P5_image::draw_line(int brightness, double x0, double y0, double x1, double y1, double gamma) {

	if (x0>x1) {
		swap(x0, y0);
	}
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx - dy, e2, x2, y2;                          /* error value e_xy */
	double ed = dx + dy == 0 ? 1 : sqrt((float)dx * dx + (float)dy * dy);
	int wd = 1;
	for (wd = (wd + 1) / 2; ; ) {                                   /* pixel loop */
		setPixel(x0, y0, brightness);
		e2 = err; x2 = x0;
		if (2 * e2 >= -dx) {                                           /* x step */
			for (e2 += dy, y2 = y0; e2 < ed * wd && (y1 != y2 || dx > dy); e2 += dx)
				if(sr<128) setPixel(x0, y2 += sy, 255-sr - max(0.0, 255 * (abs(e2) / ed - wd + 1)));
				else setPixel(x0, y2 += sy, sr + max(0.0, 255 * (abs(e2) / ed - wd + 1)));
			if (x0 == x1) break;
			e2 = err; err -= dy; x0 += sx;
		}
		if (2 * e2 <= dy) {                                            /* y step */
			for (e2 = dx - e2; e2 < ed * wd && (x1 != x2 || dx < dy); e2 += dy)
				if (sr < 128) setPixel(x2 += sx, y0, 255 - sr - max(0.0, 255 * (abs(e2) / ed - wd + 1)));
				else setPixel(x2 += sx, y0, sr + max(0.0, 255 * (abs(e2) / ed - wd + 1)));
			if (y0 == y1) break;
			err += dx; y0 += sy;
		}
	}
}


void P5_image::setPixel(int x, int y, double brightness) {
	if(x>=0 && y>=0)
		data[x][y] = brightness;

	//cout << x << " " << y << " " << brightness * brightness << endl;
		//cout << x << " " << y << " " << brightness << endl;

}



void P5_image::check(double a, int b) {
	if (a<0 || a>b) {
		cerr << "wrong point";
		exit(1);
	}
}