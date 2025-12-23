#include "UIManager.h"
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/table.hpp>
#include <sstream>
#include <iomanip>
#include <algorithm>

// Hàm style
ftxui::InputOption StyleInputDep()
{
    ftxui::InputOption option;
    option.transform = [](ftxui::InputState state)
    {
        auto element = state.element;
        if (state.is_placeholder)
        {
            element = element | ftxui::color(ftxui::Color::GrayDark);
        }
        else
        {
            element = element | ftxui::color(ftxui::Color::Black);
        }

        if (state.focused)
        {
            element = element | ftxui::bgcolor(ftxui::Color::White) | ftxui::bold;
        }
        else
        {
            element = element | ftxui::bgcolor(ftxui::Color::GrayLight);
        }

        return element;
    };
    return option;
}
ftxui::Element input_label(std::string t, int w)
{
    return ftxui::text(t) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, w) | ftxui::center;
}

// constructor destructor setup
UIManager::UIManager()
{
    nhanVienService = std::make_unique<QuanLyNhanVienService>(danhSachNhanVien);
    khachHangService = std::make_unique<QuanLyKhachHangService>(danhSachKhachHang);
    sanService = std::make_unique<QuanLySanService>(danhSachSan);
    dichVuService = std::make_unique<QuanLyDichVuService>(danhSachDichVu);
    datSanService = std::make_unique<QuanLyDatSanService>(danhSachDatSan, danhSachSan,
                                                          danhSachKhachHang, danhSachNhanVien);
    hoaDonService = std::make_unique<QuanLyHoaDonService>(danhSachHoaDon, quanLyChiTietHoaDon);

    loadData();
    authService.docUserTuFile("user.txt");
}

UIManager::~UIManager()
{
    saveData();
    authService.ghiUserVaoFile("user.txt");
}
void UIManager::run()
{
    auto loginScreen = createLoginScreen();
    auto mainMenu = createMainMenu();

    auto main_container = ftxui::Container::Tab(
        {
            loginScreen,
            mainMenu,
        },
        &app_state_selector);

    screen.Loop(main_container);
}

void UIManager::dangXuat()
{
    isLoggedIn = false;
    currentUser = nullptr;
    loginUsername = "";
    loginPassword = "";
    loginError = "";
    resetAllForms();
    app_state_selector = 0;
}

void UIManager::resetAllForms()
{
    adminMenuSelected = 0;
    staffMenuSelected = 0;
    customerMenuSelected = 0;
    statusMessage = "";
    delete_id = "";

    nv_id = "";
    nv_ten = "";
    nv_sdt = "";
    nv_luong = "";
    kh_id = "";
    kh_ten = "";
    kh_sdt = "";
    kh_diem = "0";
    san_id = "";
    san_info1 = "";
    san_info2 = "";
    dv_id = "";
    dv_ten = "";
    dv_gia = "";
    ds_id = "";
    ds_san_id = "";
    ds_kh_id = "";
    hd_id = "";
    hd_ds_id = "";
    hd_ngay_add = "";

    show_nv_input = false;
    show_kh_input = false;
    show_san_input = false;
    show_dv_input = false;
    show_ds_input = false;
    show_hd_input = false;

    tk_ngay = "";
    tk_thang_nam = "";
    ds_xem_lich_mode = false;
}

// Màn login
ftxui::Component UIManager::createLoginScreen()
{
    loginError = "";
    auto input_username = ftxui::Input(&loginUsername, "Username", StyleInputDep());

    ftxui::InputOption password_option = StyleInputDep();
    password_option.password = true;
    auto input_password = ftxui::Input(&loginPassword, "Password", password_option);

    auto button_login = ftxui::Button("🔐 Đăng nhập", [=]
                                      {
        if (loginUsername.empty() || loginPassword.empty()) {
            loginError = "❌ Vui lòng nhập đầy đủ thông tin!"; return;
        }
        if (authService.dangNhap(loginUsername, loginPassword)) {
            currentUser = authService.getCurrentUser();
            isLoggedIn = true;
            app_state_selector = 1; 
        } else {
            loginError = "❌ Sai tên đăng nhập hoặc mật khẩu!";
            loginPassword = ""; 
        } });

    auto button_exit = ftxui::Button("🚪 Thoát App", [=]
                                     { shouldExitApp = true; screen.ExitLoopClosure()(); });

    auto container = ftxui::Container::Vertical({
        input_username,
        input_password,
        ftxui::Container::Horizontal({button_login, button_exit}),
    });

    return ftxui::Renderer(container, [=]
                           { return ftxui::vbox({
                                        ftxui::text("") | ftxui::center,
                                        ftxui::text("🏸 HỆ THỐNG QUẢN LÝ SÂN CẦU LÔNG") | ftxui::color(ftxui::Color::Cyan) | ftxui::bold | ftxui::center,
                                        ftxui::text("cua Le Hoang Tin Nguyen Phu Thinh") | ftxui::color(ftxui::Color::Cyan) | ftxui::bold | ftxui::center,
                                        ftxui::text(""),
                                        ftxui::hbox({
                                            ftxui::text(" "),
                                            ftxui::vbox({
                                                ftxui::text("┌─────────────────────────────────────────┐") | ftxui::color(ftxui::Color::White),
                                                ftxui::hbox({ftxui::text("│ ") | ftxui::color(ftxui::Color::White), ftxui::text("👤 Username") | ftxui::bold | ftxui::color(ftxui::Color::Yellow), ftxui::text(" │") | ftxui::color(ftxui::Color::White)}),
                                                ftxui::hbox({ftxui::text("│ ") | ftxui::color(ftxui::Color::White), input_username->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 35), ftxui::text(" │") | ftxui::color(ftxui::Color::White)}),
                                                ftxui::text("├─────────────────────────────────────────┤") | ftxui::color(ftxui::Color::White),
                                                ftxui::hbox({ftxui::text("│ ") | ftxui::color(ftxui::Color::White), ftxui::text("🔒 Password") | ftxui::bold | ftxui::color(ftxui::Color::Yellow), ftxui::text(" │") | ftxui::color(ftxui::Color::White)}),
                                                ftxui::hbox({ftxui::text("│ ") | ftxui::color(ftxui::Color::White), input_password->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 35), ftxui::text(" │") | ftxui::color(ftxui::Color::White)}),
                                                ftxui::text("└─────────────────────────────────────────┘") | ftxui::color(ftxui::Color::White),
                                            }),
                                            ftxui::text(" "),
                                        }) | ftxui::center,
                                        ftxui::text(""),
                                        ftxui::hbox({button_login->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20), ftxui::text("  "), button_exit->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20)}) | ftxui::center,
                                        ftxui::text(""),
                                        ftxui::text(loginError) | ftxui::color(ftxui::Color::Red) | ftxui::bold | ftxui::center,
                                    }) |
                                    ftxui::border | ftxui::borderStyled(ftxui::ROUNDED) | ftxui::center; });
}

ftxui::Component UIManager::createMainMenu()
{
    auto adminDashboard = createAdminDashboard();
    auto nhanVienDashboard = createNhanVienDashboard();
    auto khachHangDashboard = createKhachHangDashboard();

    static int dashboard_selector = 0;
    auto dashboard_container = ftxui::Container::Tab(
        {adminDashboard, nhanVienDashboard, khachHangDashboard},
        &dashboard_selector);

    return ftxui::Renderer(dashboard_container, [=]() mutable
                           {
        if (!currentUser) return ftxui::text("Lỗi: User Null") | ftxui::center;
        if (currentUser->isAdmin()) dashboard_selector = 0;
        else if (currentUser->isNhanVien()) dashboard_selector = 1;
        else dashboard_selector = 2;
        return dashboard_container->Render(); });
}

ftxui::Component UIManager::createAdminDashboard()
{
    static std::vector<std::string> menu_entries = {
        "📊 Tổng quan",
        "👔 Nhân viên",
        "👤 Khách hàng",
        "🏟️  Sân",
        "🍔 Dịch vụ",
        "📅 Đặt sân",
        "💰 Hóa đơn",
        "📈 Thống kê",
        "🔐 Đổi MK",
        "💾 Lưu",
        "🚪 Đăng xuất",
    };
    auto menu = ftxui::Menu(&menu_entries, &adminMenuSelected);
    auto save_comp = ftxui::Renderer([=]
                                     { saveData(); statusMessage = "✅ Đã lưu dữ liệu!"; return ftxui::text(statusMessage) | ftxui::color(ftxui::Color::Green) | ftxui::center; });
    auto logout_button = ftxui::Button(" Bấm để xác nhận Đăng xuất ", [=]
                                       { dangXuat(); });
    auto logout_comp = ftxui::Renderer(logout_button, [=]
                                       { return ftxui::vbox({ftxui::text("Bạn có chắc chắn muốn đăng xuất?"), ftxui::text(""), logout_button->Render() | ftxui::center}) | ftxui::center | ftxui::flex; });

    auto content_container = ftxui::Container::Tab({createSimpleOverview(), createNhanVienManager(), createKhachHangManager(), createSanManager(),
                                                    createDichVuManager(), createDatSanManager(), createHoaDonManager(), createThongKe(),
                                                    createDoiMatKhau(), save_comp, logout_comp},
                                                   &adminMenuSelected);

    auto main_container = ftxui::Container::Horizontal({menu | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 25), content_container | ftxui::flex});
    return ftxui::Renderer(main_container, [=]
                           {
        auto sidebar = ftxui::vbox({ ftxui::text(" ADMIN ") | ftxui::bold | ftxui::center | ftxui::bgcolor(ftxui::Color::Red), ftxui::separator(), menu->Render() }) | ftxui::border;
        return ftxui::hbox({ sidebar, content_container->Render() | ftxui::flex | ftxui::border }); });
}

// NHÂN VIÊN DASHBOARD
ftxui::Component UIManager::createNhanVienDashboard()
{
    static std::vector<std::string> menu_entries = {
        "📅 Đặt sân",
        "💰 Hóa đơn",
        "👤 Khách hàng",
        "🏟️  Sân",
        "🍔 Dịch vụ",
        "🔐 Đổi MK",
        "💾 Lưu",
        "🚪 Đăng xuất",
    };
    auto menu = ftxui::Menu(&menu_entries, &staffMenuSelected);
    auto save_comp = ftxui::Renderer([=]
                                     { saveData(); return ftxui::text("✅ Đã lưu dữ liệu!") | ftxui::color(ftxui::Color::Green) | ftxui::center; });
    auto logout_button = ftxui::Button(" Bấm để xác nhận Đăng xuất ", [=]
                                       { dangXuat(); });
    auto logout_comp = ftxui::Renderer(logout_button, [=]
                                       { return ftxui::vbox({ftxui::text("Bạn có chắc chắn muốn đăng xuất?"), ftxui::text(""), logout_button->Render() | ftxui::center}) | ftxui::center | ftxui::flex; });

    auto content_container = ftxui::Container::Tab({createDatSanManager(), createHoaDonManager(), createKhachHangManager(), createSanManager(),
                                                    createDichVuManager(), createDoiMatKhau(), save_comp, logout_comp},
                                                   &staffMenuSelected);

    auto main_container = ftxui::Container::Horizontal({menu | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 25), content_container | ftxui::flex});
    return ftxui::Renderer(main_container, [=]
                           {
        auto sidebar = ftxui::vbox({ ftxui::text(" NHÂN VIÊN ") | ftxui::bold | ftxui::center | ftxui::bgcolor(ftxui::Color::Blue), ftxui::text(" " + currentUser->getHoTen()) | ftxui::center, ftxui::separator(), menu->Render() }) | ftxui::border;
        return ftxui::hbox({ sidebar, content_container->Render() | ftxui::flex | ftxui::border }); });
}

