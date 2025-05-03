#include "file_management.h"
#include "NguoiThue.h"

using namespace std;
#define Filephongtro "Resource FIles/Room.txt"


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

rootPhongtro* CreateNodePt(Phongtro Phongtro) {
	rootPhongtro* newNode = new rootPhongtro;
	newNode->data = Phongtro;
	newNode->Left = nullptr;
	newNode->Right = nullptr;
	return newNode;
}

rootPhongtro* InsertNodePt(rootPhongtro* root, Phongtro Phongtro) {
	int id = stoi(Phongtro.IDPhong.substr(2));
	
	if (root == nullptr) {
		return CreateNodePt(Phongtro);
	}
	int idroot = stoi(root->data.IDPhong.substr(2));
    if (id < idroot) {
		root->Left = InsertNodePt(root->Left, Phongtro);
	}
	else if (id > idroot) {
		root->Right = InsertNodePt(root->Right, Phongtro);
	}
	else {
		cout << "Phong da ton tai!" << endl;
	}
	return root;
}

// doc file vao cây
rootPhongtro* docfilevaotreePt() {
	ifstream file(Filephongtro);
	rootPhongtro* root = nullptr;
	Phongtro Phongtro;
    while (getline(file, Phongtro.IDPhong, '|')) {
    getline(file, Phongtro.SonguoiO, '|');  
    getline(file, Phongtro.NgayPhongdcthue, '|'); 
    file >> Phongtro.GiaThue;
    file.ignore(); 
    root = InsertNodePt(root, Phongtro);
    }
	file.close();
	return root;
}
// check so luong phong trong


void cntphongtrong(rootPhongtro* root, int &cnt) {
	if (root != nullptr) {
		cntphongtrong(root->Left, cnt);
		if (root->data.SonguoiO == "0") {
			cout << root->data.IDPhong << "\t\t" << root->data.SonguoiO << "\t\t\t" << root->data.NgayPhongdcthue << "\t\t\t" << root->data.GiaThue << " dong" << endl;
			cnt++;
		}
		cntphongtrong(root->Right, cnt);
	}
}
//Them Phong cho khach theo ID
void ThemPhongMoichokhachInFile(rootPhongtro *&root,string Id) {
	Id = "id" + Id;
	removeLineFromFile(Filephongtro, Id);
	ofstream file = ghifile(Filephongtro);
	Phongtro Phongtro;
	cout << "Nhap id Phong: ";
	cin >> Phongtro.IDPhong;
	cout << "Nhap so luong khach o: ";
	cin >> Phongtro.SonguoiO;
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);
	Phongtro.NgayPhongdcthue = to_string(ltm.tm_mday) + "/" + to_string(1 + ltm.tm_mon) + "/" + to_string(1900 + ltm.tm_year);
	cout << "Nhap Gia Thue: ";
	cin >> Phongtro.GiaThue;
	file  << "id" << Phongtro.IDPhong << "|" << Phongtro.SonguoiO << "|" << Phongtro.NgayPhongdcthue << "|" << Phongtro.GiaThue;
	InsertNodePt(root, Phongtro);
	file.close();
}



// Them Thong tin phong chua co trong danh sách
void ThemPhongchuaco(rootPhongtro*& root) {
	Phongtro Phongtro;
	ofstream file = ghifile(Filephongtro);
	cin.ignore();
	cout << "Nhap id Phong: ";
	string s = "";
	cin >> s;
	Phongtro.IDPhong = "id" + s;
	cout << "Nhap gia Phong: ";
	cin >> Phongtro.GiaThue;
	file << Phongtro.IDPhong << "|" << "0" << "|" << "              " << "|" << Phongtro.GiaThue << endl;
	InsertNodePt(root, Phongtro);
	file.close();
}




