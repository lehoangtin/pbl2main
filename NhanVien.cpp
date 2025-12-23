#include "NhanVien.h"
#include <iostream>
using namespace std;

NhanVien::NhanVien() : NguoiDung(), luong(0) {}

NhanVien::NhanVien(string id, string hoTen, string soDT, string email,
                   string chucVu, double luong, string caLamViec)
    : NguoiDung(id, hoTen, soDT, email),
      chucVu(chucVu), luong(luong), caLamViec(caLamViec) {}

void NhanVien::hienThi() const
{
    NguoiDung::hienThi();
    cout << " | Chuc vu: " << chucVu << " | Luong: " << luong
         << " | Ca: " << caLamViec << endl;
}

void NhanVien::nhap()
{
    NguoiDung::nhap();
    cout << "Nhap chuc vu: ";
    cin.ignore();
    getline(cin, chucVu);
    cout << "Nhap luong: ";
    cin >> luong;
    cout << "Nhap ca lam viec: ";
    cin.ignore();
    getline(cin, caLamViec);
}