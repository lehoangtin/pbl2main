#ifndef FILE_READER_H
#define FILE_READER_H

#include "MyVector.h"
#include "NguoiDung.h"
#include "KhachHang.h"
#include "NhanVien.h"
#include "SanCauLong.h"
#include "SanNgoaiTroi.h"
#include "SanTrongNha.h"
#include "SanVIP.h"
#include "DichVu.h"
#include "DichVuAnUong.h"
#include "DichVuThietBi.h"
#include "DatSan.h"
#include "HoaDon.h"
#include "QuanLyChiTietHoaDon.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Hàm hỗ trợ tính số giờ thuê (Static để dùng nội bộ)
static int tinhSoGioThue(const string &gioBatDau, const string &gioKetThuc)
{
    try
    {
        int gioBD, phutBD, gioKT, phutKT;
        char colon;

        stringstream ssBD(gioBatDau);
        stringstream ssKT(gioKetThuc);

        ssBD >> gioBD >> colon >> phutBD;
        ssKT >> gioKT >> colon >> phutKT;

        int tongPhutBD = gioBD * 60 + phutBD;
        int tongPhutKT = gioKT * 60 + phutKT;

        // 23:00 đến 01:00
        if (tongPhutKT <= tongPhutBD)
        {
            tongPhutKT += 24 * 60;
        }

        int soPhut = tongPhutKT - tongPhutBD;
        int soGio = soPhut / 60;

        // Tính tròn giờ nếu có phút lẻ (ví dụ 1h15p -> 2h)
        if (soPhut % 60 > 0)
        {
            soGio++;
        }

        return soGio > 0 ? soGio : 1; // Tối thiểu 1 giờ
    }
    catch (...)
    {
        return 1; // Mặc định 1 giờ nếu lỗi
    }
}

class FileReader
{
public:
    // 1. ĐỌC KHÁCH HÀNG
    static MyVector<KhachHang> docKhachHang(const string &filename)
    {
        MyVector<KhachHang> danhSach;
        ifstream file(filename);

        if (!file.is_open())
        {
            cerr << "⚠️ Khong the mo file: " << filename << endl;
            return danhSach;
        }

        string line;
        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);
            string maKH, tenKH, sdt, email, diemStr, ngayDangKi;

            getline(ss, maKH, ',');
            getline(ss, tenKH, ',');
            getline(ss, sdt, ',');
            getline(ss, email, ',');
            getline(ss, diemStr, ',');
            getline(ss, ngayDangKi);

            if (maKH.empty())
                continue;

