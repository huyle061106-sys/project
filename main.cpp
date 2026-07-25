#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

const int MAX_NHAN_VIEN = 100;
const double SO_NGAY_CONG_CHUAN = 26.0;

// ==================== HAM HO TRO ====================

string chuyenThanhChuThuong(string s) {
    for (int i = 0; i < (int)s.length(); i++) {
        s[i] = (char)tolower(s[i]);
    }
    return s;
}

string nhapChuoiKhongRong(string thongBao) {
    string s;

    do {
        cout << thongBao;
        getline(cin, s);

        if (s.length() == 0) {
            cout << "Loi! Khong duoc de trong. Vui long nhap lai.\n";
        }
    } while (s.length() == 0);

    return s;
}

int nhapSoNguyen(string thongBao, int minValue, int maxValue) {
    int x;
    bool hopLe;

    do {
        hopLe = true;
        cout << thongBao;
        cin >> x;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Loi! Vui long nhap so nguyen.\n";
            hopLe = false;
        } else {
            cin.ignore(1000, '\n');

            if (x < minValue || x > maxValue) {
                cout << "Loi! Gia tri phai tu "
                     << minValue << " den " << maxValue << ".\n";
                hopLe = false;
            }
        }
    } while (hopLe == false);

    return x;
}

double nhapSoThucKhongAm(string thongBao) {
    double x;
    bool hopLe;

    do {
        hopLe = true;
        cout << thongBao;
        cin >> x;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Loi! Vui long nhap so.\n";
            hopLe = false;
        } else {
            cin.ignore(1000, '\n');

            if (x < 0) {
                cout << "Loi! Gia tri khong duoc am.\n";
                hopLe = false;
            }
        }
    } while (hopLe == false);

    return x;
}

// ==================== CLASS NHAN VIEN ====================

class NhanVien {
private:
    string id;
    string hoTen;
    string phongBan;

    int loaiNhanVien;       // 1: Manager, 2: Engineer
    double luongCoBan;
    int soNgayCong;

    double bonusRate;       // Chi dung cho Manager
    double overtimeHours;   // Chi dung cho Engineer
    double overtimeRate;    // Chi dung cho Engineer

    double phuCap;
    double khauTru;
    double tongLuong;

public:
    // Constructor mac dinh
    NhanVien() {
        id = "";
        hoTen = "";
        phongBan = "";
        loaiNhanVien = 1;
        luongCoBan = 0;
        soNgayCong = 0;
        bonusRate = 0;
        overtimeHours = 0;
        overtimeRate = 0;
        phuCap = 0;
        khauTru = 0;
        tongLuong = 0;
    }

    // Constructor co tham so, dung de tao du lieu mau
    NhanVien(string idMoi, string tenMoi, string phongBanMoi,
             int loaiMoi, double luongMoi, int ngayCongMoi,
             double bonusMoi, double gioTangCaMoi,
             double tienTangCaMoi, double phuCapMoi,
             double khauTruMoi) {
        id = idMoi;
        hoTen = tenMoi;
        phongBan = phongBanMoi;
        loaiNhanVien = loaiMoi;
        luongCoBan = luongMoi;
        soNgayCong = ngayCongMoi;
        bonusRate = bonusMoi;
        overtimeHours = gioTangCaMoi;
        overtimeRate = tienTangCaMoi;
        phuCap = phuCapMoi;
        khauTru = khauTruMoi;
        tongLuong = tinhLuong();
    }

    // Cac ham getter can thiet
    string getID() {
        return id;
    }

    string getHoTen() {
        return hoTen;
    }

    string getPhongBan() {
        return phongBan;
    }

    int getLoaiNhanVien() {
        return loaiNhanVien;
    }

    double getLuongCoBan() {
        return luongCoBan;
    }

    int getSoNgayCong() {
        return soNgayCong;
    }

    double getBonusRate() {
        return bonusRate;
    }

    double getOvertimeHours() {
        return overtimeHours;
    }

    double getOvertimeRate() {
        return overtimeRate;
    }

    double getPhuCap() {
        return phuCap;
    }

    double getKhauTru() {
        return khauTru;
    }

    string tenLoaiNhanVien() {
        if (loaiNhanVien == 1) {
            return "Manager";
        }
        return "Engineer";
    }

