#include "DichVu.h"
#include <iostream>
using namespace std;

DichVu::DichVu() : id(""), tenDV(""), gia(0), donViTinh(""), soLuongTon(0) {}

DichVu::DichVu(string id, string tenDV, double gia, string donViTinh, int soLuongTon)
    : id(id), tenDV(tenDV), gia(gia), donViTinh(donViTinh), soLuongTon(soLuongTon) {}

void DichVu::hienThi() const
{
    cout << "ID: " << id << " | Ten: " << tenDV << " | Gia: " << gia
         << " | Don vi: " << donViTinh << " | Ton: " << soLuongTon;
}

double DichVu::tinhGia(int soLuong) const
{
    return gia * soLuong;
}

bool DichVu::kiemTraSoLuongTon(int soLuongCan) const
{
    return soLuongTon >= soLuongCan;
}

void DichVu::capNhatSoLuong(int soLuong)
{
    soLuongTon += soLuong;
}

bool DichVu::timTheoId(string id) const
{
    return this->id == id;
}

bool DichVu::timTheoTen(string ten) const
{
    return tenDV.find(ten) != string::npos;
}