// KHÁCH HÀNG DASHBOARD
ftxui::Component UIManager::createKhachHangDashboard()
{
    static std::vector<std::string> menu_entries = {
        "🏸 Đặt sân mới",
        "📜 Lịch sử",
        "🧾 Hóa đơn",
        "🏟️ DS Sân",
        "🍔 Menu Dịch vụ",
        "👤 Hồ sơ",
        "🔐 Đổi MK",
        "🚪 Đăng xuất",
    };
    auto menu = ftxui::Menu(&menu_entries, &customerMenuSelected);

    auto get_real_id = [this]() -> std::string
    {
        if (!currentUser)
            return "";
        if (kiemTraDinhDangID(currentUser->getUsername(), "KH"))
            return currentUser->getUsername();
        for (size_t i = 0; i < danhSachKhachHang.get_size(); i++)
            if (danhSachKhachHang[i].getHoTen() == currentUser->getHoTen())
                return danhSachKhachHang[i].getId();
        return "";
    };
    auto auto_gen_id = [this]()
    {
        int max_id = 0;
        for (size_t i = 0; i < danhSachDatSan.get_size(); i++)
        {
            std::string s = danhSachDatSan[i].getIdDatSan();
            if (s.length() > 2 && s.substr(0, 2) == "DS")
            {
                try
                {
                    int num = std::stoi(s.substr(2));
                    if (num > max_id)
                        max_id = num;
                }
                catch (...)
                {
                }
            }
        }
        std::stringstream ss;
        ss << "DS" << std::setfill('0') << std::setw(3) << (max_id + 1);
        ds_id = ss.str();
        statusMessage = "✅ Đã tạo mã mới: " + ds_id;
    };
    if (ds_id.empty())
        auto_gen_id();

    auto style = StyleInputDep();
    auto in_id = ftxui::Input(&ds_id, "DSxxx", style);
    auto in_san = ftxui::Input(&ds_san_id, "Sxxx", style);

    auto in_ngay = ftxui::Input(&ds_ngay, "dd/mm/yyyy", style);
    auto in_bd = ftxui::Input(&ds_gio_bd, "HH:MM", style);
    auto in_kt = ftxui::Input(&ds_gio_kt, "HH:MM", style);
    auto in_del = ftxui::Input(&delete_id, "ID Hủy", style);

    auto btn_gen_id = ftxui::Button("🔄 Lấy Mã", [=]
                                    { auto_gen_id(); });

    auto btn_book = ftxui::Button("✅ Đặt Sân", [=]
                                  {
        std::string kh_id_book = get_real_id();
        std::string nv_real = "SYSTEM";
        
        if(kh_id_book == "Chưa có HS" || kh_id_book.empty()) { statusMessage = "❌ Lỗi: Tài khoản chưa liên kết hồ sơ!"; return; }
        if(ds_id.empty() || ds_san_id.empty() || ds_ngay.empty() || ds_gio_bd.empty() || ds_gio_kt.empty()) {
            statusMessage = "❌ Nhập đầy đủ thông tin!"; return;
        }
        
        auto sanCheck = sanService->timKiemSan(ds_san_id);
        if (!sanCheck) { statusMessage = "❌ Mã Sân không tồn tại!"; return; }
        if (sanCheck->getTrangThai() == "Bao tri") { 
            statusMessage = "❌ Sân đang bảo trì!"; return; 
        }

        if(datSanService->datSanMoi(ds_id, ds_san_id, kh_id_book, nv_real, ds_ngay, ds_gio_bd, ds_gio_kt)) {
        std::string successMsg = "✅ Đặt thành công đơn " + ds_id + "! Tổng: " + formatMoney(danhSachDatSan[danhSachDatSan.get_size()-1].getTongTien());
        saveData();
        ds_san_id = ""; ds_ngay = ""; ds_gio_bd = ""; ds_gio_kt = ""; 
        auto_gen_id(); 
        statusMessage = successMsg + " -> Đã chuyển sang mã mới: " + ds_id; 

    } else {
        statusMessage = "❌ Lỗi: Trùng giờ hoặc Mã DS (" + ds_id + ") đã tồn tại!";
    } });

    auto btn_cancel = ftxui::Button("❌ Hủy Đặt", [=]
                                    { 
        bool found = false;
        for(size_t i=0; i<danhSachDatSan.get_size(); i++) {
            if(danhSachDatSan[i].getIdDatSan() == delete_id && danhSachDatSan[i].getIdKhachHang() == get_real_id()) {
                found = true; break;
            }
        }
        if (!found) { statusMessage = "❌ Không tìm thấy hoặc không phải đơn của bạn!"; return; }

        if(datSanService->huyDatSan(delete_id)) { statusMessage = "✅ Đã hủy: " + delete_id; saveData(); delete_id = ""; } 
        else statusMessage = "❌ Lỗi hệ thống!"; });

    // Container cho Tab Đặt Sân
    auto container_dat = ftxui::Container::Vertical({in_id, btn_gen_id, in_san, in_ngay, in_bd, in_kt, btn_book, in_del, btn_cancel});

    auto dat_san_comp = ftxui::Renderer(container_dat, [=]
                                        {
        auto input_w = ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15);
        std::string real_id = get_real_id();

        auto form = ftxui::vbox({
            ftxui::text("--- Đặt Sân Mới ---") | ftxui::bold,
            // Dòng ID: Có thêm nút lấy mã
            ftxui::hbox({ input_label("Mã DS:", 10), in_id->Render() | input_w | ftxui::border, btn_gen_id->Render() }),
            ftxui::hbox({ input_label("Mã Sân:", 10), in_san->Render() | input_w | ftxui::border, ftxui::text(" (Ví dụ: S001)") | ftxui::color(ftxui::Color::GrayDark) }),
            ftxui::hbox({ input_label("Của KH:", 10), ftxui::text(real_id) | ftxui::bold | ftxui::color(ftxui::Color::Green) | ftxui::center }),
            ftxui::hbox({ input_label("Ngày:", 10), in_ngay->Render() | input_w | ftxui::border, ftxui::text(" (dd/mm/yyyy)") | ftxui::color(ftxui::Color::GrayDark) }),
            ftxui::hbox({ input_label("Từ giờ:", 10), in_bd->Render() | input_w | ftxui::border, ftxui::text(" Đến: "), in_kt->Render() | input_w | ftxui::border }),
            ftxui::text(""),
            btn_book->Render() | ftxui::center
        }) | ftxui::border;

        auto huy_form = ftxui::vbox({
            ftxui::text("Hủy Đặt Sân") | ftxui::bold,
            ftxui::hbox({ ftxui::text("Nhập Mã DS cần hủy: "), in_del->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 10) | ftxui::border, btn_cancel->Render() })
        }) | ftxui::border;

        return ftxui::vbox({ form, huy_form }); });
    auto history_comp = ftxui::Renderer([=]
                                        {
        std::vector<std::vector<std::string>> data;
        data.push_back({"Mã DS", "Sân", "Ngày", "Giờ", "Giá", "Trạng Thái"});
        std::string my_id = get_real_id();
        if (my_id.empty()) return ftxui::vbox({ createHeader("LỊCH SỬ ĐẶT SÂN"), ftxui::text("❌ Lỗi hồ sơ!") | ftxui::color(ftxui::Color::Red) | ftxui::center });

        for(size_t i=0; i<danhSachDatSan.get_size(); i++) {
            const DatSan& ds = danhSachDatSan[i];
            if (ds.getIdKhachHang() == my_id) { 
                data.push_back({ ds.getIdDatSan(), ds.getIdSan(), ds.getNgayDat(), ds.getGioBatDau() + "-" + ds.getGioKetThuc(), formatMoney(ds.getTongTien()), "Đã đặt" });
            }
        }
        return ftxui::vbox({ createHeader("LỊCH SỬ ĐẶT SÂN (" + my_id + ")"), createTable(data) | ftxui::vscroll_indicator | ftxui::frame | ftxui::flex }); });

    auto my_invoice_comp = ftxui::Renderer([=]
                                           {
        std::vector<std::vector<std::string>> data;
        data.push_back({"Mã HĐ", "Mã Đặt Sân", "Ngày Lập", "Trạng Thái", "Tổng Tiền"});
        std::string my_id = get_real_id();
        double tongDaChi = 0;

        for(size_t i=0; i<danhSachHoaDon.get_size(); i++) {
            const HoaDon& hd = danhSachHoaDon[i];
            if (hd.getIdKhachHang() == my_id) {
                data.push_back({ hd.getIdHoaDon(), hd.getIdDatSan(), hd.getNgayLap(), hd.getTrangThai(), formatMoney(hd.getTongTien()) });
                if(hd.getTrangThai() == "Da thanh toan") tongDaChi += hd.getTongTien();
            }
        }
        return ftxui::vbox({ 
            createHeader("HÓA ĐƠN CỦA TÔI (" + my_id + ")"), 
            ftxui::text("Tổng tiền đã chi tiêu: " + formatMoney(tongDaChi)) | ftxui::center | ftxui::color(ftxui::Color::Green),
            ftxui::separator(),
            createTable(data) | ftxui::vscroll_indicator | ftxui::frame | ftxui::flex 
        }); });

    auto view_san_comp = ftxui::Renderer([=]
                                         {
        std::vector<std::vector<std::string>> data;
        data.push_back({"Mã", "Loại", "Tình trạng", "Chi tiết", "Giá/h"});
        for(size_t i=0; i<danhSachSan.get_size(); i++) {
            const auto& s = danhSachSan[i];
            std::string info = "";
            if (s->getLoaiSan() == "NgoaiTroi") info = dynamic_cast<SanNgoaiTroi*>(s.get())->getViTri();
            else if (s->getLoaiSan() == "TrongNha") info = dynamic_cast<SanTrongNha*>(s.get())->getHeThongLamMat();
            else info = dynamic_cast<SanVIP*>(s.get())->getDichVuKemTheo();
            std::string tt = s->getTrangThai(); if(tt == "Trong") tt = "Hoat dong";
            data.push_back({ s->getIdSan(), s->getLoaiSan(), tt, info, formatMoney(s->tinhGiaSan(1)) });
        }
        return ftxui::vbox({ createHeader("DANH SÁCH SÂN CẦU LÔNG"), createTable(data) | ftxui::vscroll_indicator | ftxui::frame | ftxui::flex }); });

    auto view_dv_comp = ftxui::Renderer([=]
                                        {
        std::vector<std::vector<std::string>> data;
        data.push_back({"Mã", "Tên Dịch Vụ", "Loại", "ĐVT", "Giá"});
        for(size_t i=0; i<danhSachDichVu.get_size(); i++) {
            const auto& dv = danhSachDichVu[i];
            data.push_back({ dv->getId(), dv->getTenDV(), dv->getLoaiDV(), dv->getDonViTinh(), formatMoney(dv->getGia()) });
        }
        return ftxui::vbox({ createHeader("MENU DỊCH VỤ & ĐỒ ĂN"), createTable(data) | ftxui::vscroll_indicator | ftxui::frame | ftxui::flex }); });

    auto profile_comp = ftxui::Renderer([=]
                                        { 
        std::string my_id = get_real_id();
        std::string diem = "0";
        std::string hang = "Thường";
        if (!my_id.empty()) {
            KhachHang* kh = khachHangService->timKiemKhachHang(my_id);
            if (kh) { diem = std::to_string(kh->getDiem()); hang = kh->kiemtraVIP() ? "VIP 🌟" : "Thành viên"; }
        }
        return ftxui::vbox({ 
            createHeader("THÔNG TIN CÁ NHÂN"),
            ftxui::window(ftxui::text(" HỒ SƠ ") | ftxui::center | ftxui::bold,
                ftxui::vbox({
                    ftxui::hbox({ ftxui::text("Họ tên:   "), ftxui::text(currentUser->getHoTen()) | ftxui::bold }),
                    ftxui::hbox({ ftxui::text("Username: "), ftxui::text(currentUser->getUsername()) }),
                    ftxui::hbox({ ftxui::text("Mã KH:    "), ftxui::text(my_id) | ftxui::color(ftxui::Color::Green) }),
                    ftxui::separator(),
                    ftxui::hbox({ ftxui::text("Hạng:     "), ftxui::text(hang) | ftxui::color(ftxui::Color::Yellow) }),
                    ftxui::hbox({ ftxui::text("Điểm:     "), ftxui::text(diem) })
                })
            ) | ftxui::center 
        }) | ftxui::center; });

    auto logout_button = ftxui::Button(" Bấm để xác nhận Đăng xuất ", [=]
                                       { dangXuat(); });
    auto logout_comp = ftxui::Renderer(logout_button, [=]
                                       { return ftxui::vbox({ftxui::text("Bạn có chắc chắn muốn đăng xuất?"), ftxui::text(""), logout_button->Render() | ftxui::center}) | ftxui::center | ftxui::flex; });

    auto content_container = ftxui::Container::Tab({createDatSanManager(), history_comp, my_invoice_comp, view_san_comp, view_dv_comp, profile_comp, createDoiMatKhau(), logout_comp}, &customerMenuSelected);
    auto main_container = ftxui::Container::Horizontal({menu | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 25), content_container | ftxui::flex});

    return ftxui::Renderer(main_container, [=]
                           {
        auto sidebar = ftxui::vbox({
            ftxui::text(" KHÁCH HÀNG ") | ftxui::bold | ftxui::center | ftxui::bgcolor(ftxui::Color::Green),
            ftxui::text(" " + currentUser->getHoTen() + " ") | ftxui::center,
            ftxui::separator(),
            menu->Render(),
        }) | ftxui::border;
        return ftxui::hbox({ sidebar, content_container->Render() | ftxui::flex | ftxui::border }); });
}

