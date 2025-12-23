#include "QuanLyNhanVienService.h"
#include <iostream>

QuanLyNhanVienService::QuanLyNhanVienService(MyVector<NhanVien> &danhSach)
    : danhSachNhanVien(danhSach) {}

bool QuanLyNhanVienService::themNhanVien(const NhanVien &nv)
{
    if (kiemTraIdTonTai(nv.getId()) || kiemTraSoDTTonTai(nv.getSoDT()))
    {
        return false;
    }
    danhSachNhanVien.push_back(nv);
    return true;
}

bool QuanLyNhanVienService::xoaNhanVien(const string &id)
{
    for (size_t i = 0; i < danhSachNhanVien.get_size(); i++)
    {
        if (danhSachNhanVien[i].getId() == id)
        {
            danhSachNhanVien.remove_at(i);
            return true;
        }
    }
    return false;
}

NhanVien *QuanLyNhanVienService::timKiemNhanVien(const string &id)
{
    for (size_t i = 0; i < danhSachNhanVien.get_size(); i++)
    {
        if (danhSachNhanVien[i].getId() == id)
        {
            return &danhSachNhanVien[i];
        }
    }
    return nullptr;
}

bool QuanLyNhanVienService::kiemTraIdTonTai(const string &id) const
{
    for (size_t i = 0; i < danhSachNhanVien.get_size(); i++)
    {
        if (danhSachNhanVien[i].getId() == id)
        {
            return true;
        }
    }
    return false;
}

bool QuanLyNhanVienService::kiemTraSoDTTonTai(const string &soDT) const
{
    for (size_t i = 0; i < danhSachNhanVien.get_size(); i++)
    {
        if (danhSachNhanVien[i].getSoDT() == soDT)
        {
            return true;
        }
    }
    return false;
}

double QuanLyNhanVienService::tinhTongLuong() const
{
    double tong = 0;
    for (size_t i = 0; i < danhSachNhanVien.get_size(); i++)
    {
        tong += danhSachNhanVien[i].getLuong();
    }
    return tong;
}

double QuanLyNhanVienService::tinhLuongTrungBinh() const
{
    if (danhSachNhanVien.get_size() == 0)
        return 0;
    return tinhTongLuong() / danhSachNhanVien.get_size();
}