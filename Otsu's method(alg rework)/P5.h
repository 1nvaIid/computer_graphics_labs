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
	vector<vector<double>> newdata;
public:
	double sr;
	P5_image(string filename, int class_numb);
	void write(string filename);
	int otsuThreshold();
	//void otsu(int class_count);
	void otsu2(int class_count);
	int otsu(int p1, int p2);
	void multytresholding(int class_count);
	void maximum_inter_cluster_distances(int class_count);
};