// tổng quan
ftxui::Component UIManager::createSimpleOverview()
{
    return ftxui::Renderer([=]
                           {
        double tongThu = hoaDonService->tinhTongDoanhThu();
        int khVip = khachHangService->demSoKhachHangVIP();
        int tongNV = danhSachNhanVien.get_size();
        int tongKH = danhSachKhachHang.get_size();

        auto card_doanh_thu = ftxui::window(
            ftxui::text(" 💰 DOANH THU TỔNG ") | ftxui::center | ftxui::bold,
            ftxui::text(formatMoney(tongThu)) | ftxui::center | ftxui::bold | ftxui::color(ftxui::Color::Green)
        );

        auto card_nhan_su = ftxui::window(
            ftxui::text(" 👥 QUẢN TRỊ VIÊN ") | ftxui::center | ftxui::bold,
            ftxui::vbox({
                ftxui::hbox({ ftxui::text("Nhân viên: "), ftxui::text(std::to_string(tongNV)) | ftxui::bold }),
                ftxui::hbox({ ftxui::text("Khách hàng: "), ftxui::text(std::to_string(tongKH)) | ftxui::bold })
            }) | ftxui::center
        );

        auto card_vip = ftxui::window(
            ftxui::text(" 🌟 KHÁCH HÀNG VIP ") | ftxui::center | ftxui::bold,
             ftxui::text(std::to_string(khVip)) | ftxui::center | ftxui::bold | ftxui::color(ftxui::Color::Yellow)
        );

        return ftxui::vbox({
            ftxui::text(""), createHeader("DASHBOARD QUẢN TRỊ"), ftxui::text(""),
            ftxui::text("Xin chào, " + currentUser->getHoTen() + "!") | ftxui::center,
            ftxui::text("Hệ thống quản lý sân cầu lông Le Hoang Tin Nguyen Phu Thinh") | ftxui::center | ftxui::color(ftxui::Color::GrayDark),
            ftxui::text(""), ftxui::separator(), ftxui::text(""),
            ftxui::hbox({ card_doanh_thu | ftxui::flex, card_nhan_su | ftxui::flex, card_vip | ftxui::flex }),
            ftxui::text(""), ftxui::separator(),
        }) | ftxui::flex; });
}

