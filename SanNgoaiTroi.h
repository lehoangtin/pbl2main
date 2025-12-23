#ifndef SANGOAITROI_H
#define SANGOAITROI_H

#include "SanCauLong.h"
#include <string>
using namespace std;

class SanNgoaiTroi : public SanCauLong
{
private:
    string viTri;
    double dienTich;

public:
    SanNgoaiTroi();
    SanNgoaiTroi(string idSan, string trangThai, string viTri, double dienTich);

    string getViTri() const { return viTri; }
    double getDienTich() const { return dienTich; }

    void setViTri(string viTri) { this->viTri = viTri; }
    void setDienTich(double dienTich) { this->dienTich = dienTich; }

    void hienThi() const override;
    double tinhGiaSan(int gio) const override;
    string getLoaiSan() const override;
};

#endif