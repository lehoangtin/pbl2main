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

// void QuanLySanService::thongKeSan() const
// {
//     cout << "\n=== THONG KE SAN ===" << endl;
//     cout << "Tong so san: " << danhSachSan.get_size() << endl;

//     int ngoaiTroi = 0, trongNha = 0, vip = 0;
//     for (size_t i = 0; i < danhSachSan.get_size(); i++)
//     {
//         string loai = danhSachSan[i]->getLoaiSan();
//         if (loai == "NgoaiTroi")
//             ngoaiTroi++;
//         else if (loai == "TrongNha")
//             trongNha++;
//         else if (loai == "VIP")
//             vip++;
//     }

//     cout << "SAN NGOAI TROI: " << ngoaiTroi << " san" << endl;
//     cout << "SAN TRONG NHA: " << trongNha << " san" << endl;
//     cout << "SAN VIP: " << vip << " san" << endl;

//     cout << "\nTRANG THAI SAN:" << endl;
//     cout << "San trong: " << demSanTheoTrangThai("Trong") << endl;
//     cout << "San da dat: " << demSanTheoTrangThai("Da dat") << endl;
//     cout << "San dang bao tri: " << demSanTheoTrangThai("Bao tri") << endl;

//     // Tính phần trăm
//     int total = danhSachSan.get_size();
//     if (total > 0)
//     {
//         cout << "\nTY LE:" << endl;
//         cout << "Ngoai troi: " << (ngoaiTroi * 100 / total) << "%" << endl;
//         cout << "Trong nha: " << (trongNha * 100 / total) << "%" << endl;
//         cout << "VIP: " << (vip * 100 / total) << "%" << endl;
//     }
// }