// 1. nhân viên
ftxui::Component UIManager::createNhanVienManager()
{
    auto style = StyleInputDep();

    // Input
    auto input_id = ftxui::Input(&nv_id, "NVxxx", style);
    auto input_ten = ftxui::Input(&nv_ten, "Họ tên", style);
    auto input_sdt = ftxui::Input(&nv_sdt, "SĐT", style);
    auto input_email = ftxui::Input(&nv_email, "Email", style);
    auto input_luong = ftxui::Input(&nv_luong, "Lương (số)", style);
    auto input_chucvu = ftxui::Input(&nv_chucvu, "Chức vụ", style);
    auto input_ca = ftxui::Input(&nv_ca, "Ca làm việc", style);

    auto input_del_id = ftxui::Input(&delete_id, "ID xử lý", style);
    auto input_tim_id = ftxui::Input(&nv_tim_id, "ID tìm kiếm", style);

    // --- BUTTONS ---

    auto btn_load = ftxui::Button("⬆️ Tải", [=]
                                  {
        if(nv_id.empty()) { statusMessage = "❌ Nhập ID để tải!"; return; }
        NhanVien* nv = nhanVienService->timKiemNhanVien(nv_id);
        if(nv) {
            nv_ten = nv->getHoTen();
            nv_sdt = nv->getSoDT();
            nv_email = nv->getEmail();
            nv_luong = std::to_string((long long)nv->getLuong());
            nv_chucvu = nv->getChucVu();
            nv_ca = nv->getCaLamViec();
            statusMessage = "✅ Đã tải thông tin " + nv_id;
            show_nv_input = true; 
        } else statusMessage = "❌ Không tìm thấy ID!"; });

    auto btn_edit = ftxui::Button("✏️ Sửa", [=]
                                  {
        if(nv_id.empty()) { statusMessage = "❌ Cần ID để sửa!"; return; }
        NhanVien* nv = nhanVienService->timKiemNhanVien(nv_id);
        if(nv) {
            try {
                nv->setHoTen(nv_ten);
                nv->setSoDT(nv_sdt);
                nv->setEmail(nv_email);
                nv->setChucVu(nv_chucvu);
                nv->setCaLamViec(nv_ca);
                if(!nv_luong.empty()) nv->setLuong(std::stod(nv_luong));
                
                saveData();
                statusMessage = "✅ Đã cập nhật NV " + nv_id;
            } catch(...) { statusMessage = "❌ Lỗi số liệu lương!"; }
        } else statusMessage = "❌ Không tìm thấy ID để sửa!"; });

    auto btn_add = ftxui::Button("💾 Lưu Mới", [=]
                                 {
        if(nv_id.empty()) { statusMessage = "❌ Thiếu ID!"; return; }
        try {
            double luong = std::stod(nv_luong.empty() ? "0" : nv_luong);
            NhanVien nv(nv_id, nv_ten, nv_sdt, nv_email, nv_chucvu, luong, nv_ca);
            if(nhanVienService->themNhanVien(nv)) {
                authService.themUser(nv_id, "123", VaiTro::NHAN_VIEN, nv_ten); authService.ghiUserVaoFile("user.txt");
                statusMessage = "✅ Thêm mới thành công!"; saveData();
                nv_id=""; nv_ten=""; nv_sdt=""; nv_email=""; nv_luong=""; nv_chucvu=""; nv_ca="";
            } else statusMessage = "❌ Trùng ID!";
        } catch(...) { statusMessage = "❌ Lỗi số liệu!"; } });

    auto btn_del = ftxui::Button("❌ Xóa", [=]
                                 {
        if(nhanVienService->xoaNhanVien(delete_id)) { statusMessage = "✅ Đã xóa " + delete_id; saveData(); delete_id = ""; } 
        else statusMessage = "❌ Không tìm thấy!"; });

    auto btn_tim = ftxui::Button("🔍 Tìm", [=]
                                 {
        if(nhanVienService->timKiemNhanVien(nv_tim_id)) statusMessage="✅ Có trong danh sách!"; else statusMessage="❌ Không thấy!"; });

    auto btn_toggle = ftxui::Button("➕ Form", [=]
                                    { show_nv_input = !show_nv_input; });

    // LAYOUT
    auto container = ftxui::Container::Vertical({input_id, input_ten, input_sdt, input_email, input_luong, input_chucvu, input_ca, input_del_id, input_tim_id, btn_add, btn_edit, btn_load, btn_del, btn_tim, btn_toggle});

    return ftxui::Renderer(container, [=]
                           {
        std::vector<std::vector<std::string>> data = {{"ID", "Tên", "SĐT", "Email", "CV", "Lương", "Ca"}};
        
        if(nv_tim_id.empty()) { 
            for(size_t i=0; i<danhSachNhanVien.get_size(); i++) 
                data.push_back({
                    danhSachNhanVien[i].getId(), 
                    danhSachNhanVien[i].getHoTen(), 
                    danhSachNhanVien[i].getSoDT(), 
                    danhSachNhanVien[i].getEmail(), 
                    danhSachNhanVien[i].getChucVu(), 
                    formatMoney(danhSachNhanVien[i].getLuong()),
                    danhSachNhanVien[i].getCaLamViec() 
                }); 
        }
        else { 
            auto nv = nhanVienService->timKiemNhanVien(nv_tim_id); 
            if(nv) data.push_back({
                nv->getId(), 
                nv->getHoTen(), 
                nv->getSoDT(), 
                nv->getEmail(), 
                nv->getChucVu(), 
                formatMoney(nv->getLuong()),
                nv->getCaLamViec() 
            }); 
        }

        auto input_w = ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15);
        
        // Phần Form Nhập Liệu
        auto form = show_nv_input ? ftxui::vbox({
            ftxui::text("Thông Tin Nhân Viên") | ftxui::bold,
            ftxui::hbox({ input_label("ID:", 5), input_id->Render() | input_w | ftxui::border, btn_load->Render(), ftxui::text(" "), input_label("Tên:", 5), input_ten->Render() | input_w | ftxui::border }),
            ftxui::hbox({ input_label("SĐT:", 5), input_sdt->Render() | input_w | ftxui::border, ftxui::text(" "), input_label("Email:", 5), input_email->Render() | input_w | ftxui::border }), 
            ftxui::hbox({ input_label("Lương:", 6), input_luong->Render() | input_w | ftxui::border, input_label("CV:", 3), input_chucvu->Render() | input_w | ftxui::border, input_label("Ca:", 3), input_ca->Render() | input_w | ftxui::border }),
            ftxui::hbox({ btn_add->Render(), ftxui::text("  "), btn_edit->Render() }) | ftxui::center
        }) | ftxui::border : ftxui::text("");

        // Phần Công cụ Admin (Xóa + Form Toggle)
        ftxui::Element admin_tools = ftxui::text("");
        if (currentUser->isAdmin()) {
            admin_tools = ftxui::vbox({
                // Dòng 1: Nút Form bên trái, Xóa bên phải
                ftxui::hbox({ 
                    btn_toggle->Render(), 
                    ftxui::filler(), 
                    ftxui::text("ID Xóa: "), 
                    input_del_id->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 10) | ftxui::border, 
                    btn_del->Render() 
                }) | ftxui::border,
                // Dòng 2: Form nhập liệu (nếu mở)
                form
            });
        }
        
        return ftxui::vbox({
            createHeader("QUẢN LÝ NHÂN VIÊN"),
            ftxui::text(statusMessage) | ftxui::color(ftxui::Color::Yellow) | ftxui::center, 
            ftxui::separator(),
            // Khung Tìm kiếm
            ftxui::hbox({ 
                ftxui::text("🔍 Tìm ID: "), 
                input_tim_id->Render() | input_w | ftxui::border, 
                btn_tim->Render(), 
                ftxui::filler() 
            }) | ftxui::border,
            
            admin_tools, // Chỉ còn khung công cụ + form, ĐÃ BỎ THỐNG KÊ
            
            createTable(data) | ftxui::vscroll_indicator | ftxui::frame | ftxui::flex
        }); });
}
// 2.  khách hàng
ftxui::Component UIManager::createKhachHangManager()
{
    auto style = StyleInputDep();
    auto input_id = ftxui::Input(&kh_id, "KHxxx", style);
    auto input_ten = ftxui::Input(&kh_ten, "Họ tên", style);
    auto input_sdt = ftxui::Input(&kh_sdt, "SĐT", style);
    auto input_email = ftxui::Input(&kh_email, "Email", style);
    auto input_diem = ftxui::Input(&kh_diem, "Điểm", style);
    auto input_ngay = ftxui::Input(&kh_ngaydk, "dd/mm/yyyy", style);

    auto input_del_id = ftxui::Input(&delete_id, "ID xử lý", style);
    auto input_tang_id = ftxui::Input(&kh_tang_id, "ID KH", style);
    auto input_tang_diem = ftxui::Input(&kh_tang_diem, "Điểm +", style);
    auto input_tim_id = ftxui::Input(&kh_tim_id, "ID tìm", style);

    auto btn_load = ftxui::Button("⬆️ Tải", [=]
                                  {
        KhachHang* kh = khachHangService->timKiemKhachHang(kh_id);
        if(kh) {
            kh_ten = kh->getHoTen(); kh_sdt = kh->getSoDT(); kh_email = kh->getEmail();
            kh_diem = std::to_string(kh->getDiem()); kh_ngaydk = kh->getNgayDangKi();
            statusMessage = "✅ Đã tải KH " + kh_id; show_kh_input = true;
        } else statusMessage = "❌ Không tìm thấy!"; });

    auto btn_edit = ftxui::Button("✏️ Sửa", [=]
                                  {
        KhachHang* kh = khachHangService->timKiemKhachHang(kh_id);
        if(kh) {
            try {
                kh->setHoTen(kh_ten); kh->setSoDT(kh_sdt); kh->setEmail(kh_email);
                kh->setNgayDangKi(kh_ngaydk);
                if(!kh_diem.empty()) kh->setDiem(std::stoi(kh_diem));
                saveData(); statusMessage = "✅ Đã cập nhật KH " + kh_id;
            } catch(...) { statusMessage = "❌ Lỗi dữ liệu!"; }
        } else statusMessage = "❌ Cần ID để sửa!"; });

    auto btn_add = ftxui::Button("💾 Lưu Mới", [=]
                                 {
        if(kh_id.empty() || kh_sdt.empty()) { statusMessage = "❌ Thiếu thông tin!"; return; }
        try {
            int diem = std::stoi(kh_diem.empty() ? "0" : kh_diem);
            KhachHang kh(kh_id, kh_ten, kh_sdt, kh_email, diem, kh_ngaydk);
            if(khachHangService->themKhachHang(kh)) {
                authService.themUser(kh_id, "123", VaiTro::KHACH_HANG, kh_ten); authService.ghiUserVaoFile("user.txt");
                statusMessage = "✅ Thêm thành công!"; saveData();
                kh_id=""; kh_ten=""; kh_sdt=""; kh_email=""; kh_diem="0";
            } else statusMessage = "❌ Trùng ID/SĐT!";
        } catch(...) { statusMessage = "❌ Lỗi điểm!"; } });

    auto btn_del = ftxui::Button("❌ Xóa", [=]
                                 {
        if(khachHangService->xoaKhachHang(delete_id)) { statusMessage = "✅ Đã xóa " + delete_id; saveData(); delete_id=""; } 
        else statusMessage = "❌ Không tìm thấy!"; });

    auto btn_tim = ftxui::Button("🔍 Tìm", [=]
                                 { if(khachHangService->timKiemKhachHang(kh_tim_id)) statusMessage="✅ Tìm thấy!"; else statusMessage="❌ Không thấy!"; });
    auto btn_toggle = ftxui::Button("➕ Form", [=]
                                    { show_kh_input = !show_kh_input; });
    auto btn_tang = ftxui::Button("⬆️ Tăng", [=]
                                  {
         if(khachHangService->tangDiemKhachHang(kh_tang_id, std::stoi(kh_tang_diem.empty()?"0":kh_tang_diem))) { statusMessage="✅ Đã cộng điểm!"; saveData(); } else statusMessage="❌ Lỗi!"; });

    auto container = ftxui::Container::Vertical({input_id, input_ten, input_sdt, input_email, input_diem, input_ngay, input_del_id, input_tim_id, input_tang_id, input_tang_diem, btn_add, btn_edit, btn_load, btn_del, btn_tim, btn_tang, btn_toggle});

    return ftxui::Renderer(container, [=]
                           {
        std::vector<std::vector<std::string>> data = {{"ID", "Tên", "SĐT", "Điểm", "VIP", "Ngày ĐK"}};
        
        if(kh_tim_id.empty()) 
            for(size_t i=0; i<danhSachKhachHang.get_size(); i++) 
                data.push_back({danhSachKhachHang[i].getId(), danhSachKhachHang[i].getHoTen(), danhSachKhachHang[i].getSoDT(), std::to_string(danhSachKhachHang[i].getDiem()), danhSachKhachHang[i].kiemtraVIP()?"Yes":"No", danhSachKhachHang[i].getNgayDangKi()});
        else { 
            auto kh = khachHangService->timKiemKhachHang(kh_tim_id); 
            if(kh) data.push_back({kh->getId(), kh->getHoTen(), kh->getSoDT(), std::to_string(kh->getDiem()), kh->kiemtraVIP()?"Yes":"No", kh->getNgayDangKi()}); 
        }

        auto input_w = ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15);
        
        ftxui::Element tools = ftxui::text("");
        if (currentUser->isAdmin() || currentUser->isNhanVien()) {
            auto form = show_kh_input ? ftxui::vbox({
                ftxui::text("Thông Tin Khách Hàng") | ftxui::bold,
                ftxui::hbox({ input_label("ID:", 5), input_id->Render() | input_w | ftxui::border, btn_load->Render(), ftxui::text(" "), input_label("Tên:", 5), input_ten->Render() | input_w | ftxui::border }),
                ftxui::hbox({ input_label("SĐT:", 5), input_sdt->Render() | input_w | ftxui::border, ftxui::text(" "), input_label("Email:", 5), input_email->Render() | input_w | ftxui::border }),
                ftxui::hbox({ input_label("Điểm:", 6), input_diem->Render() | input_w | ftxui::border, input_label("Ngày:", 5), input_ngay->Render() | input_w | ftxui::border }),
                ftxui::hbox({ btn_add->Render(), ftxui::text("  "), btn_edit->Render() }) | ftxui::center
            }) | ftxui::border : ftxui::text("");

            tools = ftxui::vbox({
                ftxui::hbox({ btn_toggle->Render(), ftxui::filler(), ftxui::text("ID Xóa: "), input_del_id->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 10) | ftxui::border, btn_del->Render() }) | ftxui::border,
                form,
                ftxui::vbox({ ftxui::hbox({ input_label("ID KH:", 7), input_tang_id->Render() | input_w | ftxui::border, input_label(" Điểm:", 6), input_tang_diem->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 8) | ftxui::border, btn_tang->Render() }) }) | ftxui::border
            });
        }

        return ftxui::vbox({
            createHeader("QUẢN LÝ KHÁCH HÀNG"),
            ftxui::text(statusMessage) | ftxui::color(ftxui::Color::Yellow) | ftxui::center, ftxui::separator(),
            ftxui::hbox({ ftxui::text("🔍 Tìm ID: "), input_tim_id->Render() | input_w | ftxui::border, btn_tim->Render(), ftxui::filler() }) | ftxui::border,
            tools,
            createTable(data) | ftxui::vscroll_indicator | ftxui::frame | ftxui::flex
        }); });
}
// 3. sân
ftxui::Component UIManager::createSanManager()
{
    static std::vector<std::string> opts = {"Ngoài Trời", "Trong Nhà", "VIP"};
    auto radio = ftxui::Radiobox(&opts, &san_loai_idx);
    auto style = StyleInputDep();
    static bool isFiltering = false;

    auto in_id = ftxui::Input(&san_id, "Sxxx", style);
    auto in_inf1 = ftxui::Input(&san_info1, "", style);
    auto in_inf2 = ftxui::Input(&san_info2, "", style);
    auto in_inf3 = ftxui::Input(&san_info3, "", style);
    auto in_inf4 = ftxui::Input(&san_info4, "", style);
    auto in_del = ftxui::Input(&delete_id, "ID Sân", style);
    auto in_tim_id = ftxui::Input(&san_tim_id, "ID tìm", style);

    auto btn_load = ftxui::Button("⬆️ Tải", [this]
                                  {
        auto s = sanService->timKiemSan(san_id);
        if(s) {
            std::string loai = s->getLoaiSan();
            if(loai=="NgoaiTroi") { san_loai_idx=0; auto st=dynamic_cast<SanNgoaiTroi*>(s.get()); san_info1=st->getViTri(); san_info2=std::to_string((int)st->getDienTich()); }
            else if(loai=="TrongNha") { san_loai_idx=1; auto st=dynamic_cast<SanTrongNha*>(s.get()); san_info1=st->getHeThongLamMat(); san_info2=std::to_string((int)st->getDienTich()); san_info3=st->getHeThongDen(); }
            else { san_loai_idx=2; auto st=dynamic_cast<SanVIP*>(s.get()); san_info1=st->getDichVuKemTheo(); san_info2=st->getChatLieuSan(); san_info3=std::to_string((int)st->getDienTich()); san_info4=st->getHeThongAmThanh(); }
            statusMessage = "✅ Đã tải sân " + san_id; show_san_input = true;
        } else statusMessage = "❌ Không tìm thấy!"; });

    auto btn_edit = ftxui::Button("✏️ Sửa", [this]
                                  {
        auto s = sanService->timKiemSan(san_id);
        if(s) {
            try {
                if(s->getLoaiSan()=="NgoaiTroi") { auto st=dynamic_cast<SanNgoaiTroi*>(s.get()); st->setViTri(san_info1); st->setDienTich(std::stod(san_info2)); }
                else if(s->getLoaiSan()=="TrongNha") { auto st=dynamic_cast<SanTrongNha*>(s.get()); st->setHeThongLamMat(san_info1); st->setDienTich(std::stod(san_info2)); st->setHeThongDen(san_info3); }
                else { auto st=dynamic_cast<SanVIP*>(s.get()); st->setDichVuKemTheo(san_info1); st->setChatLieuSan(san_info2); st->setDienTich(std::stod(san_info3)); st->setHeThongAmThanh(san_info4); }
                saveData(); statusMessage = "✅ Đã cập nhật sân " + san_id;
            } catch(...) { statusMessage = "❌ Lỗi dữ liệu!"; }
        } else statusMessage = "❌ Cần ID đúng để sửa!"; });

    auto btn_add = ftxui::Button("💾 Lưu Mới", [this]
                                 {
        if(san_id.empty()) { statusMessage="❌ Thiếu ID!"; return; }
        try {
            shared_ptr<SanCauLong> s = nullptr;
            
            // FIX LỖI: Chuyển đổi số đúng chỗ
            if(san_loai_idx==0) { // Ngoài trời
                double dt = std::stod(san_info2); 
                s=make_shared<SanNgoaiTroi>(san_id, "Hoat dong", san_info1, dt);
            }
            else if(san_loai_idx==1) { // Trong nhà
                double dt = std::stod(san_info2);
                s=make_shared<SanTrongNha>(san_id, "Hoat dong", san_info1, dt, san_info3);
            }
            else { // VIP
                // Ở VIP: info2 là Chất liệu (Chữ), info3 là Diện tích (Số)
                double dt = std::stod(san_info3); 
                s=make_shared<SanVIP>(san_id, "Hoat dong", san_info1, san_info2, dt, san_info4);
            }

            if(sanService->themSan(s)) { 
                statusMessage="✅ Thêm xong!"; saveData(); 
                san_id=""; san_info1=""; san_info2=""; san_info3=""; san_info4="";
            } else statusMessage="❌ Trùng ID!";
        } catch(...) { statusMessage="❌ Lỗi: Diện tích phải là số!"; } });

    auto btn_baotri = ftxui::Button("🔧 Bảo trì/Mở", [this]
                                    {
        if(delete_id.empty()) return;
        auto s = sanService->timKiemSan(delete_id);
        if(s) { s->setTrangThai(s->getTrangThai()=="Bao tri" ? "Hoat dong" : "Bao tri"); saveData(); statusMessage="✅ Đã đổi trạng thái"; } });

    auto btn_del = ftxui::Button("❌ Xóa", [this]
                                 { if(sanService->xoaSan(delete_id)) { statusMessage="✅ Đã xóa!"; saveData(); delete_id=""; } else statusMessage="❌ Không thấy!"; });

    auto btn_tim = ftxui::Button("🔍 Tìm", [this]
                                 { 
        if (san_tim_id.empty()) { statusMessage = "❌ Nhập ID!"; return; } 
        isFiltering = false; 
        statusMessage = "✅ Kết quả tìm kiếm:"; });

    auto btn_toggle = ftxui::Button("➕ Form", [this]
                                    { show_san_input = !show_san_input; });

    auto btn_loc_tot = ftxui::Button("⚡ Lọc", [this]
                                     { 
    isFiltering = !isFiltering; 
    san_tim_id = ""; });

    auto container = ftxui::Container::Vertical({radio, in_id, in_inf1, in_inf2, in_inf3, in_inf4, in_del, in_tim_id, btn_add, btn_edit, btn_load, btn_baotri, btn_del, btn_tim, btn_toggle, btn_loc_tot});

    return ftxui::Renderer(container, [=]
                           {
        std::vector<std::vector<std::string>> data = {{"ID", "Loại", "Trạng Thái", "Chi Tiết Cụ Thể", "Giá/h"}};
        
        MyVector<shared_ptr<SanCauLong>> listHienThi;
        if(isFiltering) {
             for(size_t i=0; i<danhSachSan.get_size(); i++) 
                if(danhSachSan[i]->getTrangThai() == "Hoat dong") listHienThi.push_back(danhSachSan[i]);
        } else if (!san_tim_id.empty()) {
            auto s = sanService->timKiemSan(san_tim_id);
            if(s) listHienThi.push_back(s);
        } else {
            listHienThi = danhSachSan; 
        }

        for(size_t i=0; i<listHienThi.get_size(); i++) { 
            auto s = listHienThi[i]; 
            std::string detail = "";
            
            if (s->getLoaiSan() == "NgoaiTroi") {
                auto p = dynamic_pointer_cast<SanNgoaiTroi>(s);
                if(p) detail = "Vị trí: " + p->getViTri() + " | DT: " + std::to_string((int)p->getDienTich()) + "m2";
            } else if (s->getLoaiSan() == "TrongNha") {
                auto p = dynamic_pointer_cast<SanTrongNha>(s);
                if(p) detail = "Mát: " + p->getHeThongLamMat() + " | Đèn: " + p->getHeThongDen();
            } else if (s->getLoaiSan() == "VIP") {
                auto p = dynamic_pointer_cast<SanVIP>(s);
                if(p) detail = "DV: " + p->getDichVuKemTheo() + " | " + p->getHeThongAmThanh();
            }

            data.push_back({
                s->getIdSan(), 
                s->getLoaiSan(), 
                s->getTrangThai(), 
                detail, 
                formatMoney(s->tinhGiaSan(1))
            }); 
        }

        std::string l1="Vị trí", l2="Diện tích", l3="", l4=""; 
        if(san_loai_idx == 1) { l1="Làm mát"; l2="Diện tích"; l3="Đèn"; } 
        else if(san_loai_idx == 2) { l1="Dịch vụ"; l2="Chất liệu"; l3="Diện tích"; l4="Âm thanh"; } 

        auto input_w = ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15);
        ftxui::Element row_extra = ftxui::text("");
        if (san_loai_idx == 1) row_extra = ftxui::hbox({ input_label(l3+":", 10), in_inf3->Render() | input_w | ftxui::border });
        else if (san_loai_idx == 2) row_extra = ftxui::hbox({ input_label(l3+":", 10), in_inf3->Render() | input_w | ftxui::border, ftxui::text(" "), input_label(l4+":", 10), in_inf4->Render() | input_w | ftxui::border });

        auto form = show_san_input ? ftxui::vbox({
            ftxui::text("Thông Tin Sân") | ftxui::bold, radio->Render(),
            ftxui::hbox({ input_label("ID:", 5), in_id->Render() | input_w | ftxui::border, btn_load->Render() }),
            ftxui::hbox({ input_label(l1+":", 10), in_inf1->Render() | input_w | ftxui::border, ftxui::text(" "), input_label(l2+":", 10), in_inf2->Render() | input_w | ftxui::border }),
            row_extra,
            ftxui::hbox({ btn_add->Render(), ftxui::text("  "), btn_edit->Render() }) | ftxui::center
        }) | ftxui::border : ftxui::text("");

        ftxui::Element admin_tools = currentUser->isAdmin() ? 
            ftxui::vbox({
                ftxui::hbox({ btn_toggle->Render(), ftxui::filler(), ftxui::text("ID Sân: "), in_del->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 10) | ftxui::border, btn_baotri->Render(), ftxui::text(" "), btn_del->Render() }) | ftxui::border,
                form
            }) : ftxui::text("");
        
        return ftxui::vbox({ 
            createHeader("QUẢN LÝ SÂN"), 
            ftxui::text(statusMessage)|ftxui::center|ftxui::color(ftxui::Color::Yellow), ftxui::separator(), 
            ftxui::hbox({ btn_loc_tot->Render(), ftxui::text("   "), ftxui::text("🔍 Tìm ID: "), in_tim_id->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 10) | ftxui::border, btn_tim->Render(), ftxui::filler() }) | ftxui::border,
            admin_tools,
            createTable(data) | ftxui::vscroll_indicator | ftxui::frame | ftxui::flex 
        }); });
}
// 4. dịch vụ
ftxui::Component UIManager::createDichVuManager()
{
    static std::vector<std::string> opts = {"Ăn Uống", "Thiết Bị"};
    auto radio = ftxui::Radiobox(&opts, &dv_loai_idx);
    auto style = StyleInputDep();

    auto in_id = ftxui::Input(&dv_id, "DVxxx", style);
    auto in_ten = ftxui::Input(&dv_ten, "Tên dịch vụ", style);
    auto in_gia = ftxui::Input(&dv_gia, "Giá (số)", style);
    auto in_dvt = ftxui::Input(&dv_dvt, "ĐVT", style);
    auto in_ton = ftxui::Input(&dv_ton, "Tồn (số)", style);

    auto in_del = ftxui::Input(&delete_id, "ID Xóa", style);
    auto in_tim_id = ftxui::Input(&dv_tim_id, "ID tìm", style);

    auto btn_load = ftxui::Button("⬆️ Tải", [this]
                                  {
        auto dv = dichVuService->timKiemDichVu(dv_id);
        if(dv) {
            dv_ten = dv->getTenDV();
            dv_gia = std::to_string((int)dv->getGia());
            dv_dvt = dv->getDonViTinh();
            dv_ton = std::to_string(dv->getSoLuongTon());
            if(dv->getLoaiDV()=="AnUong") dv_loai_idx=0; else dv_loai_idx=1;
            statusMessage = "✅ Đã tải DV " + dv_id; show_dv_input = true;
        } else statusMessage = "❌ Không tìm thấy!"; });

    auto btn_edit = ftxui::Button("✏️ Sửa", [this]
                                  {
        auto dv = dichVuService->timKiemDichVu(dv_id);
        if(dv) {
            try {
                dv->setTenDV(dv_ten); dv->setGia(std::stod(dv_gia)); dv->setDonViTinh(dv_dvt); dv->setSoLuongTon(std::stoi(dv_ton));
                saveData(); statusMessage = "✅ Đã cập nhật DV " + dv_id;
            } catch(...) { statusMessage = "❌ Lỗi số liệu!"; }
        } else statusMessage = "❌ Cần ID để sửa!"; });

    auto btn_add = ftxui::Button("💾 Lưu Mới", [this]
                                 {
        if(dv_id.empty()) return;
        try {
            double gia = std::stod(dv_gia); int ton = std::stoi(dv_ton);
            shared_ptr<DichVu> dv;
            if(dv_loai_idx==0) dv=make_shared<DichVuAnUong>(dv_id, dv_ten, gia, dv_dvt, ton, "MacDinh", "ConHang");
            else dv=make_shared<DichVuThietBi>(dv_id, dv_ten, gia, dv_dvt, ton, "Tot", "TheoGio");
            
            if(dichVuService->themDichVu(dv)) { statusMessage="✅ Thêm xong!"; saveData(); dv_id=""; } else statusMessage="❌ Trùng ID!";
        } catch(...) { statusMessage="❌ Lỗi số liệu!"; } });

    auto btn_del = ftxui::Button("❌ Xóa", [this]
                                 { if(dichVuService->xoaDichVu(delete_id)) { statusMessage="✅ Đã xóa!"; saveData(); delete_id=""; } else statusMessage="❌ Không thấy!"; });

    auto btn_tim = ftxui::Button("🔍 Tìm", [this]
                                 { if (dv_tim_id.empty()) { statusMessage = "❌ Nhập ID!"; return; } shared_ptr<DichVu> dv = dichVuService->timKiemDichVu(dv_tim_id); if (dv) statusMessage = "✅ Tìm thấy: " + dv->getTenDV(); else statusMessage = "❌ Không tìm thấy!"; });

    auto btn_toggle = ftxui::Button("➕ Form", [this]
                                    { show_dv_input = !show_dv_input; });

    auto container = ftxui::Container::Vertical({radio, in_id, in_ten, in_gia, in_dvt, in_ton, in_del, in_tim_id, btn_add, btn_edit, btn_load, btn_del, btn_tim, btn_toggle});

    return ftxui::Renderer(container, [=]
                           {
        std::vector<std::vector<std::string>> data = {{"ID", "Tên", "Giá", "ĐVT", "Tình trạng kho"}};
        
        auto process_row = [this](shared_ptr<DichVu> dv) -> std::vector<std::string> {
            int ton = dv->getSoLuongTon();
            std::string trangThai = (ton > 0) ? std::to_string(ton) : "HẾT HÀNG";
            return {dv->getId(), dv->getTenDV(), formatMoney(dv->getGia()), dv->getDonViTinh(), trangThai};
        };

        if(dv_tim_id.empty()) { 
            for(size_t i=0; i<danhSachDichVu.get_size(); i++) data.push_back(process_row(danhSachDichVu[i])); 
        } else { 
            auto dv=dichVuService->timKiemDichVu(dv_tim_id); 
            if(dv) data.push_back(process_row(dv)); 
        }
        
        auto input_w = ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15);
        
        auto form = show_dv_input ? ftxui::vbox({
            ftxui::text("Thông Tin Dịch Vụ") | ftxui::bold, radio->Render() | ftxui::center,
            ftxui::hbox({ input_label("ID:", 5), in_id->Render() | input_w | ftxui::border, btn_load->Render(), ftxui::text(" "), input_label("Tên:", 5), in_ten->Render() | input_w | ftxui::border }),
            ftxui::hbox({ input_label("Giá:", 5), in_gia->Render() | input_w | ftxui::border, input_label("Tồn:", 5), in_ton->Render() | input_w | ftxui::border, input_label("ĐVT:", 5), in_dvt->Render() | input_w | ftxui::border }),
            ftxui::hbox({ btn_add->Render(), ftxui::text("  "), btn_edit->Render() }) | ftxui::center
        }) | ftxui::border : ftxui::text("");

        ftxui::Element admin_tools = currentUser->isAdmin() ? ftxui::vbox({ ftxui::hbox({ btn_toggle->Render(), ftxui::filler(), ftxui::text("ID Xóa: "), in_del->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 10) | ftxui::border, btn_del->Render() }) | ftxui::border, form }) : ftxui::text("");
        
        return ftxui::vbox({ createHeader("QUẢN LÝ DỊCH VỤ"), ftxui::text(statusMessage)|ftxui::center|ftxui::color(ftxui::Color::Yellow), ftxui::separator(), ftxui::hbox({ ftxui::text("🔍 Tìm ID: "), in_tim_id->Render() | input_w | ftxui::border, btn_tim->Render(), ftxui::filler() }) | ftxui::border, admin_tools, createTable(data) | ftxui::vscroll_indicator | ftxui::frame | ftxui::flex }); });
}
// 5. đặt sân
ftxui::Component UIManager::createDatSanManager()
{
    // --- 1. Thêm Logic Tự Động Sinh Mã ---
    auto auto_gen_id = [this]()
    {
        int max_id = 0;
        for (size_t i = 0; i < danhSachDatSan.get_size(); i++)
        {
            std::string s = danhSachDatSan[i].getIdDatSan();
            // Chỉ lấy số từ các mã bắt đầu bằng "DS"
            if (s.length() > 2 && s.substr(0, 2) == "DS")
            {
                try
                {
                    int num = std::stoi(s.substr(2));
                    if (num > max_id)
                        max_id = num;
                }
                catch (...)
                {
                }
            }
        }
        std::stringstream ss;
        ss << "DS" << std::setfill('0') << std::setw(3) << (max_id + 1);
        ds_id = ss.str();
    };

    if (ds_id.empty())
        auto_gen_id();
    auto in_id = ftxui::Input(&ds_id, "DSxxx", StyleInputDep());
    auto in_san = ftxui::Input(&ds_san_id, "Sxxx", StyleInputDep());
    auto in_kh = ftxui::Input(&ds_kh_id, "KHxxx", StyleInputDep());
    auto in_ngay = ftxui::Input(&ds_ngay, "dd/mm/yyyy", StyleInputDep());
    auto in_bd = ftxui::Input(&ds_gio_bd, "HH:MM", StyleInputDep());
    auto in_kt = ftxui::Input(&ds_gio_kt, "HH:MM", StyleInputDep());
    auto in_del = ftxui::Input(&delete_id, "ID Hủy", StyleInputDep());
    auto in_tim_id = ftxui::Input(&ds_tim_id, "ID tìm kiếm", StyleInputDep());
    auto btn_gen = ftxui::Button("🔄", [=]
                                 { auto_gen_id(); });
    auto btn_book = ftxui::Button("✅ Đặt Sân", [=]
                                  {
        std::string nv_id_book = currentUser->isNhanVien() ? currentUser->getUsername() : "NV001";
        std::string kh_id_book = ds_kh_id; 

        if(ds_id.empty() || ds_san_id.empty() || kh_id_book.empty() || ds_ngay.empty() || ds_gio_bd.empty() || ds_gio_kt.empty()) {
            statusMessage = "❌ Nhập đầy đủ thông tin!"; return;
        }
                if(!kiemTraDinhDangID(ds_id, "DS") || !kiemTraDinhDangID(ds_san_id, "S")) { statusMessage = "❌ Sai định dạng ID!"; return; }
        auto sanCheck = sanService->timKiemSan(ds_san_id);
        if (!sanCheck) { statusMessage = "❌ Mã Sân không tồn tại!"; return; }
        if (sanCheck->getTrangThai() == "Bao tri") { statusMessage = "❌ Sân đang bảo trì!"; return; }

        if(datSanService->datSanMoi(ds_id, ds_san_id, kh_id_book, nv_id_book, ds_ngay, ds_gio_bd, ds_gio_kt)) {
            std::string msg = "✅ Đặt xong đơn " + ds_id + "! Tổng: " + formatMoney(danhSachDatSan[danhSachDatSan.get_size()-1].getTongTien());
            saveData(); 
            ds_san_id = ""; ds_ngay = ""; ds_gio_bd = ""; ds_gio_kt = ""; 
            if(!currentUser->isKhachHang()) ds_kh_id = "";
            auto_gen_id(); 
            statusMessage = msg + " -> Tiếp theo: " + ds_id;
        } else {
            statusMessage = "❌ Lỗi: Trùng giờ hoặc Mã DS đã tồn tại!";
        } });

    auto btn_cancel = ftxui::Button("❌ Hủy Đặt", [=]
                                    { 
        if(datSanService->huyDatSan(delete_id)) { statusMessage = "✅ Đã hủy: " + delete_id; saveData(); delete_id = ""; } 
        else statusMessage = "❌ Không tìm thấy mã đặt sân!"; });

    auto btn_tim = ftxui::Button("🔍 Tìm", [=]
                                 { 
        if (ds_tim_id.empty()) { statusMessage = "❌ Nhập từ khóa!"; return; } 
        ds_xem_lich_mode = false; statusMessage = "✅ Đang lọc dữ liệu..."; });

    auto btn_xem_lich = ftxui::Button("📅 Xem Lịch Cụ Thể", [=]
                                      { 
        if (ds_san_id.empty() || ds_ngay.empty()) { statusMessage = "❌ Nhập Mã Sân & Ngày!"; return; }
        ds_xem_lich_mode = true; ds_tim_id = ""; statusMessage = "✅ Lịch sân " + ds_san_id + " ngày " + ds_ngay; });
    auto btn_xem_all = ftxui::Button("🔄 Xem Tất Cả", [=]
                                     { ds_xem_lich_mode = false; ds_tim_id = ""; });

    auto input_option = ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15);
    auto container = ftxui::Container::Vertical({in_id, in_san, in_kh, in_ngay, in_bd, in_kt, in_del, in_tim_id, btn_book, btn_cancel, btn_tim, btn_xem_lich, btn_xem_all, btn_gen});

    return ftxui::Renderer(container, [=]
                           {
        std::vector<std::vector<std::string>> data;
        if (ds_xem_lich_mode) {
             MyVector<DatSan> lichSan = datSanService->layDanhSachDatSanTheoSanVaNgay(ds_san_id, ds_ngay);
             data.push_back({"Mã DS", "Sân", "Ngày", "Giờ BĐ", "Giờ KT", "Trạng thái"});
             if (lichSan.get_size() > 0) {
                 for (size_t i = 0; i < lichSan.get_size(); i++) 
                     data.push_back({lichSan[i].getIdDatSan(), lichSan[i].getIdSan(), lichSan[i].getNgayDat(), lichSan[i].getGioBatDau(), lichSan[i].getGioKetThuc(), "Đã đặt"});
             } else data.push_back({"-", ds_san_id, ds_ngay, "-", "-", "Trống"});
        } else {
             data.push_back({"Mã DS", "Sân", "Khách", "Ngày", "Giờ", "Tổng tiền"});
             for(size_t i=0; i<danhSachDatSan.get_size(); i++) {
                const DatSan& ds = danhSachDatSan[i];
                if (!ds_tim_id.empty() && ds.getIdDatSan().find(ds_tim_id) == std::string::npos) continue;
                data.push_back({ds.getIdDatSan(), ds.getIdSan(), ds.getIdKhachHang(), ds.getNgayDat(), ds.getGioBatDau() + "-" + ds.getGioKetThuc(), formatMoney(ds.getTongTien())});
            }
        }

        auto form_dat_san = ftxui::vbox({
            ftxui::text("--- Form Đặt Sân ---") | ftxui::bold,
            ftxui::hbox({ input_label("Mã DS:", 10), in_id->Render() | input_option | ftxui::border, btn_gen->Render(), ftxui::text("   "), input_label("Mã Sân:", 10), in_san->Render() | input_option | ftxui::border }),
            ftxui::hbox({ input_label("Ngày:", 10), in_ngay->Render() | input_option | ftxui::border, ftxui::text("   "), input_label("Mã KH:", 10), in_kh->Render() | input_option | ftxui::border }),
            ftxui::hbox({ input_label("Từ giờ:", 10), in_bd->Render() | input_option | ftxui::border, ftxui::text("   "), input_label("Đến giờ:", 10), in_kt->Render() | input_option | ftxui::border }),
            ftxui::text(""),
            ftxui::hbox({ btn_book->Render(), ftxui::text("   "), btn_xem_lich->Render() }) | ftxui::center
        }) | ftxui::border;
        
        ftxui::Element cancel_tool = ftxui::hbox({ ftxui::text("ID Hủy: "), in_del->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 10) | ftxui::border, btn_cancel->Render(), ftxui::filler() }) | ftxui::border;
        auto search_bar = ftxui::hbox({ ftxui::text("🔍 Tìm ID: "), in_tim_id->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15) | ftxui::border, btn_tim->Render(), ftxui::filler(), btn_xem_all->Render() }) | ftxui::border;

        return ftxui::vbox({ createHeader("QUẢN LÝ ĐẶT SÂN"), ftxui::text(statusMessage) | ftxui::color(ftxui::Color::Yellow) | ftxui::center, ftxui::separator(), form_dat_san, search_bar, cancel_tool, createTable(data) | ftxui::vscroll_indicator | ftxui::frame | ftxui::flex }); });
}
// 6. hoá đơn
ftxui::Component UIManager::createHoaDonManager()
{
    static std::string hd_id_add = "", hd_ds_id_add = "";
    static std::string hd_ngay_add = "";

    static std::string dv_ma_hd_edit = "";
    static std::string dv_ma_dv_edit = "";
    static std::string dv_so_luong_edit = "1";
    static std::string hd_tim_id = "";

    auto in_hd = ftxui::Input(&hd_id_add, "HDxxx", StyleInputDep());
    auto in_ds = ftxui::Input(&hd_ds_id_add, "DSxxx", StyleInputDep());
    auto in_ngay = ftxui::Input(&hd_ngay_add, "dd/mm/yyyy", StyleInputDep());

    auto in_del = ftxui::Input(&delete_id, "ID HĐ Xóa", StyleInputDep());
    auto in_dv_ma_hd = ftxui::Input(&dv_ma_hd_edit, "Mã HĐ", StyleInputDep());
    auto in_dv_ma_dv = ftxui::Input(&dv_ma_dv_edit, "Mã DV", StyleInputDep());
    auto in_dv_so_luong = ftxui::Input(&dv_so_luong_edit, "Số lượng", StyleInputDep());
    auto in_tim_id = ftxui::Input(&hd_tim_id, "ID tìm kiếm", StyleInputDep());

    auto btn_tim = ftxui::Button("🔍 Tìm", [=]
                                 {
        if(hd_tim_id.empty()) { statusMessage = "❌ Nhập ID để tìm kiếm!"; }
        view_invoice_mode = false; 
        statusMessage = "✅ Đang lọc dữ liệu..."; });

    auto btn_create = ftxui::Button("Tạo HĐ từ DS", [=]
                                    {
        if(hd_id_add.empty() || hd_ds_id_add.empty() || hd_ngay_add.empty()) { statusMessage = "❌ Nhập đầy đủ!"; return; }
        if(!kiemTraDinhDangID(hd_id_add, "HD")) { statusMessage = "❌ ID HĐ phải bắt đầu bằng 'HD'!"; return; } 
        if(!kiemTraDinhDangNgay(hd_ngay_add)) { statusMessage = "❌ Ngày không hợp lệ!"; return; }

        DatSan* ds = nullptr;
        for(size_t i=0; i<danhSachDatSan.get_size(); i++) 
            if(danhSachDatSan[i].getIdDatSan() == hd_ds_id_add) { ds = &danhSachDatSan[i]; break; }
        
        if(!ds) { statusMessage = "❌ Không tìm thấy mã Đặt Sân!"; return; }
        
        HoaDon hd(hd_id_add, ds->getIdKhachHang(), ds->getIdNhanVien(), hd_ds_id_add, hd_ngay_add, &quanLyChiTietHoaDon, "Chua thanh toan"); 
        hd.setTienSan(ds->getTongTien()); 
        hd.tinhTongTien();
        
        if(hoaDonService->taoHoaDon(hd)) {
            statusMessage = "✅ Tạo HĐ thành công!"; 
            saveData(); 
            hd_id_add = ""; hd_ds_id_add = ""; hd_ngay_add = ""; 
        } else statusMessage = "❌ Mã HĐ đã tồn tại!"; });

    auto btn_add_dv = ftxui::Button("➕ Thêm/Sửa DV", [=]
                                    {
        if(dv_ma_hd_edit.empty() || dv_ma_dv_edit.empty()) { statusMessage = "❌ Nhập Mã HĐ và Mã DV!"; return; }
        try {
            int soLuong = std::stoi(dv_so_luong_edit);
            auto dv_ptr = dichVuService->timKiemDichVu(dv_ma_dv_edit);
            HoaDon* hd = hoaDonService->timKiemHoaDon(dv_ma_hd_edit);
            
            if (!dv_ptr || !hd) { statusMessage = "❌ Không tìm thấy HĐ/DV!"; return; }

            string ketQua = "";
            if(hd->kiemTraDichVuDaCo(dv_ma_dv_edit)) { 
                ketQua = hoaDonService->capNhatSoLuongDichVu(dv_ma_hd_edit, dv_ma_dv_edit, soLuong, dv_ptr.get());
            } else {
                ketQua = hoaDonService->themDichVuVaoHoaDon(dv_ma_hd_edit, dv_ptr.get(), soLuong);
            }

            if (ketQua == "") { 
                statusMessage = "✅ Cập nhật dịch vụ thành công!"; saveData();
            } else {
                statusMessage = "❌ " + ketQua; 
            }
        } catch(...) { statusMessage = "❌ Số lượng lỗi!"; } });

    auto btn_del_dv = ftxui::Button("➖ Xóa DV", [=]
                                    {
        if(dv_ma_hd_edit.empty() || dv_ma_dv_edit.empty()) { 
            statusMessage = "❌ Nhập Mã HĐ và Mã DV!"; return; 
        }
        auto dv_ptr = dichVuService->timKiemDichVu(dv_ma_dv_edit);
        string ketQua = hoaDonService->xoaDichVuKhoiHoaDon(dv_ma_hd_edit, dv_ma_dv_edit, dv_ptr.get());
        if(ketQua == "") { statusMessage = "✅ Đã xóa DV khỏi hóa đơn!"; saveData(); } else { statusMessage = "❌ " + ketQua; } });

    auto btn_pay = ftxui::Button("💰 Thanh Toán", [=]
                                 {
        if(dv_ma_hd_edit.empty()) { statusMessage = "❌ Nhập Mã HĐ!"; return; }
        string msg = hoaDonService->thanhToanHoaDon(dv_ma_hd_edit, khachHangService.get());
        statusMessage = (msg.find("thanh cong") != string::npos) ? "✅ " + msg : "❌ " + msg;
        saveData(); });

    auto btn_unpay = ftxui::Button("🔄 Hủy TT", [=]
                                   {
        if(hoaDonService->huyThanhToanHoaDon(dv_ma_hd_edit)) { statusMessage = "✅ Đã hủy TT!"; saveData(); }
        else statusMessage = "❌ Lỗi hủy TT!"; });

    auto btn_del = ftxui::Button("❌ Xóa HĐ", [=]
                                 {
        if(hoaDonService->xoaHoaDon(delete_id)) { statusMessage = "✅ Đã xóa HĐ!"; saveData(); delete_id=""; } 
        else statusMessage = "❌ Không tìm thấy!"; });

    auto btn_chi_tiet = ftxui::Button("🧾 Xem Chi Tiết", [=]
                                      {
        if (dv_ma_hd_edit.empty()) { statusMessage = "❌ Nhập Mã HĐ!"; return; }
        if (!hoaDonService->timKiemHoaDon(dv_ma_hd_edit)) { statusMessage = "❌ Không tồn tại!"; return; }
        view_invoice_mode = true; 
        statusMessage = "✅ Đang xem chi tiết..."; });

    auto btn_back = ftxui::Button("🔙 Quay Lại", [=]
                                  { view_invoice_mode = false; statusMessage = ""; });

    auto input_option = ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15);

    auto container = ftxui::Container::Vertical({in_hd, in_ds, in_ngay,
                                                 in_del, in_dv_ma_hd, in_dv_ma_dv, in_dv_so_luong,
                                                 in_tim_id, btn_tim, btn_create, btn_add_dv, btn_del_dv,
                                                 btn_pay, btn_unpay, btn_del, btn_chi_tiet, btn_back});

    return ftxui::Renderer(container, [=]
                           {

        if (view_invoice_mode) {
            HoaDon* hd = hoaDonService->timKiemHoaDon(dv_ma_hd_edit);
            hd->tinhTongTien(); 
            
            std::string tenKH = "Khách vãng lai";
            KhachHang* kh = khachHangService->timKiemKhachHang(hd->getIdKhachHang());
            if(kh) tenKH = kh->getHoTen();

            std::vector<std::vector<std::string>> billData;
            billData.push_back({"Nội dung", "Đơn giá", "SL", "Thành tiền"});
            billData.push_back({"Thuê sân (" + hd->getIdDatSan() + ")", "-", "-", formatMoney(hd->getTienSan())});

            auto chiTietList = hd->getChiTietTheoHoaDon();
            for(size_t i=0; i<chiTietList.get_size(); i++) {
                auto ct = chiTietList[i];
                auto dv = dichVuService->timKiemDichVu(ct.getMaDichVu());
                std::string tenDV = dv ? dv->getTenDV() : ct.getMaDichVu();
                billData.push_back({ "DV: " + tenDV, formatMoney(ct.getDonGia()), std::to_string(ct.getSoLuong()), formatMoney(ct.getThanhTien()) });
            }
            billData.push_back({"TỔNG CỘNG", "", "", formatMoney(hd->getTongTien())});

            return ftxui::vbox({
                ftxui::text(""), createHeader("CHI TIẾT HÓA ĐƠN"), ftxui::text(""),
                ftxui::window(ftxui::text(" THÔNG TIN ") | ftxui::center | ftxui::bold,
                    ftxui::vbox({
                        ftxui::hbox({ ftxui::text("Mã HĐ:   "), ftxui::text(hd->getIdHoaDon()) | ftxui::bold }),
                        ftxui::hbox({ ftxui::text("Ngày lập:"), ftxui::text(hd->getNgayLap()) }),
                        ftxui::hbox({ ftxui::text("Khách:   "), ftxui::text(tenKH) }),
                        ftxui::hbox({ ftxui::text("Trạng thái: "), ftxui::text(hd->getTrangThai()) | ftxui::color(hd->getTrangThai()=="Da thanh toan" ? ftxui::Color::Green : ftxui::Color::Red) })
                    })
                ) | ftxui::center | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 60),
                ftxui::text(""),
                createTable(billData) | ftxui::center | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 80),
                ftxui::text(""),
                btn_back->Render() | ftxui::center
            });
        }
        for(size_t i=0; i<danhSachHoaDon.get_size(); i++) { danhSachHoaDon[i].tinhTongTien(); }
        std::vector<std::vector<std::string>> data;
        data.push_back({"HD", "Khách", "DS", "Ngày Lập", "Trạng thái", "Tổng tiền"});
        for(size_t i=0; i<danhSachHoaDon.get_size(); i++) {
            const HoaDon& hd = danhSachHoaDon[i];
            if (!hd_tim_id.empty() && hd.getIdHoaDon().find(hd_tim_id) == std::string::npos && hd.getIdKhachHang().find(hd_tim_id) == std::string::npos) continue;
            data.push_back({ hd.getIdHoaDon(), hd.getIdKhachHang(), hd.getIdDatSan(), hd.getNgayLap(), hd.getTrangThai(), formatMoney(hd.getTongTien()) });
        }
        
        ftxui::Element thong_ke = ftxui::vbox({
            ftxui::text("--- Thống Kê Hóa Đơn ---") | ftxui::bold,
            ftxui::hbox({ ftxui::text("Tổng số: " + std::to_string(danhSachHoaDon.get_size())), ftxui::filler(), ftxui::text("Tổng Doanh Thu: " + formatMoney(hoaDonService->tinhTongDoanhThu())) }),
        }) | ftxui::border;

        auto form_tao_hd = ftxui::vbox({
            ftxui::text("--- Tạo Hóa Đơn Mới ---") | ftxui::bold,
            ftxui::hbox({ input_label("Mã HĐ:", 8), in_hd->Render() | input_option | ftxui::border, ftxui::text(" "), input_label(" Từ Mã DS:", 11), in_ds->Render() | input_option | ftxui::border }),
            ftxui::hbox({ input_label("Ngày Lập:", 10), in_ngay->Render() | input_option | ftxui::border, ftxui::text("       "), btn_create->Render() })
        }) | ftxui::border;

        auto form_ql_dv = ftxui::vbox({
            ftxui::text("--- Quản Lý Dịch Vụ & Thanh Toán ---") | ftxui::bold,
            ftxui::hbox({
                input_label("Mã HĐ:", 7), in_dv_ma_hd->Render() | input_option | ftxui::border, 
                ftxui::text(" "), input_label(" Mã DV:", 8), in_dv_ma_dv->Render() | input_option | ftxui::border, 
                ftxui::text(" "), input_label(" SL:", 5), in_dv_so_luong->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 5) | ftxui::border, 
            }),
            ftxui::hbox({ btn_add_dv->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15), ftxui::text(" "), btn_del_dv->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15), ftxui::text(" "), btn_chi_tiet->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15) }),
            ftxui::separator(),
            ftxui::hbox({ btn_pay->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15), ftxui::text(" "), btn_unpay->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15) })
        }) | ftxui::border;

        ftxui::Element admin_tools = currentUser->isAdmin() ? 
            ftxui::hbox({ ftxui::filler(), ftxui::text("ID Xóa HĐ: "), in_del->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 10) | ftxui::border, btn_del->Render() }) :
            ftxui::text("");

        return ftxui::vbox({
            createHeader("QUẢN LÝ HÓA ĐƠN"), 
            ftxui::text(statusMessage) | ftxui::color(ftxui::Color::Yellow) | ftxui::center, ftxui::separator(),
            ftxui::hbox({ ftxui::text("🔍 Tìm ID HĐ: "), in_tim_id->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15) | ftxui::border, btn_tim->Render(), ftxui::filler() }) | ftxui::border,
            form_tao_hd, form_ql_dv, thong_ke, admin_tools,
            createTable(data) | ftxui::vscroll_indicator | ftxui::frame | ftxui::flex
        }); });
}
// 7. thống kê
ftxui::Component UIManager::createThongKe()
{
    auto in_ngay = ftxui::Input(&tk_ngay, "dd/mm/yyyy", StyleInputDep());
    auto in_thang_nam = ftxui::Input(&tk_thang_nam, "mm/yyyy", StyleInputDep());

    auto btn_reset = ftxui::Button("🔄 Làm mới", [=]
                                   { tk_ngay = ""; tk_thang_nam = ""; });

    auto input_option = ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15);

    auto container = ftxui::Container::Vertical({in_ngay, in_thang_nam, btn_reset});

    return ftxui::Renderer(container, [=]
                           {
        double tongThu = hoaDonService->tinhTongDoanhThu();
        int khVip = khachHangService->demSoKhachHangVIP();
        double thuNgay = 0;
        std::string msg_ngay = "(Nhập ngày để xem)";
        if (tk_ngay.length() == 10) { 
            if (kiemTraDinhDangNgay(tk_ngay)) { 
                thuNgay = hoaDonService->tinhTongDoanhThuTheoNgay(tk_ngay);
                msg_ngay = "";
            } else { msg_ngay = "❌ Sai định dạng!"; }
        }
        
        double thuThang = 0;
        std::string msg_thang = "(Nhập tháng để xem)";
        if (tk_thang_nam.length() == 7 && tk_thang_nam[2] == '/') {
            thuThang = hoaDonService->tinhTongDoanhThuTheoThang(tk_thang_nam);
            msg_thang = "";
        } else if (!tk_thang_nam.empty()) { msg_thang = "❌ Sai định dạng!"; }
        double tongLuong = nhanVienService->tinhTongLuong();
        double tongTonKho = dichVuService->tinhTongGiaTriTonKho();
        return ftxui::vbox({
            createHeader("THỐNG KÊ HỆ THỐNG"), 
            ftxui::text(""),
            
            ftxui::hbox({
                ftxui::window(ftxui::text(" TỔNG DOANH THU ") | ftxui::center | ftxui::bold, 
                    ftxui::text(formatMoney(tongThu)) | ftxui::center | ftxui::bold | ftxui::color(ftxui::Color::Green)
                ) | ftxui::flex,
                
                ftxui::window(ftxui::text(" KHÁCH VIP ") | ftxui::center | ftxui::bold, 
                    ftxui::text(std::to_string(khVip)) | ftxui::center | ftxui::bold | ftxui::color(ftxui::Color::Yellow)
                ) | ftxui::flex,
            }),
            
            ftxui::separator(),
            ftxui::text(" 🔍 TRA CỨU CHI TIẾT (Chỉ tính hóa đơn 'Đã thanh toán')") | ftxui::center,
            ftxui::text(""),
            ftxui::hbox({
                input_label("📅 Theo Ngày:", 15), 
                in_ngay->Render() | input_option | ftxui::border,
                ftxui::text("  👉  "),
                (msg_ngay.empty() 
                    ? ftxui::text(formatMoney(thuNgay)) | ftxui::color(ftxui::Color::Green) | ftxui::bold 
                    : ftxui::text(msg_ngay) | ftxui::color(ftxui::Color::GrayDark))
            }),
            ftxui::hbox({
                input_label("📅 Theo Tháng:", 15), 
                in_thang_nam->Render() | input_option | ftxui::border,
                ftxui::text("  👉  "),
                (msg_thang.empty() 
                    ? ftxui::text(formatMoney(thuThang)) | ftxui::color(ftxui::Color::Green) | ftxui::bold 
                    : ftxui::text(msg_thang) | ftxui::color(ftxui::Color::GrayDark))
            }),

            ftxui::text(""),
            btn_reset->Render() | ftxui::center,
            
            ftxui::separator(),
            ftxui::text("📊 TỔNG QUÁT TÀI SẢN & CHI PHÍ") | ftxui::bold,
            ftxui::hbox({ 
                ftxui::text("• Tổng Quỹ Lương NV:  "), 
                ftxui::text(formatMoney(tongLuong)) | ftxui::color(ftxui::Color::Magenta) | ftxui::bold 
            }),
            ftxui::hbox({ 
                ftxui::text("• Tổng Giá trị Tồn kho: "), 
                ftxui::text(formatMoney(tongTonKho)) | ftxui::color(ftxui::Color::Magenta) | ftxui::bold 
            })
        }); });
}

