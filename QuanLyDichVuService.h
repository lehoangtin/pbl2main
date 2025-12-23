#ifndef QUANLYDICHVUSERVICE_H
#define QUANLYDICHVUSERVICE_H

#include "DichVu.h"
#include "DichVuAnUong.h"
#include "DichVuThietBi.h"
#include "MyVector.h"
#include <memory>

class QuanLyDichVuService
{
private:
    MyVector<shared_ptr<DichVu>> &danhSachDichVu;

public:
    QuanLyDichVuService(MyVector<shared_ptr<DichVu>> &danhSach);

    bool themDichVu(shared_ptr<DichVu> dv);
    bool xoaDichVu(const string &id);
    bool capNhatSoLuongDichVu(const string &id, int soLuong);

    shared_ptr<DichVu> timKiemDichVu(const string &id);
    MyVector<shared_ptr<DichVu>> timKiemTheoTen(const string &ten);
    MyVector<shared_ptr<DichVu>> timKiemTheoLoai(const string &loai);
    MyVector<shared_ptr<DichVu>> timKiemConHang();

    bool kiemTraSoLuongTon(const string &id, int soLuongCan);
    bool giamSoLuongTon(const string &id, int soLuong);
    bool tangSoLuongTon(const string &id, int soLuong);

    double tinhTongGiaTriTonKho() const;

    bool kiemTraIdTonTai(const string &id) const;

    int demSoLuongDichVuTheoLoai(const string &loai) const;
    void thongKeTonKho() const;
};

#endif