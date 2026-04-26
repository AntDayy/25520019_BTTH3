#ifndef TAMGIAC_H
#define TAMGIAC_H
#include "Dinh.h"

class TamGiac
{
private:
    Dinh A;
    Dinh B;
    Dinh C;

public:
    TamGiac();
    TamGiac(Dinh a, Dinh b, Dinh c);
    ~TamGiac();

    void Nhap();
    void Xuat();
    int kiemTraLoaiTamGiac(); // 0: Không hợp lệ 1: Thường 2: Vuông 3: Vuông cân 4: Cân 5: Đều

    double tinhChuVi();
    double tinhDienTich();

    void tinhTien();
    void quay();
    void phongTo();
    void thuNho();
};

#endif