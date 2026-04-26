#include "Dinh.h"
#include <iostream>
#include <limits>
#include <cmath>

using namespace std;

// Hàm hỗ trợ kiểm tra nhập liệu, đảm bảo người dùng nhập đúng số thực
double kiemTraInput(const string &error)
{
    double val;
    while (1)
    {
        cout << error;
        // Kiểm tra nếu nhập vào là số
        if (cin >> val)
        {
            // Kiểm tra không có ký tự lạ sau số (ví dụ: 12abc)
            if (cin.peek() == '\n')
                break;
        }
        else
        {
            cout << "[!] Loi. Vui long nhap lai!\n";
            cin.clear();                                         // Xóa trạng thái lỗi của cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ nhớ đệm
        }
    }
    return val;
}

// Khởi tạo điểm mặc định tại gốc tọa độ (0,0)
Dinh::Dinh()
{
    this->x = 0;
    this->y = 0;
}

// Khởi tạo điểm với tọa độ x, y tùy chỉnh
Dinh::Dinh(double x, double y)
{
    this->x = x;
    this->y = y;
}

// Nhập tọa độ x, y từ bàn phím kèm kiểm tra lỗi
void Dinh::nhap()
{
    x = kiemTraInput("Nhap x: ");
    y = kiemTraInput("Nhap y: ");
}

// Xuất tọa độ điểm ra màn hình theo định dạng (x, y)
void Dinh::xuat()
{
    cout << "(" << x << ", " << y << ")\n";
}

// Tính khoảng cách giữa điểm hiện tại và điểm d truyền vào
double Dinh::tinhKhoangCach(const Dinh &d)
{
    // Áp dụng công thức: căn bậc hai của tổng bình phương hiệu tọa độ
    return sqrt(pow(x - d.x, 2) + pow(y - d.y, 2));
}