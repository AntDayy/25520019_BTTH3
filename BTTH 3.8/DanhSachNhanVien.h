#ifndef DANHSACHNHANVIEN_H
#define DANHSACHNHANVIEN_H
#include "NhanVienSX.h"

class DanhSach
{
private:
    int n;
    NhanVienSX *nv;
    double giaSP;

public:
    DanhSach();
    DanhSach(int n, double gia);
    ~DanhSach();

    void nhapDanhSach();
    void xuatDanhSach();
    NhanVienSX timNVluongThapNhat();
    double tongLuongPhaiTra();
    NhanVienSX timNVcoTuoiCaoNhat();
    void sapXepTheoLuongTangDan(DanhSach &ds);
};

#endif