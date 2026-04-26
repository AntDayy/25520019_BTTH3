#include "TamGiac.h"
#include "Dinh.h"
#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

// Hàm hỗ trợ nhập số thực an toàn, chống trôi lệnh khi nhập sai định dạng chữ/kí tự
double kiemTraNhapInPut(const string &error)
{
    double val;

    while (1) // Lặp vô tận cho đến khi nhập đúng số thực
    {
        cout << error;
        if (cin >> val)
        {
            if (cin.peek() == '\n') // Nếu kết thúc bằng Enter thì nhập thành công
                break;
        }
        else
        {
            cout << "[!] Loi. Vui long nhap lai!\n";
            cin.clear();                                         // Xóa cờ lỗi của luồng nhập
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ nhớ đệm
        }
    }

    return val;
}

// Hàm kiểm tra và phân loại tam giác, trả về mã số tương ứng với từng loại
int TamGiac::kiemTraLoaiTamGiac()
{
    // Tính độ dài 3 cạnh của tam giác
    double ab = A.tinhKhoangCach(B);
    double bc = B.tinhKhoangCach(C);
    double ca = C.tinhKhoangCach(A);
    double eps = 1e-5; // Khởi tạo sai số cực nhỏ để so sánh số thực (double)

    // Kiểm tra điều kiện tồn tại tam giác (tổng 2 cạnh phải lớn hơn cạnh còn lại)
    if (ab + bc <= ca + eps || bc + ca <= ab + eps || ca + ab <= bc + eps)
        return 0; // 0: Không phải tam giác hợp lệ

    // Kiểm tra tam giác cân (có 2 cạnh bằng nhau) và đều (3 cạnh bằng nhau)
    bool isCan = (abs(ab - bc) < eps) || (abs(ab - ca) < eps) || (abs(bc - ca) < eps);
    bool isDeu = (abs(ab - bc) < eps) && (abs(bc - ca) < eps);

    // Kiểm tra tam giác vuông dựa trên định lý Pytago
    bool isVuong = (abs(ab * ab + bc * bc - ca * ca) < eps) ||
                   (abs(bc * bc + ca * ca - ab * ab) < eps) ||
                   (abs(ca * ca + ab * ab - bc * bc) < eps);

    // Trả về kết quả phân loại
    if (isDeu)
        return 5; // 5: Tam giác đều
    if (isVuong && isCan)
        return 3; // 3: Tam giác vuông cân
    if (isCan)
        return 4; // 4: Tam giác cân
    if (isVuong)
        return 2; // 2: Tam giác vuông
    return 1;     // 1: Tam giác thường
}

// Hàm khởi tạo mặc định
TamGiac::TamGiac() : A(0, 0), B(0, 0), C(0, 0) {}

// Hàm khởi tạo có tham số
TamGiac::TamGiac(Dinh a, Dinh b, Dinh c) : A(a), B(b), C(c) {}

TamGiac::~TamGiac() {}

// Hàm nhập tọa độ 3 đỉnh của tam giác
void TamGiac::Nhap()
{
    while (1)
    {
        cout << "Nhap dinh A!\n";
        A.nhap();
        cout << "Nhap dinh B!\n";
        B.nhap();
        cout << "Nhap dinh C!\n";
        C.nhap();

        // Nếu 3 đỉnh vừa nhập không tạo thành tam giác, yêu cầu nhập lại toàn bộ
        if (kiemTraLoaiTamGiac() == 0)
            cout << "[!] Loi. Tam giac ban nhap khong hop le. Vui long nhap lai!\n";
        else
            break; // Nhập đúng thì thoát vòng lặp
    }
}

// Hàm xuất tọa độ 3 đỉnh của tam giác ra màn hình
void TamGiac::Xuat()
{
    cout << "A";
    A.xuat();
    cout << "B";
    B.xuat();
    cout << "C";
    C.xuat();
}