    void nhapThongTin(string idMoi) {
        id = idMoi;
        hoTen = nhapChuoiKhongRong("Nhap ho ten: ");
        phongBan = nhapChuoiKhongRong("Nhap phong ban: ");

        cout << "Loai nhan vien:\n";
        cout << "1. Manager\n";
        cout << "2. Engineer\n";
        loaiNhanVien = nhapSoNguyen("Nhap loai nhan vien: ", 1, 2);

        luongCoBan = nhapSoThucKhongAm("Nhap luong co ban: ");
        soNgayCong = nhapSoNguyen("Nhap so ngay cong (0-26): ", 0, 26);
        phuCap = nhapSoThucKhongAm("Nhap phu cap: ");
        khauTru = nhapSoThucKhongAm("Nhap khau tru: ");

        bonusRate = 0;
        overtimeHours = 0;
        overtimeRate = 0;

        if (loaiNhanVien == 1) {
            bonusRate = nhapSoThucKhongAm(
                "Nhap ti le thuong (vi du 0.2 = 20%): ");
        } else {
            overtimeHours = nhapSoThucKhongAm("Nhap so gio tang ca: ");
            overtimeRate = nhapSoThucKhongAm("Nhap tien tang ca moi gio: ");
        }

        tongLuong = tinhLuong();
    }

    void capNhatThongTin() {
        cout << "ID hien tai: " << id << "\n";
        cout << "Ban se cap nhat cac thong tin khac, khong doi ID.\n";

        hoTen = nhapChuoiKhongRong("Nhap ho ten moi: ");
        phongBan = nhapChuoiKhongRong("Nhap phong ban moi: ");

        cout << "Loai nhan vien:\n";
        cout << "1. Manager\n";
        cout << "2. Engineer\n";
        loaiNhanVien = nhapSoNguyen("Nhap loai nhan vien moi: ", 1, 2);

        luongCoBan = nhapSoThucKhongAm("Nhap luong co ban moi: ");
        soNgayCong = nhapSoNguyen("Nhap so ngay cong moi (0-26): ", 0, 26);
        phuCap = nhapSoThucKhongAm("Nhap phu cap moi: ");
        khauTru = nhapSoThucKhongAm("Nhap khau tru moi: ");

        bonusRate = 0;
        overtimeHours = 0;
        overtimeRate = 0;

        if (loaiNhanVien == 1) {
            bonusRate = nhapSoThucKhongAm("Nhap ti le thuong moi: ");
        } else {
            overtimeHours = nhapSoThucKhongAm("Nhap so gio tang ca moi: ");
            overtimeRate = nhapSoThucKhongAm(
                "Nhap tien tang ca moi gio moi: ");
        }

        tongLuong = tinhLuong();
    }

    double tinhLuong() {
        double luongTheoNgayCong;

        luongTheoNgayCong =
            (luongCoBan / SO_NGAY_CONG_CHUAN) * soNgayCong;

        tongLuong = luongTheoNgayCong + phuCap - khauTru;

        if (loaiNhanVien == 1) {
            tongLuong = tongLuong + luongCoBan * bonusRate;
        } else if (loaiNhanVien == 2) {
            tongLuong = tongLuong + overtimeHours * overtimeRate;
        }

        if (tongLuong < 0) {
            tongLuong = 0;
        }

        return tongLuong;
    }

    void hienThi() {
        tongLuong = tinhLuong();

        cout << left
             << setw(10) << id
             << setw(22) << hoTen
             << setw(15) << phongBan
             << setw(12) << tenLoaiNhanVien()
             << setw(14) << fixed << setprecision(0) << luongCoBan
             << setw(10) << soNgayCong
             << setw(14) << fixed << setprecision(0) << tongLuong
             << "\n";
    }

    void ghiVaoFile(ofstream &fileOut) {
        fileOut << id << "\n";
        fileOut << hoTen << "\n";
        fileOut << phongBan << "\n";
        fileOut << loaiNhanVien << "\n";
        fileOut << luongCoBan << "\n";
        fileOut << soNgayCong << "\n";
        fileOut << bonusRate << "\n";
        fileOut << overtimeHours << "\n";
        fileOut << overtimeRate << "\n";
        fileOut << phuCap << "\n";
        fileOut << khauTru << "\n";
    }

    bool docTuFile(ifstream &fileIn) {
        string line;

        if (!getline(fileIn, id)) {
            return false;
        }

        getline(fileIn, hoTen);
        getline(fileIn, phongBan);

        getline(fileIn, line);
        loaiNhanVien = atoi(line.c_str());

        getline(fileIn, line);
        luongCoBan = atof(line.c_str());

        getline(fileIn, line);
        soNgayCong = atoi(line.c_str());

        getline(fileIn, line);
        bonusRate = atof(line.c_str());

        getline(fileIn, line);
        overtimeHours = atof(line.c_str());

        getline(fileIn, line);
        overtimeRate = atof(line.c_str());

        getline(fileIn, line);
        phuCap = atof(line.c_str());

        getline(fileIn, line);
        khauTru = atof(line.c_str());

        tongLuong = tinhLuong();
        return true;
    }
};

