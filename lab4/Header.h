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
Point RGB_to_HSV(Point p);
Point HSV_to_RGB(Point p);
Point RGB_to_YCbCr601(Point p);
Point YCbCr601_to_RGB(Point p);
Point RGB_to_YCbCr709(Point p);
Point YCbCr709_to_RGB(Point p);
Point RGB_to_YCoCg(Point p);
Point YCoCg_to_RGB(Point p);
Point RGB_to_CMY(Point p);
Point CMY_to_RGB(Point p);