// 8. đổi mật khẩu
ftxui::Component UIManager::createDoiMatKhau()
{
    ftxui::InputOption password_option = StyleInputDep();
    password_option.password = true;

    auto in_pass_old = ftxui::Input(&pass_old, "Mật khẩu cũ", password_option);
    auto in_pass_new1 = ftxui::Input(&pass_new1, "Mật khẩu mới", password_option);
    auto in_pass_new2 = ftxui::Input(&pass_new2, "Nhập lại mật khẩu mới", password_option);

    auto btn_save_pass = ftxui::Button(" Lưu Thay Đổi ", [=]
                                       {
        if (pass_old.empty() || pass_new1.empty() || pass_new2.empty()) {
            statusMessage = "❌ Vui lòng nhập đầy đủ thông tin!";
            return;
        }
        if (pass_new1 != pass_new2) {
            statusMessage = "❌ Mật khẩu mới không khớp!";
            return;
        }

        if (authService.doiMatKhau(pass_old, pass_new1)) {
            statusMessage = "✅ Đổi mật khẩu thành công!";
            pass_old = ""; pass_new1 = ""; pass_new2 = "";
            authService.ghiUserVaoFile("user.txt"); 
        } else {
            statusMessage = "❌ Mật khẩu cũ không đúng!";
        } });

    auto container = ftxui::Container::Vertical({in_pass_old, in_pass_new1, in_pass_new2, btn_save_pass});

    return ftxui::Renderer(container, [=]
                           { return ftxui::vbox({createHeader("🔐 ĐỔI MẬT KHẨU"),
                                                 ftxui::text(statusMessage) | ftxui::color(ftxui::Color::Yellow) | ftxui::center,
                                                 ftxui::separator(),
                                                 ftxui::vbox({ftxui::text(" Mật khẩu cũ:"), in_pass_old->Render() | ftxui::border,
                                                              ftxui::text(" Mật khẩu mới:"), in_pass_new1->Render() | ftxui::border,
                                                              ftxui::text(" Nhập lại mật khẩu mới:"), in_pass_new2->Render() | ftxui::border,
                                                              ftxui::text(""), btn_save_pass->Render() | ftxui::center}) |
                                                     ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 60)}) |
                                    ftxui::center; });
}

