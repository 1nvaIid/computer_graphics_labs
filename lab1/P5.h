#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <tuple>
#include <fstream>

using namespace std;

class P5_image {
private:
	int width, height, depth;
	vector<vector<unsigned char>> data;
public:
	P5_image(string);
	void inversion();
	void rotate_right();
	void rotate_left();
	void vertical_reflection();
	void horizontal_reflection();
	void write(string);
};