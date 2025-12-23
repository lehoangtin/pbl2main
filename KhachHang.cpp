#include "KhachHang.h"
#include <iostream>
using namespace std;

KhachHang::KhachHang() : NguoiDung(), diem(0), ngayDangKi("") {}

KhachHang::KhachHang(string id, string hoTen, string soDT, string email,
                     int diem, string ngayDangKi)
    : NguoiDung(id, hoTen, soDT, email), diem(diem), ngayDangKi(ngayDangKi) {}

void KhachHang::hienThi() const
{
    NguoiDung::hienThi();
    cout << " | Diem: " << diem
         << " | Ngay dang ki: " << ngayDangKi
         << " | VIP: " << (kiemtraVIP() ? "Co" : "Khong") << endl;
}

void KhachHang::nhap()
{
    NguoiDung::nhap();
    cout << "Nhap diem: ";
    cin >> diem;
    cout << "Nhap ngay dang ki: ";
    cin.ignore();
    getline(cin, ngayDangKi);
}

void KhachHang::tangDiem(int diemThem)
{
    diem += diemThem;
}

bool KhachHang::kiemtraVIP() const
{
    return diem >= 100;
}