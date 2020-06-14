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

void  P6::conv(string from, string to) {
	if (from == "HSL") {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				data[i][j] = HSL_to_RGB(data[i][j]);
			}
	}
	if (from == "HSV") {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				data[i][j] = HSV_to_RGB(data[i][j]);
			}
	}
	if (from == "YCbCr.601") {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				data[i][j] = YCbCr601_to_RGB(data[i][j]);
			}
	}
	if (from == "YCbCr.709") {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				data[i][j] = YCbCr709_to_RGB(data[i][j]);
			}
	}
	if (from == "YCoCg") {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				data[i][j] = YCoCg_to_RGB(data[i][j]);
			}
	}
	if (from == "CMY") {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				data[i][j] = CMY_to_RGB(data[i][j]);
			}
	}

	if (to == "HSL") {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				data[i][j] = RGB_to_HSL(data[i][j]);
			}
	}
	if (to == "HSV") {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				data[i][j] = RGB_to_HSV(data[i][j]);
			}
	}
	if (to == "YCbCr.601") {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				data[i][j] = RGB_to_YCbCr601(data[i][j]);
			}
	}
	if (to == "YCbCr.709") {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				data[i][j] = RGB_to_YCbCr709(data[i][j]);
			}
	}
	if (to == "YCoCg") {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				data[i][j] = RGB_to_YCoCg(data[i][j]);
			}
	}
	if (to == "CMY") {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				data[i][j] = RGB_to_CMY(data[i][j]);
			}
	}
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
Point RGB_to_HSV(Point p) {
	double r = p.b1 * 1.0 / 255;
	double g = p.b2 * 1.0 / 255;
	double b = p.b3 * 1.0 / 255;
	double Cmax = max(r, max(g, b));
	double Cmin = min(r, min(g, b));
	double h, s, v = Cmax;
	double delta = Cmax - Cmin;
	if (Cmax == 0)
		s = 0;
	else
		s = (delta) / Cmax;
	if (Cmax == Cmin)
		h = 0;
	else if (r == Cmax)
		h = ((int)round((g - b) / delta) % 6) * 60;
	else if (Cmax == g)
		h = ((int)round((b - r) / delta) + 2) * 60;
	else if (Cmax == b)
		h = ((int)round((r - g) / delta) + 4) * 60;;
	return Point{ (unsigned char)round(h),(unsigned char)round(s * 100),(unsigned char)round(v * 100) };
}
Point HSV_to_RGB(Point p) {
	float r, g, b;
	float h = p.b1;
	float s = p.b2 * 1.0 / 100;
	float v = p.b3 * 1.0 / 100;
	float c = 1.0 * v * s;
	float x = c * 1.0 * (1 - abs((int)round((h / 60)) % 2 - 1));
	float m = v - c * 1.0 ;
	if (h >= 0 && h < 60) {
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
	return Point{ (unsigned char)round((r + m) * 255),(unsigned char)round((g + m) * 255),(unsigned char)round((b + m) * 255) };
}

Point RGB_to_YCbCr601(Point p) {
	double r = p.b1 * 1.0 / 255;
	double g = p.b2 * 1.0 / 255;
	double b = p.b3 * 1.0 / 255;

	double Kb = 0.299;
	double Kr = 0.587;
	double Kg = 0.114;

	double Y = Kr * r + Kg * g + Kb * b;
	double Cb = (b - Y) / (2 * (1 - Kb));
	double Cr = (r - Y) / (2 * (1 - Kr));

	int y = round(Y * 255);
	int cb = round((Cb + 0.5) * 255); 
	int cr = round((Cr + 0.5) * 255);
	if (y < 0) y = 0;
	if (y > 255) y = 255;
	if (cb < 0) cb = 0;
	if (cb > 255) cb = 255;
	if (cr < 0) cr = 0;
	if (cr > 255) cr = 255;
	return Point{ (unsigned char)y, (unsigned char)cb, (unsigned char)cr };
}

Point YCbCr601_to_RGB(Point p) {
	double Y = p.b1 / 255.0;
	double Cb = p.b2 / 255.0 - 0.5;
	double Cr = p.b3 / 255.0 - 0.5;

	double Kb = 0.299;
	double Kr = 0.587;
	double Kg = 0.114;

	double r = Y + (2.0 - 2.0 * Kr) * Cr;
	double g = Y - Kb * (2.0 - 2.0 * Kb) * Cb / Kg - Kr * (2 - 2.0 * Kr) * Cr / Kg;
	double b = Y + (2.0 - 2.0 * Kb) * Cb;

	int R = round(r * 255);
	int G = round(g * 255);
	int B = round(b * 255);

	if (R > 255) R = 255;
	if (R < 0) R = 0;
	if (G > 255) G = 255;
	if (G < 0) G = 0;
	if (B > 255) B = 255;
	if (B < 0) B = 0;
	return Point{ (unsigned char)R, (unsigned char)G, (unsigned char)B };
}

Point RGB_to_YCbCr709(Point p) {
	double r = p.b1 * 1.0 / 255;
	double g = p.b2 * 1.0 / 255;
	double b = p.b3 * 1.0 / 255;

	double Kb = 0.0722;
	double Kr = 0.2126;
	double Kg = 0.7152;

	double Y = Kr * r + Kg * g + Kb * b;
	double Cb = (b - Y) / (2 * (1 - Kb));
	double Cr = (r - Y) / (2 * (1 - Kr));

	int y = round(Y * 255);
	int cb = round((Cb + 0.5) * 255);
	int cr = round((Cr + 0.5) * 255);
	if (y < 0) y = 0;
	if (y > 255) y = 255;
	if (cb < 0) cb = 0;
	if (cb > 255) cb = 255;
	if (cr < 0) cr = 0;
	if (cr > 255) cr = 255;
	return Point{ (unsigned char)y, (unsigned char)cb, (unsigned char)cr };
}

Point YCbCr709_to_RGB(Point p) {
	double Y = p.b1 / 255.0;
	double Cb = p.b2 / 255.0 - 0.5;
	double Cr = p.b3 / 255.0 - 0.5;

	double Kb = 0.0722;
	double Kr = 0.2126;
	double Kg = 0.7152;

	double r = Y + (2.0 - 2.0 * Kr) * Cr;
	double g = Y - Kb * (2.0 - 2.0 * Kb) * Cb / Kg - Kr * (2 - 2.0 * Kr) * Cr / Kg;
	double b = Y + (2.0 - 2.0 * Kb) * Cb;

	int R = round(r * 255);
	int G = round(g * 255);
	int B = round(b * 255);

	if (R > 255) R = 255;
	if (R < 0) R = 0;
	if (G > 255) G = 255;
	if (G < 0) G = 0;
	if (B > 255) B = 255;
	if (B < 0) B = 0;
	return Point{ (unsigned char)R, (unsigned char)G, (unsigned char)B };
}
Point RGB_to_YCoCg(Point p) {
	int r = p.b1;
	int g = p.b2;
	int b = p.b3;

	int tmp = round((r + b) / 2);
	int Co = r - tmp;
	int Cg = round((g - tmp) / 2);
	int Y = tmp + Cg;
	//cout << Y<<" "<< Co<< " "<<Cg;
	return Point{ (unsigned char)Y, (unsigned char)Co, (unsigned char)Cg };
}
Point YCoCg_to_RGB(Point p) {
	int Y = p.b1;
	int Co = p.b2;
	int Cg = p.b3;

	int tmp = Y - Cg;
	int R = tmp + Co;
	int G = Y + Cg;
	int B = (tmp - Co);

	return Point{ (unsigned char)R, (unsigned char)G, (unsigned char)B };
}

Point RGB_to_CMY(Point p) {
	return Point{ (unsigned char)(255-p.b1), (unsigned char)(255 - p.b2), (unsigned char)(255 - p.b3) };
}
Point CMY_to_RGB(Point p) {
	return Point{ (unsigned char)(255 - p.b1), (unsigned char)(255 - p.b2), (unsigned char)(255 - p.b3) };
}