# 🏠 HỆ THỐNG QUẢN LÝ PHÒNG TRỌ (C++)

![C++](https://img.shields.io/badge/C++-17-blue?logo=cplusplus)
![License](https://img.shields.io/badge/License-MIT-green)
![Data](https://img.shields.io/badge/Data-TXT_files-yellow)

Hệ thống quản lý phòng trọ với đầy đủ chức năng: từ quản lý người thuê, phòng trọ đến thống kê doanh thu tự động.

## 📌 Tính năng chính
- **Quản lý phòng trọ**: Thêm/xóa/sửa phòng, kiểm tra trạng thái
- **Quản lý người thuê**: Kết nối người thuê với phòng
- **Hóa đơn**: Tự động tính tiền theo ngày
- **Thống kê**: Doanh thu theo ngày/tháng/quý/năm

## 📂 Cấu trúc file

```bash
main/
├── main.cpp # Chương trình chính
├── NguoiThue.h # Class người thuê (BST)
├── PhongTro.h # Class phòng trọ
├── Hoadon.h # Class hóa đơn
├── Resource_Files/
│ ├── Lessee.txt # Dữ liệu người thuê (Mã khách hàng|CCCD|Name khách hàng|Tuổi|ID phòng ở|SDT|Ngày thuê phòng|Tiền cọc)
│ ├── Room.txt  # Dữ liệu phòng (ID Phòng|Số người|Ngày thuê|Giá thuê)
│ └── Bill.txt # Dữ liệu Bill (Mã Bill|Mã khách hàng|Name khách hàng|ID phòng|Tiền điện|Tiền Nước|Tiền phòng|Tổng tiền|Trạng thái|Ngày thanh toán)
└── (Các file.cpp tương ứng)
```

## 🚀 Cách chạy chương trình
1. Biên dịch:
```bash
g++ main.cpp NguoiThue.cpp PhongTro.cpp Hoadon.cpp -o main
```

📊 Menu chính

1. Quản lý người thuê
2. Quản lý phòng trọ
3. Hóa đơn
4. Thống kê doanh thu
5. Thêm người thuê mới
6. Thoát

📌 Lưu ý quan trọng
1. Chương trình sử dụng cây nhị phân (BST) để quản lý người thuê

2. Dữ liệu được lưu dạng text, phân cách bằng |

3. Hỗ trợ kiểm tra ngày tháng hợp lệ (bao gồm năm nhuận)

✉️ Liên hệ: [Mạnh Trường] - mtruong2509@gmail.com