            try
            {
                int diem = stoi(diemStr);
                danhSach.push_back(KhachHang(maKH, tenKH, sdt, email, diem, ngayDangKi));
            }
            catch (...)
            {
                continue;
            }
        }
        file.close();
        return danhSach;
    }

    // 2. ĐỌC NHÂN VIÊN
    static MyVector<NhanVien> docNhanVien(const string &filename)
    {
        MyVector<NhanVien> danhSach;
        ifstream file(filename);

        if (!file.is_open())
            return danhSach;

        string line;
        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);
            string maNV, tenNV, sdt, email, chucVu, luongStr, caLamViec;

            getline(ss, maNV, ',');
            getline(ss, tenNV, ',');
            getline(ss, sdt, ',');
            getline(ss, email, ',');
            getline(ss, chucVu, ',');
            getline(ss, luongStr, ',');
            getline(ss, caLamViec);

            if (maNV.empty())
                continue;

            try
            {
                double luong = stod(luongStr);
                danhSach.push_back(NhanVien(maNV, tenNV, sdt, email, chucVu, luong, caLamViec));
            }
            catch (...)
            {
                continue;
            }
        }
        file.close();
        return danhSach;
    }

    // 3. ĐỌC SÂN CẦU LÔNG
    static MyVector<shared_ptr<SanCauLong>> docSan(const string &filename)
    {
        MyVector<shared_ptr<SanCauLong>> danhSach;
        ifstream file(filename);

        if (!file.is_open())
            return danhSach;

        string line;
        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);
            string loaiSan, maSan, tinhTrang, thongTin1, thongTin2, thongTin3, thongTin4;

            getline(ss, loaiSan, ',');
            getline(ss, maSan, ',');
            getline(ss, tinhTrang, ',');
            getline(ss, thongTin1, ','); // NgoaiTroi: ViTri, TrongNha: LamMat, VIP: DichVu
            getline(ss, thongTin2, ','); // NgoaiTroi: DienTich, TrongNha: DienTich, VIP: ChatLieu

            if (maSan.empty())
                continue;

            try
            {
                if (loaiSan == "NgoaiTroi")
                {
                    double dienTich = stod(thongTin2);
                    danhSach.push_back(make_shared<SanNgoaiTroi>(maSan, tinhTrang, thongTin1, dienTich));
                }
                else if (loaiSan == "TrongNha")
                {
                    getline(ss, thongTin3); // HeThongDen
                    double dienTich = stod(thongTin2);
                    danhSach.push_back(make_shared<SanTrongNha>(maSan, tinhTrang, thongTin1, dienTich, thongTin3));
                }
                else if (loaiSan == "VIP")
                {
                    getline(ss, thongTin3, ','); // DienTich
                    getline(ss, thongTin4);      // HeThongAmThanh
                    double dienTich = stod(thongTin3);
                    danhSach.push_back(make_shared<SanVIP>(maSan, tinhTrang, thongTin1, thongTin2, dienTich, thongTin4));
                }
            }
            catch (...)
            {
                continue;
            }
        }
        file.close();
        return danhSach;
    }

    // 4. ĐỌC DỊCH VỤ
    // 4. ĐỌC DỊCH VỤ - PHIÊN BẢN GỌN (Bỏ Info 1)
    static MyVector<shared_ptr<DichVu>> docDichVu(const string &filename)
    {
        MyVector<shared_ptr<DichVu>> danhSach;
        ifstream file(filename);

        if (!file.is_open())
            return danhSach;

        string line;
        while (getline(file, line))
        {
            if (line.empty())
                continue;
            if (line.back() == '\r')
                line.pop_back();

            stringstream ss(line);
            string loaiDV, id, tenDV, giaStr, donViTinh, soLuongStr;
            string trangThai = "";

            // 1. Đọc 6 trường cơ bản
            getline(ss, loaiDV, ',');
            getline(ss, id, ',');
            getline(ss, tenDV, ',');
            getline(ss, giaStr, ',');
            getline(ss, donViTinh, ',');
            getline(ss, soLuongStr, ',');

            if (id.empty())
                continue;

            // 2. Đọc trường cuối cùng (Trạng thái)
            if (ss.good())
                getline(ss, trangThai);

            try
            {
                double gia = stod(giaStr);
                int soLuong = stoi(soLuongStr);

                // Tự động cập nhật trạng thái nếu số lượng = 0
                if (soLuong == 0)
                    trangThai = "Het hang";
                else if (trangThai.empty())
                    trangThai = "Con hang";

                if (loaiDV == "AnUong")
                {
                    // Info1 (Loại ẩm thực) = "" (Rỗng)
                    // Info2 = trangThai
                    danhSach.push_back(make_shared<DichVuAnUong>(id, tenDV, gia, donViTinh, soLuong, "", trangThai));
                }
                else if (loaiDV == "ThietBi")
                {
                    // Info1 (Tình trạng) = "Tot" (Mặc định)
                    // Info2 = trangThai
                    danhSach.push_back(make_shared<DichVuThietBi>(id, tenDV, gia, donViTinh, soLuong, "Tot", trangThai));
                }
            }
            catch (...)
            {
                continue;
            }
        }
        file.close();
        return danhSach;
    }

    // 5. ĐỌC ĐẶT SÂN
    static MyVector<DatSan> docDatSan(const string &filename,
                                      MyVector<shared_ptr<SanCauLong>> &sanList,
                                      MyVector<KhachHang> &khachHangList,
                                      MyVector<NhanVien> &nhanVienList)
    {
        MyVector<DatSan> danhSach;
        ifstream file(filename);

        if (!file.is_open())
            return danhSach;

        string line;
        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);
            string maDS, maSan, maKH, maNV, ngayDat, gioBatDau, gioKetThuc;

            getline(ss, maDS, ',');
            getline(ss, maSan, ',');
            getline(ss, maKH, ',');
            getline(ss, maNV, ',');
            getline(ss, ngayDat, ',');
            getline(ss, gioBatDau, ',');
            getline(ss, gioKetThuc);

            if (maDS.empty() || maSan.empty())
                continue;

            DatSan datSan(maDS, maSan, maKH, maNV, ngayDat, gioBatDau, gioKetThuc);

            double tongTienSan = 0;
            shared_ptr<SanCauLong> sanPtr = nullptr;
            for (size_t i = 0; i < sanList.get_size(); i++)
            {
                if (sanList[i]->getIdSan() == maSan)
                {
                    sanPtr = sanList[i];
                    break;
                }
            }

            if (sanPtr)
            {
                int soGio = tinhSoGioThue(gioBatDau, gioKetThuc);
                tongTienSan = sanPtr->tinhGiaSan(soGio);
            }

            datSan.setTongTien(tongTienSan);
            danhSach.push_back(datSan);
        }
        file.close();
        return danhSach;
    }

    // 6. ĐỌC HÓA ĐƠN
    static MyVector<HoaDon> docHoaDon(const string &filename,
                                      MyVector<KhachHang> &khachHangList,
                                      MyVector<NhanVien> &nhanVienList,
                                      MyVector<DatSan> &datSanList,
                                      QuanLyChiTietHoaDon *quanLyChiTiet)
    {
        MyVector<HoaDon> danhSach;
        ifstream file(filename);

        if (!file.is_open())
            return danhSach;

        string line;
        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);
            string maHD, maKH, maNV, maDS, ngayLap, trangThai;

            getline(ss, maHD, ',');
            getline(ss, maKH, ',');
            getline(ss, maNV, ',');
            getline(ss, maDS, ',');
            getline(ss, ngayLap, ',');
            getline(ss, trangThai);

            if (maHD.empty())
                continue;

            string trangThaiChuan = HoaDon::chuanHoaTrangThai(trangThai);

            HoaDon hoaDon(maHD, maKH, maNV, maDS, ngayLap, quanLyChiTiet, trangThaiChuan);

            double tienSan = 0;
            if (!maDS.empty() && maDS != "NULL")
            {
                for (size_t i = 0; i < datSanList.get_size(); i++)
                {
                    if (datSanList[i].getIdDatSan() == maDS)
                    {
                        tienSan = datSanList[i].getTongTien();
                        break;
                    }
                }
            }

            // 4.set tiền sân riêng biệt
            hoaDon.setTienSan(tienSan);

            // 5. Tính toán tổng thể (tiền sân + tiền dịch vụ từ ChiTietHoaDon)
            hoaDon.tinhTongTien();

            danhSach.push_back(hoaDon);
        }
        file.close();
        return danhSach;
    }
};

#endif