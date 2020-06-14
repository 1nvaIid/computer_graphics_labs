#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <stdexcept>

using namespace std;

struct Point {
	unsigned char b1, b2, b3;
};

class P6 {
private:
    int width, height, depth;
    vector<vector<Point>> data;
public:
    P6(string);
    P6(string, string, string);
    void write(string);
    void write(string, string, string);
    void conv(string, string);
}; 


Point RGB_to_HSL(Point p);
Point HSL_to_RGB(Point p);