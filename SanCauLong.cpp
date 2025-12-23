#include "SanCauLong.h"
#include <iostream>
using namespace std;

SanCauLong::SanCauLong() : idSan(""), trangThai("Trong") {}

SanCauLong::SanCauLong(string idSan, string trangThai)
    : idSan(idSan), trangThai(trangThai) {}

void SanCauLong::hienThi() const
{
    cout << "ID San: " << idSan << " | Trang thai: " << trangThai;
}

bool SanCauLong::timTheoId(string id) const
{
    return idSan == id;
}

void SanCauLong::capNhatTrangThai(string trangThaiMoi)
{
    trangThai = trangThaiMoi;
}