// ==================== CLASS QUAN LY LUONG ====================

class QuanLyLuong {
private:
    NhanVien danhSach[MAX_NHAN_VIEN];
    int soLuong;

    void inTieuDeBang() {
        cout << left;
        cout << setw(10) << "ID"
             << setw(22) << "Ho ten"
             << setw(15) << "Phong ban"
             << setw(12) << "Loai"
             << setw(14) << "Luong CB"
             << setw(10) << "Ngay"
             << setw(14) << "Tong luong" << "\n";

        cout << string(97, '-') << "\n";
    }

    int timViTriTheoID(string id) {
        for (int i = 0; i < soLuong; i++) {
            if (danhSach[i].getID() == id) {
                return i;
            }
        }
        return -1;
    }

    bool kiemTraTrungID(string id) {
        if (timViTriTheoID(id) != -1) {
            return true;
        }
        return false;
    }

    void doiCho(NhanVien &a, NhanVien &b) {
        NhanVien tam = a;
        a = b;
        b = tam;
    }

public:
    QuanLyLuong() {
        soLuong = 0;
    }

    void themNhanVien() {
        if (soLuong >= MAX_NHAN_VIEN) {
            cout << "Danh sach da day. Khong the them moi.\n";
            return;
        }

        string id;

        do {
            id = nhapChuoiKhongRong("Nhap ID: ");

            if (kiemTraTrungID(id)) {
                cout << "Loi! ID da ton tai. Vui long nhap ID khac.\n";
            }
        } while (kiemTraTrungID(id));

        danhSach[soLuong].nhapThongTin(id);
        soLuong++;

        cout << "Them nhan vien thanh cong.\n";
    }

    void capNhatNhanVien() {
        string id = nhapChuoiKhongRong("Nhap ID can cap nhat: ");
        int viTri = timViTriTheoID(id);

        if (viTri == -1) {
            cout << "Khong tim thay nhan vien co ID nay.\n";
            return;
        }

        cout << "Thong tin hien tai:\n";
        inTieuDeBang();
        danhSach[viTri].hienThi();

        danhSach[viTri].capNhatThongTin();
        cout << "Cap nhat thanh cong.\n";
    }

    void xoaNhanVien() {
        string id = nhapChuoiKhongRong("Nhap ID can xoa: ");
        int viTri = timViTriTheoID(id);

        if (viTri == -1) {
            cout << "Khong tim thay nhan vien co ID nay.\n";
            return;
        }

        char xacNhan;
        cout << "Ban co chac muon xoa nhan vien "
             << danhSach[viTri].getHoTen() << "? (y/n): ";
        cin >> xacNhan;
        cin.ignore(1000, '\n');

        if (xacNhan == 'y' || xacNhan == 'Y') {
            for (int i = viTri; i < soLuong - 1; i++) {
                danhSach[i] = danhSach[i + 1];
            }

            soLuong--;
            cout << "Xoa thanh cong.\n";
        } else {
            cout << "Da huy thao tac xoa.\n";
        }
    }

    void timKiemNhanVien() {
        if (soLuong == 0) {
            cout << "Danh sach rong.\n";
            return;
        }

        cout << "\n1. Tim theo ID\n";
        cout << "2. Tim theo ten\n";
        cout << "3. Tim theo phong ban\n";
        int luaChon = nhapSoNguyen("Nhap lua chon: ", 1, 3);

        string tuKhoa = nhapChuoiKhongRong("Nhap tu khoa can tim: ");
        string tuKhoaThuong = chuyenThanhChuThuong(tuKhoa);
        bool timThay = false;

        inTieuDeBang();

        for (int i = 0; i < soLuong; i++) {
            bool dung = false;

            if (luaChon == 1 &&
                chuyenThanhChuThuong(danhSach[i].getID()) == tuKhoaThuong) {
                dung = true;
            } else if (luaChon == 2 &&
                       chuyenThanhChuThuong(danhSach[i].getHoTen()).find(
                           tuKhoaThuong) != string::npos) {
                dung = true;
            } else if (luaChon == 3 &&
                       chuyenThanhChuThuong(danhSach[i].getPhongBan()).find(
                           tuKhoaThuong) != string::npos) {
                dung = true;
            }

            if (dung == true) {
                danhSach[i].hienThi();
                timThay = true;
            }
        }

        if (timThay == false) {
            cout << "Khong tim thay ket qua phu hop.\n";
        }
    }

