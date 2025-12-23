#ifndef DICHVU_H
#define DICHVU_H

#include <string>
#include <iostream>
using namespace std;

class DichVu
{
protected:
    string id;
    string tenDV;
    double gia;
    string donViTinh;
    int soLuongTon;

public:
    DichVu();
    DichVu(string id, string tenDV, double gia, string donViTinh, int soLuongTon);

    virtual ~DichVu() = default;
    virtual string getLoaiDV() const = 0;

    string getId() const { return id; }
    string getTenDV() const { return tenDV; }
    double getGia() const { return gia; }
    string getDonViTinh() const { return donViTinh; }
    int getSoLuongTon() const { return soLuongTon; }

    void setId(string id) { this->id = id; }
    void setTenDV(string tenDV) { this->tenDV = tenDV; }
    void setGia(double gia) { this->gia = gia; }
    void setDonViTinh(string donViTinh) { this->donViTinh = donViTinh; }
    void setSoLuongTon(int soLuongTon) { this->soLuongTon = soLuongTon; }

    virtual void hienThi() const;
    virtual double tinhGia(int soLuong) const;

    bool kiemTraSoLuongTon(int soLuongCan) const;
    void capNhatSoLuong(int soLuong);
    bool timTheoId(string id) const;
    bool timTheoTen(string ten) const;
};

#endif