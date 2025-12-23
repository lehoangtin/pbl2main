#include "QuanLyHoaDonService.h"
#include <iostream>
#include <iomanip>

QuanLyHoaDonService::QuanLyHoaDonService(MyVector<HoaDon> &danhSach, QuanLyChiTietHoaDon &qlct)
    : danhSachHoaDon(danhSach), quanLyChiTiet(qlct) {}

bool QuanLyHoaDonService::taoHoaDon(const HoaDon &hd)
{
    if (kiemTraIdHoaDonTonTai(hd.getIdHoaDon()))
        return false;
    danhSachHoaDon.push_back(hd);
    return true;
}

bool QuanLyHoaDonService::xoaHoaDon(const string &id)
{
    for (size_t i = 0; i < danhSachHoaDon.get_size(); i++)
    {
        if (danhSachHoaDon[i].getIdHoaDon() == id)
        {
            auto chiTietList = quanLyChiTiet.getChiTietTheoHoaDon(id);
            for (size_t j = 0; j < chiTietList.get_size(); j++)
            {
                quanLyChiTiet.xoaChiTiet(id, chiTietList[j].getMaDichVu());
            }
            danhSachHoaDon.remove_at(i);
            return true;
        }
    }
    return false;
}

HoaDon *QuanLyHoaDonService::timKiemHoaDon(const string &id)
{
    for (size_t i = 0; i < danhSachHoaDon.get_size(); i++)
    {
        if (danhSachHoaDon[i].getIdHoaDon() == id)
            return &danhSachHoaDon[i];
    }
    return nullptr;
}

MyVector<HoaDon *> QuanLyHoaDonService::timKiemHoaDonTheoKhachHang(const string &idKhachHang)
{
    MyVector<HoaDon *> ketQua;
    for (size_t i = 0; i < danhSachHoaDon.get_size(); i++)
    {
        if (danhSachHoaDon[i].getIdKhachHang() == idKhachHang)
        {
            ketQua.push_back(&danhSachHoaDon[i]);
        }
    }
    return ketQua;
}

MyVector<HoaDon *> QuanLyHoaDonService::timKiemHoaDonTheoNgay(const string &ngay) const
{
    MyVector<HoaDon *> ketQua;
    for (size_t i = 0; i < danhSachHoaDon.get_size(); i++)
    {
        if (danhSachHoaDon[i].getNgayLap() == ngay)
        {
            ketQua.push_back(&danhSachHoaDon[i]);
        }
    }
    return ketQua;
}

bool QuanLyHoaDonService::capNhatTrangThaiHoaDon(const string &id, const string &trangThai)
{
    HoaDon *hd = timKiemHoaDon(id);
    if (hd)
    {
        hd->setTrangThai(trangThai);
        return true;
    }
    return false;
}

string QuanLyHoaDonService::thanhToanHoaDon(const string &id, QuanLyKhachHangService *khService)
{
    HoaDon *hd = timKiemHoaDon(id);
    if (hd)
    {
        if (hd->getTrangThai() == "Da thanh toan")
            return "Hoa don da thanh toan roi!";

        hd->setTrangThai("Da thanh toan");
        if (khService != nullptr)
        {
            int diemCong = khService->tichDiemTuDong(hd->getIdKhachHang(), hd->getTongTien());
            if (diemCong > 0)
            {
                return "Thanh toan thanh cong! Cong " + to_string(diemCong) + " diem.";
            }
        }
        return "Thanh toan thanh cong!";
    }
    return "Khong tim thay hoa don!";
}
string QuanLyHoaDonService::themDichVuVaoHoaDon(const string &idHoaDon, DichVu *dichVu, int soLuong)
{
    HoaDon *hd = timKiemHoaDon(idHoaDon);
    if (hd && dichVu)
        return hd->themDichVu(dichVu, soLuong);
    return "Khong tim thay hoa don hoac dich vu!";
}
string QuanLyHoaDonService::xoaDichVuKhoiHoaDon(const string &idHoaDon, const string &idDichVu, DichVu *dichVu)
{
    HoaDon *hd = timKiemHoaDon(idHoaDon);
    if (hd && dichVu)
        return hd->xoaDichVu(idDichVu, dichVu);
    return "Loi du lieu!";
}
bool QuanLyHoaDonService::huyThanhToanHoaDon(const string &id)
{
    return capNhatTrangThaiHoaDon(id, "Chua thanh toan");
}

string QuanLyHoaDonService::capNhatSoLuongDichVu(const string &idHoaDon, const string &idDichVu, int soLuongMoi, DichVu *dichVu)
{
    HoaDon *hd = timKiemHoaDon(idHoaDon);
    if (hd && dichVu)
        return hd->suaSoLuongDichVu(idDichVu, soLuongMoi, dichVu);
    return "Loi du lieu!";
}

double QuanLyHoaDonService::tinhTongDoanhThuTheoNgay(const string &ngay) const
{
    double tong = 0;
    auto hoaDonList = timKiemHoaDonTheoNgay(ngay);
    for (size_t i = 0; i < hoaDonList.get_size(); i++)
    {
        if (hoaDonList[i]->getTrangThai() == "Da thanh toan")
        {
            tong += hoaDonList[i]->getTongTien();
        }
    }
    return tong;
}

double QuanLyHoaDonService::tinhTongDoanhThuTheoThang(const string &thangNam) const
{
    double tong = 0;
    for (size_t i = 0; i < danhSachHoaDon.get_size(); i++)
    {
        string ngayLap = danhSachHoaDon[i].getNgayLap();
        if (ngayLap.length() >= 10)
        {
            string thangCuaHoaDon = ngayLap.substr(3); // Lấy phần "mm/yyyy"
            if (thangCuaHoaDon == thangNam && danhSachHoaDon[i].getTrangThai() == "Da thanh toan")
            {
                tong += danhSachHoaDon[i].getTongTien();
            }
        }
    }
    return tong;
}

double QuanLyHoaDonService::tinhTongDoanhThu() const
{
    double tong = 0;
    for (size_t i = 0; i < danhSachHoaDon.get_size(); i++)
    {
        if (danhSachHoaDon[i].getTrangThai() == "Da thanh toan")
        {
            tong += danhSachHoaDon[i].getTongTien();
        }
    }
    return tong;
}

// void QuanLyHoaDonService::baoCaoDoanhThuTheoThang(const string &thangNam) const
// {
//     cout << "\n=== BAO CAO DOANH THU THANG " << thangNam << " ===" << endl;
//     double doanhThu = tinhTongDoanhThuTheoThang(thangNam);
//     cout << "Tong doanh thu: " << fixed << setprecision(0) << doanhThu << " VND" << endl;
// }

bool QuanLyHoaDonService::kiemTraIdHoaDonTonTai(const string &id) const
{
    for (size_t i = 0; i < danhSachHoaDon.get_size(); i++)
    {
        if (danhSachHoaDon[i].getIdHoaDon() == id)
        {
            return true;
        }
    }
    return false;
}