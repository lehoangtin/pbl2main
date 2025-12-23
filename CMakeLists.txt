cmake_minimum_required(VERSION 3.11)
project(QuanLySanCauLong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch FTXUI
include(FetchContent)
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(ftxui)

# Source files
set(SOURCES
    main.cpp
    # Core classes
    NguoiDung.cpp
    KhachHang.cpp
    NhanVien.cpp
    SanCauLong.cpp
    SanNgoaiTroi.cpp
    SanTrongNha.cpp
    SanVIP.cpp
    DichVu.cpp
    DichVuAnUong.cpp
    DichVuThietBi.cpp
    DatSan.cpp
    HoaDon.cpp
    ChiTietHoaDon.cpp
    # Services
    AuthenticationService.cpp       
    QuanLyNhanVienService.cpp
    QuanLyKhachHangService.cpp
    QuanLySanService.cpp
    QuanLyDichVuService.cpp
    QuanLyDatSanService.cpp
    QuanLyHoaDonService.cpp
    QuanLyChiTietHoaDon.cpp
    # UI
    UIManager.cpp
)

add_executable(QuanLySanCauLong ${SOURCES})

target_link_libraries(QuanLySanCauLong
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)