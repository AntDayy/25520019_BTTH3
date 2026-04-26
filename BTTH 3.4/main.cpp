#include "Array.h"
#include <iostream>

using namespace std;

int main()
{
    Array arr;
    cout << "Nhap mang so nguyen!\n";
    arr.Nhap();
    cout << "Mang so nguyen ban vua nhap: ";
    arr.Xuat();
    cout << endl;

    // Tính toán
    arr.demSoLanXuatHien();

    if (arr.kiemTraMangTangDan())
        cout << "Mang ban nhap la mang tang dan\n";
    else
        cout << "Mang ban nhap khong la mang tang dan\n";

    // Nêu có số lẻ trong mảng thì in ra số lẻ nhỏ nhất trong mảng
    int minLe = arr.timSoLeNhoNhat();
    if (minLe != 9999999)
        cout << "\nSo le nho nhat trong mang: " << minLe << endl;
    else
        cout << "\nKhong co so le nao trong mang ban nhap!\n";

    // Nếu có số nguyên tố trong mang thì mới in ra sô nguyên tố lớn nhất
    if (arr.timSoNguyenToLonNhat() != -1)
        cout << "So nguyen to lon nhat trong mang: " << arr.timSoNguyenToLonNhat() << endl;
    else
        cout << "Khong co so nguyen co nao trong mang ban nhap!\n";

    cout << "\nSap xep mang tang dan: ";
    arr.sapXepTangDan();
    cout << "\nSap xep mang giam dan: ";
    arr.sapXepGiamDan();
    cout << endl;

    return 0;
}