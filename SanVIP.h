#ifndef SANVIP_H
#define SANVIP_H

#include "SanCauLong.h"
#include <string>
using namespace std;

class SanVIP : public SanCauLong
{
private:
    string dichVuKemTheo;
    string chatLieuSan;
    double dienTich;
    string heThongAmThanh;

public:
    SanVIP();
    SanVIP(string idSan, string trangThai, string dichVuKemTheo,
           string chatLieuSan, double dienTich, string heThongAmThanh);

    string getDichVuKemTheo() const { return dichVuKemTheo; }
    string getChatLieuSan() const { return chatLieuSan; }
    double getDienTich() const { return dienTich; }
    string getHeThongAmThanh() const { return heThongAmThanh; }

    void setDichVuKemTheo(string dichVuKemTheo) { this->dichVuKemTheo = dichVuKemTheo; }
    void setChatLieuSan(string chatLieuSan) { this->chatLieuSan = chatLieuSan; }
    void setDienTich(double dienTich) { this->dienTich = dienTich; }
    void setHeThongAmThanh(string heThongAmThanh) { this->heThongAmThanh = heThongAmThanh; }

    void hienThi() const override;
    double tinhGiaSan(int gio) const override;
    string getLoaiSan() const override;
};

#endif