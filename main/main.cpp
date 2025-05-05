#include <iostream>
#include "NguoiThue.h"
#include "PhongTro.h"
#include "Hoadon.h"
#include <iomanip>
#include <sstream>
using namespace std;


// Hàm kiểm tra năm nhuận
bool isLeapYear(int year) {
    return (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
}

// Hàm kiểm tra ngày hợp lệ
bool isValidDate(int day, int month, int year) {
    if (year < 1900 || month < 1 || month > 12 || day < 1) {
        return false;
    }

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 2 && isLeapYear(year)) {
        if (day > 29) return false;
    }
    else {
        if (day > daysInMonth[month - 1]) return false;
    }

    return true;
}

// Hàm phân tách chuỗi
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Hàm chuyển đổi ngày tháng và kiểm tra hợp lệ
bool parseDate(const string& dateStr, struct tm& date) {
    size_t slash1 = dateStr.find('/');
    size_t slash2 = dateStr.find('/', slash1 + 1);

    if (slash1 == string::npos || slash2 == string::npos) return false;

    int day = stoi(dateStr.substr(0, slash1));
    int month = stoi(dateStr.substr(slash1 + 1, slash2 - slash1 - 1));
    int year = stoi(dateStr.substr(slash2 + 1));

    if (!isValidDate(day, month, year)) {
        cerr << "Ngày không hợp lệ: " << dateStr << endl;
        return false;
    }

    date.tm_mday = day;
    date.tm_mon = month - 1;
    date.tm_year = year - 1900;
    date.tm_hour = 0;
    date.tm_min = 0;
    date.tm_sec = 0;
    date.tm_isdst = -1;

    return true;
}

// Hàm kiểm tra ngày trong khoảng
bool isDateInRange(const string& dateStr, const string& startDateStr, const string& endDateStr) {
    struct tm date = { 0 }, startDate = { 0 }, endDate = { 0 };

    if (!parseDate(dateStr, date) || !parseDate(startDateStr, startDate) || !parseDate(endDateStr, endDate)) {
        return false;
    }

    time_t t_date = mktime(&date);
    time_t t_start = mktime(&startDate);
    time_t t_end = mktime(&endDate);

    return (t_date >= t_start) && (t_date <= t_end);
}

