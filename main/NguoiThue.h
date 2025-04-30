#pragma once

struct NguoiThue {};
struct RootNguoiThue {};
RootNguoiThue* CreateNode(NguoiThue nguoiThue);
RootNguoiThue* InsertNode(RootNguoiThue* root, NguoiThue nguoiThue);
RootNguoiThue* DeleteNode(RootNguoiThue* root, long long CCCD);
void newLESSEE(NguoiThue nguoiThue);
RootNguoiThue* ThemDanhSachNguoiThuetufile();
void InOrder(RootNguoiThue* root);
void DeleteDataInFile(long long CCCD);
void MenuforLessee();