#ifndef DINH_H
#define DINH_H

class Dinh
{
private:
    double x;
    double y;

public:
    Dinh();
    Dinh(double x, double y);
    ~Dinh() {}

    void nhap();
    void xuat();

    double tinhKhoangCach(const Dinh &d);
    Dinh tinhTien(double dx, double dy);
    Dinh quay(double rad);
    Dinh thuPhong(double k);
};

#endif