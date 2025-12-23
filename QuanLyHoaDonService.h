#ifndef QUANLYHOADONSERVICE_H
#define QUANLYHOADONSERVICE_H

#include "HoaDon.h"
#include "QuanLyChiTietHoaDon.h"
#include "QuanLyKhachHangService.h"
#include "MyVector.h"
#include <string>
using namespace std;

class QuanLyHoaDonService
{
private:
    MyVector<HoaDon> &danhSachHoaDon;
    QuanLyChiTietHoaDon &quanLyChiTiet;

public:
    QuanLyHoaDonService(MyVector<HoaDon> &danhSach, QuanLyChiTietHoaDon &qlct);

    bool taoHoaDon(const HoaDon &hd);
    bool xoaHoaDon(const string &id);
    bool capNhatTrangThaiHoaDon(const string &id, const string &trangThai);

    HoaDon *timKiemHoaDon(const string &id);
    MyVector<HoaDon *> timKiemHoaDonTheoKhachHang(const string &idKhachHang);
    MyVector<HoaDon *> timKiemHoaDonTheoNgay(const string &ngay) const;

    string thanhToanHoaDon(const string &id, QuanLyKhachHangService *khService);
    bool huyThanhToanHoaDon(const string &id);

    string themDichVuVaoHoaDon(const string &idHoaDon, DichVu *dichVu, int soLuong);
    string xoaDichVuKhoiHoaDon(const string &idHoaDon, const string &idDichVu, DichVu *dichVu);
    string capNhatSoLuongDichVu(const string &idHoaDon, const string &idDichVu, int soLuongMoi, DichVu *dichVu);

    double tinhTongDoanhThuTheoNgay(const string &ngay) const;
    double tinhTongDoanhThuTheoThang(const string &thangNam) const;
    double tinhTongDoanhThu() const;

    void baoCaoDoanhThuTheoThang(const string &thangNam) const;

    bool kiemTraIdHoaDonTonTai(const string &id) const;
};

#endif