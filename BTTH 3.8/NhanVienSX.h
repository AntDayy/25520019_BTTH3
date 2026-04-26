#ifndef NHANVIENSX_H
#define NHANVIENSX_H
#include <string>

class NhanVienSX
{
private:
    int maNV;
    std::string hoTen;
    int ngaySinh;
    int thangSinh;
    int namSinh;
    int soSP;
    double luong;

public:
    NhanVienSX();
    NhanVienSX(int maNV, std::string hoTen, int ngay, int thang, int nam, int soSP, double luong);
    ~NhanVienSX();

    void Nhap();
    void Xuat();
    void setLuong(double luong);
    double getLuong();
    int getSP();
    int getNgay();
    int getThang();
    int getNam();
};

#endif