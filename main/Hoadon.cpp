#include "file_management.h"
#include "Phongtro.h"
#include "NguoiThue.h"
using namespace std;
#define FileHoadon "Resource FIles/Bill.txt"


struct HoaDon{
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

// ham tao 1 Node hoa don
rootBill* CreateNodeBill(HoaDon hoadon) {
	rootBill* newNode = new rootBill;
	newNode->Bill = hoadon;
	newNode->Left = nullptr;
	newNode->Right = nullptr;
	return newNode;
}

// Insert Bill vao BST
rootBill* InsertNodeBillall(rootBill* root, HoaDon hoadon) {
	if (root == nullptr) {
		return CreateNodeBill(hoadon);
	}
	if (hoadon.MaBill < root->Bill.MaBill) {
		root->Left = InsertNodeBillall(root->Left, hoadon);
	}
	else if (hoadon.MaBill > root->Bill.MaBill) {
		root->Right = InsertNodeBillall(root->Right, hoadon);
	}
	else {
		cout << "Hoa don da ton tai!" << endl;
	}
	return root;
}


// Đọc file bill vào BST
rootBill* DocFileBill() {
	ifstream file = chidocfile(FileHoadon);
	rootBill* root = NULL;
	HoaDon p;
	while (file >> p.MaBill)
	{
		file.ignore();
		file >> p.Makhachhang;
		file.ignore();
		getline(file, p.name, '|');
		getline(file, p.IDphong, '|');
		file >> p.TienDien;
		file.ignore();
		file >> p.TienNuoc;
		file.ignore();
		file >> p.TienPhong;
		file.ignore();
		file >> p.TongTien;
		file.ignore();
		getline(file, p.status, '|');
		getline(file, p.ngayThanhToan);
		root = InsertNodeBillall(root, p);
	}
	return root;
}


rootBill* findHoaDonflSHD(rootBill*, int );
// Thêm hóa đơn vào file
void newBill(rootBill* root) {
	HoaDon HoaDon;
	ofstream file = ghifile(FileHoadon);
	cin.ignore();
	// sinh ma bill ngau nhien
random:
	srand(time(0));
	HoaDon.MaBill = rand() % 100000 + 1000000;
	if (findHoaDonflSHD(root, HoaDon.MaBill) != NULL) {
		goto random;
	}
	cout << "Nhap Ma Khach Hang Trung Voi Ma Khach Hang Cua Nguoi Thue(lay o trong file Lessee.txt): ";
	cin >> HoaDon.Makhachhang;
	cin.ignore();
	NguoiThue p;
	LayThongTin(p, HoaDon.Makhachhang);
	if (p.maKhachHang == -1) {
		goto random;
	}
	HoaDon.TienPhong = timgiaGiaThue(to_string(p.IDPhong));
	if (HoaDon.TienPhong == -1) {
		goto random;
	}
	HoaDon.name = p.Name;
	HoaDon.IDphong = "id" + to_string(p.IDPhong);
	cout << "Nhap Tien Dien: ";
	cin >> HoaDon.TienDien;
	cin.ignore();
	cout << "Nhap Tien Nuoc: ";
	cin >> HoaDon.TienNuoc;
	cin.ignore();
	HoaDon.TongTien = HoaDon.TienDien + HoaDon.TienNuoc + HoaDon.TienPhong;
	HoaDon.status = "Da Thanh Toan";
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);
	HoaDon.ngayThanhToan = to_string(ltm.tm_mday) + "/" + to_string(1 + ltm.tm_mon) + "/" + to_string(1900 + ltm.tm_year);
	file << HoaDon.MaBill << "|" << HoaDon.Makhachhang << "|" << HoaDon.name<< "|" << HoaDon.IDphong << "|" << HoaDon.TienDien << "|" << HoaDon.TienNuoc << "|" << HoaDon.TienPhong << "|" << HoaDon.TongTien << "|" << HoaDon.status << "|" << HoaDon.ngayThanhToan << endl;
	root = InsertNodeBillall(root, HoaDon);
	file.close();
}

// Hàm sắp xếp các hóa đơn giảm dần theo Tổng tiền
vector<HoaDon> Giamdan(vector<HoaDon>& a, rootBill* root) {
	if (root == nullptr) return a;
    Giamdan(a, root->Left);
    a.push_back(root->Bill);
    Giamdan(a, root->Right);
    sort(a.begin(), a.end(), [](const HoaDon& bill1, const HoaDon& bill2) {
        return bill1.TongTien > bill2.TongTien;
    });
    return a;
}
// Hàm sắp xếp các hóa đơn tăng dần theo Name, neu Name giong nhau thi sap xep theo ma khach hang
vector <HoaDon> Tangdan(vector<HoaDon>& b, rootBill* root) {
	if (root == NULL) return b;
	Tangdan(b, root->Left);
	b.push_back(root->Bill);
	Tangdan(b, root->Right);

    sort(b.begin(), b.end(), [](const HoaDon& bill1, const HoaDon& bill2) {
					if (bill1.name == bill2.name) {
						return bill1.Makhachhang < bill2.Makhachhang;
					}
					return bill1.name < bill2.name;
    });
	return b;
}