void Menu() {
    h:
    ifstream inputFile("Resource FIles/Room.txt");
    vector<Phongtro> bookings;

    if (!inputFile.is_open()) {
        cout << "Khong the mo file Room.txt" << endl;
        return;
    }

    // Đọc dữ liệu từ file
    string line;
    while (getline(inputFile, line)) {
        vector<string> parts = split(line, '|');
        if (parts.size() == 4) {
            Phongtro b;
            b.IDPhong = parts[0];
            b.SonguoiO = stoi(parts[1]);
            b.NgayPhongdcthue = parts[2];
            b.GiaThue= stod(parts[3]);

            // Kiểm tra ngày hợp lệ trước khi thêm vào danh sách
            struct tm date = { 0 };
            if (parseDate(b.NgayPhongdcthue, date)) {
                bookings.push_back(b);
            }
            else {
                cout << "Bo qua dong hop le: " << line << endl;
            }
        }
    }
    inputFile.close();

    // Menu lựa chọn
    cout << "THONG KE DOANG THU" << endl;
    cout << "- 1. Theo ngay" << endl;
    cout << "- 2. Theo thang" << endl;
    cout << "- 3. Theo quy" << endl;
    cout << "- 4. Theo nam" << endl;
    cout << "- 5. Theo khoang thoi gian tuy chon" << endl;
    cout << "- 6. Quay Lai" << endl;
    cout << "- Lua chon cua ban: ";

    int choice;
    cin >> choice;

    map<string, double> revenue;
    string startDate, endDate;

    switch (choice) {
    case 1: // Theo ngày
        for (const auto& b : bookings) {
            revenue[b.NgayPhongdcthue] += b.GiaThue;
        }
        break;

    case 2: { // Theo tháng
        for (const auto& b : bookings) {
            size_t slashPos = b.NgayPhongdcthue.find('/');
            size_t secondSlashPos = b.NgayPhongdcthue.find('/', slashPos + 1);
            string monthYear = b.NgayPhongdcthue.substr(slashPos + 1, secondSlashPos - slashPos) + "/" + b.NgayPhongdcthue.substr(secondSlashPos + 1);
            revenue[monthYear] += b.GiaThue;
        }
        break;
    }

    case 3: { // Theo quý
        for (const auto& b : bookings) {
            struct tm date = { 0 };
            if (parseDate(b.NgayPhongdcthue, date)) {
                int quarter = (date.tm_mon / 3) + 1;
                string quarterYear = "Q" + to_string(quarter) + " " + to_string(date.tm_year + 1900);
                revenue[quarterYear] += b.GiaThue;
            }
        }
        break;
    }

    case 4: { // Theo năm
        for (const auto& b : bookings) {
            size_t lastSlashPos = b.NgayPhongdcthue.find_last_of('/');
            string year = b.NgayPhongdcthue.substr(lastSlashPos + 1);
            revenue[year] += b.GiaThue;
        }
        break;
    }

    case 5: {
        cout << "Nhap ngay bat dau (d/m/yyyy): ";
        cin >> startDate;
        cout << "Nhap ngay ket thuc (d/m/yyyy): ";
        cin >> endDate;

        double total = 0.0;
        int count = 0;
        for (const auto& b : bookings) {
            if (isDateInRange(b.NgayPhongdcthue, startDate, endDate)) {
                total += b.GiaThue;
                count++;
            }
        }

        cout << "\nTONG TIEN TU " << startDate << " DEN " << endDate << ":" << endl;
        cout << "----------------------------------------" << endl;
        cout << "So Luong phong: " << count << endl;
        cout << "Tong Doang Thu: " << fixed << setprecision(2) << total << "d" << endl;
        cout << "----------------------------------------" << endl;
        break;
        goto h;
    }
    case 6:
        return;
    default:
        cout << "Ban da nhap sai\n";
        break;
        goto h;
 
    }
    
    

    // Hiển thị kết quả
    cout << "\nKet qua thong ke:" << endl;
    cout << "----------------------------------------" << endl;
    cout << left << setw(20) << "Thoi gian" << setw(15) << "Doanh thu" << endl;
    cout << "----------------------------------------" << endl;

    for (const auto& entry : revenue) {
        cout << left << setw(20) << entry.first << setw(15) << fixed << setprecision(2) << entry.second << endl;
    }
    system("pause");
    system("cls");
    goto h;
    return ;
}


int main() {
MENU:
	cout << "============================================== CHUONG TRINH QUAN LY PHONG TRO ==============================================" << endl;
	cout << "- 1. Truy Cap Quan Ly Nguoi Thue\n";
	cout << "- 2. Truy Cap Quan Ly Phong Tro\n";
	cout << "- 3. Truy Cap Quan Ly Hoa Don\n";
	cout << "- 4. Thong Ke Doanh Thu Cho Thue Phong\n";
	cout << "- 5. Them 1 Nguoi Toi Thue Phong\n";
	cout << "- 6. Thoat\n";
	cout << "- Moi Lua Chon: ";
	int option;
	cin >> option;
	RootNguoiThue* rootLessee = nullptr;
	rootPhongtro* rootRoom = nullptr;
	rootBill* rootbill = nullptr;
	switch (option)
	{
	case 1:
		system("cls");
		MenuforLessee();
		break;
	case 2:
		system("cls");
		MenucuaRoom();
		break;
	case 3:
		system("cls");
		MenuforBill();
		break;
	case 4:
		system("cls");
        Menu();
		break;
	case 5:
	{	
		system("cls");
		NguoiThue nguoiThue;
		rootLessee = ThemDanhSachNguoiThuetufile();
		newLESSEE(rootLessee, nguoiThue);
		rootRoom = docfilevaotreePt();
		int cnt = 0;
		system("cls");
		cout << "ID Phong\t\tSo Nguoi O\t\tNgay Thue\t\tGia Thue" << endl;
		cntphongtrong(rootRoom, cnt);
		if (cnt == 0) {
			cout << "Khong Co Phong Nao Trong\n";
		}
		cout << "Nhap id phong moi: ";
		string id;
		cin >> id;
		system("cls");
		rootRoom = DeleteNodePt(rootRoom,"id"+id);
		ThemPhongMoichokhachInFile(rootRoom, id);
		rootbill = DocFileBill();
		newBill(rootbill);
		break;
	}
	case 6:
		cout << "Cam On Ban Da Su Dung!" << endl;
		exit(5);
	default:
		cout << "Ban da nhap sai vui long nhap lai\n";
		break;
	}
	system("pause");
	system("cls");
	goto MENU;
	return 0;
}