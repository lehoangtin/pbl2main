#include "QuanLyKhachHangService.h"
#include <iostream>

QuanLyKhachHangService::QuanLyKhachHangService(MyVector<KhachHang> &danhSach)
    : danhSachKhachHang(danhSach) {}

bool QuanLyKhachHangService::themKhachHang(const KhachHang &kh)
{
    if (kiemTraIdTonTai(kh.getId()) || kiemTraSoDTTonTai(kh.getSoDT()))
    {
        return false;
    }
    danhSachKhachHang.push_back(kh);
    return true;
}

bool QuanLyKhachHangService::xoaKhachHang(const string &id)
{
    for (size_t i = 0; i < danhSachKhachHang.get_size(); i++)
    {
        if (danhSachKhachHang[i].getId() == id)
        {
            danhSachKhachHang.remove_at(i);
            return true;
        }
    }
    return false;
}

bool QuanLyKhachHangService::capNhatKhachHang(const string &id, const KhachHang &kh)
{
    for (size_t i = 0; i < danhSachKhachHang.get_size(); i++)
    {
        if (danhSachKhachHang[i].getId() == id)
        {
            if (kh.getSoDT() != danhSachKhachHang[i].getSoDT() &&
                kiemTraSoDTTonTai(kh.getSoDT()))
            {
                return false;
            }
            danhSachKhachHang[i] = kh;
            return true;
        }
    }
    return false;
}

KhachHang *QuanLyKhachHangService::timKiemKhachHang(const string &id)
{
    for (size_t i = 0; i < danhSachKhachHang.get_size(); i++)
    {
        if (danhSachKhachHang[i].getId() == id)
        {
            return &danhSachKhachHang[i];
        }
    }
    return nullptr;
}

MyVector<KhachHang *> QuanLyKhachHangService::timKiemTheoTen(const string &ten)
{
    MyVector<KhachHang *> ketQua;
    for (size_t i = 0; i < danhSachKhachHang.get_size(); i++)
    {
        if (danhSachKhachHang[i].getHoTen().find(ten) != string::npos)
        {
            ketQua.push_back(&danhSachKhachHang[i]);
        }
    }
    return ketQua;
}

MyVector<KhachHang *> QuanLyKhachHangService::timKiemTheoSDT(const string &sdt)
{
    MyVector<KhachHang *> ketQua;
    for (size_t i = 0; i < danhSachKhachHang.get_size(); i++)
    {
        if (danhSachKhachHang[i].getSoDT() == sdt)
        {
            ketQua.push_back(&danhSachKhachHang[i]);
        }
    }
    return ketQua;
}

MyVector<KhachHang *> QuanLyKhachHangService::timKiemKhachHangVIP()
{
    MyVector<KhachHang *> ketQua;
    for (size_t i = 0; i < danhSachKhachHang.get_size(); i++)
    {
        if (danhSachKhachHang[i].kiemtraVIP())
        {
            ketQua.push_back(&danhSachKhachHang[i]);
        }
    }
    return ketQua;
}

bool QuanLyKhachHangService::tangDiemKhachHang(const string &id, int diem)
{
    KhachHang *kh = timKiemKhachHang(id);
    if (kh)
    {
        kh->tangDiem(diem);
        return true;
    }
    return false;
}

bool QuanLyKhachHangService::giamDiemKhachHang(const string &id, int diem)
{
    KhachHang *kh = timKiemKhachHang(id);
    if (kh && kh->getDiem() >= diem)
    {
        kh->setDiem(kh->getDiem() - diem);
        return true;
    }
    return false;
}
int QuanLyKhachHangService::tichDiemTuDong(const string &id, double tongTien)
{
    const double MUC_QUY_DOI = 100000.0; // 100k = 1 điểm

    int diemCong = (int)(tongTien / MUC_QUY_DOI);

    if (diemCong > 0)
    {
        tangDiemKhachHang(id, diemCong);
    }

    return diemCong;
}
bool QuanLyKhachHangService::kiemTraVIP(const string &id)
{
    KhachHang *kh = timKiemKhachHang(id);
    return kh ? kh->kiemtraVIP() : false;
}

bool QuanLyKhachHangService::kiemTraIdTonTai(const string &id) const
{
    for (size_t i = 0; i < danhSachKhachHang.get_size(); i++)
    {
        if (danhSachKhachHang[i].getId() == id)
        {
            return true;
        }
    }
    return false;
}

bool QuanLyKhachHangService::kiemTraSoDTTonTai(const string &soDT) const
{
    for (size_t i = 0; i < danhSachKhachHang.get_size(); i++)
    {
        if (danhSachKhachHang[i].getSoDT() == soDT)
        {
            return true;
        }
    }
    return false;
}

int QuanLyKhachHangService::demSoKhachHangVIP() const
{
    int count = 0;
    for (size_t i = 0; i < danhSachKhachHang.get_size(); i++)
    {
        if (danhSachKhachHang[i].kiemtraVIP())
        {
            count++;
        }
    }
    return count;
}

double QuanLyKhachHangService::tinhTyLeKhachHangVIP() const
{
    if (danhSachKhachHang.get_size() == 0)
        return 0;
    return (double)demSoKhachHangVIP() / danhSachKhachHang.get_size() * 100;
}