// helper methods
ftxui::Element UIManager::createHeader(const std::string &title)
{
    return ftxui::text(title) | ftxui::bold | ftxui::color(ftxui::Color::Cyan) | ftxui::center;
}

ftxui::Element UIManager::createTable(const std::vector<std::vector<std::string>> &data)
{
    if (data.empty())
        return ftxui::text("Không có dữ liệu") | ftxui::center;
    auto table = ftxui::Table(data);
    table.SelectAll().Border(ftxui::LIGHT);
    table.SelectAll().DecorateCells(ftxui::center);
    table.SelectRow(0).Decorate(ftxui::bold);
    table.SelectRow(0).DecorateCells(ftxui::color(ftxui::Color::Cyan));
    table.SelectRow(0).Separator(ftxui::HEAVY);
    return table.Render();
}

std::string UIManager::formatMoney(double amount)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(0) << amount;
    std::string s = oss.str();
    int n = s.length() - 3;
    while (n > 0)
    {
        s.insert(n, ".");
        n -= 3;
    }
    return s + " VND";
}

void UIManager::loadData() { FileManager::loadAllData(danhSachKhachHang, danhSachNhanVien, danhSachSan, danhSachDichVu, danhSachDatSan, danhSachHoaDon, &quanLyChiTietHoaDon); }
void UIManager::saveData() { FileManager::saveAllData(danhSachKhachHang, danhSachNhanVien, danhSachSan, danhSachDichVu, danhSachDatSan, danhSachHoaDon); }
bool UIManager::kiemTraDinhDangID(const std::string &id, const std::string &loai)
{
    if (id.empty())
        return false;
    if (loai == "NV" && id.rfind("NV", 0) != 0)
        return false;
    if (loai == "KH" && id.rfind("KH", 0) != 0)
        return false;
    if (loai == "S" && id.rfind("S", 0) != 0)
        return false;
    if (loai == "DV" && id.rfind("DV", 0) != 0)
        return false;
    if (loai == "DS" && id.rfind("DS", 0) != 0)
        return false;
    if (loai == "HD" && id.rfind("HD", 0) != 0)
        return false;
    if (id.length() > 10)
        return false;
    return true;
}
bool UIManager::kiemTraDinhDangSoDT(const std::string &sdt)
{
    if (sdt.length() != 10)
        return false;
    for (char c : sdt)
        if (!isdigit(c))
            return false;
    return true;
}
bool UIManager::kiemTraDinhDangNgay(const std::string &ngay)
{
    if (ngay.length() != 10 || ngay[2] != '/' || ngay[5] != '/')
        return false;
    try
    {
        int d = stoi(ngay.substr(0, 2));
        int m = stoi(ngay.substr(3, 2));
        int y = stoi(ngay.substr(6, 4));
        if (d < 1 || d > 31 || m < 1 || m > 12 || y < 2020)
            return false;
    }
    catch (...)
    {
        return false;
    }
    return true;
}
bool UIManager::kiemTraDinhDangGio(const std::string &gio)
{
    if (gio.length() != 5 || gio[2] != ':')
        return false;
    try
    {
        int h = stoi(gio.substr(0, 2));
        int m = stoi(gio.substr(3, 2));
        if (h < 0 || h > 23 || m < 0 || m > 59)
            return false;
    }
    catch (...)
    {
        return false;
    }
    return true;
}