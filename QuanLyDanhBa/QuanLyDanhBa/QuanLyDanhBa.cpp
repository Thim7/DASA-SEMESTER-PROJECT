﻿#include<iostream>
#include <stdio.h>
#include <string>
using namespace std;

struct DATE {
	int day;
	int month;
	int year;
};

struct SDT {
	int sdt;
	//int maQuocGia;
	string loai;
};

struct DIACHI { //Danh sách liên kết đơn
	string tinh;
	string nuoc;
	DIACHI* next;
};

struct NHOM { //Lưu theo danh sách liên kết đơn
	string ten;
	NHOM* next;
};

struct DATA {
	SDT  SDT;
	string ten;
	NHOM nhom;
	string gioiTinh;
	DIACHI diachi;
	DATE ngaysinh;
	string email;
	string ghiChu;
};

struct CONTACT { //Cây nhị phân tìm kiếm
	DATA data;
	CONTACT* right;
	CONTACT* left;
};
typedef CONTACT* TREE;

//Hàm tách 3 số đầu của số điện thoại
int tachSoDau(int sdt) {
	int dem = 1;
	while (dem <= 7) {
		sdt /= 10;
		dem++;
	}
	return sdt;
}

//Hàm nhập thông điện thoại
void inputPhoneNumber(SDT& dt) {
	/*cout << "\tNhập mã nước: ";
	cin >> dt.maQuocGia;*/
	cout << "\t\tNhap so dien thoai: ";
	cin >> dt.sdt;
	int soDau = tachSoDau(dt.sdt); //Biến để tạm lưu số điện thoại
	if (soDau == 86 || soDau == 96 || soDau == 97 || soDau == 98 || soDau == 32 || soDau == 33 || soDau == 34 || soDau == 35
		|| soDau == 36 || soDau == 37 || soDau == 38 || soDau == 39)
		dt.loai = "Viettel";
	else if (soDau == 88 || soDau == 91 || soDau == 94 || soDau == 83 || soDau == 84 || soDau == 85 || soDau == 81 || soDau == 82)
		dt.loai = "Vinaphone";
	else if (soDau == 89 || soDau == 90 || soDau == 93 || soDau == 70 || soDau == 79 || soDau == 77 || soDau == 76 || soDau == 78)
		dt.loai = "Mobiphone";
	else if (soDau == 92 || soDau == 56 || soDau == 58)
		dt.loai = "Vietnammobile";
}

//Hàm nhập ngày sinh
void inputDateBirth(DATE& date) {
	cout << "\t\tNhap ngay sinh: ";
	cin >> date.day;
	cout << "\t\tNhap thang sinh: ";
	cin >> date.month;
	cout << "\t\tNhap nam sinh: ";
	cin >> date.year;
}
 
//Hàm nhập địa chỉ
void inputAddress(DIACHI& diaChi) {
	while (getchar() != '\n');
	cout << "\t\tTinh: ";
	getline(cin, diaChi.tinh);
}

//Hàm nhập thông tin DATA
void inputDATA(DATA& x) {
	while (getchar() != '\n');
	cout << "\t\tNhap ten: ";
	getline(cin, x.ten);
	cout << "\t\tGioi tinh: ";
	getline(cin, x.gioiTinh);
	inputPhoneNumber(x.SDT);
	inputAddress(x.diachi);
	inputDateBirth(x.ngaysinh);
	while (getchar() != '\n');
	string ktMail;
	do {
		cout << "\t\tBan co muon nhap email <y/n>?";
		getline(cin, ktMail);
		if (ktMail == "y") {
			cout << "\t\tEmail: ";
			getline(cin, x.email);
			break;
		}
		else {
			x.email = "";
			break;
		}
	} while (ktMail == "y" || ktMail == "n");
	string ktNote;
	do {
		cout << "\t\tBan co them ghi chu <y/n>?";
		getline(cin, ktNote);
		if (ktMail == "y") {
			cout << "\t\tGhi chu: ";
			getline(cin, x.ghiChu);
			break;
		}
		else {
			x.ghiChu = "";
			break;
		}
	} while (ktNote == "y" || ktNote == "n");
}

//Hàm thêm data
void insertData(TREE &contact, DATA data) {
	if (contact == NULL) { //Nếu cây rỗng
		CONTACT* p = new CONTACT;
		p->data = data;
		p->left = NULL;
		p->right = NULL;
		contact = p; //Thêm node p vào cây
	}
	else {
		if (contact->data.SDT.sdt < data.SDT.sdt) {
			insertData(contact->right, data);
		}
		else {
			insertData(contact->left, data);
		}
	}
}

//Hàm xuất thông tin
void printDATA(DATA data) {
	cout << "\n\t\tTen: " << data.ten;
	cout << "\n\t\tSo dien thoai: 0" << data.SDT.sdt;
	cout << "\n\t\tNha mang: " << data.SDT.loai;
	cout << "\n\t\tGioi tinh: " << data.gioiTinh;
	cout << "\n\t\tDia chi: tinh " << data.diachi.tinh;
	cout << "\n\t\tNgay sinh: " << data.ngaysinh.day << "/" << data.ngaysinh.month << "/" << data.ngaysinh.year;
	if (data.email != "")
		cout << "\n\t\tEmail: " << data.email;
	if (data.ghiChu != "")
		cout << "\n\t\tGhi chu: " << data.ghiChu;
	cout << "\n";
}

//Hàm duyệt data
void duyetContact(TREE contact) {
	if (contact != NULL) {
		printDATA(contact->data);
		duyetContact(contact->left);
		duyetContact(contact->right);
	}
}

void Menu(TREE& contact) {
	int luachon;
	while (true) {
		system("cls");
		cout << "\n\n\t\t::::::::::::::::::::::::::::QUAN LY DANH BA DIEN THOAI::::::::::::::::::::::::::::::::::";
		cout << "\n\n\t\t1. Them thong tin so dien thoai";
		cout << "\n\n\t\t2. Xoa thong tin so dien thoai";
		cout << "\n\n\t\t3. Xuat danh sach so dien thoai";
		cout << "\n\n\t\t:::::::::::::::::::::::::::::::::::::::END:::::::::::::::::::::::::::::::::::::::::::::::";

		cout << "\n\n\t\t\t Nhap luachon: ";
		cin >> luachon;

		if (luachon == 1) {
			DATA data;
			inputDATA(data);
			insertData(contact, data);
		}
		else if (luachon == 3) {
			duyetContact(contact);
			system("pause");
		}
		else {
			break;
		}

	}
}


int main() {
	TREE contact = NULL;
	Menu(contact);
}
