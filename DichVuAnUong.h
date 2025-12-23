#ifndef DICHVUANUONG_H
#define DICHVUANUONG_H

#include "DichVu.h"
#include <string>
using namespace std;

class DichVuAnUong : public DichVu
{
private:
    string loaiAmThuc;
    string tinhTrangTon;

public:
    DichVuAnUong();
    DichVuAnUong(string id, string tenDV, double gia, string donViTinh,
                 int soLuongTon, string loaiAmThuc, string tinhTrangTon);

    string getLoaiAmThuc() const { return loaiAmThuc; }
    string getTinhTrangTon() const { return tinhTrangTon; }
    string getLoaiDV() const override { return "AnUong"; }

    void setLoaiAmThuc(string loaiAmThuc) { this->loaiAmThuc = loaiAmThuc; }
    void setTinhTrangTon(string tinhTrangTon) { this->tinhTrangTon = tinhTrangTon; }

    void hienThi() const override;
    double tinhGia(int soLuong) const override;
};

#endif