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
		//cout << c << " " << c1;

		cerr << "Wrong Header";
		exit(1);
	}

	fin.read(&c, 1);
	try {
		data.assign(height, vector<Point>(width));
		newdata.assign(height, vector<Point>(width));
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
				cerr << "N E pixels";
				exit(1);
			}
			fin.read(&br, 1);
			data[i][j].b1 = ((unsigned char)br);
			//data[i][j].b1 = ((unsigned char)br);
			fin.read(&br, 1);
			data[i][j].b2 = ((unsigned char)br);
			fin.read(&br, 1);
			data[i][j].b3 = ((unsigned char)br);
		}
	fin.close();
}

P5::P5(string in1) {

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
	if (c != 'P' || c1 != '5') {
		//cout << c << " " << c1;

		cerr << "Wrong Header";
		exit(1);
	}

	fin.read(&c, 1);
	try {
		data.assign(height, vector<unsigned char>(width));
		newdata.assign(height, vector<unsigned char>(width));
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
				cerr << "N E pixels";
				exit(1);
			}
			fin.read(&br, 1);
			data[i][j] = ((unsigned char)br);

		}
	fin.close();
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
			fout << newdata[i][j].b1;
			fout << newdata[i][j].b2;
			fout << newdata[i][j].b3;
		}
	//cerr << filename;

	fout.flush();
	fout.close();
}

void P5::write(string filename) {
	ofstream fout(filename, ios::binary);
	if (!fout.is_open()) {
		throw runtime_error("Can't open output file");
	}
	fout << "P5\n" << width << ' ' << height << '\n' << depth << '\n';
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			fout << newdata[i][j];
		}
	//cerr << filename;
	fout.flush();
	fout.close();
}

void P6::conv(double sh) {
	for (int i = 1; i < height - 1; i++)
		for (int j = 1; j < width - 1; j++)
		{
			newdata[i][j].b1 = conv1(i, j, sh);
			newdata[i][j].b2 = conv2(i, j, sh);
			newdata[i][j].b3 = conv3(i, j, sh);
		}
}


void P5::convf(double sh) {
	for (int i = 1; i < height - 1; i++)
		for (int j = 1; j < width - 1; j++)
		{
			newdata[i][j] = conv(i, j, sh);
		}
}

