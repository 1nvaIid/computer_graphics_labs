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
	int width, height, depth, cc;
	int start_x, start_y, end_x, end_y;
	vector<vector<double>> data;
	vector<vector<double>> newdata;
	vector<vector<int>> count;
public:
	double sr;
	P5_image(string filename);
	void write(string filename);
	void akoefs();
};