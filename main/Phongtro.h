#pragma once
#include <iostream>  
#include <fstream>  
#include <string>  
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
struct Phongtro {
	string IDPhong; // duoc dung string cho de check
	string SonguoiO;
	long long GiaThue;// gia thue 1 thang
	string NgayPhongdcthue;// Ngay Phong dc thue trung voi Ngay khach thue 
};

struct rootPhongtro {
	Phongtro data;
	rootPhongtro* Left;
	rootPhongtro* Right;
};
rootPhongtro* CreateNodePt(Phongtro Phongtro);
rootPhongtro* InsertNodePt(rootPhongtro* root, Phongtro Phongtro);
rootPhongtro* docfilevaotreePt();
void cntphongtrong(rootPhongtro* root, int& cnt);
void ThemPhongMoichokhachInFile(rootPhongtro*& root, string Id);
void ThemPhongchuaco(rootPhongtro*& root);
void InOrderPt(rootPhongtro* root);
void HienThiDanhSachPhongTro(rootPhongtro* root);
rootPhongtro* DeleteNodePt(rootPhongtro* root, string id);
rootPhongtro* SearchNodePt(rootPhongtro* root, string ID);
void dvmap(rootPhongtro* root, multimap<string, Phongtro>& mtp);
void Timkiemmax(rootPhongtro* root);
long long timgiaGiaThue(string id);


void MenucuaRoom();