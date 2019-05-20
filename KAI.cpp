#include <iostream>
#include <string.h>
#include <stdio.h>
#define max 10
using namespace std;

struct Tumpuk1
{
	int top;
	string namaka[max];
}T1;

struct Tumpuk2
{
	int top;
	string tujuan[max];
}T2;

struct Tumpuk3
{
	int top;
	string berangkat[max];
} T3;

struct Tumpuk4
{
	int top;
	string tiba[max];
} T4;

struct Tumpuk5
{
	int top;
	string kelas[max];
}T5;

struct Tumpuk6
{
	int top;
	float harga[max];
}T6;

void awal()
{
	T1.top = -1;
	T2.top = -1;
	T3.top = -1;
	T4.top = -1;
	T5.top = -1;
	T6.top = -1;
}

int kosong()
{
	if(T1.top == -1 && T2.top == -1 && T3.top == -1 && T4.top == -1 && T5.top == -1 && T6.top == -1)
		return 1;
	else
		return 0;
}

int penuh()
{
	if(T1.top == max - 1 && T2.top == max - 1 && T3.top == max - 1 && T4.top == max - 1 && T5.top == max - 1 && T6.top == max - 1)
		return 1;
	else
		return 0;
}

void input(string namaka, string tujuan, string berangkat, string tiba, string kelas, float harga)
{
	if(kosong() == 1 || penuh() == 0)
	{
		T1.top++;
		T2.top++;
		T3.top++;
		T4.top++;
		T5.top++;
		T6.top++;
		T1.namaka[T1.top] = namaka;
		T2.tujuan[T2.top] = tujuan;
		T3.berangkat[T3.top] = berangkat;
		T4.tiba[T3.top] = tiba;
		T5.kelas[T5.top] = kelas;
		T6.harga[T6.top] = harga;
		cout << "Jadwal kereta api " << T1.namaka[T1.top] << " berhasil diinput!" << endl;
	}
	else
		cout << "Jadwal sudah melewati batas maksimum!";
}

void tampil()
{
	if(kosong() == 0)
	{
		cout << "-------------------------------------------------------------------------------------------------------" << endl;
		cout << "\t\t\t\t\tJADWAL KEBERANGKATAN KERETA API" << endl;
		cout << "\t\t\t\t\tSTASIUN BESAR YOGYAKARTA ( TUGU )" << endl;
		cout << "-------------------------------------------------------------------------------------------------------" << endl;
		cout << "\nKereta Api/ID\t\tTujuan\t\tBerangkat\tTiba\t\tKelas\t\tHarga (Rp)\n" << endl;
		for(int i=T1.top; i >= 0; i--)
		{
			cout << T1.namaka[i] << "\t\t" << T2.tujuan[i] << "\t\t" << T3.berangkat[i] << "\t\t" << T4.tiba[i] << "\t\t";
			cout << T5.kelas[i] << "\t\t" << T6.harga[i] << endl;
		}
		cout << "-------------------------------------------------------------------------------------------------------" << endl;
	}
	else
		cout << "Tidak ada jadwal kereta api!";
}

void pembuka()
{
	system("cls");
	cout << "Selamat datang di aplikasi KAI Access." << endl;
	cout << "Menu yang tersedia :" << endl;
}

int main()
{
	pembuka();
	awal();
	int pil;
	string namaka, tujuan, berangkat, tiba, kelas;
	float harga;
	do
	{
		cout << "1. Input\n2. Hapus\n3. Tampil\n4. Bersihkan\n";
		cout << "5. Keluar\n\nMasukkan pilihan : ";
		cin >> pil;

		switch(pil)
		{
			case 1 :
				cout << "Lengkapi data berikut !" << endl;
				cout << "Nama KAI/ID                 : "; cin >> namaka;
				cout << "Stasiun Tujuan              : "; cin >> tujuan;
				cout << "Waktu Berangkat             : "; cin >> berangkat;
				cout << "Waktu Tiba                  : "; cin >> tiba;
				cout << "Jenis Kelas [ EKS/BUS/EKO ] : "; cin >> kelas;
				cout << "Harga                       : Rp "; cin >> harga;
				input(namaka, tujuan, berangkat, tiba, kelas, harga);
				break;
			case 2 :
			case 3 :
				tampil();
				break;
			case 4 :
			default :
				cout << "Terimakasih telah menggunakan layanan KAI Access";
		}
	} while(pil != 5);

	return 0;
}
