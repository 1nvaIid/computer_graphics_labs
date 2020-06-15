#include <iostream>
#include <string>
#include <vector>
#include "Header.h"


using namespace std;

int main(int argc, char* argv[]) {
    //cerr << argv[1] << " " << argv[2] << " " << argv[3];
    string in = argv[1], out = argv[2];
    int sh = stold(argv[3]);

  


    try {
        if (in.substr(in.length()-4,4) == ".pgm") {
            P5 image(in);
            image.convf(sh);
            image.write(out);
       }
        if (in.substr(in.length() - 4, 4) == ".ppm") {
            P6 image(in);
            image.conv(sh);
            image.write(out);
        }
    }
    catch (const exception e) {
        cerr << "Cant create obj";
    }
    /* Point p = { 0,0,128 };
        cout << (int)p.b1 << " " << (int)p.b2 << " " << (int)p.b3<<endl;
        Point p1 = RGB_to_HSL(p);
        p1 = HSL_to_RGB(p1);
        cout << (int)p1.b1 << " " << (int)p1.b2 << " " << (int)p1.b3;*/
    return 0;
}