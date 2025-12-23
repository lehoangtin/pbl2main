#ifndef NHANVIEN_H
#define NHANVIEN_H

#include "NguoiDung.h"
#include <string>
using namespace std;

class NhanVien : public NguoiDung
{
private:
    string chucVu;
    double luong;
    string caLamViec;

public:
    NhanVien();
    NhanVien(string id, string hoTen, string soDT, string email,
             string chucVu, double luong, string caLamViec);

    void hienThi() const override;
    void nhap() override;

    string getChucVu() const { return chucVu; }
    double getLuong() const { return luong; }
    string getCaLamViec() const { return caLamViec; }

    void setChucVu(string chucVu) { this->chucVu = chucVu; }
    void setLuong(double luong) { this->luong = luong; }
    void setCaLamViec(string caLamViec) { this->caLamViec = caLamViec; }
};

#endif