    void hienThiDanhSach() {
        if (soLuong == 0) {
            cout << "Danh sach rong.\n";
            return;
        }

        inTieuDeBang();

        for (int i = 0; i < soLuong; i++) {
            danhSach[i].hienThi();
        }
    }

   void xuatBangLuong() {
        if (soLuong == 0) {
            cout << "Danh sach rong.\n";
            return;
        }

        ofstream fileOut("bangluong.csv");
        fileOut << "\xEF\xBB\xBF";
        fileOut << "ID,Ho ten,Phong ban,Loai,Luong CB,Ngay cong,Tong luong\n";

        for (int i = 0; i < soLuong; i++) {
            fileOut << danhSach[i].getID() << ","
                    << danhSach[i].getHoTen() << ","
                    << danhSach[i].getPhongBan() << ","
                    << danhSach[i].tenLoaiNhanVien() << ","
                    << danhSach[i].getLuongCoBan() << ","
                    << danhSach[i].getSoNgayCong() << ","
                    << danhSach[i].tinhLuong() << "\n";
        }

        fileOut.close();
        cout << "Da xuat bang luong ra file bangluong.csv.\n";
    }


    void sapXepTheoTen() {
        for (int i = 0; i < soLuong - 1; i++) {
            for (int j = i + 1; j < soLuong; j++) {
                if (chuyenThanhChuThuong(danhSach[i].getHoTen()) >
                    chuyenThanhChuThuong(danhSach[j].getHoTen())) {
                    doiCho(danhSach[i], danhSach[j]);
                }
            }
        }

        cout << "Da sap xep theo ten.\n";
    }

    void sapXepTheoLuongGiamDan() {
        for (int i = 0; i < soLuong - 1; i++) {
            for (int j = i + 1; j < soLuong; j++) {
                if (danhSach[i].tinhLuong() < danhSach[j].tinhLuong()) {
                    doiCho(danhSach[i], danhSach[j]);
                }
            }
        }

        cout << "Da sap xep theo luong giam dan.\n";
    }

    void sapXepTheoPhongBan() {
        for (int i = 0; i < soLuong - 1; i++) {
            for (int j = i + 1; j < soLuong; j++) {
                if (chuyenThanhChuThuong(danhSach[i].getPhongBan()) >
                    chuyenThanhChuThuong(danhSach[j].getPhongBan())) {
                    doiCho(danhSach[i], danhSach[j]);
                }
            }
        }

        cout << "Da sap xep theo phong ban.\n";
    }

    void menuSapXep() {
        if (soLuong == 0) {
            cout << "Danh sach rong.\n";
            return;
        }

        cout << "\n1. Sap xep theo ten\n";
        cout << "2. Sap xep theo luong giam dan\n";
        cout << "3. Sap xep theo phong ban\n";

        int luaChon = nhapSoNguyen("Nhap lua chon: ", 1, 3);

        if (luaChon == 1) {
            sapXepTheoTen();
        } else if (luaChon == 2) {
            sapXepTheoLuongGiamDan();
        } else {
            sapXepTheoPhongBan();
        }
    }

    void thongKe() {
        if (soLuong == 0) {
            cout << "Danh sach rong.\n";
            return;
        }

        double tongLuong = 0;
        int viTriCaoNhat = 0;
        int viTriThapNhat = 0;

        for (int i = 0; i < soLuong; i++) {
            double luong = danhSach[i].tinhLuong();
            tongLuong = tongLuong + luong;

            if (luong > danhSach[viTriCaoNhat].tinhLuong()) {
                viTriCaoNhat = i;
            }

            if (luong < danhSach[viTriThapNhat].tinhLuong()) {
                viTriThapNhat = i;
            }
        }

        cout << fixed << setprecision(0);
        cout << "\n========== THONG KE ==========\n";
        cout << "Tong so nhan vien: " << soLuong << "\n";
        cout << "Tong quy luong: " << tongLuong << "\n";
        cout << "Luong trung binh: " << tongLuong / soLuong << "\n";

        cout << "\nNhan vien co luong cao nhat:\n";
        inTieuDeBang();
        danhSach[viTriCaoNhat].hienThi();

        cout << "\nNhan vien co luong thap nhat:\n";
        inTieuDeBang();
        danhSach[viTriThapNhat].hienThi();
    }

    void luuFile() {
        ofstream fileOut("employees.txt");

        if (!fileOut) {
            cout << "Khong mo duoc file de ghi.\n";
            return;
        }

        fileOut << soLuong << "\n";

        for (int i = 0; i < soLuong; i++) {
            danhSach[i].ghiVaoFile(fileOut);
        }

        fileOut.close();
        cout << "Da luu du lieu vao file employees.txt.\n";
    }

