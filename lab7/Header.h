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
    vector<vector<Point>> tmp;
    int conv1(int x, int y, double sh);
    int conv2(int x, int y, double sh);
    int conv3(int x, int y, double sh);
public:
    P6(string);
    void write(string);
    void conv(double sh);
    
};


class P5 {
private:
    int width, height, depth;
    vector<vector<unsigned char>> data;
    vector<vector<unsigned char>> tmp;
    int conv(int x, int y, double sh);
public:
    P5(string);
    void write(string);
    void convf(double sh);
    
};

double mins(double b, double e, double f, double h, double d);
double maxs(double b, double e, double f, double h, double d);