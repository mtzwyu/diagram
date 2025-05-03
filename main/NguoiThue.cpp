#include "file_management.h"
using namespace std;
#define FileNguoiThue "Resource FIles/Lessee.txt"


struct NguoiThue {
	long long maKhachHang;
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
// Hàm này sẽ tạo một node mới cho cây nhị phân 
RootNguoiThue* CreateNode(NguoiThue nguoiThue) {
    RootNguoiThue* newNode = new RootNguoiThue;
    newNode->data = nguoiThue;
    newNode->Left = nullptr;
    newNode->Right = nullptr;
    return newNode;
}





// Hàm này sẽ thêm một node mới vào cây nhị phân
RootNguoiThue* InsertNode(RootNguoiThue* root, NguoiThue nguoiThue) {
    if (root == nullptr) {
        return CreateNode(nguoiThue);
    }
    if (nguoiThue.maKhachHang < root->data.maKhachHang) {
        root->Left = InsertNode(root->Left, nguoiThue);
    }
    else if (nguoiThue.maKhachHang > root->data.maKhachHang) {
        root->Right = InsertNode(root->Right, nguoiThue);
	}
	else {
		cout << "Nguoi thue da ton tai!" << endl;
	}
    return root;
}

// Hàm này sẽ đọc danh sách người thuê từ file và thêm vào cây 
RootNguoiThue* ThemDanhSachNguoiThuetufile() {
	ifstream file = chidocfile(FileNguoiThue);
	NguoiThue nguoiThue;
	RootNguoiThue* root = nullptr;
	while (file >> nguoiThue.maKhachHang) {
		file.ignore();
		file >> nguoiThue.CCCD;
		file.ignore();
		getline(file, nguoiThue.Name, '|');
		file >> nguoiThue.age;
		file.ignore();
		file >> nguoiThue.IDPhong;
		file.ignore();
		file >> nguoiThue.SDT;
		file.ignore();
		getline(file, nguoiThue.NgayThue, '|');
		file >> nguoiThue.TienCoc;
		root = InsertNode(root, nguoiThue);
	}
	file.close();
	return root;
}

// check trong file neu da co MakhachHang roi thi random lai
bool checkMakhachhang(long long maKhachHang) {
	ifstream file(FileNguoiThue);
	NguoiThue nguoiThue;
	while (file >> nguoiThue.maKhachHang) {
		file.ignore();
		file >> nguoiThue.CCCD;
		file.ignore();
		getline(file, nguoiThue.Name, '|');
		file >> nguoiThue.age;
		file.ignore();
		file >> nguoiThue.IDPhong;
		file.ignore();
		getline(file, nguoiThue.NgayThue, '|');
		file >> nguoiThue.TienCoc;
		if (nguoiThue.maKhachHang == maKhachHang) {
			cout << "Ma khach hang da ton tai!" << endl;
			return false;
		}
	}
	file.close();
	return true;
}

// Hàm này sẽ ghi thông tin người thuê mới vào file 
void newLESSEE(RootNguoiThue *&root,NguoiThue nguoiThue) {
	ofstream file = ghifile(FileNguoiThue);
	// sinh ma khach hang ngau nhien
	random:
	srand(time(0));
	nguoiThue.maKhachHang = rand() % 100000 + 1000000;
	if (!checkMakhachhang(nguoiThue.maKhachHang)) {
		goto random;
	}
	cout << "Nhap CCCD: ";
	cin >> nguoiThue.CCCD;
	cin.ignore();
	cout << "Nhap Ho Ten: ";
	getline(cin, nguoiThue.Name);
	cout << "Nhap Tuoi: ";
	cin >> nguoiThue.age;
	cout << "Nhap IDPhong: ";
	cin >> nguoiThue.IDPhong;
	cout << "Nhap SDT: ";
	cin >> nguoiThue.SDT;
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    nguoiThue.NgayThue = to_string(ltm.tm_mday) + "/" + to_string(1 + ltm.tm_mon) + "/" + to_string(1900 + ltm.tm_year);
	cout << "Nhap Tien Coc: ";
	cin >> nguoiThue.TienCoc;
	file << nguoiThue.maKhachHang << "|" << nguoiThue.CCCD << "|" << nguoiThue.Name << "|" << nguoiThue.age << "|" << nguoiThue.IDPhong << "|" << "0" + to_string(nguoiThue.SDT) << "|" << nguoiThue.NgayThue << "|" << nguoiThue.TienCoc << endl;
	InsertNode(root, nguoiThue);
	file.close();
}



// Hàm này sẽ duyệt cây nhị phân theo thứ tự InOrder và in ra thông tin người thuê
void InOrder(RootNguoiThue* root) {
    if (root == nullptr) {
        return;
    }
    if (root != nullptr) {
        InOrder(root->Left);
        cout << root->data.maKhachHang << "\t\t\t" << root->data.CCCD << "\t\t" << root->data.Name << "\t\t" << root->data.age << "\t\t" << root->data.IDPhong <<"\t\t" << "0" << +root->data.SDT << "\t\t" << root->data.NgayThue << "\t\t" << root->data.TienCoc << "d" << endl;
        InOrder(root->Right);
    }
}

// tìm kiếm người thuê theo Ma khach hang
RootNguoiThue* SearchByMKH(RootNguoiThue* root, long long Makhachhang) {
	if (root == nullptr || root->data.maKhachHang == Makhachhang) {
		return root;
	}
	if (Makhachhang < root->data.maKhachHang) {
		return SearchByMKH(root->Left, Makhachhang);
	}
	return SearchByMKH(root->Right, Makhachhang);
}
// Hàm này sẽ xóa một node trong cây nhị phân bằng MAKHACHHANG
RootNguoiThue* DeleteNode(RootNguoiThue* root, long long Makhachhang) {
	if (root == nullptr) {
		return root;
	}
	if (Makhachhang < root->data.maKhachHang) {
		root->Left = DeleteNode(root->Left, Makhachhang);
	}
	else if (Makhachhang > root->data.maKhachHang) {
		root->Right = DeleteNode(root->Right, Makhachhang);
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
		root->Right = DeleteNode(root->Right, temp->data.maKhachHang);
	}
	return root;
}
// Hàm Xóa Dữ liệu trong file và trong cây khi tìm kiếm được Makhachhang
void DeleteDataInFile(long long Makhachhang) {
	ifstream file(FileNguoiThue);
	ofstream tempFile("temp.txt");
	ofstream file1("resouce files\old_lessee.txt");
	NguoiThue nguoiThue;
	while (file >> nguoiThue.maKhachHang) {
		file.ignore();
		file >> nguoiThue.CCCD;
		file.ignore();
		getline(file, nguoiThue.Name, '|');
		file >> nguoiThue.age;
		file.ignore();
		file >> nguoiThue.IDPhong;
		file.ignore();
		file >> nguoiThue.SDT;
		file.ignore();
		getline(file, nguoiThue.NgayThue, '|');
		file >> nguoiThue.TienCoc;
		if (nguoiThue.maKhachHang != Makhachhang) {
			tempFile << nguoiThue.maKhachHang << "|" << nguoiThue.CCCD << "|" << nguoiThue.Name << "|" << nguoiThue.age << "|" << nguoiThue.IDPhong << "|" <<nguoiThue.SDT <<"|" << nguoiThue.NgayThue << "|" << nguoiThue.TienCoc << endl;
		}
		else {
			file1 <<nguoiThue.maKhachHang<< "|" << nguoiThue.CCCD << "|" << nguoiThue.Name << "|" << nguoiThue.age << "|" << nguoiThue.IDPhong << "|" << nguoiThue.SDT << "|" << nguoiThue.NgayThue << "|" << nguoiThue.TienCoc << endl;
		}
	}
	file.close();
	tempFile.close();
	remove(FileNguoiThue);
	rename("temp.txt", FileNguoiThue);
}






// Hàm Menu cua Lessee
void MenuforLessee() {
LOOP:
	RootNguoiThue* root = ThemDanhSachNguoiThuetufile();

	cout << "====================QUAN LY NGUOI THUE====================" << endl;
	cout << "- 1. Them nguoi thue" << endl;
	cout << "- 2. Xoa Nguoi Da Tra Phong" << endl;
	cout << "- 3. Tim kiem nguoi thue bang Ma Khach Hang" << endl;
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
		newLESSEE(root,nguoiThue);
		break;
	}
	case 2: {
		system("cls");
		long long MakhachHang;
		cout << "Nhap Ma Khach Hang can xoa: ";
		cin >> MakhachHang;
		RootNguoiThue* result = SearchByMKH(root, MakhachHang);
		if (result == nullptr) {
			cout << "Khong tim thay nguoi thue co ma khach hang: " << MakhachHang << endl;
			break;
		}
		DeleteDataInFile(MakhachHang);
		root = DeleteNode(root, MakhachHang);
		break;
	}
	case 3:
	{	
		system("cls");
		long long MKH;
		cout << "Nhap Ma Khach Hang can tim: ";
		cin >> MKH;
		system("cls");
		RootNguoiThue* result = SearchByMKH(root, MKH);
		if (result != nullptr) {
			cout << "--------------------------------------------Nguoi thue co Ma khach hang " << MKH << " da ton tai!----------------------------------------------------" << endl;
			cout << "Ma Khach Hang\t\tCCCD\t\t\tHo Ten\t\t\tTuoi\t\tID Phong\tSDT\t\tNgay Thue\tTien Coc" << endl;
			cout << result->data.maKhachHang << "\t\t\t" << result->data.CCCD << "\t\t" << result->data.Name << "\t\t" << result->data.age << "\t\t" << result->data.IDPhong << "\t\t" << "0" << +result->data.SDT << "\t\t" << result->data.NgayThue << "\t\t" << result->data.TienCoc << "d" << endl;
		}
		else {
			cout << "Khong tim thay nguoi thue co ma khach hang " << MKH << endl;
		}
		break;
	}
	case 4:
	{
		system("cls");
		cout << "----------------------------------------------------------------DANH SACH NGUOI THUE----------------------------------------------------------------" << endl;
		cout << "Ma Khach Hang\t\tCCCD\t\t\tHo Ten\t\t\tTuoi\t\tID Phong\tSDT\t\tNgay Thue\tTien Coc" << endl;
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