    void docFile() {
        ifstream fileIn("employees.txt");

        if (!fileIn) {
            cout << "Khong tim thay file employees.txt.\n";
            return;
        }

        string line;
        int soLuongTrongFile = 0;

        if (getline(fileIn, line)) {
            soLuongTrongFile = atoi(line.c_str());
        }

        soLuong = 0;

        while (soLuong < soLuongTrongFile &&
               soLuong < MAX_NHAN_VIEN) {
            NhanVien nv;

            if (nv.docTuFile(fileIn) == false) {
                break;
            }

            danhSach[soLuong] = nv;
            soLuong++;
        }

        fileIn.close();
        cout << "Da doc du lieu tu file employees.txt.\n";
    }

    void themDuLieuMau() {
        if (soLuong + 4 > MAX_NHAN_VIEN) {
            cout << "Khong du bo nho de them du lieu mau.\n";
            return;
        }

        NhanVien a(
            "E001", "Nguyen Van An", "HR", 1,
            15000000, 26, 0.2, 0, 0, 1000000, 500000);

        NhanVien b(
            "E002", "Tran Thi Binh", "IT", 2,
            12000000, 25, 0, 12, 80000, 700000, 300000);

        NhanVien c(
            "E003", "Le Minh Chau", "Accounting", 1,
            18000000, 24, 0.15, 0, 0, 1200000, 700000);

        NhanVien d(
            "E004", "Pham Quoc Dung", "IT", 2,
            14000000, 26, 0, 20, 90000, 800000, 400000);

        if (kiemTraTrungID(a.getID()) == false) {
            danhSach[soLuong] = a;
            soLuong++;
        }

        if (kiemTraTrungID(b.getID()) == false) {
            danhSach[soLuong] = b;
            soLuong++;
        }

        if (kiemTraTrungID(c.getID()) == false) {
            danhSach[soLuong] = c;
            soLuong++;
        }

        if (kiemTraTrungID(d.getID()) == false) {
            danhSach[soLuong] = d;
            soLuong++;
        }

        cout << "Da them du lieu mau.\n";
    }

    void hienThiMenu() {
        cout << "\n====================================\n";
        cout << "    PAYROLL MANAGEMENT SYSTEM OOP\n";
        cout << "====================================\n";
        cout << "1. Them nhan vien\n";
        cout << "2. Cap nhat nhan vien\n";
        cout << "3. Xoa nhan vien\n";
        cout << "4. Tim kiem nhan vien\n";
        cout << "5. Hien thi danh sach\n";
        cout << "6. Xuat bang luong\n";
        cout << "7. Sap xep danh sach\n";
        cout << "8. Thong ke\n";
        cout << "9. Luu file\n";
        cout << "10. Doc file\n";
        cout << "11. Them du lieu mau\n";
        cout << "0. Thoat\n";
        cout << "====================================\n";
    }

    void chayChuongTrinh() {
        int luaChon;

        do {
            hienThiMenu();
            luaChon = nhapSoNguyen("Nhap lua chon: ", 0, 11);

            if (luaChon == 1) {
                themNhanVien();
            } else if (luaChon == 2) {
                capNhatNhanVien();
            } else if (luaChon == 3) {
                xoaNhanVien();
            } else if (luaChon == 4) {
                timKiemNhanVien();
            } else if (luaChon == 5) {
                hienThiDanhSach();
            } else if (luaChon == 6) {
                xuatBangLuong();
            } else if (luaChon == 7) {
                menuSapXep();
            } else if (luaChon == 8) {
                thongKe();
            } else if (luaChon == 9) {
                luuFile();
            } else if (luaChon == 10) {
                docFile();
            } else if (luaChon == 11) {
                themDuLieuMau();
            } else if (luaChon == 0) {
                cout << "Cam on ban da su dung chuong trinh.\n";
            }
        } while (luaChon != 0);
    }
};

int main() {
  string tentaikhoan;
	string matkhau;
	
    QuanLyLuong chuongTrinh;
    do{ 
    cout <<"Moi nhap ten tai khoan: ";
    cin >> tentaikhoan;
    cout << "Moi nhap mat khau: ";
    cin >> matkhau;
    if(tentaikhoan == "huy" && matkhau == "061106"){
    	chuongTrinh.chayChuongTrinh();
    	
	}
	else{
		cout <<"Sai ten tai khoan hoac mat khau! Moi nhap lai: \n";
	}
	}
    
    while(tentaikhoan != "huy" || matkhau != "061106");
    	
	
    
    

    return 0;
}

