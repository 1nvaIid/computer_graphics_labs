#include "Header.h";
#include <iostream>

using namespace std;

P6::P6(string in1) {
	ifstream fin(in1, ios::binary);
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
	if (c != 'P' || c1 != '6') {
		cout << c << " " << c1;

		cerr << "Wrong Header";
		exit(1);
	}

	fin.read(&c, 1);
	try {
		data.assign(height, vector<Point>(width));
	}
	catch (const exception& e) {
		cerr << "troubles with memory";
		exit(1);
	}

	//check header;


	char br;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (fin.eof()) {
				fin.close();
				throw runtime_error("N E pixels");
			}
			fin.read(&br, 1);
			data[i][j].b1 = ((unsigned char)br);
			fin.read(&br, 1);
			data[i][j].b2 = ((unsigned char)br);
			fin.read(&br, 1);
			data[i][j].b3 = ((unsigned char)br);
		}
	fin.close();
}

P6::P6(string in1, string in2, string in3) {
	ifstream fin1(in1, ios::binary);
	ifstream fin2(in2, ios::binary);
	ifstream fin3(in3, ios::binary);
	if (!fin1.is_open() && !fin2.is_open() && !fin3.is_open()) {
		cerr << "Can't open file, use different files";
		exit(1);
	}
	char c, c1,c2,c3;
	int buf1,buf2, buf3;
	try {
		fin1 >> c >> c1;
		fin1 >> width >> height >> depth;

		fin2 >> c2 >> c3;
		fin2 >> buf1 >> buf2 >> buf3;
		if (c != c2 && c1 != c3 && width != buf1 && height != buf2 && depth != buf3) {
			cerr << "Wrong files";
			exit(1);
		}
		fin3 >> c2 >> c3;
		fin3 >> buf1 >> buf2 >> buf3;
		if (c != c2 && c1 != c3 && width != buf1 && height != buf2 && depth != buf3) {
			cerr << "Wrong files";
			exit(1);
		}
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
//		cout << c << " " << c1;
		cerr << "Wrong Header";
		exit(1);
	}

	fin1.read(&c, 1);
	fin2.read(&c, 1);
	fin3.read(&c, 1);
	try {
		data.assign(height, vector<Point>(width));
	}
	catch (const exception& e) {
		cerr << "troubles with memory";
		exit(1);
	}

	//check header;


	char br;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (fin1.eof() && fin2.eof()&& fin3.eof()) {
				fin1.close();
				fin2.close();
				fin3.close();
				throw runtime_error("N E pixels");
			}
			fin1.read(&br, 1);
			data[i][j].b1 = ((unsigned char)br);
			fin2.read(&br, 1);
			data[i][j].b2 = ((unsigned char)br);
			fin3.read(&br, 1);
			data[i][j].b3 = ((unsigned char)br);
		}
	fin1.close();
	fin2.close();
	fin3.close();
}


void P6::write(string filename) {
		ofstream fout(filename, ios::binary);
		if (!fout.is_open()) {
			throw runtime_error("Can't open output file");
		}
		fout << "P6\n" << width << ' ' << height << '\n' << depth << '\n';
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				fout << data[i][j].b1;
				fout << data[i][j].b2;
				fout << data[i][j].b3;
			}
		//cerr << filename;
		fout.flush();
		fout.close();
}
void P6::write(string out1, string out2, string out3) {
	ofstream fout1(out1, ios::binary);
	ofstream fout2(out2, ios::binary);
	ofstream fout3(out3, ios::binary);
	if (!fout1.is_open() && !fout2.is_open()&&!fout3.is_open()) {
		throw runtime_error("Can't open output file");
	}
	fout1 << "P5\n" << width << ' ' << height << '\n' << depth << '\n';
	fout2 << "P5\n" << width << ' ' << height << '\n' << depth << '\n';
	fout3 << "P5\n" << width << ' ' << height << '\n' << depth << '\n';
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			fout1 << data[i][j].b1;
			fout2 << data[i][j].b2;
			fout3 << data[i][j].b3;
		}
	//cerr << filename;
	fout1.flush();
	fout1.close();
	fout2.flush();
	fout2.close();
	fout3.flush();
	fout3.close();

}

// https://www.rapidtables.com/convert/color/rgb-to-hsl.html
Point RGB_to_HSL(Point p) {
	double r = p.b1 * 1.0 / 255;
	double g = p.b2 * 1.0 / 255;
	double b = p.b3 * 1.0 / 255;
	double Cmax = max(r, max(g, b));
	double Cmin = min(r, min(g, b));
	double h, s ,l= (Cmax + Cmin) / 2;
	double delta = Cmax - Cmin;	
	if (Cmax - Cmin == 0)
		s = 0;
	else
		s = (delta) / (1 - abs((Cmax + Cmin)-1));
	if (Cmax == Cmin)
		h = 0;
	else if (r == Cmax)
		h = ((int)round((g - b) / delta)%6)*60;
	else if (Cmax == g)
		h = ((int)round((b - r) / delta) + 2 ) * 60;
	else if (Cmax == b)
		h = ((int)round((r - g) / delta) + 4) * 60;;
	return Point{ (unsigned char)round(h ),(unsigned char)round(s*100),(unsigned char)round(l*100) };
}
Point HSL_to_RGB(Point p) {
	float r, g, b;
	float h = p.b1;
	float s = p.b2*1.0/ 100;
	float l = p.b3 * 1.0 / 100;
	float c = 1.0*(1 - abs(2*l - 1)) * s;
	float x = c *1.0* (1 - abs((int)round((h / 60))%2-1));
	float m = l - c*1.0 / 2;
	if (h >= 0 && h < 60){
		r = c; g = x; b = 0;
	}
	else if (h < 120) {
		r = x; g = c; b = 0;
	}
	else if (h < 180) {
		r = 0; g = c; b = x;
	}
	else if (h < 240) {
		r = 0; g = x; b = c;
	}
	else if (h < 300) {
		r = x; g = 0; b = c;
	}
	else if (h < 360) {
		r = c; g = 0; b = x;
	}
	return Point{ (unsigned char)round((r+m)*255),(unsigned char)round((g + m) * 255),(unsigned char)round((b + m) * 255) };
}
