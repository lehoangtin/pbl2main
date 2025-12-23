#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include "MyVector.h"
#include "KhachHang.h"
#include "NhanVien.h"
#include "SanCauLong.h"
#include "SanNgoaiTroi.h"
#include "SanTrongNha.h"
#include "SanVIP.h"
#include "DichVu.h"
#include "DichVuAnUong.h"
#include "DichVuThietBi.h"
#include "DatSan.h"
#include "HoaDon.h"
#include <fstream>
#include <iostream>

using namespace std;

class FileWriter
{
public:
    static bool ghiKhachHang(const string &filename, const MyVector<KhachHang> &danhSach)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Khong the mo file de ghi: " << filename << endl;
            return false;
        }

        for (size_t i = 0; i < danhSach.get_size(); i++)
        {
            const KhachHang &kh = danhSach[i];
            file << kh.getId() << ","
                 << kh.getHoTen() << ","
                 << kh.getSoDT() << ","
                 << kh.getEmail() << ","
                 << kh.getDiem() << ","
                 << kh.getNgayDangKi() << endl;
        }

        file.close();
        cout << "Da ghi " << danhSach.get_size() << " khach hang vao file " << filename << endl;
        return true;
    }

    static bool ghiNhanVien(const string &filename, const MyVector<NhanVien> &danhSach)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Khong the mo file de ghi: " << filename << endl;
            return false;
        }

        for (size_t i = 0; i < danhSach.get_size(); i++)
        {
            const NhanVien &nv = danhSach[i];
            file << nv.getId() << ","
                 << nv.getHoTen() << ","
                 << nv.getSoDT() << ","
                 << nv.getEmail() << ","
                 << nv.getChucVu() << ","
                 << nv.getLuong() << ","
                 << nv.getCaLamViec() << endl;
        }

        file.close();
        cout << "Da ghi " << danhSach.get_size() << " nhan vien vao file " << filename << endl;
        return true;
    }
    static bool ghiSan(const string &filename, const MyVector<shared_ptr<SanCauLong>> &danhSach)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Khong the mo file de ghi: " << filename << endl;
            return false;
        }

        for (size_t i = 0; i < danhSach.get_size(); i++)
        {
            const auto &san = danhSach[i];
            string loaiSan = san->getLoaiSan();

            file << loaiSan << ","
                 << san->getIdSan() << ","
                 << san->getTrangThai();

            if (loaiSan == "NgoaiTroi")
            {
                SanNgoaiTroi *sanNT = dynamic_cast<SanNgoaiTroi *>(san.get());
                if (sanNT)
                {
                    file << "," << sanNT->getViTri()
                         << "," << sanNT->getDienTich();
                }
            }
            else if (loaiSan == "TrongNha")
            {
                SanTrongNha *sanTN = dynamic_cast<SanTrongNha *>(san.get());
                if (sanTN)
                {
                    file << "," << sanTN->getHeThongLamMat()
                         << "," << sanTN->getDienTich()
                         << "," << sanTN->getHeThongDen();
                }
            }
            else if (loaiSan == "VIP")
            {
                SanVIP *sanV = dynamic_cast<SanVIP *>(san.get());
                if (sanV)
                {
                    file << "," << sanV->getDichVuKemTheo()
                         << "," << sanV->getChatLieuSan()
                         << "," << sanV->getDienTich()
                         << "," << sanV->getHeThongAmThanh();
                }
            }
            file << endl;
        }

        file.close();
        cout << "Da ghi " << danhSach.get_size() << " san vao file " << filename << endl;
        return true;
    }
    static bool ghiDichVu(const string &filename, const MyVector<shared_ptr<DichVu>> &danhSach)
    {
        ofstream file(filename);
        if (!file.is_open())
            return false;

        for (size_t i = 0; i < danhSach.get_size(); i++)
        {
            const auto &dv = danhSach[i];
            string loaiDV = dv->getLoaiDV();
            file << loaiDV << ","
                 << dv->getId() << ","
                 << dv->getTenDV() << ","
                 << (size_t)dv->getGia() << ","
                 << dv->getDonViTinh() << ","
                 << dv->getSoLuongTon();

            string trangThai = (dv->getSoLuongTon() > 0) ? "Con hang" : "Het hang";
            if (loaiDV == "AnUong")
            {
                file << "," << trangThai;
            }
            else if (loaiDV == "ThietBi")
            {
                DichVuThietBi *dvTB = dynamic_cast<DichVuThietBi *>(dv.get());
                if (dvTB)
                {
                    file << "," << trangThai;
                }
            }
            file << endl;
        }
        file.close();
        return true;
    }
    static bool ghiDatSan(const string &filename, const MyVector<DatSan> &danhSach)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Khong the mo file de ghi: " << filename << endl;
            return false;
        }

        for (size_t i = 0; i < danhSach.get_size(); i++)
        {
            const DatSan &ds = danhSach[i];
            file << ds.getIdDatSan() << ","
                 << ds.getIdSan() << ","
                 << ds.getIdKhachHang() << ","
                 << ds.getIdNhanVien() << ","
                 << ds.getNgayDat() << ","
                 << ds.getGioBatDau() << ","
                 << ds.getGioKetThuc() << endl;
        }
        file.close();
        cout << "Da ghi " << danhSach.get_size() << " dat san vao file " << filename << endl;
        return true;
    }
    static bool ghiHoaDon(const string &filename, const MyVector<HoaDon> &danhSach)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Khong the mo file de ghi: " << filename << endl;
            return false;
        }

        for (size_t i = 0; i < danhSach.get_size(); i++)
        {
            const HoaDon &hd = danhSach[i];
            file << hd.getIdHoaDon() << ","
                 << hd.getIdKhachHang() << ","
                 << hd.getIdNhanVien() << ","
                 << hd.getIdDatSan() << ","
                 << hd.getNgayLap() << ","
                 << hd.getTrangThai() << endl;
        }

        file.close();
        cout << "Da ghi " << danhSach.get_size() << " hoa don vao file " << filename << endl;
        return true;
    }
};

#endif
