#pragma once
#include <iostream>  
#include <fstream>  
#include <string>  
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

struct HoaDon {
	int MaBill;
	int Makhachhang;
	string name;
	string IDphong;
	long long TienDien;
	long long TienNuoc;
	long long TienPhong;
	long long TongTien;
	string status;
	string ngayThanhToan;
};



struct rootBill {
	HoaDon Bill;
	rootBill* Left;
	rootBill* Right;
};
void newBill(rootBill* root);

rootBill* DocFileBill();


void MenuforBill();