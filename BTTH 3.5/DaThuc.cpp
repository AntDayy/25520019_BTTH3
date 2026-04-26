#include "DaThuc.h"
#include <iostream>
#include <limits>

using namespace std;

// Hàm hỗ trợ: Kiểm tra quá trình nhập số thực an toàn, chống trôi lệnh hoặc nhập sai kiểu dữ liệu (chữ cái, kí tự đặc biệt)
double kiemTraNhap(const string &error)
{
    double val;
    while (1) // Vòng lặp vô hạn cho đến khi nhập đúng
    {
        cout << error;
        if (cin >> val)
        {
            // Kiểm tra nếu ký tự tiếp theo là dấu Enter (xuống dòng) thì dữ liệu hợp lệ
            if (cin.peek() == '\n')
                break;
        }
        else
        {
            cout << "[!] Loi. Vui long nhap lai!\n";
            cin.clear();                                         // Xóa cờ lỗi của cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Loại bỏ các ký tự bị kẹt trong bộ nhớ đệm
        }
    }
    return val;
}

// Constructor mặc định: Tạo đa thức rỗng (bậc 0, mảng hệ số rỗng)
DaThuc::DaThuc()
{
    this->n = 0;
    this->a = nullptr;
}

// Constructor có tham số: Cấp phát mảng hệ số với bậc n cho trước
DaThuc::DaThuc(int n)
{
    this->n = n;
    a = new double[n + 1]; // Đa thức bậc n luôn có n + 1 phần tử (từ x^n đến x^0)
}

// Copy Constructor (Sao chép sâu): Dùng để copy nội dung mảng thay vì copy địa chỉ con trỏ, tránh lỗi crash chương trình
DaThuc::DaThuc(const DaThuc &dt)
{
    this->n = dt.n;
    if (dt.a != nullptr)
    {
        // Cấp phát mảng mới và chép từng giá trị qua
        this->a = new double[this->n + 1];
        for (int i = 0; i <= this->n; i++)
        {
            this->a[i] = dt.a[i];
        }
    }
    else
    {
        this->a = nullptr;
    }
}

// Destructor (Hàm hủy): Giải phóng bộ nhớ động khi đa thức không còn sử dụng
DaThuc::~DaThuc()
{
    if (a != nullptr)
    {
        delete[] a;
        a = nullptr;
    }
}

// Hàm nhập dữ liệu cho đa thức
void DaThuc::Nhap()
{
    cout << "Nhap bac cua da thuc (n >= 0)!\n";
    while (1)
    {
        n = kiemTraNhap("Nhap n: ");

        if (n < 0)
            cout << "Vui long nhap n >= 0!\n";
        else
            break;
    }

    // In ra dạng nguyên mẫu để người dùng dễ hình dung thứ tự nhập
    cout << "Da thuc ban nhap co dang: ";
    for (int i = 0; i <= n; i++)
    {
        if (n - i == 0)
        {
            cout << "a" << i + 1;
            continue;
        }
        cout << "a" << i + 1 << "x^" << n - i;
        if (i < n)
            cout << " + ";
    }
    cout << "\n";

    // Cấp phát bộ nhớ và tiến hành nhập từng hệ số
    a = new double[n + 1];
    for (int i = 0; i <= n; i++)
    {
        string cauNhac = "Nhap he so a" + to_string(i + 1) + ": ";
        a[i] = kiemTraNhap(cauNhac);
    }
}

// Hàm xuất đa thức (đã tối ưu hiển thị: ẩn x^0, ẩn hệ số 1, dấu +/- rõ ràng)
void DaThuc::Xuat()
{
    bool isAllZero = true; // Cờ kiểm tra trường hợp toàn bộ đa thức bằng 0

    for (int i = 0; i <= n; i++)
    {
        // Bỏ qua không in nếu hệ số bằng 0
        if (a[i] == 0)
            continue;

        // Xử lý in dấu '+' hoặc '-' phù hợp cho từng phần tử
        if (isAllZero == false) // Nếu không phải là phần tử đầu tiên được in
        {
            if (a[i] > 0)
                cout << " + ";
            else
                cout << " - ";
        }
        else // Nếu là phần tử khác 0 đầu tiên
        {
            if (a[i] < 0)
                cout << "-";
        }

        isAllZero = false; // Đã tìm thấy ít nhất 1 phần tử khác 0
        double giatriTuyetDoi = abs(a[i]);
        int bacThu_i = n - i;

        // In hệ số (Chỉ in nếu giá trị tuyệt đối khác 1 hoặc đây là hệ số tự do)
        if (giatriTuyetDoi != 1 || bacThu_i == 0)
            cout << giatriTuyetDoi;

        // In phần biến x và số mũ tương ứng
        if (bacThu_i > 0)
        {
            cout << "x";
            if (bacThu_i > 1)
                cout << "^" << bacThu_i;
        }
    }

    // Nếu đa thức chỉ toàn số 0
    if (isAllZero == true)
        cout << "0";
}