//Hàm Duyệt Thông tin in theo vector
void Duyetvector(vector <HoaDon> Bill) {
	cout << "------------------------------------------------------------------------- Danh Sach Hoa Don -------------------------------------------------------------------------" << endl;
	cout << "Ma Hoa Don" << "\t" << "Ma Khach Hang" << "\t" << "Ten Khach Hang" << "\t\t" << "Id Phong" << "\t" << "Tong Tien" << "\t" << "Trang Thai" << "\t" << "Ngay Thanh Toan" << endl;
	for (auto a : Bill) {
		cout << a.MaBill << "\t\t" << a.Makhachhang << "\t\t" << a.name << "\t\t" << a.IDphong << "\t\t" << a.TongTien << "d" << "\t" << a.status << "\t" << a.ngayThanhToan << endl;
	}
}


//Hàm Hiển Thị Bill voi Tong tien
void HienThiBIllfullLAR(rootBill* root) {
	if (root == NULL) return;
	if (root != NULL) {
		HienThiBIllfullLAR(root->Left);
		cout << root->Bill.MaBill << "\t\t" << root->Bill.Makhachhang << "\t\t" << root->Bill.name << "\t\t" << root->Bill.IDphong << "\t\t" << root->Bill.TongTien <<  "d" << "\t" << root->Bill.status << "\t" << root->Bill.ngayThanhToan << endl;
		HienThiBIllfullLAR(root->Right);
	}
}
// Hàm Hiển thị Bill CTBill
void HienThiCTBill(rootBill* root) {
	if (root == NULL) return;
	if (root != NULL) {
		HienThiCTBill(root->Left);
		cout << root->Bill.MaBill << "\t\t" << root->Bill.Makhachhang << "\t\t" << root->Bill.name << "\t\t" << root->Bill.IDphong << "\t\t" << root->Bill.TienDien << "d" << "\t\t" << root->Bill.TienNuoc << "d" << "\t\t" << root->Bill.TienPhong << "d" << "        " << root->Bill.TongTien << "d" << "\t" << root->Bill.status << "\t" << root->Bill.ngayThanhToan << endl;
		HienThiCTBill(root->Right);
	}
}



//Tìm kiếm và cho biết thông tin của một Hóa đơn cùng với các CT Hóa đơn tương ứng khi biết Số hóa đơn.

rootBill* findHoaDonflSHD(rootBill* root, int SHD) {
	if (root == NULL || SHD == root->Bill.MaBill) {
		return root;
	}
	if (SHD < root->Bill.MaBill) {
		return findHoaDonflSHD(root->Left, SHD);
	}
	return findHoaDonflSHD(root->Right, SHD);
}

//Tìm kiếm hóa đơn khi biết Mã khách hàng
rootBill* findHoaDonflMKH(rootBill* root, int MKH) {
	if (root == NULL || MKH == root->Bill.Makhachhang) {
		findHoaDonflMKH(root->Left, MKH);
		return root;
		findHoaDonflMKH(root->Right, MKH);
	}
	return root;
	
}

// Xóa 1 hóa đơn bằng SHD
rootBill* DeleteBillBySHD(rootBill* root, int SHD) {
	if (root == nullptr) {
       return root;
   }
   if (SHD < root->Bill.MaBill) {
       root->Left = DeleteBillBySHD(root->Left, SHD);
   } else if (SHD > root->Bill.MaBill) {
       root->Right = DeleteBillBySHD(root->Right, SHD);
   } else {
       if (root->Left == nullptr) {
           rootBill* temp = root->Right;
           delete root;
           return temp;
       } else if (root->Right == nullptr) {
           rootBill* temp = root->Left;
           delete root;
           return temp;
       }
       rootBill* temp = root->Right;
       while (temp->Left != nullptr) {
           temp = temp->Left;
       }
       root->Bill = temp->Bill;
       root->Right = DeleteBillBySHD(root->Right, temp->Bill.MaBill);
   }
   return root;
}





