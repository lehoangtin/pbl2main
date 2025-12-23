#include "QuanLyChiTietHoaDon.h"
#include <iostream>
using namespace std;

bool QuanLyChiTietHoaDon::themChiTiet(string maHD, string maDV, int soLuong, double donGia)
{
    ChiTietHoaDon *existing = timChiTiet(maHD, maDV);
    if (existing != nullptr)
    {
        return false;
    }

    ChiTietHoaDon chiTiet(maHD, maDV, soLuong, donGia);
    danhSachChiTiet.push_back(chiTiet);
    return true;
}

bool QuanLyChiTietHoaDon::xoaChiTiet(string maHD, string maDV)
{
    for (size_t i = 0; i < danhSachChiTiet.get_size(); i++)
    {
        if (danhSachChiTiet[i].getMaHoaDon() == maHD &&
            danhSachChiTiet[i].getMaDichVu() == maDV)
        {
            danhSachChiTiet.remove_at(i);
            return true;
        }
    }
    return false;
}

MyVector<ChiTietHoaDon> QuanLyChiTietHoaDon::getChiTietTheoHoaDon(string maHD) const
{
    MyVector<ChiTietHoaDon> ketQua;
    for (size_t i = 0; i < danhSachChiTiet.get_size(); i++)
    {
        if (danhSachChiTiet[i].getMaHoaDon() == maHD)
        {
            ketQua.push_back(danhSachChiTiet[i]);
        }
    }
    return ketQua;
}

MyVector<ChiTietHoaDon> QuanLyChiTietHoaDon::getChiTietTheoDichVu(string maDV) const
{
    MyVector<ChiTietHoaDon> ketQua;
    for (size_t i = 0; i < danhSachChiTiet.get_size(); i++)
    {
        if (danhSachChiTiet[i].getMaDichVu() == maDV)
        {
            ketQua.push_back(danhSachChiTiet[i]);
        }
    }
    return ketQua;
}

ChiTietHoaDon *QuanLyChiTietHoaDon::timChiTiet(string maHD, string maDV)
{
    for (size_t i = 0; i < danhSachChiTiet.get_size(); i++)
    {
        if (danhSachChiTiet[i].getMaHoaDon() == maHD &&
            danhSachChiTiet[i].getMaDichVu() == maDV)
        {
            return &danhSachChiTiet[i];
        }
    }
    return nullptr;
}

double QuanLyChiTietHoaDon::tinhTongTienHoaDon(string maHD) const
{
    double tong = 0;
    for (size_t i = 0; i < danhSachChiTiet.get_size(); i++)
    {
        if (danhSachChiTiet[i].getMaHoaDon() == maHD)
        {
            tong += danhSachChiTiet[i].getThanhTien();
        }
    }
    return tong;
}

int QuanLyChiTietHoaDon::tinhTongSoLuongDichVu(string maDV) const
{
    int tong = 0;
    for (size_t i = 0; i < danhSachChiTiet.get_size(); i++)
    {
        if (danhSachChiTiet[i].getMaDichVu() == maDV)
        {
            tong += danhSachChiTiet[i].getSoLuong();
        }
    }
    return tong;
}