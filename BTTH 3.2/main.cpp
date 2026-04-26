#include <iostream>
#include "DaGiac.h"

using namespace std;

int main()
{
    DaGiac dg;
    cout << "Nhap so dinh cua da giac!\n";
    dg.Nhap();
    cout << "\nToa do cac dinh ban vua nhap!\n";
    dg.Xuat();

    // Tinh toan
    cout << "\nChu vi: " << dg.tinhChuVi() << endl;
    cout << "Dien tich: " << dg.tinhDienTich() << endl;

    dg.tinhTien();
    dg.quay();
    dg.phongTo();
    dg.thuNho();
}