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
	vector<vector<double>> data;
	vector<vector<double>> data_plus;
	vector<vector<double>> data_tilda;
public:
	double sr;
	P5_image(string filename);
	void write(string filename);
	void akoefs();
};