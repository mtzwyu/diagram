#include "file_management.h"
using namespace std;
#define FileNguoiThue "Lessee.txt"


struct NguoiThue {
	long long CCCD;
	string Name;
	int age;
	int IDPhong; // IDPhong là mã số phòng mà người thuê đang ở
	double TienCoc; // tiền cọc
};

struct RootNguoiThue {
    NguoiThue data;
    RootNguoiThue* Left;
    RootNguoiThue* Right;
};
// Hàm này sẽ tạo một node mới cho cây nhị phân 
RootNguoiThue* CreateNode(NguoiThue nguoiThue) {
    RootNguoiThue* newNode = new RootNguoiThue;
    newNode->data = nguoiThue;
    newNode->Left = nullptr;
    newNode->Right = nullptr;
    return newNode;
}

// Hàm này sẽ ghi thông tin người thuê mới vào file 
void newLESSEE(NguoiThue nguoiThue) {
    ofstream file = ghifile(FileNguoiThue);
    cout << "Nhap CCCD: ";
    cin >> nguoiThue.CCCD;
    cin.ignore();
    cout << "Nhap Ho Ten: ";
    getline(cin, nguoiThue.Name);
    cout << "Nhap Tuoi: ";
    cin >> nguoiThue.age;
    cout << "Nhap IDPhong: ";
    cin >> nguoiThue.IDPhong;
    cout << "Nhap Tien Coc: ";
    cin >> nguoiThue.TienCoc;
    file << nguoiThue.CCCD << "|" << nguoiThue.Name << "|" << nguoiThue.age << "|" << nguoiThue.IDPhong << "|" << nguoiThue.TienCoc << endl;
    file.close();
}



// Hàm này sẽ thêm một node mới vào cây nhị phân
RootNguoiThue* InsertNode(RootNguoiThue* root, NguoiThue nguoiThue) {
    if (root == nullptr) {
        return CreateNode(nguoiThue);
    }
    if (nguoiThue.CCCD < root->data.CCCD) {
        root->Left = InsertNode(root->Left, nguoiThue);
    }
    else if (nguoiThue.CCCD > root->data.CCCD) {
        root->Right = InsertNode(root->Right, nguoiThue);
	}
	else {
		cout << "Nguoi thue da ton tai!" << endl;
	}
    return root;
}
// Hàm này sẽ đọc danh sách người thuê từ file và thêm vào cây nhị phân
RootNguoiThue* ThemDanhSachNguoiThuetufile() {
	ifstream file = chidocfile(FileNguoiThue);
	NguoiThue nguoiThue;
	RootNguoiThue* root = nullptr;
	while (file >> nguoiThue.CCCD) {
		file.ignore();
		getline(file, nguoiThue.Name, '|');
		file >> nguoiThue.age;
		file.ignore();
		file >> nguoiThue.IDPhong;
		file.ignore();
		file >> nguoiThue.TienCoc;
		root = InsertNode(root, nguoiThue);
	}
	file.close();
	return root;
}

// Hàm này sẽ duyệt cây nhị phân theo thứ tự InOrder và in ra thông tin người thuê
void InOrder(RootNguoiThue* root) {
    if (root == nullptr) {
        return;
    }
    if (root != nullptr) {
        InOrder(root->Left);
        cout << root->data.CCCD << "\t" << root->data.Name << "\t" << root->data.age << "\t" << root->data.IDPhong << "\t\t" << root->data.TienCoc << "d" << endl;
        InOrder(root->Right);
    }
}

