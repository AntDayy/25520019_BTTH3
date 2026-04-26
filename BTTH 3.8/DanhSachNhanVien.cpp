#include "DanhSachNhanVien.h"
#include "NhanVienSX.h"
#include <iostream>
#include <limits>

using namespace std;

// Hàm hỗ trợ nhập số thực (double) an toàn, chống trôi lệnh hoặc lỗi luồng nhập
// Tương tự hàm kiemTraNhap bên NhanVienSX nhưng dùng cho kiểu double
double kiemTraInput(const string &error)
{
    double val;
    // Vòng lặp vô hạn, chỉ thoát khi người dùng nhập đúng số
    while (1)
    {
        cout << error;
        // Kiểm tra xem luồng nhập vào có thành công chuyển thành số double không
        if (cin >> val)
        {
            // Kiểm tra kí tự tiếp theo, nếu là Enter ('\n') thì nhập chuẩn, thoát vòng lặp
            if (cin.peek() == '\n')
                break;
        }
        else
        {
            // Báo lỗi nếu nhập sai định dạng (ví dụ nhập chữ)
            cout << "[!] Loi. Vui long nhap lai!\n";
            cin.clear();                                         // Xóa cờ lỗi của cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa sạch bộ đệm
        }
    }
    return val;
}

// Constructor mặc định: Khởi tạo danh sách rỗng ban đầu
DanhSach::DanhSach()
{
    this->n = 0;        // Số lượng nhân viên ban đầu bằng 0
    this->giaSP = 0;    // Giá sản phẩm ban đầu bằng 0
    this->nv = nullptr; // Con trỏ quản lý mảng nhân viên trỏ vào null (chưa có dữ liệu)
}

// Constructor có tham số: Khởi tạo danh sách với số lượng nhân viên và giá sản phẩm biết trước
DanhSach::DanhSach(int n, double gia)
{
    this->n = n;
    this->giaSP = gia;
    this->nv = new NhanVienSX[n]; // Cấp phát động một mảng chứa n nhân viên
}

// Destructor (Hàm hủy): Tự động dọn dẹp bộ nhớ khi đối tượng DanhSach không còn được sử dụng
DanhSach::~DanhSach()
{
    // Nếu con trỏ nv đang quản lý một mảng đã được cấp phát
    if (nv != nullptr)
    {
        delete[] nv;  // Thu hồi vùng nhớ của mảng để tránh rò rỉ bộ nhớ (memory leak)
        nv = nullptr; // Đưa con trỏ về null cho an toàn
    }
}

// Hàm nhập thông tin cho toàn bộ danh sách nhân viên
void DanhSach::nhapDanhSach()
{
    // Lặp yêu cầu nhập số lượng nhân viên cho đến khi nhận được số >= 0
    while (1)
    {
        n = kiemTraInput("Nhap so nhan vien: ");

        if (n < 0)
            cout << "[!] Loi. So nhan vien khong hop le. Vui long nhap lai!\n";
        else
            break;
    }

    // Lặp yêu cầu nhập đơn giá sản phẩm cho đến khi nhận được số >= 0
    while (1)
    {
        giaSP = kiemTraInput("Nhap gia cua mot san pham: ");

        if (giaSP < 0)
            cout << "[!] Loi. Gia san pham khong hop le. Vui long nhap lai!\n";
        else
            break;
    }

    // Cấp phát mảng động để chứa n nhân viên vừa nhập
    nv = new NhanVienSX[n];

    // Duyệt qua từng vị trí trong mảng để nhập thông tin
    for (int i = 0; i < n; i++)
    {
        cout << "Nhap nhan vien thu " << i + 1 << "!\n";
        nv[i].Nhap(); // Gọi hàm Nhap() của từng đối tượng NhanVienSX

        // Tính lương cho nhân viên hiện tại = Số sản phẩm * Đơn giá
        nv[i].setLuong(nv[i].getSP() * giaSP);
    }
}

// Hàm in toàn bộ danh sách nhân viên ra màn hình
void DanhSach::xuatDanhSach()
{
    for (int i = 0; i < n; i++)
        nv[i].Xuat(); // Gọi hàm Xuat() của từng đối tượng NhanVienSX
}

// Hàm tìm và trả về đối tượng nhân viên có mức lương thấp nhất
NhanVienSX DanhSach::timNVluongThapNhat()
{
    // Giả sử nhân viên đầu tiên (vị trí 0) có lương thấp nhất
    NhanVienSX res = nv[0];

    // Duyệt qua các nhân viên còn lại trong danh sách
    for (int i = 0; i < n; i++)
    {
        // Nếu tìm thấy nhân viên nào có lương thấp hơn nhân viên đang giữ kỷ lục (res)
        if (nv[i].getLuong() < res.getLuong())
        {
            res = nv[i]; // Cập nhật lại kỷ lục lương thấp nhất
        }
    }
    return res; // Trả về nhân viên có lương thấp nhất
}

// Hàm tính tổng số tiền lương mà công ty phải trả cho tất cả nhân viên
double DanhSach::tongLuongPhaiTra()
{
    double sum = 0; // Biến tích lũy tổng lương
    for (int i = 0; i < n; i++)
        sum += nv[i].getLuong(); // Cộng dồn lương của từng nhân viên vào sum
    return sum;
}

// Hàm tìm và trả về đối tượng nhân viên lớn tuổi nhất
NhanVienSX DanhSach::timNVcoTuoiCaoNhat()
{
    // Giả sử nhân viên đầu tiên là người lớn tuổi nhất
    NhanVienSX res = nv[0];

    for (int i = 0; i < n; i++)
    {
        // Tuổi cao nhất nghĩa là năm sinh phải nhỏ nhất
        if (nv[i].getNam() < res.getNam())
            res = nv[i];
        // Nếu sinh cùng năm, thì so sánh tiếp đến tháng sinh
        else if (nv[i].getNam() == res.getNam())
        {
            // Tháng sinh nhỏ hơn thì ra đời trước (lớn tuổi hơn)
            if (nv[i].getThang() < res.getThang())
                res = nv[i];
            // Nếu cùng năm, cùng tháng thì so sánh đến ngày sinh
            else if (nv[i].getThang() == res.getThang())
            {
                // Ngày sinh nhỏ hơn thì lớn tuổi hơn
                if (nv[i].getNgay() < res.getNgay())
                    res = nv[i];
            }
        }
    }
    return res; // Trả về nhân viên lớn tuổi nhất
}

// Hàm sắp xếp danh sách nhân viên theo mức lương tăng dần
// (Sử dụng thuật toán Sắp xếp chèn - Insertion Sort)
void DanhSach::sapXepTheoLuongTangDan(DanhSach &ds)
{
    for (int i = 0; i < n; i++)
    {
        // Lấy mức lương của nhân viên đang xét để làm mốc so sánh
        double luong = nv[i].getLuong();
        int j = i - 1;

        // Dịch chuyển các nhân viên có lương lớn hơn 'luong' về phía sau 1 vị trí
        while (j >= 0 && nv[j].getLuong() > luong)
        {
            nv[j + 1] = nv[j];
            j--;
        }
        // Chèn nhân viên đang xét (vị trí i ban đầu) vào đúng vị trí sau khi đã dịch chuyển
        nv[j + 1] = nv[i];
    }

    // Gọi đối tượng truyền vào để xuất danh sách sau khi đã sắp xếp xong
    ds.xuatDanhSach();
}