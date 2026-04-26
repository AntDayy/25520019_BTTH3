#include "Dinh.h"
#include <iostream>
#include <limits>
#include <cmath>

using namespace std;

// Hàm hỗ trợ nhập số thực an toàn, tránh lỗi trôi lệnh khi người dùng nhập sai định dạng (ví dụ: nhập chữ thay vì số)
double kiemTraNhap(const string &error)
{
    double val;

    // Vòng lặp vô hạn, chỉ thoát khi người dùng nhập đúng một số thực
    while (1)
    {
        cout << error;
        // Kiểm tra xem việc gán dữ liệu nhập vào biến val có thành công không
        if (cin >> val)
        {
            // Nếu ký tự tiếp theo là Enter ('\n') nghĩa là nhập chuẩn, thoát vòng lặp
            if (cin.peek() == '\n')
                break;
        }
        else
        {
            // Thông báo lỗi và tiến hành dọn dẹp luồng nhập (cin)
            cout << "[!] Loi. Vui long nhap lai!\n";
            cin.clear();                                         // Xóa trạng thái lỗi của luồng
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Loại bỏ các ký tự rác còn sót lại trong bộ nhớ đệm
        }
    }

    return val; // Trả về giá trị đã nhập đúng
}

// Constructor mặc định: Khởi tạo tọa độ đỉnh tại gốc tọa độ (0, 0)
Dinh::Dinh() : x(0.0), y(0.0) {}

// Constructor có tham số: Khởi tạo tọa độ đỉnh với giá trị x, y được truyền vào
Dinh::Dinh(double x, double y) : x(x), y(y) {}

// Hàm nhập tọa độ cho đỉnh từ bàn phím
void Dinh::nhap()
{
    // Sử dụng hàm kiemTraNhap để đảm bảo x và y nhận được giá trị số hợp lệ
    x = kiemTraNhap("Nhap x: ");
    y = kiemTraNhap("Nhap y: ");
}

// Hàm xuất tọa độ của đỉnh ra màn hình theo định dạng (x, y)
void Dinh::xuat()
{
    cout << "(" << x << ", " << y << ")\n";
}

// Hàm tính khoảng cách từ đỉnh hiện tại (this) đến một đỉnh d khác
double Dinh::tinhKhoangCach(const Dinh &d)
{
    // Áp dụng công thức khoảng cách Euclid: căn bậc 2 của tổng bình phương hiệu tọa độ
    return sqrt(pow(x - d.x, 2) + pow(y - d.y, 2));
}

// Hàm tịnh tiến đỉnh hiện tại theo vectơ (dx, dy)
Dinh Dinh::tinhTien(double dx, double dy)
{
    Dinh d; // Tạo một đỉnh mới để lưu kết quả

    // Cộng thêm độ dời dx, dy vào tọa độ x, y ban đầu
    d.x = x + dx;
    d.y = y + dy;

    return d; // Trả về đỉnh mới sau phép tịnh tiến
}

// Hàm quay đỉnh quanh gốc tọa độ (0,0) một góc rad (tính bằng radian)
Dinh Dinh::quay(double rad)
{
    Dinh d; // Tạo một đỉnh mới để lưu kết quả

    // Áp dụng công thức lượng giác của phép quay tọa độ 2D
    d.x = x * cos(rad) - y * sin(rad);
    d.y = x * sin(rad) + y * cos(rad);

    return d; // Trả về đỉnh mới sau phép quay
}

// Hàm thu phóng (vị tự) đỉnh hiện tại theo hệ số k với tâm thu phóng là gốc tọa độ (0,0)
Dinh Dinh::thuPhong(double k)
{
    Dinh d; // Tạo một đỉnh mới để lưu kết quả

    // Nhân tọa độ x, y hiện tại với hệ số thu phóng k
    d.x = x * k;
    d.y = y * k;

    return d; // Trả về đỉnh mới sau phép thu phóng
}