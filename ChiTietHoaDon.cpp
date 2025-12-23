#include "ChiTietHoaDon.h"

ChiTietHoaDon::ChiTietHoaDon(string maHD, string maDV, int soLuong, double donGia)
    : maHoaDon(maHD), maDichVu(maDV), soLuong(soLuong), donGia(donGia), thanhTien(0)
{
    tinhThanhTien();
}

void ChiTietHoaDon::tinhThanhTien()
{
    thanhTien = soLuong * donGia;
}