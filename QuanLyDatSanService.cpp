#include "QuanLyDatSanService.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

QuanLyDatSanService::QuanLyDatSanService(MyVector<DatSan> &dsDS,
                                         MyVector<shared_ptr<SanCauLong>> &dsSan,
                                         MyVector<KhachHang> &dsKH,
                                         MyVector<NhanVien> &dsNV)
    : danhSachDatSan(dsDS), danhSachSan(dsSan),
      danhSachKhachHang(dsKH), danhSachNhanVien(dsNV) {}
int QuanLyDatSanService::tinhSoGioThue(const string &gioBatDau, const string &gioKetThuc)
{
    try
    {
        int gioBD, phutBD, gioKT, phutKT;
        char colon;

        stringstream ssBD(gioBatDau);
        stringstream ssKT(gioKetThuc);

        ssBD >> gioBD >> colon >> phutBD;
        ssKT >> gioKT >> colon >> phutKT;

        int tongPhutBD = gioBD * 60 + phutBD;
        int tongPhutKT = gioKT * 60 + phutKT;

        if (tongPhutKT <= tongPhutBD)
        {
            tongPhutKT += 24 * 60; // Qua ngày hôm sau
        }

        int soPhut = tongPhutKT - tongPhutBD;
        int soGio = soPhut / 60;
        if (soPhut % 60 > 0)
        {
            soGio++;
        }

        return soGio > 0 ? soGio : 1; // Ít nhất 1 giờ
    }
    catch (...)
    {
        return 1; // Mặc định 1 giờ nếu có lỗi
    }
}
bool QuanLyDatSanService::kiemTraTrungGio(const string &maSan, const string &ngayDat,
                                          const string &gioBatDau, const string &gioKetThuc)
{
    int newStartMin = chuyenGioSangPhut(gioBatDau);
    int newEndMin = chuyenGioSangPhut(gioKetThuc);

    for (size_t i = 0; i < danhSachDatSan.get_size(); i++)
    {
        const DatSan &ds = danhSachDatSan[i];
        if ((ds.getIdSan() == maSan && ds.getNgayDat() == ngayDat))
        {
            int existingStartMin = chuyenGioSangPhut(ds.getGioBatDau());
            int existingEndMin = chuyenGioSangPhut(ds.getGioKetThuc());
            bool conflict =
                (newStartMin >= existingStartMin && newStartMin < existingEndMin) ||
                (newEndMin > existingStartMin && newEndMin <= existingEndMin) ||
                (newStartMin <= existingStartMin && newEndMin >= existingEndMin) ||
                (newStartMin >= existingStartMin && newEndMin <= existingEndMin);

            if (conflict)
            {
                return true;
            }
        }
    }
    return false;
}

int QuanLyDatSanService::chuyenGioSangPhut(const string &gio)
{
    try
    {
        int gioInt = stoi(gio.substr(0, 2));
        int phutInt = stoi(gio.substr(3, 2));
        return gioInt * 60 + phutInt;
    }
    catch (...)
    {
        return 0;
    }
}

bool QuanLyDatSanService::kiemTraKhungGioHopLe(const string &gioBatDau, const string &gioKetThuc)
{
    if (gioBatDau.length() != 5 || gioKetThuc.length() != 5 ||
        gioBatDau[2] != ':' || gioKetThuc[2] != ':')
    {
        return false;
    }

    try
    {
        int gioBD = stoi(gioBatDau.substr(0, 2));
        int phutBD = stoi(gioBatDau.substr(3, 2));
        int gioKT = stoi(gioKetThuc.substr(0, 2));
        int phutKT = stoi(gioKetThuc.substr(3, 2));

        if (gioBD < 0 || gioBD > 23 || phutBD < 0 || phutBD > 59 ||
            gioKT < 0 || gioKT > 23 || phutKT < 0 || phutKT > 59)
        {
            return false;
        }

        int tongPhutBD = gioBD * 60 + phutBD;
        int tongPhutKT = gioKT * 60 + phutKT;

        return tongPhutKT > tongPhutBD;
    }
    catch (...)
    {
        return false;
    }
}

MyVector<DatSan> QuanLyDatSanService::layDanhSachDatSanTheoSanVaNgay(const string &maSan, const string &ngayDat)
{
    MyVector<DatSan> ketQua;
    for (size_t i = 0; i < danhSachDatSan.get_size(); i++)
    {
        if (danhSachDatSan[i].getIdSan() == maSan && danhSachDatSan[i].getNgayDat() == ngayDat)
        {
            ketQua.push_back(danhSachDatSan[i]);
        }
    }
    return ketQua;
}
bool QuanLyDatSanService::datSanMoi(const string &idDS, const string &idSan,
                                    const string &idKH, const string &idNV,
                                    const string &ngayDat, const string &gioBD,
                                    const string &gioKT)
{
    for (size_t i = 0; i < danhSachDatSan.get_size(); i++)
        if (danhSachDatSan[i].getIdDatSan() == idDS)
            return false;

    if (kiemTraTrungGio(idSan, ngayDat, gioBD, gioKT))
        return false;

    shared_ptr<SanCauLong> san = nullptr;
    for (size_t i = 0; i < danhSachSan.get_size(); i++)
        if (danhSachSan[i]->getIdSan() == idSan)
        {
            san = danhSachSan[i];
            break;
        }

    if (!san)
        return false;

    DatSan datSan(idDS, idSan, idKH, idNV, ngayDat, gioBD, gioKT);
    int soGio = tinhSoGioThue(gioBD, gioKT);
    datSan.setTongTien(san->tinhGiaSan(soGio));

    danhSachDatSan.push_back(datSan);
    return true;
}
bool QuanLyDatSanService::huyDatSan(const string &id)
{
    for (size_t i = 0; i < danhSachDatSan.get_size(); i++)
    {
        if (danhSachDatSan[i].getIdDatSan() == id)
        {
            danhSachDatSan.remove_at(i);
            return true;
        }
    }
    return false;
}