// Hàm tính giá trị đa thức tại x bằng thuật toán Horner (Tối ưu O(n))
double DaThuc::tinhGiaTri(double x)
{
    if (n < 0 || a == nullptr)
        return 0;

    double val = a[0];
    for (int i = 1; i <= n; i++)
    {
        val = val * x + a[i]; // val = (...((a0*x + a1)*x + a2)...)*x + an
    }
    return val;
}

// Hàm thực hiện phép cộng hai đa thức
DaThuc DaThuc::Cong(const DaThuc &dt)
{
    DaThuc res;
    // Bậc của đa thức kết quả tạm thời bằng bậc lớn nhất của 2 đa thức
    res.n = (this->n >= dt.n) ? this->n : dt.n;
    res.a = new double[res.n + 1];

    // Lặp ngược từ bậc thấp nhất lên bậc cao nhất để cộng các hệ số tương ứng
    for (int i = res.n; i >= 0; i--)
    {
        // Toán tử 3 ngôi: Đảm bảo nếu một đa thức bậc ngắn hơn thì hệ số bị thiếu coi như là 0
        double heSo1 = (this->n - i >= 0) ? this->a[this->n - i] : 0;
        double heSo2 = (dt.n - i >= 0) ? dt.a[dt.n - i] : 0;

        res.a[res.n - i] = heSo1 + heSo2;
    }

    // Chuẩn hóa đa thức: Xử lý trường hợp cộng làm triệt tiêu hệ số bậc cao nhất
    int soBacBiGiam = 0;
    while (soBacBiGiam < res.n && res.a[soBacBiGiam] == 0)
    {
        soBacBiGiam++; // Đếm số lượng bậc vô nghĩa bị gán bằng 0 ở đầu mảng
    }

    // Nếu bị giảm bậc, cấp phát mảng mới nhỏ hơn và chép dữ liệu có ý nghĩa sang
    if (soBacBiGiam > 0)
    {
        int bacMoi = res.n - soBacBiGiam;
        double *mangMoi = new double[bacMoi + 1];
        for (int i = 0; i <= bacMoi; i++)
        {
            mangMoi[i] = res.a[soBacBiGiam + i];
        }
        delete[] res.a;  // Giải phóng mảng tạm cũ
        res.a = mangMoi; // Trỏ sang mảng mới đã chuẩn hóa
        res.n = bacMoi;
    }

    return res;
}

// Hàm thực hiện phép trừ hai đa thức
DaThuc DaThuc::Tru(const DaThuc &dt)
{
    DaThuc res;
    // Bậc của đa thức kết quả tạm thời bằng bậc lớn nhất của 2 đa thức
    res.n = (this->n >= dt.n) ? this->n : dt.n;
    res.a = new double[res.n + 1];

    // Lặp ngược từ bậc thấp nhất lên bậc cao nhất để trừ các hệ số tương ứng
    for (int i = res.n; i >= 0; i--)
    {
        double heSo1 = (this->n - i >= 0) ? this->a[this->n - i] : 0;
        double heSo2 = (dt.n - i >= 0) ? dt.a[dt.n - i] : 0;

        res.a[res.n - i] = heSo1 - heSo2;
    }

    // Chuẩn hóa đa thức: Rút gọn mảng tương tự như hàm Cộng
    int soBacBiGiam = 0;
    while (soBacBiGiam < res.n && res.a[soBacBiGiam] == 0)
    {
        soBacBiGiam++;
    }

    if (soBacBiGiam > 0)
    {
        int bacMoi = res.n - soBacBiGiam;
        double *mangMoi = new double[bacMoi + 1];
        for (int i = 0; i <= bacMoi; i++)
        {
            mangMoi[i] = res.a[soBacBiGiam + i];
        }
        delete[] res.a;
        res.a = mangMoi;
        res.n = bacMoi;
    }

    return res;
}