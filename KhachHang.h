#ifndef KHACHHANG_H
#define KHACHHANG_H

#include "NguoiDung.h"
#include <string>
using namespace std;

class KhachHang : public NguoiDung
{
private:
    int diem;
    string ngayDangKi;

public:
    KhachHang();
    KhachHang(string id, string hoTen, string soDT, string email,
              int diem, string ngayDangKi);

    void hienThi() const override;
    void nhap() override;

    int getDiem() const { return diem; }
    string getNgayDangKi() const { return ngayDangKi; }

    void setDiem(int diem) { this->diem = diem; }
    void setNgayDangKi(string ngayDangKi) { this->ngayDangKi = ngayDangKi; }

    void tangDiem(int diemThem);
    bool kiemtraVIP() const;
};

#endif