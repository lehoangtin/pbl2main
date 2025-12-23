#include "AuthenticationService.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

AuthenticationService::AuthenticationService() : currentUser(nullptr)
{
    khoiTaoTaiKhoanMacDinh();
}

void AuthenticationService::khoiTaoTaiKhoanMacDinh()
{
    // Admin mặc định
    User admin("admin", "admin123", VaiTro::ADMIN, "Administrator");
    danhSachUser.push_back(admin);

    // Nhân viên mặc định
    User nv1("nhanvien1", "nv123", VaiTro::NHAN_VIEN, "Nguyen Van A");
    danhSachUser.push_back(nv1);

    // Khách hàng mặc định
    User kh1("khach1", "kh123", VaiTro::KHACH_HANG, "Tran Thi B");
    danhSachUser.push_back(kh1);
}

bool AuthenticationService::dangNhap(const string &username, const string &password)
{
    for (size_t i = 0; i < danhSachUser.get_size(); i++)
    {
        if (danhSachUser[i].getUsername() == username)
        {
            if (danhSachUser[i].xacThucMatKhau(password))
            {
                currentUser = &danhSachUser[i];
                return true; // Thành công
            }
            else
            {
                return false; // Sai mật khẩu
            }
        }
    }
    return false; // Không tìm thấy user
}

void AuthenticationService::dangXuat()
{
    if (currentUser)
    {
        currentUser = nullptr;
    }
}

User *AuthenticationService::getCurrentUser()
{
    return currentUser;
}

bool AuthenticationService::isDangNhap() const
{
    return currentUser != nullptr;
}

bool AuthenticationService::isAdmin() const
{
    return currentUser && currentUser->isAdmin();
}

bool AuthenticationService::isNhanVien() const
{
    return currentUser && currentUser->isNhanVien();
}

bool AuthenticationService::isKhachHang() const
{
    return currentUser && currentUser->isKhachHang();
}

bool AuthenticationService::themUser(const string &username, const string &password, VaiTro role, const string &hoTen)
{
    if (!isAdmin())
    {
        return false;
    }

    // Kiểm tra username đã tồn tại
    for (size_t i = 0; i < danhSachUser.get_size(); i++)
    {
        if (danhSachUser[i].getUsername() == username)
        {
            return false;
        }
    }

    User newUser(username, password, role, hoTen);
    danhSachUser.push_back(newUser);
    return true;
}
bool AuthenticationService::xoaUser(const string &username)
{

    for (size_t i = 0; i < danhSachUser.get_size(); i++)
    {
        if (danhSachUser[i].getUsername() == username)
        {
            danhSachUser.remove_at(i);
            return true;
        }
    }
    return false;
}

bool AuthenticationService::doiMatKhau(const string &oldPass, const string &newPass)
{
    if (!currentUser)
    {
        return false;
    }

    if (!currentUser->xacThucMatKhau(oldPass))
    {
        return false;
    }

    currentUser->setPassword(newPass);
    return true;
}

void AuthenticationService::hienThiDanhSachUser()
{
    if (!isAdmin())
    {
        cout << "Ban khong co quyen thuc hien chuc nang nay!" << endl;
        return;
    }

    cout << "\n=== DANH SACH USER ===" << endl;
    cout << "+---------+----------------+----------------+---------------+--------+" << endl;
    cout << "| STT     | Username       | Ho Ten         | Vai Tro       | Active |" << endl;
    cout << "+---------+----------------+----------------+---------------+--------+" << endl;

    for (size_t i = 0; i < danhSachUser.get_size(); i++)
    {
        const User &u = danhSachUser[i];
        cout << "| " << i + 1 << "       "
             << "| " << u.getUsername() << "      "
             << "| " << u.getHoTen() << "    "
             << "| " << u.getTenVaiTro() << "  "
             << "| " << (u.getIsActive() ? "Yes" : "No") << "    |" << endl;
    }
    cout << "+---------+----------------+----------------+---------------+--------+" << endl;
}

void AuthenticationService::docUserTuFile(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        return;
    }

    danhSachUser.clear();
    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string username, password, roleStr, hoTen;

        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, roleStr, ',');
        getline(ss, hoTen);

        VaiTro role;
        if (roleStr == "ADMIN")
            role = VaiTro::ADMIN;
        else if (roleStr == "NHAN_VIEN")
            role = VaiTro::NHAN_VIEN;
        else
            role = VaiTro::KHACH_HANG;

        User user(username, password, role, hoTen);
        danhSachUser.push_back(user);
    }
    file.close();
}

void AuthenticationService::ghiUserVaoFile(const string &filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        return;
    }

    for (size_t i = 0; i < danhSachUser.get_size(); i++)
    {
        const User &u = danhSachUser[i];
        string roleStr;
        if (u.isAdmin())
            roleStr = "ADMIN";
        else if (u.isNhanVien())
            roleStr = "NHAN_VIEN";
        else
            roleStr = "KHACH_HANG";

        file << u.getUsername() << ","
             << u.getPassword() << ","
             << roleStr << ","
             << u.getHoTen() << endl;
    }
    file.close();
}