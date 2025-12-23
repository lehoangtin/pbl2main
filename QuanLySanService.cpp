#include "QuanLySanService.h"
#include <iostream>

QuanLySanService::QuanLySanService(MyVector<shared_ptr<SanCauLong>> &danhSach)
    : danhSachSan(danhSach) {}

bool QuanLySanService::themSan(shared_ptr<SanCauLong> san)
{
    if (kiemTraIdSanTonTai(san->getIdSan()))
    {
        return false;
    }
    danhSachSan.push_back(san);
    return true;
}

bool QuanLySanService::xoaSan(const string &id)
{
    for (size_t i = 0; i < danhSachSan.get_size(); i++)
    {
        if (danhSachSan[i]->getIdSan() == id)
        {
            danhSachSan.remove_at(i);
            return true;
        }
    }
    return false;
}

shared_ptr<SanCauLong> QuanLySanService::timKiemSan(const string &id)
{
    for (size_t i = 0; i < danhSachSan.get_size(); i++)
    {
        if (danhSachSan[i]->getIdSan() == id)
        {
            return danhSachSan[i];
        }
    }
    return nullptr;
}

MyVector<shared_ptr<SanCauLong>> QuanLySanService::timKiemSanTrong()
{
    MyVector<shared_ptr<SanCauLong>> ketQua;
    for (size_t i = 0; i < danhSachSan.get_size(); i++)
    {
        if (danhSachSan[i]->getTrangThai() == "Trong")
        {
            ketQua.push_back(danhSachSan[i]);
        }
    }
    return ketQua;
}

bool QuanLySanService::kiemTraIdSanTonTai(const string &id) const
{
    for (size_t i = 0; i < danhSachSan.get_size(); i++)
    {
        if (danhSachSan[i]->getIdSan() == id)
        {
            return true;
        }
    }
    return false;
}

int QuanLySanService::demSanTheoTrangThai(const string &trangThai) const
{
    int count = 0;
    for (size_t i = 0; i < danhSachSan.get_size(); i++)
    {
        if (danhSachSan[i]->getTrangThai() == trangThai)
        {
            count++;
        }
    }
    return count;
}