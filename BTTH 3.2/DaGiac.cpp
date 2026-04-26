#include <iostream>
#include <limits>
#include <cmath>
#include "DaGiac.h"
#include "Dinh.h"

using namespace std;

// Hàm hỗ trợ kiểm tra nhập liệu, đảm bảo người dùng nhập đúng số thực
double kiemTraNhap(const string &error)
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

// Constructor mặc định: khởi tạo đa giác rỗng
DaGiac::DaGiac()
{
    this->soDinh = 0;
    this->dinh = nullptr;
}

// Constructor có tham số: cấp phát mảng đỉnh n phần tử
DaGiac::DaGiac(int n)
{
    if (n < 3)
    {
        this->soDinh = 0;
        this->dinh = nullptr;
    }
    else
    {
        this->soDinh = n;
        this->dinh = new Dinh[n];
    }
}

// Copy Constructor: thực hiện sao chép sâu (Deep Copy) vùng nhớ mảng đỉnh
DaGiac::DaGiac(const DaGiac &dg)
{
    this->soDinh = dg.soDinh;
    if (dg.dinh != nullptr)
    {
        this->dinh = new Dinh[this->soDinh];
        for (int i = 0; i < soDinh; i++)
            this->dinh[i] = dg.dinh[i];
    }
    else
        this->dinh = nullptr;
}

// Destructor: giải phóng bộ nhớ động của mảng đỉnh để tránh rò rỉ bộ nhớ
DaGiac::~DaGiac()
{
    if (dinh != nullptr)
    {
        delete[] dinh;
        dinh = nullptr;
    }
}

// Kiểm tra đa giác có thỏa mãn điều kiện hình học cơ bản không
bool DaGiac::kiemTraHopLe()
{
    // 1. Phải có ít nhất 3 đỉnh để tạo thành hình
    if (soDinh < 3)
    {
        cout << "[!] Loi. Da giac phai co it nhat 3 dinh!\n";
        return false;
    }

    // 2. Hai đỉnh liên tiếp không được nằm cùng một vị trí
    for (int i = 0; i < soDinh; i++)
    {
        int j = (i + 1) % soDinh;
        if (dinh[i].x == dinh[j].x && dinh[i].y == dinh[j].y)
        {
            cout << "[!] Loi. Hai dinh lien tiep (" << i + 1 << " va " << j + 1 << ") trung nhau!\n";
            return false;
        }
    }

    // 3. Kiểm tra 3 đỉnh liên tiếp không được thẳng hàng (S > 0)
    for (int i = 0; i < soDinh; i++)
    {
        int j = (i + 1) % soDinh;
        int k = (i + 2) % soDinh;
        double s = (dinh[i].x * (dinh[j].y - dinh[k].y) +
                    dinh[j].x * (dinh[k].y - dinh[i].y) +
                    dinh[k].x * (dinh[i].y - dinh[j].y));
        if (s == 0)
        {
            cout << "[!] Loi 3 dinh lien tiep thang hang!\n";
            return false;
        }
    }
    return true;
}

// Nhập dữ liệu đa giác và lặp lại nếu đa giác không hợp lệ
void DaGiac::Nhap()
{
    while (1)
    {
        soDinh = (int)kiemTraNhap("Nhap so dinh: ");
        if (dinh != nullptr)
            delete[] dinh; // Xóa mảng cũ trước khi cấp phát mới

        dinh = new Dinh[soDinh];
        for (int i = 0; i < soDinh; i++)
        {
            cout << "Nhap toa do dinh thu " << i + 1 << "!\n";
            dinh[i].nhap();
        }

        if (kiemTraHopLe())
            break; // Chỉ thoát vòng lặp khi đa giác hợp lệ
        else
            cout << "Vui long nhap lai da giac!\n";
    }
}

