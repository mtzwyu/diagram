#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using ll = long long;

#define FilePhongTro ""
#define FileHoaDon ""
#define FileCThoaDon ""


ifstream chidocfile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Khong mo duoc file " << filename << endl;
        exit(1);
    }
    return file;
}

ofstream ghifile(string filename) {  
    ofstream outfile;
    outfile.open(filename,ios::app);
    return outfile;
}





