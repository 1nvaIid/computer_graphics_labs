#include <iostream>
#include <string>
#include <vector>
#include "Header.h"


using namespace std;

int main(int argc, char* argv[]) {
    string space_in, space_out;
    string in, out;
        
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
                in = string(argv[i + 2]);
            }
            if (string(argv[i]) == "-o") {
				out_count = atoi(argv[i + 1]);
				out = string(argv[i + 2]);
                
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
        if (in_count == 1) {
            P6 image(in);
            //cout << " ok";
            image.conv(space_in, space_out); 
            if (out_count == 1) {
                image.write(out);
            }
            else {
				string o1 = out;
				o1.insert(out.length() - 4, "_1");
				string o2 = out;
				o2.insert(out.length() - 4, "_2");
				string o3 = out;
				o3.insert(out.length() - 4, "_3");
				image.write(o1, o2, o3);
            }
        }
        else {
            string i1 = in;
            i1.insert(in.length() - 4, "_1");
            string i2 = in;
            i2.insert(in.length() - 4, "_2");
            string i3 = in;
            i3.insert(in.length() - 4, "_3");
            P6 image(i1,i2,i3);
            image.conv(space_in, space_out);
            if (out_count == 1) {
                image.write(out);
            }
            else {
                string o1 = out;
                o1.insert(out.length() - 4, "_1");
                string o2 = out;
                o2.insert(out.length() - 4, "_2");
                string o3 = out;
                o3.insert(out.length() - 4, "_3");
                image.write(o1, o2, o3);
            }
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