#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <tuple>
#include <fstream>

using namespace std;

class P6_image {
private:
	typedef tuple<unsigned char, unsigned char, unsigned char> color;
	int width, height, depth;
	vector<vector<color>> data;
public:
	P6_image(string);
	void inversion();
	void rotate_right();
	void rotate_left();
	void vertical_reflection();
	void horizontal_reflection();
	void write(string);
};