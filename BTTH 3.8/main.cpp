#include "DanhSachNhanVien.h"
#include "NhanVienSX.h"
#include <iostream>

using namespace std;

int main()
{
    DanhSach ds;
    cout << "Nhap danh sach nhan vien!\n";
    ds.nhapDanhSach();

    cout << "\nDanh sach nhan vien!\n";
    ds.xuatDanhSach();

    cout << "\nNhan vien co luong thap nhat: ";
    NhanVienSX nv = ds.timNVluongThapNhat();
    nv.Xuat();

    cout << "Tong luong ma cong ty phai tra: " << ds.tongLuongPhaiTra() << " nghin dong\n";

    cout << "Nhan vien co tuoi cao nhat: ";
    NhanVienSX nv1 = ds.timNVcoTuoiCaoNhat();
    nv1.Xuat();

    cout << "\nDanh sach nhan vien sau khi sap xep theo luong tang dan!\n";
    ds.sapXepTheoLuongTangDan(ds);

    return 0;
}