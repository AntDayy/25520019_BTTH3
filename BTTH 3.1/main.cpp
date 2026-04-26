#include <iostream>
#include <limits>
#include "TamGiac.h"
#include "Dinh.h"

using namespace std;

int main()
{
    TamGiac t;

    cout << "Nhap 3 dinh A B C cua tam giac!\n";
    t.Nhap();
    cout << "\nToa do 3 dinh cua tam giac ban vua nhap la\n";
    t.Xuat();

    // Kiểm tra loại tam giác
    int n = t.kiemTraLoaiTamGiac();
    cout << "Tam giac ban vua nhap la tam giac ";
    if (n == 5)
        cout << "deu!\n";
    if (n == 3)
        cout << "vuong can!\n";
    if (n == 4)
        cout << "can!\n";
    if (n == 2)
        cout << "vuong!\n";
    if (n == 1)
        cout << "thuong!\n";

    // Tính toán
    cout << "\nChu vi cua tam giac: " << t.tinhChuVi() << endl;
    cout << "Dien tich cua tam giac: " << t.tinhDienTich() << endl;

    t.tinhTien();
    t.quay();
    t.phongTo();
    t.thuNho();

    return 0;
}