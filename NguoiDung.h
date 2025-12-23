#ifndef NGUOIDUNG_H
#define NGUOIDUNG_H

#include <string>
#include <iostream>
using namespace std;

class NguoiDung
{
protected:
    string id;
    string hoTen;
    string soDT;
    string email;

public:
    NguoiDung();
    NguoiDung(string id, string hoTen, string soDT, string email);
    virtual ~NguoiDung() = default;

    string getId() const { return id; }
    string getHoTen() const { return hoTen; }
    string getSoDT() const { return soDT; }
    string getEmail() const { return email; }

    void setId(string id) { this->id = id; }
    void setHoTen(string hoTen) { this->hoTen = hoTen; }
    void setSoDT(string soDT) { this->soDT = soDT; }
    void setEmail(string email) { this->email = email; }

    virtual void hienThi() const;
    virtual void nhap();

    bool timTheoSoDT(string sdt) const;
    bool timTheoId(string id) const;
};

#endif