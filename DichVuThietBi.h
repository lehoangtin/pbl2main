#ifndef DICHVUTHIETBI_H
#define DICHVUTHIETBI_H

#include "DichVu.h"
#include <string>
using namespace std;

class DichVuThietBi : public DichVu
{
private:
    string tinhTrang;
    string thoiGianThue;

public:
    DichVuThietBi();
    DichVuThietBi(string id, string tenDV, double gia, string donViTinh,
                  int soLuongTon, string tinhTrang, string thoiGianThue);

    string getTinhTrang() const { return tinhTrang; }
    string getThoiGianThue() const { return thoiGianThue; }
    string getLoaiDV() const override { return "ThietBi"; }

    void setTinhTrang(string tinhTrang) { this->tinhTrang = tinhTrang; }
    void setThoiGianThue(string thoiGianThue) { this->thoiGianThue = thoiGianThue; }

    void hienThi() const override;
    double tinhGia(int soLuong) const override;
};

#endif