int P6::conv1(int x, int y, double sh) {

	double a = (double)((int)data[x - 1][y - 1].b1) / 255.0;
	double b = (double)((int)data[x][y - 1].b1) / 255.0;
	double c = (double)((int)data[x + 1][y - 1].b1) / 255;
	double d = (double)((int)data[x - 1][y].b1) / 255;
	double e = (double)((int)data[x][y].b1) / 255;
	double f = (double)((int)data[x + 1][y].b1) / 255;
	double g = (double)((int)data[x - 1][y + 1].b1) / 255;
	double h = (double)((int)data[x][y + 1].b1) / 255;
	double i = (double)((int)data[x + 1][y + 1].b1) / 255;
	double mn = mins(b, d, e, f, h) + mins(mins(b, d, e, f, h), a, c, g, i);
	double mx = maxs(b, d, e, f, h) + maxs(maxs(b, d, e, f, h), a, c, g, i);
	double A;
	double W;
	if (mx == 0.0)
	{
		A = 0;
		W = 0;
	}
	else {
		A = sqrt(min(mn, 2 - mx) / mx);
		W = A * (-1) / (8.0 - 3.0 * sh);
	}

	double brigt = ((b * W + d * W + e + f * W + h * W) / (1 + 4.0 * W));
	int brigthness = (round(((b * W + d * W + e + f * W + h * W) / (1 + 4.0 * W)) * 255));
	return brigthness;
}
int P6::conv2(int x, int y, double sh) {

	double a = (double)((int)data[x - 1][y - 1].b2) / 255.0;
	double b = (double)((int)data[x][y - 1].b2) / 255.0;
	double c = (double)((int)data[x + 1][y - 1].b2) / 255;
	double d = (double)((int)data[x - 1][y].b2) / 255;
	double e = (double)((int)data[x][y].b2) / 255;
	double f = (double)((int)data[x + 1][y].b2) / 255;
	double g = (double)((int)data[x - 1][y + 1].b2) / 255;
	double h = (double)((int)data[x][y + 1].b2) / 255;
	double i = (double)((int)data[x + 1][y + 1].b2) / 255;
	double mn = mins(b, d, e, f, h) + mins(mins(b, d, e, f, h), a, c, g, i);
	double mx = maxs(b, d, e, f, h) + maxs(maxs(b, d, e, f, h), a, c, g, i);
	double A;
	double W;
	if (mx == 0.0)
	{
		A = 0;
		W = 0;
	}
	else {
		A = sqrt(min(mn, 2 - mx) / mx);
		W = A * (-1) / (8.0 - 3.0 * sh);
	}

	double brigt = ((b * W + d * W + e + f * W + h * W) / (1 + 4.0 * W));
	int brigthness = (round(((b * W + d * W + e + f * W + h * W) / (1 + 4.0 * W)) * 255));
	return brigthness;

}
int P6::conv3(int x, int y, double sh) {

	double a = (double)((int)data[x - 1][y - 1].b3) / 255.0;
	double b = (double)((int)data[x][y - 1].b3) / 255.0;
	double c = (double)((int)data[x + 1][y - 1].b3) / 255;
	double d = (double)((int)data[x - 1][y].b3) / 255;
	double e = (double)((int)data[x][y].b3) / 255;
	double f = (double)((int)data[x + 1][y].b3) / 255;
	double g = (double)((int)data[x - 1][y + 1].b3) / 255;
	double h = (double)((int)data[x][y + 1].b3) / 255;
	double i = (double)((int)data[x + 1][y + 1].b3) / 255;
	double mn = mins(b, d, e, f, h) + mins(mins(b, d, e, f, h), a, c, g, i);
	double mx = maxs(b, d, e, f, h) + maxs(maxs(b, d, e, f, h), a, c, g, i);
	double A;
	double W;
	if (mx == 0.0)
	{
		A = 0;
		W = 0;
	}
	else {
		A = sqrt(min(mn, 2 - mx) / mx);
		W = A * (-1) / (8.0 - 3.0 * sh);
	}

	double brigt = ((b * W + d * W + e + f * W + h * W) / (1 + 4.0 * W));
	int brigthness = (round(((b * W + d * W + e + f * W + h * W) / (1 + 4.0 * W)) * 255));
	return brigthness;

}

int P5::conv(int x, int y, double sh) {

	double a = (double)((int)data[x - 1][y - 1]) / 255.0;
	double b = (double)((int)data[x][y - 1]) / 255.0;
	double c = (double)((int)data[x + 1][y - 1]) / 255;
	double d = (double)((int)data[x - 1][y]) / 255;
	double e = (double)((int)data[x][y]) / 255;
	double f = (double)((int)data[x + 1][y]) / 255;
	double g = (double)((int)data[x - 1][y + 1]) / 255;
	double h = (double)((int)data[x][y + 1]) / 255;
	double i = (double)((int)data[x + 1][y + 1]) / 255;
	double mn = mins(b, d, e, f, h) + mins(mins(b, d, e, f, h), a, c, g, i);
	double mx = maxs(b, d, e, f, h) + maxs(maxs(b, d, e, f, h), a, c, g, i);
	double A;
	double W;
	if (mx == 0.0)
	{
		A = 0;
		W = 0;
	}
	else {
		A = sqrt(min(mn, 2 - mx) / mx);
		W = A * (-1) / (8.0 - 3.0 * sh);
	}
	
	double brigt = ((b * W + d * W + e + f * W + h * W) / (1 + 4.0 * W));
	int brigthness = (round(((b * W + d * W + e + f * W + h * W) / (1 + 4.0 * W)) * 255));
	return brigthness;

}

double mins(double b, double e, double f, double h, double d) {
	return min(min(b, e), min(min(f, h), d));
}
double maxs(double b, double e, double f, double h, double d) {
	return max(max(b, e), max(max(f, h), d));
}