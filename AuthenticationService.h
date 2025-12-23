#ifndef AUTHENTICATION_SERVICE_H
#define AUTHENTICATION_SERVICE_H

#include "User.h"
#include "MyVector.h"
#include <string>

using namespace std;

class AuthenticationService
{
private:
    MyVector<User> danhSachUser;
    User *currentUser;

public:
    AuthenticationService();

    void khoiTaoTaiKhoanMacDinh();

    bool dangNhap(const string &username, const string &password);
    void dangXuat();

    bool doiMatKhau(const string &oldPass, const string &newPass);

    bool themUser(const string &username, const string &password, VaiTro role, const string &hoTen);
    bool xoaUser(const string &username);
    User *getCurrentUser();
    bool isDangNhap() const;
    bool isAdmin() const;
    bool isNhanVien() const;
    bool isKhachHang() const;

    void docUserTuFile(const string &filename);
    void ghiUserVaoFile(const string &filename);

    void hienThiDanhSachUser();
};

#endif