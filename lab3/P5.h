#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <fstream>

using namespace std;

class P5 {
private:
    int width, height, depth;
    vector<vector<double>> image;
    vector<vector<double>> err;
public:
    P5(string, bool, double, bool);
    void write(string, double, bool, int);
    void dither(int, int, double);
};