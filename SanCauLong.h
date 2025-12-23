#ifndef SANCAULONG_H
#define SANCAULONG_H

#include <string>
#include <iostream>
using namespace std;

class SanCauLong
{
protected:
    string idSan;
    string trangThai;

public:
    SanCauLong();
    SanCauLong(string idSan, string trangThai);
    virtual ~SanCauLong() = default;

    string getIdSan() const { return idSan; }
    string getTrangThai() const { return trangThai; }

    void setIdSan(string idSan) { this->idSan = idSan; }
    void setTrangThai(string trangThai) { this->trangThai = trangThai; }

    virtual void hienThi() const;
    virtual double tinhGiaSan(int gio) const = 0;
    virtual string getLoaiSan() const = 0;

    bool timTheoId(string id) const;
    void capNhatTrangThai(string trangThaiMoi);
};

#endif