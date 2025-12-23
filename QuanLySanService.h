#ifndef QUANLYSANSERVICE_H
#define QUANLYSANSERVICE_H

#include "SanCauLong.h"
#include "MyVector.h"
#include <memory>
#include <string>
using namespace std;

class QuanLySanService
{
private:
    MyVector<shared_ptr<SanCauLong>> &danhSachSan;

public:
    QuanLySanService(MyVector<shared_ptr<SanCauLong>> &danhSach);

    bool themSan(shared_ptr<SanCauLong> san);
    bool xoaSan(const string &id);
    shared_ptr<SanCauLong> timKiemSan(const string &id);
    MyVector<shared_ptr<SanCauLong>> timKiemSanTrong();

    bool kiemTraIdSanTonTai(const string &id) const;

    int demSanTheoTrangThai(const string &trangThai) const;
    void thongKeSan() const;
};

#endif