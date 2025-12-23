#ifndef QUANLYNHANVIENSERVICE_H
#define QUANLYNHANVIENSERVICE_H

#include "NhanVien.h"
#include "MyVector.h"
#include <string>
using namespace std;

class QuanLyNhanVienService
{
private:
    MyVector<NhanVien> &danhSachNhanVien;

public:
    QuanLyNhanVienService(MyVector<NhanVien> &danhSach);

    bool themNhanVien(const NhanVien &nv);
    bool xoaNhanVien(const string &id);
    NhanVien *timKiemNhanVien(const string &id);

    bool kiemTraIdTonTai(const string &id) const;
    bool kiemTraSoDTTonTai(const string &soDT) const;

    double tinhTongLuong() const;
    double tinhLuongTrungBinh() const;
};

#endif