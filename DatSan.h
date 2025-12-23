#ifndef DATSAN_H
#define DATSAN_H

#include "SanCauLong.h"
#include "KhachHang.h"
#include "NhanVien.h"
#include <string>
#include <iostream>
using namespace std;

class DatSan
{
private:
    string idDatSan;
    string idSan;
    string idKhachHang;
    string idNhanVien;

    string ngayDat;
    string gioBatDau;
    string gioKetThuc;
    double tongTien;

public:
    DatSan();
    DatSan(string idDatSan, string idSan, string idKhachHang,
           string idNhanVien, string ngayDat, string gioBatDau, string gioKetThuc);

    string getIdDatSan() const { return idDatSan; }
    string getIdSan() const { return idSan; }
    string getIdKhachHang() const { return idKhachHang; }
    string getIdNhanVien() const { return idNhanVien; }
    string getNgayDat() const { return ngayDat; }
    string getGioBatDau() const { return gioBatDau; }
    string getGioKetThuc() const { return gioKetThuc; }
    double getTongTien() const { return tongTien; }

    void setIdDatSan(string id) { this->idDatSan = id; }
    void setIdSan(string id) { this->idSan = id; }
    void setIdKhachHang(string id) { this->idKhachHang = id; }
    void setIdNhanVien(string id) { this->idNhanVien = id; }
    void setNgayDat(string ngay) { this->ngayDat = ngay; }
    void setGioBatDau(string gio) { this->gioBatDau = gio; }
    void setGioKetThuc(string gio) { this->gioKetThuc = gio; }

    void setTongTien(double tien) { this->tongTien = tien; }
    void hienThi() const;
    bool timTheoId(string id) const;
    bool timTheoKhachHang(string idKhach) const;
    bool timTheoSan(string idSan) const;
};

#endif