// tìm kiếm người thuê theo CCCD
RootNguoiThue* SearchByCCCD(RootNguoiThue* root, long long CCCD) {
	if (root == nullptr || root->data.CCCD == CCCD) {
		return root;
	}
	if (CCCD < root->data.CCCD) {
		return SearchByCCCD(root->Left, CCCD);
	}
	return SearchByCCCD(root->Right, CCCD);
}
// Hàm này sẽ xóa một node trong cây nhị phân bằng CCCD
RootNguoiThue* DeleteNode(RootNguoiThue* root, long long CCCD) {
	if (root == nullptr) {
		return root;
	}
	if (CCCD < root->data.CCCD) {
		root->Left = DeleteNode(root->Left, CCCD);
	}
	else if (CCCD > root->data.CCCD) {
		root->Right = DeleteNode(root->Right, CCCD);
	}
	else {
		if (root->Left == nullptr) {
			RootNguoiThue* temp = root->Right;
			delete root;
			return temp;
		}
		else if (root->Right == nullptr) {
			RootNguoiThue* temp = root->Left;
			delete root;
			return temp;
		}
		RootNguoiThue* temp = root->Right;
		while (temp && temp->Left != nullptr) {
			temp = temp->Left;
		}
		root->data = temp->data;
		root->Right = DeleteNode(root->Right, temp->data.CCCD);
	}
	return root;
}
// Hàm Xóa Dữ liệu trong file và trong cây khi tìm kiếm được CCCD
void DeleteDataInFile(long long CCCD) {
	ifstream file(FileNguoiThue);
	ofstream tempFile("temp.txt");
	ofstream file1("resouce files\old_lessee.txt");
	NguoiThue nguoiThue;
	while (file >> nguoiThue.CCCD) {
		file.ignore();
		getline(file, nguoiThue.Name, '|');
		file >> nguoiThue.age;
		file.ignore();
		file >> nguoiThue.IDPhong;
		file.ignore();
		file >> nguoiThue.TienCoc;
		if (nguoiThue.CCCD != CCCD) {
			tempFile << nguoiThue.CCCD << "|" << nguoiThue.Name << "|" << nguoiThue.age << "|" << nguoiThue.IDPhong << "|" << nguoiThue.TienCoc << endl;
		}
		else {
			file1 << nguoiThue.CCCD << "|" << nguoiThue.Name << "|" << nguoiThue.age << "|" << nguoiThue.IDPhong << "|" << nguoiThue.TienCoc << endl;
		}
	}
	file.close();
	tempFile.close();
	remove(FileNguoiThue);
	rename("temp.txt", FileNguoiThue);
}

// Hàm Menu
void MenuforLessee() {

	RootNguoiThue* root = ThemDanhSachNguoiThuetufile();
	LOOP:
	cout << "====================QUAN LY NGUOI THUE====================" << endl;
	cout << "- 1. Them nguoi thue" << endl;
	cout << "- 2. Xoa Nguoi Da Tra Phong" << endl;
	cout << "- 3. Tim kiem nguoi thue bang CCCD" << endl;
	cout << "- 4. Hien thi danh sach tat ca nguoi da thue" << endl;
	cout << "- 5. Thoat" << endl;
	cout << "- Nhap lua chon: ";
	
	int choice;
	cin >> choice;
	switch (choice)
	{
	
	case 1: {
		system("cls");
		NguoiThue nguoiThue;
		newLESSEE(nguoiThue);
		break;
	}
	case 2: {
		system("cls");
		long long CCCD;
		cout << "Nhap CCCD nguoi thue can xoa: ";
		cin >> CCCD;
		RootNguoiThue* result = SearchByCCCD(root, CCCD);
		if (result == nullptr) {
			cout << "Khong tim thay nguoi thue co CCCD " << CCCD << endl;
			break;
		}
		DeleteDataInFile(CCCD);
		root = DeleteNode(root, CCCD);
		break;
	}
	case 3:
	{	
		system("cls");
		long long CCCD;
		cout << "Nhap CCCD nguoi thue can tim: ";
		cin >> CCCD;
		RootNguoiThue* result = SearchByCCCD(root, CCCD);
		if (result != nullptr) {
			cout << "------------Nguoi thue co CCCD " << CCCD << " da ton tai!---------------" << endl;
			cout << "CCCD\t\tHo Ten\t\tTuoi\tIDPhong\t\tTien Coc" << endl;
			cout << result->data.CCCD << "\t" << result->data.Name << "\t" << result->data.age << "\t" << result->data.IDPhong << "\t\t" << result->data.TienCoc << "d" << endl;
		}
		else {
			cout << "Khong tim thay nguoi thue co CCCD " << CCCD << endl;
		}
		break;
	}
	case 4:
	{
		system("cls");
		cout << "------------------------DANH SACH NGUOI THUE----------------------------" << endl;
		cout << "CCCD\t\tHo Ten\t\tTuoi\tIDPhong\t\tTien Coc" << endl;
		InOrder(root);
		break;
	}
	case 5:
		cout << "--------------Cam on ban da su dung chuong trinh!-----------------------" << endl;
		return;
	default:
		cout << "Lua chon khong hop le!" << endl;
		break;
	}
	system("pause");
	system("cls");
	goto LOOP;
}