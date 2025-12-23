#include "SanVIP.h"
#include <iostream>
using namespace std;

SanVIP::SanVIP() : SanCauLong(), dichVuKemTheo(""), chatLieuSan(""),
                   dienTich(0), heThongAmThanh("") {}

SanVIP::SanVIP(string idSan, string trangThai, string dichVuKemTheo,
               string chatLieuSan, double dienTich, string heThongAmThanh)
    : SanCauLong(idSan, trangThai), dichVuKemTheo(dichVuKemTheo),
      chatLieuSan(chatLieuSan), dienTich(dienTich), heThongAmThanh(heThongAmThanh) {}

void SanVIP::hienThi() const
{
    SanCauLong::hienThi();
    cout << " | Loai: VIP | DV kem theo: " << dichVuKemTheo
         << " | Chat lieu: " << chatLieuSan << " | Dien tich: " << dienTich
         << "m2 | Am thanh: " << heThongAmThanh << endl;
}

double SanVIP::tinhGiaSan(int gio) const
{
    return gio * 120000; // 120,000 VND per hour
}

string SanVIP::getLoaiSan() const
{
    return "VIP";
}