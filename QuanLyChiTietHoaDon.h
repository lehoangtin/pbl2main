#ifndef QUANLYCHITIETHOADON_H
#define QUANLYCHITIETHOADON_H

#include "ChiTietHoaDon.h"
#include "MyVector.h"
#include <string>
using namespace std;

class QuanLyChiTietHoaDon
{
private:
    MyVector<ChiTietHoaDon> danhSachChiTiet;

public:
    QuanLyChiTietHoaDon() = default;

    bool themChiTiet(string maHD, string maDV, int soLuong, double donGia);
    bool xoaChiTiet(string maHD, string maDV);

    MyVector<ChiTietHoaDon> getChiTietTheoHoaDon(string maHD) const;
    MyVector<ChiTietHoaDon> getChiTietTheoDichVu(string maDV) const;
    ChiTietHoaDon *timChiTiet(string maHD, string maDV);

    double tinhTongTienHoaDon(string maHD) const;
    int tinhTongSoLuongDichVu(string maDV) const;
};

#endif