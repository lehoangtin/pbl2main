#include "SanTrongNha.h"
#include <iostream>
using namespace std;

SanTrongNha::SanTrongNha() : SanCauLong(), heThongLamMat(""), dienTich(0), heThongDen("") {}

SanTrongNha::SanTrongNha(string idSan, string trangThai, string heThongLamMat,
                         double dienTich, string heThongDen)
    : SanCauLong(idSan, trangThai), heThongLamMat(heThongLamMat),
      dienTich(dienTich), heThongDen(heThongDen) {}

void SanTrongNha::hienThi() const
{
    SanCauLong::hienThi();
    cout << " | Loai: Trong nha | Lam mat: " << heThongLamMat
         << " | Dien tich: " << dienTich << "m2 | Den: " << heThongDen << endl;
}

double SanTrongNha::tinhGiaSan(int gio) const
{
    return gio * 80000; // 80,000 VND per hour
}

string SanTrongNha::getLoaiSan() const
{
    return "TrongNha";
}