void MenuforBill() {  
Lap:  
   rootBill* root = DocFileBill();  
   cout << "====================QUAN LY HOA DON====================" << endl;  
   cout << "- 1. Them Hoa Don Moi" << endl;  
   cout << "- 2. Xoa Hoa Don" << endl;  
   cout << "- 3. Tim kiem Hoa Don (khi biet so hoa don)" << endl;  
   cout << "- 4. Tim kiem Hoa Don (khi biet ma khach hang)" << endl;  
   cout << "- 5. Hien thi Danh Sach Hoa Don" << endl;  
   cout << "- 6. Hien thi Danh Sach Chi Tiet Hoa Don (bao gom tien nuoc, tien dien, tien phong)" << endl;  
   cout << "- 7. Hien thi Danh Sach Hoa Don (sap xep giam dan theo tong tien)" << endl;  
   cout << "- 8. Hien Thi Danh Sach Hoa Don (sap xep tang dan theo ten khach hang, neu trung ten thi sap xep theo ma khach hang)" << endl;  
   cout << "- 9. Quay Lai" << endl;  
   cout << "- Nhap lua chon: ";  
   int luachon;  
   cin >> luachon;  
   switch (luachon) {  
       case 1:  
		   system("cls");
           newBill(root);  
           break;  
       case 2:  
		   system("cls");
		   int SHD;
		   cout << "Nhap So Hoa Don Can Xoa: ";
		   cin >> SHD;
		   if (findHoaDonflSHD(root, SHD) == NULL) {
			   cout << "Khong tim Thay Hoa Don!";
			   break;
		   }
		   root = DeleteBillBySHD(root, SHD);
		   removeLineFromFile(FileHoadon, to_string(SHD));
           break;  
       case 3: {  
		   system("cls");
           int SHD;  
           cout << "Nhap So Hoa Don Muon Tim: ";  
           cin >> SHD;  
		   system("cls");
           rootBill* bill = findHoaDonflSHD(root, SHD);  
           if (bill == NULL) {  
               cout << "Khong tim thay!" << endl;  
               break;  
           } else {  
               cout << "------------------------------------------------------------------------- Da Tim Thay Hoa Don -------------------------------------------------------------------------" << endl;  
			   cout << "Ma Hoa Don" << "\t" << "Ma Khach Hang" << "\t" << "Ten Khach Hang" << "\t\t" << "Id Phong" << "\t" << "Tien Dien" << "\t" << "Tien Nuoc" << "\t" << "Tien Phong" << "\t" << "Tong Tien" << "\t" << "Trang Thai" << "\t" << "Ngay Thanh Toan" << endl;
			   cout << bill->Bill.MaBill << "\t\t" << bill->Bill.Makhachhang << "\t\t" << bill->Bill.name << "\t\t" << bill->Bill.IDphong << "\t\t" << bill->Bill.TienDien << "d" << "\t\t" << bill->Bill.TienNuoc << "d" << "\t\t" << bill->Bill.TienPhong << "d" << "        " << bill->Bill.TongTien << "d" << "\t" << bill->Bill.status << "\t" << bill->Bill.ngayThanhToan << endl;
			   
           }  
           break;  
       }  
       case 4: {  
		   system("cls");
           int MKH;  
           cout << "Nhap Ma Khach Hang Muon Tim: ";  
           cin >> MKH;  
		   system("cls");
           rootBill* bill = findHoaDonflMKH(root, MKH);  
           if (bill == NULL) {  
               cout << "Khong tim thay!" << endl;  
               break;  
           } else {  
               cout << "------------------------------------------------------------------------- Da Tim Thay Hoa Don -------------------------------------------------------------------------" << endl;
			   cout << "Ma Hoa Don" << "\t" << "Ma Khach Hang" << "\t" << "Ten Khach Hang" << "\t\t" << "Id Phong" << "\t" << "Tien Dien" << "\t" << "Tien Nuoc" << "\t" << "Tien Phong" << "\t" << "Tong Tien" << "\t" << "Trang Thai" << "\t" << "Ngay Thanh Toan" << endl;
			   cout << bill->Bill.MaBill << "\t\t" << bill->Bill.Makhachhang << "\t\t" << bill->Bill.name << "\t\t" << bill->Bill.IDphong << "\t\t" << bill->Bill.TienDien << "d" << "\t\t" << bill->Bill.TienNuoc << "d" << "\t\t" << bill->Bill.TienPhong << "d" << "        " << bill->Bill.TongTien << "d" << "\t" << bill->Bill.status << "\t" << bill->Bill.ngayThanhToan << endl;
           }  
           break;  
       }  
       case 5:  
		   system("cls");
           cout << "---------------------------------------------------------- Danh Sach Hoa Don -----------------------------------------------" << endl;  
		   cout << "Ma Hoa Don" << "\t" << "Ma Khach Hang" << "\t" << "Ten Khach Hang" << "\t\t" << "Id Phong" << "\t" << "Tong Tien" << "\t" << "Trang Thai" << "\t" << "Ngay Thanh Toan" << endl;
           HienThiBIllfullLAR(root);  
           break;  
       case 6:  
		   system("cls");
           cout << "------------------------------------------------------------------------- Danh Sach Chi Tiet Hoa Don -------------------------------------------------------------------------" << endl;  
		   cout << "Ma Hoa Don" << "\t" << "Ma Khach Hang" << "\t" << "Ten Khach Hang" << "\t\t" << "Id Phong" << "\t" << "Tien Dien" << "\t" << "Tien Nuoc" << "\t" << "Tien Phong" << "\t" << "Tong Tien" << "\t" << "Trang Thai" << "\t" << "Ngay Thanh Toan" << endl;
           HienThiCTBill(root);  
           break;  
       case 7: {  
		   system("cls");
           vector<HoaDon> p;  
           Giamdan(p, root);  
           Duyetvector(p);  
           break;  
       }  
       case 8: {  
		   system("cls");
           vector<HoaDon> p;  
           Tangdan(p, root);  
           Duyetvector(p);  
           break;  
       }  
       case 9:  
		   return; 
       default:  
           system("cls");  
           cout << "Lua chon khong hop le!" << endl;  
           break;  
   }  
   system("pause");
   system("cls");
   goto Lap;
}