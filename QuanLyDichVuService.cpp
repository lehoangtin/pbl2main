#include "QuanLyDichVuService.h"
#include <iostream>

QuanLyDichVuService::QuanLyDichVuService(MyVector<shared_ptr<DichVu>> &danhSach)
    : danhSachDichVu(danhSach) {}

bool QuanLyDichVuService::themDichVu(shared_ptr<DichVu> dv)
{
    if (kiemTraIdTonTai(dv->getId()))
    {
        return false;
    }
    danhSachDichVu.push_back(dv);
    return true;
}

bool QuanLyDichVuService::xoaDichVu(const string &id)
{
    for (size_t i = 0; i < danhSachDichVu.get_size(); i++)
    {
        if (danhSachDichVu[i]->getId() == id)
        {
            danhSachDichVu.remove_at(i);
            return true;
        }
    }
    return false;
}

bool QuanLyDichVuService::capNhatSoLuongDichVu(const string &id, int soLuong)
{
    auto dv = timKiemDichVu(id);
    if (dv && soLuong >= 0)
    {
        dv->setSoLuongTon(soLuong);
        return true;
    }
    return false;
}

shared_ptr<DichVu> QuanLyDichVuService::timKiemDichVu(const string &id)
{
    for (size_t i = 0; i < danhSachDichVu.get_size(); i++)
    {
        if (danhSachDichVu[i]->getId() == id)
        {
            return danhSachDichVu[i];
        }
    }
    return nullptr;
}

MyVector<shared_ptr<DichVu>> QuanLyDichVuService::timKiemTheoTen(const string &ten)
{
    MyVector<shared_ptr<DichVu>> ketQua;
    for (size_t i = 0; i < danhSachDichVu.get_size(); i++)
    {
        if (danhSachDichVu[i]->getTenDV().find(ten) != string::npos)
        {
            ketQua.push_back(danhSachDichVu[i]);
        }
    }
    return ketQua;
}

MyVector<shared_ptr<DichVu>> QuanLyDichVuService::timKiemTheoLoai(const string &loai)
{
    MyVector<shared_ptr<DichVu>> ketQua;
    for (size_t i = 0; i < danhSachDichVu.get_size(); i++)
    {
        if (danhSachDichVu[i]->getLoaiDV() == loai)
        {
            ketQua.push_back(danhSachDichVu[i]);
        }
    }
    return ketQua;
}

MyVector<shared_ptr<DichVu>> QuanLyDichVuService::timKiemConHang()
{
    MyVector<shared_ptr<DichVu>> ketQua;
    for (size_t i = 0; i < danhSachDichVu.get_size(); i++)
    {
        if (danhSachDichVu[i]->getSoLuongTon() > 0)
        {
            ketQua.push_back(danhSachDichVu[i]);
        }
    }
    return ketQua;
}

bool QuanLyDichVuService::kiemTraSoLuongTon(const string &id, int soLuongCan)
{
    auto dv = timKiemDichVu(id);
    return dv ? dv->kiemTraSoLuongTon(soLuongCan) : false;
}

bool QuanLyDichVuService::giamSoLuongTon(const string &id, int soLuong)
{
    auto dv = timKiemDichVu(id);
    if (dv && dv->getSoLuongTon() >= soLuong)
    {
        dv->setSoLuongTon(dv->getSoLuongTon() - soLuong);
        return true;
    }
    return false;
}

bool QuanLyDichVuService::tangSoLuongTon(const string &id, int soLuong)
{
    auto dv = timKiemDichVu(id);
    if (dv && soLuong > 0)
    {
        dv->setSoLuongTon(dv->getSoLuongTon() + soLuong);
        return true;
    }
    return false;
}

double QuanLyDichVuService::tinhTongGiaTriTonKho() const
{
    double tong = 0;
    for (size_t i = 0; i < danhSachDichVu.get_size(); i++)
    {
        tong += danhSachDichVu[i]->getGia() * danhSachDichVu[i]->getSoLuongTon();
    }
    return tong;
}

bool QuanLyDichVuService::kiemTraIdTonTai(const string &id) const
{
    for (size_t i = 0; i < danhSachDichVu.get_size(); i++)
    {
        if (danhSachDichVu[i]->getId() == id)
        {
            return true;
        }
    }
    return false;
}

int QuanLyDichVuService::demSoLuongDichVuTheoLoai(const string &loai) const
{
    int count = 0;
    for (size_t i = 0; i < danhSachDichVu.get_size(); i++)
    {
        if (danhSachDichVu[i]->getLoaiDV() == loai)
        {
            count++;
        }
    }
    return count;
}