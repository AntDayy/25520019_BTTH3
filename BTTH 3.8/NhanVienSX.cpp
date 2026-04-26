#include "NhanVienSX.h"
#include <iostream>
#include <limits>

using namespace std;

// Hàm hỗ trợ nhập số nguyên an toàn, chống trôi lệnh hoặc lỗi luồng nhập
// Nhận vào một chuỗi thông báo lỗi (error) và trả về số nguyên hợp lệ người dùng nhập.
int kiemTraNhap(const string &error)
{
    int val;
    // Vòng lặp vô hạn, chỉ thoát ra (break) khi người dùng nhập đúng định dạng số nguyên
    while (1)
    {
        cout << error;
        // Kiểm tra xem việc đọc dữ liệu vào biến 'val' có thành công hay không (có phải là số không)
        if (cin >> val)
        {
            // Kiểm tra kí tự tiếp theo trong bộ đệm. Nếu là phím Enter ('\n'), nghĩa là nhập chuẩn.
            if (cin.peek() == '\n')
                break; // Nhập đúng số nguyên, thoát vòng lặp
        }
        else
        {
            // Nếu người dùng nhập sai (ví dụ: nhập chữ thay vì số), báo lỗi
            cout << "[!] Loi. Vui long nhap lai!\n";
            cin.clear(); // Xóa trạng thái lỗi của đối tượng cin để có thể nhập tiếp
            // Bỏ qua tất cả các kí tự còn kẹt lại trong bộ đệm cho đến khi gặp kí tự xuống dòng ('\n')
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return val;
}

// Hàm kiểm tra năm nhuận (chia hết cho 400 hoặc chia hết cho 4 nhưng không chia hết cho 100)
bool laNamNhuan(int nam)
{
    return (nam % 400 == 0) || (nam % 4 == 0 && nam % 100 != 0);
}

// Hàm trả về số ngày tối đa trong một tháng của một năm cụ thể
int soNgayTrongThang(int thang, int nam)
{
    switch (thang)
    {
    // Các tháng có 31 ngày
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    // Các tháng có 30 ngày
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    // Tháng 2 phụ thuộc vào năm nhuận
    case 2:
        return laNamNhuan(nam) ? 29 : 28;
    // Nếu nhập sai tháng (không nằm trong 1-12)
    default:
        return 0;
    }
}

// Hàm kiểm tra tính hợp lệ của một mốc thời gian (ngày, tháng, năm)
bool kiemTraNgayHopLe(int ngay, int thang, int nam)
{
    // Năm phải là số dương, tháng phải từ 1 đến 12
    if (nam <= 0 || thang < 1 || thang > 12)
        return false;
    // Ngày không được nhỏ hơn 1 và không được vượt quá số ngày tối đa của tháng đó
    if (ngay < 1 || ngay > soNgayTrongThang(thang, nam))
        return false;

    return true; // Nếu qua được hết các điều kiện trên thì ngày hợp lệ
}

// Constructor (Hàm tạo) mặc định: Tự động gán giá trị mặc định khi khởi tạo 1 đối tượng
NhanVienSX::NhanVienSX()
{
    this->maNV = 0;
    this->hoTen = "";
    this->ngaySinh = 1;
    this->thangSinh = 1;
    this->namSinh = 0;
    this->soSP = 0;
    this->luong = 0;
}

// Constructor có tham số: Giúp khởi tạo nhanh thông tin nhân viên ngay lúc khai báo
NhanVienSX::NhanVienSX(int maNV, string hoTen, int ngay, int thang, int nam, int soSP, double luong)
{
    this->maNV = maNV;
    this->hoTen = hoTen;
    this->ngaySinh = ngay;
    this->thangSinh = thang;
    this->namSinh = nam;
    this->soSP = soSP;
    this->luong = luong;
}

// Destructor (Hàm hủy): Dọn dẹp bộ nhớ khi đối tượng bị hủy.
// Do class không có con trỏ cấp phát động nên để rỗng.
NhanVienSX::~NhanVienSX() {}

// Phương thức nhập thông tin cho 1 nhân viên từ bàn phím
void NhanVienSX::Nhap()
{
    // Lặp nhập mã nhân viên cho đến khi lớn hơn hoặc bằng 0
    while (1)
    {
        maNV = kiemTraNhap("Nhap ma nhan vien: ");

        if (maNV < 0)
            cout << "[!] Loi. Ma nhan vien khong duoc nho hon khong. Vui long nhap lai!\n";
        else
            break;
    }

    // Nhập họ tên nhân viên
    cout << "Nhap ten nhan vien: ";
    cin.ignore();        // Xóa kí tự '\n' còn kẹt lại sau khi nhập mã nhân viên bằng cin
    getline(cin, hoTen); // Dùng getline để đọc được chuỗi có chứa khoảng trắng

    // Lặp nhập ngày tháng năm sinh cho đến khi tạo thành 1 ngày hợp lệ
    while (1)
    {
        ngaySinh = kiemTraNhap("Nhap ngay sinh: ");
        thangSinh = kiemTraNhap("Nhap thang sinh: ");
        namSinh = kiemTraNhap("Nhap nam sinh: ");

        if (!kiemTraNgayHopLe(ngaySinh, thangSinh, namSinh))
            cout << "[!] Loi. Ngay sinh khong hop le. Vui long nhap lai!\n";
        else
            break;
    }

    // Lặp nhập số sản phẩm cho đến khi lớn hơn hoặc bằng 0
    while (1)
    {
        soSP = kiemTraNhap("Nhap so san pham: ");

        if (soSP < 0)
            cout << "[!] Loi. So san pham khong duoc nho hon khong. Vui long nhap lai!\n";
        else
            break;
    }
}

// Phương thức in thông tin của nhân viên ra màn hình, phân cách bằng tab (\t)
void NhanVienSX::Xuat()
{
    cout << maNV << "\t" << hoTen << "\t" << ngaySinh << "/" << thangSinh << "/" << namSinh << "\t" << soSP << "\t" << luong << endl;
}

// Cập nhật (set) lương cho nhân viên
void NhanVienSX::setLuong(double luong)
{
    this->luong = luong;
}

// Lấy (get) tiền lương của nhân viên
double NhanVienSX::getLuong()
{
    return luong;
}

// Lấy (get) số sản phẩm nhân viên đã làm được
int NhanVienSX::getSP()
{
    return soSP;
}

// Lấy (get) thông tin ngày sinh
int NhanVienSX::getNgay()
{
    return ngaySinh;
}

// Lấy (get) thông tin tháng sinh
int NhanVienSX::getThang()
{
    return thangSinh;
}

// Lấy (get) thông tin năm sinh
int NhanVienSX::getNam()
{
    return namSinh;
}