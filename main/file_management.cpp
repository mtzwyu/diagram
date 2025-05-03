#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include <cstdlib>
#include <format> 
#include <sstream>
#include <vector>
using namespace std;



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


void removeLineFromFile(const string& filePath, const string& searchString) {
    ifstream fileIn(filePath);
    if (!fileIn) {
        cerr << "Error opening file for reading: " << filePath << endl;
        return;
    }

    vector<string> lines;
    string line;
    while (getline(fileIn, line)) {
        if (line.find(searchString) == string::npos) {
            lines.push_back(line);
        }
    }
    fileIn.close();

    ofstream fileOut(filePath, ios::trunc);
    if (!fileOut) {
        cerr << "Error opening file for writing: " << filePath << endl;
        return;
    }

    for (const auto& l : lines) {
        fileOut << l << endl;
    }
    fileOut.close();
}



