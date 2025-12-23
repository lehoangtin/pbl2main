#ifndef SANTRONGNHA_H
#define SANTRONGNHA_H

#include "SanCauLong.h"
#include <string>
using namespace std;

class SanTrongNha : public SanCauLong
{
private:
    string heThongLamMat;
    double dienTich;
    string heThongDen;

public:
    SanTrongNha();
    SanTrongNha(string idSan, string trangThai, string heThongLamMat,
                double dienTich, string heThongDen);

    string getHeThongLamMat() const { return heThongLamMat; }
    double getDienTich() const { return dienTich; }
    string getHeThongDen() const { return heThongDen; }

    void setHeThongLamMat(string heThongLamMat) { this->heThongLamMat = heThongLamMat; }
    void setDienTich(double dienTich) { this->dienTich = dienTich; }
    void setHeThongDen(string heThongDen) { this->heThongDen = heThongDen; }

    void hienThi() const override;
    double tinhGiaSan(int gio) const override;
    string getLoaiSan() const override;
};

#endif