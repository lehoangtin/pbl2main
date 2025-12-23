#ifndef HOADON_H
#define HOADON_H

#include "KhachHang.h"
#include "NhanVien.h"
#include "DatSan.h"
#include "DichVu.h"
#include "ChiTietHoaDon.h"
#include "QuanLyChiTietHoaDon.h"
#include "MyVector.h"
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// Constants cho trạng thái
const string TRANG_THAI_CHUA_THANH_TOAN = "Chua thanh toan";
const string TRANG_THAI_DA_THANH_TOAN = "Da thanh toan";
const string TRANG_THAI_DA_HUY = "Da huy";

class HoaDon
{
private:
    string idHoaDon;
    string idKhachHang;
    string idNhanVien;
    string idDatSan;
    string ngayLap;
    string trangThai;
    QuanLyChiTietHoaDon *quanLyChiTiet;

    double tongTien;
    double tienSan;

public:
    HoaDon();
    HoaDon(string id, string idKhachHang, string idNhanVien, string idDatSan,
           string ngay, QuanLyChiTietHoaDon *qlct,
           string trangThai = TRANG_THAI_CHUA_THANH_TOAN);

    HoaDon(const HoaDon &other);

    HoaDon &operator=(const HoaDon &other);

    ~HoaDon();

    string getIdHoaDon() const { return idHoaDon; }
    string getIdKhachHang() const { return idKhachHang; }
    string getIdNhanVien() const { return idNhanVien; }
    string getIdDatSan() const { return idDatSan; }
    string getNgayLap() const { return ngayLap; }
    string getTrangThai() const { return trangThai; }
    double getTongTien() const { return tongTien; }
    double getTienSan() const { return tienSan; } 
    QuanLyChiTietHoaDon *getQuanLyChiTiet() const { return quanLyChiTiet; }

    void setIdHoaDon(string id) { idHoaDon = id; }
    void setIdKhachHang(string id) { idKhachHang = id; }
    void setIdNhanVien(string id) { idNhanVien = id; }
    void setIdDatSan(string id) { idDatSan = id; }
    void setTongTien(double tien) { this->tongTien = tien; }
    void setTienSan(double tien) { this->tienSan = tien; }
    void setNgayLap(string ngay) { ngayLap = ngay; }
    void setTrangThai(string tt) { trangThai = tt; }

    QuanLyChiTietHoaDon *&getQuanLyChiTiet() { return quanLyChiTiet; }

    string themDichVu(DichVu *dv, int soLuong = 1);
    string xoaDichVu(string maDV, DichVu *dichVu);
    string suaSoLuongDichVu(string maDV, int soLuongMoi, DichVu *dichVu);

    bool kiemTraDichVuDaCo(string maDV) const;
    double tinhTongTien();
    void hienThi() const;

    static bool kiemTraTrangThaiHopLe(const string &trangThai);
    static string chuanHoaTrangThai(const string &trangThai);

    MyVector<ChiTietHoaDon> getChiTietTheoHoaDon() const;
    ChiTietHoaDon *timChiTietTheoDichVu(string maDV);
    int getSoLuongDichVu() const;
    bool timTheoId(string id) const;
};

#endif