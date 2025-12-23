#include "DichVuThietBi.h"
#include <iostream>
using namespace std;

DichVuThietBi::DichVuThietBi() : DichVu(), tinhTrang(""), thoiGianThue("") {}

DichVuThietBi::DichVuThietBi(string id, string tenDV, double gia, string donViTinh,
                             int soLuongTon, string tinhTrang, string thoiGianThue)
    : DichVu(id, tenDV, gia, donViTinh, soLuongTon),
      tinhTrang(tinhTrang), thoiGianThue(thoiGianThue) {}

void DichVuThietBi::hienThi() const
{
    DichVu::hienThi();
    cout << " | Tinh trang: " << tinhTrang << " | Thoi gian thue: " << thoiGianThue << endl;
}

double DichVuThietBi::tinhGia(int soLuong) const
{
    return gia * soLuong;
}