// Hàm tính chu vi tam giác (Tổng độ dài 3 cạnh)
double TamGiac::tinhChuVi()
{
    double ab = A.tinhKhoangCach(B);
    double bc = B.tinhKhoangCach(C);
    double ca = C.tinhKhoangCach(A);

    return ab + bc + ca;
}

// Hàm tính diện tích tam giác sử dụng công thức Heron
double TamGiac::tinhDienTich()
{
    double ab = A.tinhKhoangCach(B);
    double bc = B.tinhKhoangCach(C);
    double ca = C.tinhKhoangCach(A);
    double p = (ab + bc + ca) / 2; // Tính nửa chu vi (p)

    // Trả về diện tích
    return sqrt(p * (p - ab) * (p - bc) * (p - ca));
}

// Hàm thực hiện phép tịnh tiến tam giác theo vector (dx, dy)
void TamGiac::tinhTien()
{
    double dx, dy;
    TamGiac t; // Tạo một tam giác tạm để lưu kết quả biến hình

    cout << "\nNhap he so dx dy ma ban muon tinh tien!\n";
    dx = kiemTraNhapInPut("Nhap he so dx: ");
    dy = kiemTraNhapInPut("Nhap he so dy: ");

    // Tịnh tiến từng đỉnh và gán vào tam giác tạm t
    t.A = A.tinhTien(dx, dy);
    t.B = B.tinhTien(dx, dy);
    t.C = C.tinhTien(dx, dy);

    cout << "Toa do 3 dinh cua tam giac sau khi tinh tien\n";
    t.Xuat(); // In ra kết quả
}

// Hàm thực hiện phép quay tam giác quanh gốc tọa độ một góc (tính bằng độ)
void TamGiac::quay()
{
    double goc;
    TamGiac t; // Tạo một tam giác tạm để lưu kết quả biến hình

    cout << endl;
    goc = kiemTraNhapInPut("Nhap goc quay (do): ");
    double rad = goc * M_PI / 180.0; // Chuyển đổi từ độ sang radian

    // Quay từng đỉnh và gán vào tam giác tạm t
    t.A = A.quay(rad);
    t.B = B.quay(rad);
    t.C = C.quay(rad);

    cout << "Toa do 3 dinh cua tam giac sau khi quay\n";
    t.Xuat(); // In ra kết quả
}

// Hàm thực hiện phép phóng to tam giác theo hệ số k
void TamGiac::phongTo()
{
    double k;
    TamGiac t; // Tạo một tam giác tạm để lưu kết quả biến hình

    cout << endl;
    while (1)
    {
        k = kiemTraNhapInPut("Nhap he so phong to (k >= 1): ");

        if (k < 1) // Ràng buộc hệ số phóng to phải >= 1
            cout << "Vui long nhap he so khong nho hon 1!\n";
        else
            break;
    }

    // Phóng to từng đỉnh và gán vào tam giác tạm t
    t.A = A.thuPhong(k);
    t.B = B.thuPhong(k);
    t.C = C.thuPhong(k);

    cout << "Toa do 3 dinh cua tam giac sau khi phong to\n";
    t.Xuat(); // In ra kết quả
}

// Hàm thực hiện phép thu nhỏ tam giác theo hệ số k
void TamGiac::thuNho()
{
    double k;
    TamGiac t; // Tạo một tam giác tạm để lưu kết quả biến hình

    cout << endl;
    while (1)
    {
        k = kiemTraNhapInPut("Nhap he so thu nho (k >= 1): ");

        if (k < 1) // Ràng buộc hệ số đầu vào phải >= 1 để đảm bảo tỷ lệ thu nhỏ 1/k hợp lệ
            cout << "Vui long nhap he khong nho hon 1!\n";
        else
            break;
    }

    // Thu nhỏ từng đỉnh theo tỷ lệ nghịch (1/k) và gán vào tam giác tạm t
    t.A = A.thuPhong(1 / k);
    t.B = B.thuPhong(1 / k);
    t.C = C.thuPhong(1 / k);

    cout << "Toa do 3 dinh cua tam giac sau khi thu nho\n";
    t.Xuat(); // In ra kết quả
}