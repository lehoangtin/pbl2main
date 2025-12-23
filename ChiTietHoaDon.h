#ifndef CHITIETHOADON_H
#define CHITIETHOADON_H

#include "DichVu.h"
#include <string>
#include <memory>
using namespace std;

class ChiTietHoaDon
{
private:
    string maHoaDon;
    string maDichVu;
    int soLuong;
    double donGia;
    double thanhTien;

public:
    ChiTietHoaDon() : maHoaDon(""), maDichVu(""), soLuong(0), donGia(0), thanhTien(0) {}

    ChiTietHoaDon(string maHD, string maDV, int soLuong, double donGia);

    void tinhThanhTien();

    string getMaHoaDon() const { return maHoaDon; }
    string getMaDichVu() const { return maDichVu; }
    int getSoLuong() const { return soLuong; }
    double getDonGia() const { return donGia; }
    double getThanhTien() const { return thanhTien; }

    void setSoLuong(int sl)
    {
        soLuong = sl;
        tinhThanhTien();
    }
    void setDonGia(double gia)
    {
        donGia = gia;
        tinhThanhTien();
    }
};

#endif