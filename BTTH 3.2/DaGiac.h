#ifndef DAGIAC_H
#define DAGIAC_H
#include "Dinh.h"

class DaGiac
{
private:
    int soDinh;
    Dinh *dinh;

public:
    DaGiac();
    DaGiac(int n);
    ~DaGiac();
    DaGiac(const DaGiac &dg);

    bool kiemTraHopLe();

    void Nhap();
    void Xuat();

    double tinhChuVi();
    double tinhDienTich();

    void tinhTien();
    void quay();
    void phongTo();
    void thuNho();
};

#endif