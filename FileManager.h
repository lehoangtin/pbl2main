#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "filereader.h"
#include "filewriter.h"
#include "MyVector.h"
#include "QuanLyChiTietHoaDon.h"

class FileManager
{
public:
    // Hàm tải tất cả dữ liệu (được gọi từ UIManager)
    static void loadAllData(
        MyVector<KhachHang> &kh,
        MyVector<NhanVien> &nv,
        MyVector<shared_ptr<SanCauLong>> &san,
        MyVector<shared_ptr<DichVu>> &dv,
        MyVector<DatSan> &ds,
        MyVector<HoaDon> &hd,
        QuanLyChiTietHoaDon *qlct)
    {
        // Gọi FileReader để đọc từng loại dữ liệu
        kh = FileReader::docKhachHang("khachhang.txt");
        nv = FileReader::docNhanVien("nhanvien.txt");
        san = FileReader::docSan("san.txt");
        dv = FileReader::docDichVu("dichvu.txt");
        ds = FileReader::docDatSan("datsan.txt", san, kh, nv);
        hd = FileReader::docHoaDon("hoadon.txt", kh, nv, ds, qlct);
    }

    // Hàm lưu tất cả dữ liệu (được gọi từ UIManager)
    static void saveAllData(
        const MyVector<KhachHang> &kh,
        const MyVector<NhanVien> &nv,
        const MyVector<shared_ptr<SanCauLong>> &san,
        const MyVector<shared_ptr<DichVu>> &dv,
        const MyVector<DatSan> &ds,
        const MyVector<HoaDon> &hd)
    {
        // Gọi FileWriter để ghi từng loại dữ liệu
        FileWriter::ghiKhachHang("khachhang.txt", kh);
        FileWriter::ghiNhanVien("nhanvien.txt", nv);
        FileWriter::ghiSan("san.txt", san);
        FileWriter::ghiDichVu("dichvu.txt", dv);
        FileWriter::ghiDatSan("datsan.txt", ds);
        FileWriter::ghiHoaDon("hoadon.txt", hd);
    }
};

#endif