void InOrderPt(rootPhongtro* root) {
	if (root != nullptr) {
		InOrderPt(root->Left);
		cout << root->data.IDPhong << "\t\t\t" << root->data.SonguoiO << "\t\t\t" << root->data.NgayPhongdcthue << "\t\t" << root->data.GiaThue << " dong" << endl;
		InOrderPt(root->Right);
	}
}
// hien thi danh sach phong tro
void HienThiDanhSachPhongTro(rootPhongtro* root) {
	cout << "ID Phong\t\tSo Nguoi O\t\tNgay Thue\t\tGia Thue" << endl;
	InOrderPt(root);
}
// xoa phong tro theo Id
rootPhongtro* DeleteNodePt(rootPhongtro* root, string id) {
	id = "id" + id;
	if (root == nullptr) {
		return root;
	}
	if (id < root->data.IDPhong) {
		root->Left = DeleteNodePt(root->Left, id);
	}
	else if (id > root->data.IDPhong) {
		root->Right = DeleteNodePt(root->Right, id);
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
// tim kiem phong tro theo Id phong
rootPhongtro* SearchNodePt(rootPhongtro* root, string ID) {
	if (root == nullptr || root->data.IDPhong == ID) {
		return root;
	}
	if (ID < root->data.IDPhong) {
		return SearchNodePt(root->Left, ID);
	}
	return SearchNodePt(root->Right, ID);
}

//Cho biết thông tin các Phòng thuê có số người thuê đông nhất(nhiều người ở cùng phòng nhất).
// duyet vao multimap de tim kiem de hon
void dvmap(rootPhongtro* root, multimap<string, Phongtro> &mtp) {
	if (root != nullptr) {
		dvmap(root->Left, mtp);
		mtp.insert(make_pair(root->data.SonguoiO, root->data));
		dvmap(root->Right, mtp);
	}
}

// Tìm kiếm Phong tro dong nhat
void Timkiemmax(rootPhongtro *root) {
    multimap<string, Phongtro> mtp; 
    dvmap(root, mtp);
    if (!mtp.empty()) {
		auto max = mtp.rbegin()->first;
		cout << "ID Phong\t\tSo Nguoi O\t\tNgay Thue\t\tGia Thue" << endl;
		for (auto it = mtp.rbegin(); it != mtp.rend(); it++) {
			if (max == it->first) {
				cout << it->second.IDPhong << "\t\t\t" << it->second.SonguoiO << "\t\t\t" << it->second.NgayPhongdcthue << "\t\t" << it->second.GiaThue << " dong" << endl;
			}
			else {
				break;
			}
		}
       
		
        
    } else {
        cout << "Khong co phong tro nao trong danh sach." << endl;
    }
}





void MenucuaRoom() {
LOOP:
	rootPhongtro* root = NULL;
	root = docfilevaotreePt();

	cout << "====================QUAN LY PHONG TRO====================" << endl;
	cout << "- 1. Them phong tro moi" << endl;
	cout << "- 2. Xoa phong tro" << endl;
	cout << "- 3. Tim kiem phong tro" << endl;
	cout << "- 4. Hien thi danh sach tat ca phong tro" << endl;
	cout << "- 5. Hien thi cac phong tro co so nguoi o dong nhat" << endl;
	cout << "- 6. Thoat" << endl;
	cout << "- Nhap lua chon: ";
	int choice;
	cin >> choice;
	switch (choice) {
	case 1: {
		system("cls");
		int chon;
		cout << "1. Them thong tin phong tro moi (khong nam trong file truoc day)" << endl;
		cout << "2. Them phong tin phong tro cho khach hang toi thue" << endl;
		cout << "Lua chon: ";
		cin >> chon;
		system("cls");
		if (chon == 1) {
			ThemPhongchuaco(root);
		}
		else if (chon == 2) {
			int cnt = 0;
			cout << "ID Phong\t\tSo Nguoi O\t\tNgay Thue\t\tGia Thue" << endl;
			cntphongtrong(root, cnt);
			if (cnt == 0) break;
			cout << "Nhap id phong moi: ";
			string id;
			cin >> id;
			DeleteNodePt(root, id);
			ThemPhongMoichokhachInFile(root,id);
		}
		break;
	}
	case 2: {
		system("cls");
		string Id;
		cout << "Nhap so phong can xoa: ";
		cin >> Id;
		Id = "id" + Id;
		root = DeleteNodePt(root, Id);
		removeLineFromFile(Filephongtro, Id);
		break;
	}
	case 3: {
		system("cls");
		string Id;
		cout << "Nhap so phong can tim: ";
		cin >> Id;
		Id = "id" + Id;
		system("cls");
		rootPhongtro* result = SearchNodePt(root, Id);
		if (result != nullptr) {
			cout << "---------------------------------- Da Tim Thay Phong ----------------------------------" << endl;
			cout << "ID Phong\t\tSo Nguoi O\t\tNgay Thue\t\tGia Thue" << endl;
			cout << result->data.IDPhong << "\t\t\t" << result->data.SonguoiO << "\t\t\t" << result->data.NgayPhongdcthue << "\t\t" << result->data.GiaThue << " dong" << endl;
			
		}
		else {
			cout << "Phong khong ton tai!" << endl;
		}
		break;
	}
	case 4: {
		system("cls");
		cout << "---------------------------------- Danh Sach Phong Tro ----------------------------------\n";
		HienThiDanhSachPhongTro(root);
		break;
	}case 5: {
		system("cls");
		cout << "---------------------------------- Danh Sach Phong Tro ----------------------------------\n";
		Timkiemmax(root);
		break;
	}case 6: {
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

