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




double fpart(double x) {
	return x - floor(x);
}

void P5_image::draw_line(int brightness, double x1, double y1, double x2, double y2, double gamma) {

	if (x2 < x1) {
		swap(x1, x2);
		swap(y1, y2);
	}
	double dx = x2 - x1;
	double dy = y2 - y1;
	double gradient = dy / dx;
	double xend = round(x1);
	double yend = y1 + gradient * (xend - x1);
	double xgap = 1 - fpart(x1 + 0.5);
	double xpxl1 = xend;
	double ypxl1 = floor(yend);
	plot(xpxl1, ypxl1, (1 - fpart(yend)) * xgap*brightness/255);
	plot(xpxl1, ypxl1 + 1, fpart(yend) * xgap * brightness / 255);
	double intery = yend + gradient;
	 xend = round(x2);
	yend = y2 + gradient * (xend - x2);
	 xgap = fpart(x2 + 0.5);
	double xpxl2 = xend;
	double ypxl2 = floor(yend);
	plot(xpxl2, ypxl2, (1 - fpart(yend)) * xgap * brightness / 255);
	plot(xpxl2, ypxl2 + 1, fpart(yend) * xgap * brightness / 255);

	for (int i = xpxl1 + 1; i < xpxl2 - 1; i++) {
		plot(i, floor(intery), (1 - fpart(intery)) * brightness / 255);
		plot(i, floor(intery) + 1, fpart(intery) * brightness / 255);
		intery = intery + gradient;
	}
		
}










void P5_image::plot(int x, int y, double brightness) {
	if(x>=0 && y>=0)
		data[floor(x)][floor(y)] = round(brightness*255);

	//cout << x << " " << y << " " << brightness * brightness << endl;
		//cout << x << " " << y << " " << brightness << endl;

}



void P5_image::check(double a, int b) {
	if (a<0 || a>b) {
		cerr << "wrong point";
		exit(1);
	}
}