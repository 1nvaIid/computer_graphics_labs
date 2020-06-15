#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

class P5_image {
private:
	int width, height, depth;
	vector<vector<double>> data;
public:
	double sr;
	P5_image(string filename, double gamma, bool sRGB);
	void draw_line(int brightness, double x1, double y1, double x2, double y2, double gamma);
	void write(string filename, double gamma, bool srgb);
	void plot(int x, int y, double);
	void check(double, int);
};