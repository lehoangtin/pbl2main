#include "HoaDon.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

HoaDon::HoaDon()
    : idHoaDon(""), idKhachHang(""), idNhanVien(""), idDatSan(""),
      ngayLap(""), trangThai(TRANG_THAI_CHUA_THANH_TOAN),
      quanLyChiTiet(nullptr), tongTien(0), tienSan(0)
{
}

HoaDon::HoaDon(string id, string idKhach, string idNV, string idDS,
               string ngay, QuanLyChiTietHoaDon *qlct, string tt)
    : idHoaDon(id), idKhachHang(idKhach), idNhanVien(idNV), idDatSan(idDS),
      ngayLap(ngay), quanLyChiTiet(qlct), tongTien(0), tienSan(0)
{
    trangThai = chuanHoaTrangThai(tt);
}

HoaDon::HoaDon(const HoaDon &other)
    : idHoaDon(other.idHoaDon),
      idKhachHang(other.idKhachHang),
      idNhanVien(other.idNhanVien),
      idDatSan(other.idDatSan),
      ngayLap(other.ngayLap),
      trangThai(other.trangThai),
      quanLyChiTiet(other.quanLyChiTiet),
      tongTien(other.tongTien),
      tienSan(other.tienSan)
{
}

HoaDon &HoaDon::operator=(const HoaDon &other)
{
    if (this != &other)
    {
        idHoaDon = other.idHoaDon;
        idKhachHang = other.idKhachHang;
        idNhanVien = other.idNhanVien;
        idDatSan = other.idDatSan;
        ngayLap = other.ngayLap;
        trangThai = other.trangThai;
        quanLyChiTiet = other.quanLyChiTiet;
        tongTien = other.tongTien;
        tienSan = other.tienSan;
    }
    return *this;
}

HoaDon::~HoaDon()
{
}

double HoaDon::tinhTongTien()
{
    tongTien = tienSan;

    if (quanLyChiTiet != nullptr)
    {
        tongTien += quanLyChiTiet->tinhTongTienHoaDon(idHoaDon);
    }

    return tongTien;
}
string HoaDon::themDichVu(DichVu *dv, int soLuong)
{
    if (dv == nullptr || quanLyChiTiet == nullptr)
        return "Loi: Dich vu hoac quan ly chi tiet khong hop le!";
    if (trangThai == TRANG_THAI_DA_THANH_TOAN)
        return "Khong the them dich vu vao hoa don da thanh toan!";
    if (!dv->kiemTraSoLuongTon(soLuong))
        return "Khong du so luong ton! Chi con " + to_string(dv->getSoLuongTon());

    if (quanLyChiTiet->themChiTiet(idHoaDon, dv->getId(), soLuong, dv->getGia()))
    {
        dv->setSoLuongTon(dv->getSoLuongTon() - soLuong);
        tinhTongTien();
        return ""; // Thành công trả về chuỗi rỗng
    }
    return "Dich vu da ton tai trong hoa don! Vui long chon chuc nang cap nhat.";
}
string HoaDon::xoaDichVu(string maDV, DichVu *dichVu)
{
    if (quanLyChiTiet == nullptr || dichVu == nullptr)
        return "Du lieu khong hop le";
    if (trangThai == TRANG_THAI_DA_THANH_TOAN)
        return "Hoa don da thanh toan, khong the xoa!";

    ChiTietHoaDon *chiTiet = quanLyChiTiet->timChiTiet(idHoaDon, maDV);
    if (chiTiet == nullptr)
        return "Khong tim thay dich vu trong hoa don";

    int soLuongHoanTra = chiTiet->getSoLuong();
    if (quanLyChiTiet->xoaChiTiet(idHoaDon, maDV))
    {
        dichVu->setSoLuongTon(dichVu->getSoLuongTon() + soLuongHoanTra);
        tinhTongTien();
        return ""; // Thành công
    }
    return "Loi xoa chi tiet";
}
string HoaDon::suaSoLuongDichVu(string maDV, int soLuongMoi, DichVu *dichVu)
{
    if (quanLyChiTiet == nullptr || dichVu == nullptr)
        return "Du lieu khong hop le";
    if (trangThai == TRANG_THAI_DA_THANH_TOAN)
        return "Hoa don da thanh toan, khong the sua!";

    ChiTietHoaDon *chiTiet = quanLyChiTiet->timChiTiet(idHoaDon, maDV);
    if (chiTiet == nullptr)
        return "Khong tim thay dich vu";

    int soLuongCu = chiTiet->getSoLuong();
    int chenhLech = soLuongMoi - soLuongCu;

    if (chenhLech > 0 && !dichVu->kiemTraSoLuongTon(chenhLech))
    {
        return "Khong du hang trong kho! Can them: " + to_string(chenhLech);
    }

    dichVu->setSoLuongTon(dichVu->getSoLuongTon() - chenhLech);
    chiTiet->setSoLuong(soLuongMoi);
    tinhTongTien();
    return ""; // Thành công
}

void HoaDon::hienThi() const
{
    cout << "HD: " << idHoaDon
         << " | " << ngayLap
         << " | " << trangThai
         << " | " << fixed << setprecision(0) << tongTien << " VND"
         << " | KH: " << idKhachHang;
    cout << endl;
}

bool HoaDon::timTheoId(string id) const
{
    return idHoaDon == id;
}

MyVector<ChiTietHoaDon> HoaDon::getChiTietTheoHoaDon() const
{
    if (quanLyChiTiet != nullptr)
    {
        return quanLyChiTiet->getChiTietTheoHoaDon(idHoaDon);
    }
    return MyVector<ChiTietHoaDon>();
}

ChiTietHoaDon *HoaDon::timChiTietTheoDichVu(string maDV)
{
    if (quanLyChiTiet != nullptr)
    {
        return quanLyChiTiet->timChiTiet(idHoaDon, maDV);
    }
    return nullptr;
}

int HoaDon::getSoLuongDichVu() const
{
    if (quanLyChiTiet != nullptr)
    {
        return quanLyChiTiet->getChiTietTheoHoaDon(idHoaDon).get_size();
    }
    return 0;
}

bool HoaDon::kiemTraDichVuDaCo(string maDV) const
{
    if (quanLyChiTiet != nullptr)
    {
        return quanLyChiTiet->timChiTiet(idHoaDon, maDV) != nullptr;
    }
    return false;
}

bool HoaDon::kiemTraTrangThaiHopLe(const string &trangThai)
{
    string tt = chuanHoaTrangThai(trangThai);
    return (tt == TRANG_THAI_CHUA_THANH_TOAN || tt == TRANG_THAI_DA_THANH_TOAN);
}

string HoaDon::chuanHoaTrangThai(const string &trangThai)
{
    string result = trangThai;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    // Xóa khoảng trắng
    result.erase(remove(result.begin(), result.end(), ' '), result.end());

    if (result == "chuathanhtoan" || result == "chua" || result == "0")
        return TRANG_THAI_CHUA_THANH_TOAN;
    else if (result == "dathanhtoan" || result == "da" || result == "1")
        return TRANG_THAI_DA_THANH_TOAN;

    return TRANG_THAI_CHUA_THANH_TOAN;
}