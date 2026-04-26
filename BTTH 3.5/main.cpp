#include "DaThuc.h"
#include <iostream>

using namespace std;

int main()
{
    DaThuc a, b;
    cout << "Nhap da thuc A!\n";
    a.Nhap();
    cout << "Nhap da thuc B!\n";
    b.Nhap();

    cout << "\nDa thuc A: ";
    a.Xuat();
    cout << "\nDa thuc B: ";
    b.Xuat();

    double x;
    cout << "\n\nNhap gia tri x: ";
    cin >> x;
    cout << "Gia tri cua da thuc A: " << a.tinhGiaTri(x) << endl;
    cout << "Gia tru cua da thuc B: " << b.tinhGiaTri(x) << endl;

    DaThuc cong = a.Cong(b);
    DaThuc tru = a.Tru(b);
    cout << "\nA + B: ";
    cong.Xuat();
    cout << "\nA - B: ";
    tru.Xuat();
    cout << endl;

    return 0;
}
