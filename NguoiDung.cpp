#include "NguoiDung.h"
#include <iostream>
using namespace std;

NguoiDung::NguoiDung() : id(""), hoTen(""), soDT(""), email("") {}

NguoiDung::NguoiDung(string id, string hoTen, string soDT, string email)
    : id(id), hoTen(hoTen), soDT(soDT), email(email) {}

void NguoiDung::hienThi() const
{
    cout << "ID: " << id << " | Ho ten: " << hoTen
         << " | So DT: " << soDT << " | Email: " << email;
}

void NguoiDung::nhap()
{
    cout << "Nhap ID: ";
    cin >> id;
    cout << "Nhap ho ten: ";
    cin.ignore();
    getline(cin, hoTen);
    cout << "Nhap so DT: ";
    cin >> soDT;
    cout << "Nhap email: ";
    cin >> email;
}

bool NguoiDung::timTheoSoDT(string sdt) const
{
    return soDT == sdt;
}

bool NguoiDung::timTheoId(string id) const
{
    return this->id == id;
}