// Xuất danh sách tọa độ các đỉnh của đa giác
void DaGiac::Xuat()
{
    for (int i = 0; i < soDinh; i++)
    {
        cout << "Toa do dinh " << i + 1 << " ";
        dinh[i].xuat();
    }
}

// Tính tổng khoảng cách giữa các cặp đỉnh liên tiếp
double DaGiac::tinhChuVi()
{
    double res = 0;
    for (int i = 0; i < soDinh; i++)
    {
        // Dùng toán tử % để lấy cạnh nối từ đỉnh cuối về đỉnh đầu
        res += dinh[i].tinhKhoangCach(dinh[(i + 1) % soDinh]);
    }
    return res;
}

// Tính diện tích đa giác theo công thức Shoelace
double DaGiac::tinhDienTich()
{
    double dienTich = 0.0;
    for (int i = 0; i < soDinh; i++)
    {
        int j = (i + 1) % soDinh;
        dienTich += dinh[i].x * dinh[j].y;
        dienTich -= dinh[j].x * dinh[i].y;
    }
    return fabs(dienTich) / 2.0; // Lấy giá trị tuyệt đối vì diện tích luôn dương
}

// Tịnh tiến đa giác theo vector (dx, dy) trên bản sao để giữ nguyên đa giác gốc
void DaGiac::tinhTien()
{
    DaGiac dg(*this); // Tạo bản sao
    cout << "\nNhap he so dx dy ma ban muon tinh tien!";
    double dx = kiemTraNhap("\nNhap he so dx: ");
    double dy = kiemTraNhap("Nhap he so dy: ");

    for (int i = 0; i < soDinh; i++)
    {
        dg.dinh[i].x += dx;
        dg.dinh[i].y += dy;
    }
    cout << "Toa do cac dinh sau khi tinh tien!\n";
    dg.Xuat();
}

// Quay đa giác quanh gốc tọa độ một góc alpha
void DaGiac::quay()
{
    DaGiac dg(*this);
    cout << "\nNhap goc quay (do) ma ban muon quay!";
    double goc = kiemTraNhap("\nNhap goc quay (do): ");
    double rad = goc * M_PI / 180.0; // Đổi độ sang Radian

    for (int i = 0; i < soDinh; i++)
    {
        double xCu = dg.dinh[i].x;
        double yCu = dg.dinh[i].y;
        // Áp dụng công thức quay lượng giác (dùng biến tạm xCu để không sai lệch y)
        dg.dinh[i].x = xCu * cos(rad) - yCu * sin(rad);
        dg.dinh[i].y = xCu * sin(rad) + yCu * cos(rad);
    }
    cout << "Toa do cac dinh sau khi quay!\n";
    dg.Xuat();
}

// Phóng to tọa độ đa giác k lần (k >= 1)
void DaGiac::phongTo()
{
    DaGiac dg(*this);
    double k;
    while (1)
    {
        k = kiemTraNhap("\nNhap he so phong to (k >= 1): ");
        if (k >= 1)
            break;
        cout << "[!] Loi. He so k khong nho hon 1. Vui long nhap lai!\n";
    }

    for (int i = 0; i < soDinh; i++)
    {
        dg.dinh[i].x *= k;
        dg.dinh[i].y *= k;
    }
    cout << "Toa do cac dinh sau khi phong to!\n";
    dg.Xuat();
}

// Thu nhỏ tọa độ đa giác k lần (k >= 1)
void DaGiac::thuNho()
{
    DaGiac dg(*this);
    double k;
    while (1)
    {
        k = kiemTraNhap("\nNhap he so thu nho (k >= 1): ");
        if (k >= 1)
            break;
        cout << "[!] Loi. He so k khong nho hon 1. Vui long nhap lai!\n";
    }

    for (int i = 0; i < soDinh; i++)
    {
        dg.dinh[i].x /= k;
        dg.dinh[i].y /= k;
    }
    cout << "Toa do cac dinh sau khi thu nho!\n";
    dg.Xuat();
}