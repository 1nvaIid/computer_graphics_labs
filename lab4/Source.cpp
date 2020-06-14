#include <iostream>
#include <string>
#include <vector>
#include "Header.h"


using namespace std;

int main(int argc, char* argv[]) {
    string space_in, space_out;
    string in[] = { "Sunday", "Monday", "Tuesday" }, out[] = { "Sunday", "Monday", "Tuesday" };
        
    int in_count, out_count;
    try {
        for (int i = 1; i < argc; i++)
        {
            if (string(argv[i]) == "-f") {
               // cout << "ok" ;
                space_in = string(argv[i + 1]);
               // cout << "ok" << endl;
            }
            if (string(argv[i]) == "-t") {
               // cout << "ok";          
                space_out = string(argv[i + 1]);
                //cout << "ok" << endl;
            }
            if (string(argv[i]) == "-i") {
                in_count = atoi(argv[i + 1]);
                for (int j = 0; j < in_count; j++)
                {
                    in[j] = string(argv[i + 2]);
                    i++;
                }
            }
            if (string(argv[i]) == "-o") {
                out_count = atoi(argv[i + 1]);
                for (int j = 0; j < out_count; j++)
                {
                    out[j] = string(argv[i + 2]);
                    i++;
                }
            }
        }
    }
    catch(const exception e){
        cerr << "Wrong Input";
    }
//	cout << space_in << " " << space_out << " " << in_count << " " << out_count << endl;
  /* 
  for (int i = 0; i < in_count; i++)
        cout << in[i] << " ";
    for (int i = 0; i < out_count; i++)
        cout << out[i] << " ";
        */



    try {
        P6 image(in[0], in[1], in[2]);
        image.conv(space_in,space_out);
        image.write(out[0], out[1], out[2]);
    }
    catch (const exception e) {
        cerr << "Cant create obj";
    }
 /* Point p = { 76,255,35 };
    cout << (int)p.b1 << " " << (int)p.b2 << " " << (int)p.b3<<endl;
    Point p1 = YCoCg_to_RGB(p);
    p1 = RGB_to_YCoCg(p1);
    cout << (int)p1.b1 << " " << (int)p1.b2 << " " << (int)p1.b3;*/
   return 0;
}