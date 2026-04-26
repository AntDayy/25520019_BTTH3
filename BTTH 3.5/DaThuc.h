#ifndef DATHUC_H
#define DATHUC_H

class DaThuc
{
private:
    int n;
    double *a;

public:
    DaThuc();
    DaThuc(int n);
    DaThuc(const DaThuc &dt);
    ~DaThuc();

    void Nhap();
    void Xuat();

    double tinhGiaTri(double x);
    DaThuc Cong(const DaThuc &dt);
    DaThuc Tru(const DaThuc &dt);
};

#endif