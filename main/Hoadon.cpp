#include "file_management.h"

using namespace std;
#define FileHoadon "Resource FIles/Bill.txt"
#define FileCThoadon "Resource FIles/BillDetail.txt"

struct HoaDon{
	int IdBill;
	string name; // ten ng dung ra thue phong
	int IdPhong;
	double TongTien;
};

struct TienRac:HoaDon {
	int IdTienRac;
	double TienRac;
};

struct TienNuoc :HoaDon {
	int IdTienNuoc;
	double TienNuoc;
};

struct TienDien :TienNuoc {
	int IdTienDien;
	double TienDien;
};
typedef TienDien Full;

struct rootBill {
	Full data;
	rootBill* Left;
	rootBill* Right;
};

// ham tao 1 Node hoa don

rootBill* CreateNodeBill(Full hoadon) {
	rootBill* newNode = new rootBill;
	newNode->data = hoadon;
	newNode->Left = nullptr;
	newNode->Right = nullptr;
	return newNode;
}
// sap xep cay them hoa don giam dan
rootBill* InsertNodeBill(rootBill* root, Full hoadon) {
	if (root == nullptr) {
		return CreateNodeBill(hoadon);
	}
	if (hoadon.TongTien < root->data.TongTien) {
		root->Left = InsertNodeBill(root->Left, hoadon);
	}
	else if (hoadon.TongTien > root->data.TongTien) {
		root->Right = InsertNodeBill(root->Right, hoadon);
	}
	else {
		cout << "Hoa don da ton tai!" << endl;
	}
	return root;
}

rootBill* docfilevaotreeBill() {
	ifstream file = chidocfile(FileHoadon);
	Full hoadon;
	rootBill* root = nullptr;
	while (file >> hoadon.IdBill) {
		file.ignore();
		getline(file, hoadon.name, '|');
		file >> hoadon.IdPhong;
		file.ignore();
		file >> hoadon.TongTien;
		root = InsertNodeBill(root, hoadon);
	}
	file.close();
	return root;
}




