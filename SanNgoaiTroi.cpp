#include "SanNgoaiTroi.h"
#include <iostream>
using namespace std;

SanNgoaiTroi::SanNgoaiTroi() : SanCauLong(), viTri(""), dienTich(0) {}

SanNgoaiTroi::SanNgoaiTroi(string idSan, string trangThai, string viTri, double dienTich)
    : SanCauLong(idSan, trangThai), viTri(viTri), dienTich(dienTich) {}

void SanNgoaiTroi::hienThi() const
{
    SanCauLong::hienThi();
    cout << " | Loai: Ngoai troi | Vi tri: " << viTri
         << " | Dien tich: " << dienTich << "m2" << endl;
}

double SanNgoaiTroi::tinhGiaSan(int gio) const
{
    return gio * 50000; // 50,000 VND per hour
}

string SanNgoaiTroi::getLoaiSan() const
{
    return "NgoaiTroi";
}