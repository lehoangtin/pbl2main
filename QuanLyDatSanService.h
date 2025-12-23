#ifndef QUANLYDATSANSERVICE_H
#define QUANLYDATSANSERVICE_H

#include "DatSan.h"
#include "SanCauLong.h"
#include "KhachHang.h"
#include "NhanVien.h"
#include "MyVector.h"
#include <memory>
#include <string>
using namespace std;

class QuanLyDatSanService
{
private:
    MyVector<DatSan> &danhSachDatSan;
    MyVector<shared_ptr<SanCauLong>> &danhSachSan;
    MyVector<KhachHang> &danhSachKhachHang;
    MyVector<NhanVien> &danhSachNhanVien;
    static int tinhSoGioThue(const string &gioBatDau, const string &gioKetThuc);

public:
    QuanLyDatSanService(MyVector<DatSan> &dsDatSan,
                        MyVector<shared_ptr<SanCauLong>> &dsSan,
                        MyVector<KhachHang> &dsKhachHang,
                        MyVector<NhanVien> &dsNhanVien);
    // Các phương thức hiện có
    bool datSanMoi(const string &idDatSan, const string &maSan, const string &maKH,
                   const string &maNV, const string &ngayDat, const string &gioBatDau,
                   const string &gioKetThuc);

    bool huyDatSan(const string &idDatSan);

    bool datSanVoiLichTrung(const string &idDatSan, const string &maSan,
                            const string &maKH, const string &maNV,
                            const string &ngayDat);

    void hienThiLichSanTheoNgay(const string &maSan, const string &ngayDat);

    bool kiemTraTrungGio(const string &maSan, const string &ngayDat,
                         const string &gioBatDau, const string &gioKetThuc);

    MyVector<DatSan> layDanhSachDatSanTheoSanVaNgay(const string &maSan, const string &ngayDat);

    bool kiemTraKhungGioHopLe(const string &gioBatDau, const string &gioKetThuc);

    int chuyenGioSangPhut(const string &gio);
    string chuyenPhutSangGio(int phut);

    MyVector<pair<string, string>> timKhungGioTrong(const string &maSan, const string &ngayDat);
};

#endif