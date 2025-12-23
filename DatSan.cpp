#include "DatSan.h"
#include <sstream>
#include <iostream>
using namespace std;

DatSan::DatSan() : idDatSan(""), idSan(""), idKhachHang(""), idNhanVien(""),
                   ngayDat(""), gioBatDau(""), gioKetThuc(""), tongTien(0) {}

DatSan::DatSan(string idDatSan, string idSan, string idKhachHang,
               string idNhanVien, string ngayDat, string gioBatDau, string gioKetThuc)
    : idDatSan(idDatSan), idSan(idSan), idKhachHang(idKhachHang), idNhanVien(idNhanVien),
      ngayDat(ngayDat), gioBatDau(gioBatDau), gioKetThuc(gioKetThuc), tongTien(0)
{
}

void DatSan::hienThi() const
{
    cout << "ID Dat san: " << idDatSan << " | ";
    cout << "ID San: " << idSan;
    cout << " | ID Khach: " << idKhachHang;
    cout << " | ID NV: " << idNhanVien;
    cout << " | Ngay: " << ngayDat << " | " << gioBatDau << "-" << gioKetThuc
         << " | Tong tien: " << tongTien << " VND" << endl;
}

bool DatSan::timTheoId(string id) const
{
    return idDatSan == id;
}

bool DatSan::timTheoKhachHang(string idKhach) const
{
    return idKhachHang == idKhach;
}

bool DatSan::timTheoSan(string idSan) const
{
    return this->idSan == idSan;
}