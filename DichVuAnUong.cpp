#include "DichVuAnUong.h"
#include <iostream>
using namespace std;

DichVuAnUong::DichVuAnUong() : DichVu(), loaiAmThuc(""), tinhTrangTon("") {}

DichVuAnUong::DichVuAnUong(string id, string tenDV, double gia, string donViTinh,
                           int soLuongTon, string loaiAmThuc, string tinhTrangTon)
    : DichVu(id, tenDV, gia, donViTinh, soLuongTon),
      loaiAmThuc(loaiAmThuc), tinhTrangTon(tinhTrangTon) {}

void DichVuAnUong::hienThi() const
{
    DichVu::hienThi();
    cout << " | Loai am thuc: " << loaiAmThuc << " | Tinh trang ton: " << tinhTrangTon << endl;
}

double DichVuAnUong::tinhGia(int soLuong) const
{
    return gia * soLuong;
}