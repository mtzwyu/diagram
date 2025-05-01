#include "file_management.h"
using namespace std;
#define Filephongtro "Resource FIles/Room.txt"


struct Phongtro {
	int IDPhong;
	int SonguoiO;
	double GiaThue;// gia thue 1 thang
};

struct rootPhongtro {
	Phongtro data;
	rootPhongtro* Left;
	rootPhongtro* Right;
};


rootPhongtro* CreateNodePt(Phongtro Phongtro) {
	rootPhongtro* newNode = new rootPhongtro;
	newNode->data = Phongtro;
	newNode->Left = nullptr;
	newNode->Right = nullptr;
	return newNode;
}

rootPhongtro* InsertNodePt(rootPhongtro* root, Phongtro Phongtro) {
	if (root == nullptr) {
		return CreateNodePt(Phongtro);
	}
	if (Phongtro.IDPhong < root->data.IDPhong) {
		root->Left = InsertNodePt(root->Left, Phongtro);
	}
	else if (Phongtro.IDPhong > root->data.IDPhong) {
		root->Right = InsertNodePt(root->Right, Phongtro);
	}
	else {
		cout << "Phong da ton tai!" << endl;
	}
	return root;
}


rootPhongtro* docfilevaotreePt() {
	ifstream file(Filephongtro);
	rootPhongtro* root = nullptr;
	Phongtro Phongtro;
	while (file >> Phongtro.IDPhong) {
		file.ignore();
		file >> Phongtro.SonguoiO;
		file.ignore();
		file >> Phongtro.GiaThue;
		root = InsertNodePt(root, Phongtro);
	}
	file.close();
	return root;
}

void ThemPhongTromoi(rootPhongtro*& root) {
	Phongtro Phongtro;
	ofstream file = ghifile(Filephongtro);
	cout << "Nhap ID phong: ";
	cin >> Phongtro.IDPhong;
	cout << "Nhap so nguoi o: ";
	cin >> Phongtro.SonguoiO;
	cout << "Nhap gia thue: ";
	cin >> Phongtro.GiaThue;
	file << Phongtro.IDPhong << "|" << Phongtro.SonguoiO << "|" << Phongtro.GiaThue << endl;
	root = InsertNodePt(root, Phongtro);
	file.close();
}


void InOrderPt(rootPhongtro* root) {
	if (root != nullptr) {
		InOrderPt(root->Left);
		cout << root->data.IDPhong << "\t\t" << root->data.SonguoiO << "\t\t\t" << root->data.GiaThue << " dong" << endl;
		InOrderPt(root->Right);
	}
}
// hien thi danh sach phong tro
void HienThiDanhSachPhongTro(rootPhongtro* root) {
	cout << "IDPhong\t\tSoNguoiO\t\tGiaThue" << endl;
	InOrderPt(root);
}
// xoa phong tro theo Id
rootPhongtro* DeleteNodePt(rootPhongtro* root, int IDPhong) {
	if (root == nullptr) {
		return root;
	}
	if (IDPhong < root->data.IDPhong) {
		root->Left = DeleteNodePt(root->Left, IDPhong);
	}
	else if (IDPhong > root->data.IDPhong) {
		root->Right = DeleteNodePt(root->Right, IDPhong);
	}
	else {
		if (root->Left == nullptr) {
			rootPhongtro* temp = root->Right;
			delete root;
			return temp;
		}
		else if (root->Right == nullptr) {
			rootPhongtro* temp = root->Left;
			delete root;
			return temp;
		}
		rootPhongtro* temp = root->Right;
		while (temp && temp->Left != nullptr) {
			temp = temp->Left;
		}
		root->data = temp->data;
		root->Right = DeleteNodePt(root->Right, temp->data.IDPhong);
	}
	return root;
}
// tim kiem phong tro theo ID
rootPhongtro* SearchNodePt(rootPhongtro* root, int IDPhong) {
	if (root == nullptr || root->data.IDPhong == IDPhong) {
		return root;
	}
	if (IDPhong < root->data.IDPhong) {
		return SearchNodePt(root->Left, IDPhong);
	}
	return SearchNodePt(root->Right, IDPhong);
}



// xoa du lieu trong file vua tim kiem duoc theo ID phong
void DeleteDataInFilePt(int IDPhong) {
	ifstream file(Filephongtro);
	ofstream tempFile("resouce files/temp.txt");
	ofstream file1("resouce files/old_room.txt");
	Phongtro Phongtro;
	while (file >> Phongtro.IDPhong) {
		file.ignore();
		file >> Phongtro.SonguoiO;
		file.ignore();
		file >> Phongtro.GiaThue;
		if (Phongtro.IDPhong != IDPhong) {
			tempFile << Phongtro.IDPhong << "|" << Phongtro.SonguoiO << "|" << Phongtro.GiaThue << endl;
		}
		else {
			file1 << Phongtro.IDPhong << "|" << Phongtro.SonguoiO << "|" << Phongtro.GiaThue << endl;
		}
	}
	file.close();
	tempFile.close();
	remove(Filephongtro);
	rename("resouce files/temp.txt", Filephongtro);
}

void MenucuaRoom() {
	rootPhongtro* root = docfilevaotreePt();
LOOP:
	cout << "====================QUAN LY PHONG TRO====================" << endl;
	cout << "- 1. Them phong tro" << endl;
	cout << "- 2. Xoa phong tro" << endl;
	cout << "- 3. Tim kiem phong tro" << endl;
	cout << "- 4. Hien thi danh sach tat ca phong tro" << endl;
	cout << "- 5. Thoat" << endl;
	cout << "- Nhap lua chon: ";
	int choice;
	cin >> choice;
	switch (choice) {
	case 1: {
		system("cls");
		ThemPhongTromoi(root);
		break;
	}
	case 2: {
		system("cls");
		int IDPhong;
		cout << "Nhap ID phong can xoa: ";
		cin >> IDPhong;
		root = DeleteNodePt(root, IDPhong);
		DeleteDataInFilePt(IDPhong);
		break;
	}
	case 3: {
		system("cls");
		int IDPhong;
		cout << "Nhap ID phong can tim: ";
		cin >> IDPhong;
		rootPhongtro* result = SearchNodePt(root, IDPhong);
		if (result != nullptr) {
			cout << "Phong da ton tai!" << endl;
			cout << "IDPhong\t\tSoNguoiO\t\tGiaThue" << endl;
			cout << result->data.IDPhong << "\t\t" << result->data.SonguoiO << "\t\t\t" << result->data.GiaThue << " dong" << endl;
		}
		else {
			cout << "Phong khong ton tai!" << endl;
		}
		break;
	}
	case 4: {
		system("cls");
		cout << "----------------------Danh Sach Phong Tro------------------------\n";
		HienThiDanhSachPhongTro(root);
		break;
	}
	case 5: {
		cout << "Cam on ban da su dung phan mem!" << endl;
		break;
	}
	default:
	{
		system("cls");
		cout << "Lua chon khong hop le!" << endl;
		break;
	}
	}
	system("pause");
	system("cls");
		goto LOOP;
}

