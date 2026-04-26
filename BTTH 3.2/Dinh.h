#ifndef DINH_H
#define DINH_H

class Dinh
{
private:
    double x;
    double y;
    friend class DaGiac;

public:
    Dinh();
    Dinh(double x, double y);
    ~Dinh() {}

    void nhap();
    void xuat();
    double tinhKhoangCach(const Dinh &d);
};

#endif