#include "Array.h"
#include <iostream>
#include <limits>

using namespace std;

// Hàm hỗ trợ kiểm tra nhập liệu, chỉ chấp nhận số nguyên hợp lệ
int kiemTraNhap(const string &error)
{
    int val;
    while (1)
    {
        cout << error;
        if (cin >> val)
        {
            // Kiểm tra xem sau số vừa nhập có phải là ký tự xuống dòng không (tránh nhập chữ kèm số)
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

// Kiểm tra một số có phải số nguyên tố hay không
bool kiemTraSoNguyenTo(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

// Constructor mặc định: Khởi tạo mảng rỗng
Array::Array()
{
    this->n = 0;
    this->arr = nullptr;
}

// Constructor có tham số: Cấp phát mảng động với n phần tử
Array::Array(int n)
{
    this->n = n;
    this->arr = new int[n];
}

// Destructor: Giải phóng bộ nhớ động khi đối tượng bị hủy
Array::~Array()
{
    if (arr != nullptr)
    {
        delete[] arr;
        arr = nullptr;
    }
}

// Nhập kích thước và giá trị từng phần tử cho mảng
void Array::Nhap()
{
    cout << "Nhap so phan tu trong mang (n >= 0)!\n";
    while (1)
    {
        n = kiemTraNhap("Nhap n: ");
        if (n < 0)
            cout << "Vui long nhap n >= 0!\n";
        else
            break;
    }

    cout << "Nhap tung phan tu trong mang!\n";
    arr = new int[n]; // Cấp phát vùng nhớ cho n phần tử
    for (int i = 0; i < n; i++)
    {
        cout << "Nhap phan tu thu " << i + 1 << ": ";
        arr[i] = kiemTraNhap("");
    }
}

// Xuất các phần tử hiện có trong mảng ra màn hình
void Array::Xuat()
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
}

// Đếm và thông báo số lần xuất hiện của giá trị x trong mảng
void Array::demSoLanXuatHien()
{
    cout << "\nNhap so nguyen de dem so lan xuat hien trong mang!\n";
    int x = kiemTraNhap("Nhap x: ");
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == x)
            ++count;
    }
    cout << "So " << x << " xuat hien " << count << " lan\n";
}

// Kiểm tra mảng có được sắp xếp tăng dần hay không
bool Array::kiemTraMangTangDan()
{
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < arr[i - 1]) // Nếu phần tử sau nhỏ hơn phần tử trước
            return false;
    }
    return true;
}

// Tìm giá trị lẻ nhỏ nhất trong mảng (mặc định trả về 9999999 nếu không có)
int Array::timSoLeNhoNhat()
{
    int min = 9999999;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] % 2 != 0) // Kiểm tra số lẻ
        {
            if (arr[i] < min)
                min = arr[i];
        }
    }
    return min;
}

// Tìm số nguyên tố lớn nhất trong mảng (trả về -1 nếu không có)
int Array::timSoNguyenToLonNhat()
{
    int maxPrime = -1;
    for (int i = 0; i < n; i++)
    {
        if (kiemTraSoNguyenTo(arr[i]))
        {
            if (arr[i] > maxPrime)
                maxPrime = arr[i];
        }
    }
    return maxPrime;
}

// Sắp xếp mảng tăng dần bằng thuật toán Insertion Sort (Sắp xếp chèn)
void Array::sapXepTangDan()
{
    for (int i = 0; i < n; i++)
    {
        int key = arr[i]; // Giá trị đang xét
        int j = i - 1;

        // Dịch chuyển các phần tử lớn hơn key về sau
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; // Chèn key vào vị trí phù hợp
    }

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
}

// Sắp xếp mảng giảm dần bằng thuật toán Insertion Sort
void Array::sapXepGiamDan()
{
    for (int i = 0; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        // Dịch chuyển các phần tử nhỏ hơn key về sau
        while (j >= 0 && arr[j] < key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
}