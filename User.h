#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
using namespace std;

// Enum cho vai trò người dùng
enum class VaiTro
{
    ADMIN,
    NHAN_VIEN,
    KHACH_HANG
};

// Class User cho hệ thống đăng nhập
class User
{
private:
    string username;
    string password;
    VaiTro vaiTro;
    string hoTen;
    bool isActive;

public:
    User() : username(""), password(""), vaiTro(VaiTro::KHACH_HANG),
             hoTen(""), isActive(true) {}

    User(string user, string pass, VaiTro role, string ten)
        : username(user), password(pass), vaiTro(role), hoTen(ten), isActive(true) {}

    // Getters
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    VaiTro getVaiTro() const { return vaiTro; }
    string getHoTen() const { return hoTen; }
    bool getIsActive() const { return isActive; }

    // Setters
    void setPassword(string pass) { password = pass; }
    void setHoTen(string ten) { hoTen = ten; }
    void setIsActive(bool active) { isActive = active; }

    // Phương thức kiểm tra quyền
    bool isAdmin() const { return vaiTro == VaiTro::ADMIN; }
    bool isNhanVien() const { return vaiTro == VaiTro::NHAN_VIEN; }
    bool isKhachHang() const { return vaiTro == VaiTro::KHACH_HANG; }

    // Lấy tên vai trò
    string getTenVaiTro() const
    {
        switch (vaiTro)
        {
        case VaiTro::ADMIN:
            return "Admin";
        case VaiTro::NHAN_VIEN:
            return "Nhan Vien";
        case VaiTro::KHACH_HANG:
            return "Khach Hang";
        default:
            return "Unknown";
        }
    }

    // Xác thực mật khẩu
    bool xacThucMatKhau(const string &pass) const
    {
        return password == pass && isActive;
    }
};

#endif