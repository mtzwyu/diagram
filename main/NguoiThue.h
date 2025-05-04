#pragma once
#include <iostream>  
#include <fstream>  
#include <string>  
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
struct NguoiThue {
	int maKhachHang;
	long long CCCD;
	string Name;
	int age;
	int IDPhong; // IDPhong là mã số phòng mà người thuê đang ở
	long long SDT;
	string NgayThue;
	long long TienCoc; // tiền cọc
};
struct RootNguoiThue {
	NguoiThue data;
	RootNguoiThue* Left;
	RootNguoiThue* Right;
};
RootNguoiThue* CreateNode(NguoiThue nguoiThue);
RootNguoiThue* InsertNode(RootNguoiThue* root, NguoiThue nguoiThue);
RootNguoiThue* DeleteNode(RootNguoiThue* root, long long CCCD);
void newLESSEE(RootNguoiThue*& root, NguoiThue nguoiThue);
RootNguoiThue* ThemDanhSachNguoiThuetufile();
void InOrder(RootNguoiThue* root);
void DeleteDataInFile(int MKh);
void LayThongTin(NguoiThue& a, int MKH);
void MenuforLessee();