#ifndef ARRAY_H
#define ARRAY_H

class Array
{
private:
    int n;
    int *arr;

public:
    Array();      // Hàm khởi tạo mặc định
    Array(int n); // Hàm khởi tạo có tham số
    ~Array();

    void Nhap();
    void Xuat();

    void demSoLanXuatHien();
    bool kiemTraMangTangDan();
    int timSoLeNhoNhat();
    int timSoNguyenToLonNhat();
    void sapXepTangDan();
    void sapXepGiamDan();
};

#endif