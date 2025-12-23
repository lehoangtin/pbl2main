#ifndef QUANLYKHACHHANGSERVICE_H
#define QUANLYKHACHHANGSERVICE_H

#include "KhachHang.h"
#include "MyVector.h"
#include <string>

class QuanLyKhachHangService
{
private:
    MyVector<KhachHang> &danhSachKhachHang;

public:
    QuanLyKhachHangService(MyVector<KhachHang> &danhSach);

    bool themKhachHang(const KhachHang &kh);
    bool xoaKhachHang(const string &id);
    bool capNhatKhachHang(const string &id, const KhachHang &kh);
    KhachHang *timKiemKhachHang(const string &id);

    MyVector<KhachHang *> timKiemTheoTen(const string &ten);
    MyVector<KhachHang *> timKiemTheoSDT(const string &sdt);
    MyVector<KhachHang *> timKiemKhachHangVIP();

    bool tangDiemKhachHang(const string &id, int diem);
    bool giamDiemKhachHang(const string &id, int diem);
    bool kiemTraVIP(const string &id);
    int tichDiemTuDong(const string &id, double tongTien);
    bool kiemTraIdTonTai(const string &id) const;
    bool kiemTraSoDTTonTai(const string &soDT) const;

    int demSoKhachHangVIP() const;
    double tinhTyLeKhachHangVIP() const;
    void thongKeKhachHangTheoDiem() const;
};

#endif