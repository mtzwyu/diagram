#pragma once  
#include <iostream>  
#include <fstream>  
#include <string>  
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

ifstream chidocfile(string );  
ofstream ghifile(string );
void removeLineFromFile(const string& filePath, const string& searchString);