#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <memory>
#include <string>
#include <vector>
#include "User.h"
#include "AuthenticationService.h"
#include "QuanLyNhanVienService.h"
#include "QuanLyKhachHangService.h"
#include "QuanLySanService.h"
#include "QuanLyDichVuService.h"
#include "QuanLyDatSanService.h"
#include "QuanLyHoaDonService.h"
#include "FileManager.h"
#include "NhanVien.h"
#include "KhachHang.h"
#include "SanCauLong.h"
#include "SanNgoaiTroi.h"
#include "SanTrongNha.h"
#include "SanVIP.h"
#include "DichVu.h"
#include "DichVuAnUong.h"
#include "DichVuThietBi.h"
#include "DatSan.h"
#include "HoaDon.h"

class UIManager
{
private:
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
    AuthenticationService authService;
    User *currentUser = nullptr;

    // du lieu
    MyVector<KhachHang> danhSachKhachHang;
    MyVector<NhanVien> danhSachNhanVien;
    MyVector<shared_ptr<SanCauLong>> danhSachSan;
    MyVector<shared_ptr<DichVu>> danhSachDichVu;
    MyVector<DatSan> danhSachDatSan;
    MyVector<HoaDon> danhSachHoaDon;
    QuanLyChiTietHoaDon quanLyChiTietHoaDon;

    // nghiep vu
    std::unique_ptr<QuanLyNhanVienService> nhanVienService;
    std::unique_ptr<QuanLyKhachHangService> khachHangService;
    std::unique_ptr<QuanLySanService> sanService;
    std::unique_ptr<QuanLyDichVuService> dichVuService;
    std::unique_ptr<QuanLyDatSanService> datSanService;
    std::unique_ptr<QuanLyHoaDonService> hoaDonService;

    // trang thai
    bool isLoggedIn = false;
    bool shouldExitApp = false;
    int app_state_selector = 0;
    std::string loginUsername = "", loginPassword = "", loginError = "";
    std::string statusMessage = "";

    // lua chon menu
    int adminMenuSelected = 0;
    int staffMenuSelected = 0;
    int customerMenuSelected = 0;

    std::string delete_id = "";

    // 1. Nhân viên
    std::string nv_id = "", nv_ten = "", nv_sdt = "", nv_email = "", nv_chucvu = "", nv_luong = "", nv_ca = "";
    bool show_nv_input = false;
    std::string nv_tim_id = "";

    // 2. Khách hàng
    std::string kh_id = "", kh_ten = "", kh_sdt = "", kh_email = "", kh_diem = "0", kh_ngaydk = "";
    bool show_kh_input = false;
    std::string kh_tang_id = "", kh_tang_diem = "10";
    std::string kh_tim_id = "";

    // 3. Sân
    std::string san_id = "";
    int san_loai_idx = 0; // 0: NgoaiTroi, 1: TrongNha, 2: VIP
    std::string san_info1 = "", san_info2 = "", san_info3 = "", san_info4 = "";
    bool show_san_input = false;
    std::string san_tim_id = "";

    // 4. Dịch vụ
    std::string dv_id = "", dv_ten = "", dv_gia = "", dv_dvt = "", dv_ton = "";
    int dv_loai_idx = 0; // 0: AnUong, 1: ThietBi
    std::string dv_info1 = "", dv_info2 = "";
    bool show_dv_input = false;
    std::string dv_tim_id = "";

    // 5. Đặt sân
    std::string ds_id = "",
                ds_san_id = "", ds_kh_id = "", ds_ngay = "", ds_gio_bd = "", ds_gio_kt = "";
    bool show_ds_input = false;
    std::string ds_tim_id = "";
    bool ds_xem_lich_mode = false;
    // 6. Hóa đơn
    std::string hd_id = "", hd_ds_id = "";
    std::string hd_ngay_add = "";
    bool show_hd_input = false;
    std::string dv_ma_hd = "", dv_ma_dv = "", dv_so_luong = "1";
    std::string hd_tim_id = "";
    bool view_invoice_mode = false;
    // 7. Thống kê
    std::string tk_ngay = "";
    std::string tk_thang_nam = "";
    std::string pass_old = "";
    std::string pass_new1 = "";
    std::string pass_new2 = "";

public:
    UIManager();
    ~UIManager();
    void run();

private:
    ftxui::Component createLoginScreen();
    ftxui::Component createMainMenu();
    ftxui::Component createAdminDashboard();
    ftxui::Component createNhanVienDashboard();
    ftxui::Component createKhachHangDashboard();

    // Các hàm quản lý
    ftxui::Component createNhanVienManager();
    ftxui::Component createKhachHangManager();
    ftxui::Component createSanManager();
    ftxui::Component createDichVuManager();
    ftxui::Component createDatSanManager();
    ftxui::Component createHoaDonManager();
    ftxui::Component createThongKe();
    ftxui::Component createDoiMatKhau();
    ftxui::Component createSimpleOverview();
    // Helpers
    void loadData();
    void saveData();
    void dangXuat();
    void resetAllForms();
    bool kiemTraDinhDangID(const std::string &id, const std::string &loai);
    bool kiemTraDinhDangSoDT(const std::string &sdt);
    bool kiemTraDinhDangNgay(const std::string &ngay);
    bool kiemTraDinhDangGio(const std::string &gio);
    ftxui::Element createHeader(const std::string &title);
    ftxui::Element createTable(const std::vector<std::vector<std::string>> &data);
    std::string formatMoney(double amount);
};

#endif