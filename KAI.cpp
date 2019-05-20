#include <iostream>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#define max 10
using namespace std;

struct Tumpuk
{
	int top;
	string namaka[max];
	string tujuan[max];
	string berangkat[max];
	string tiba[max];
	string kelas[max];
	float harga[max];
	int kursi[max];
}T;

void awal()
{
	T.top = -1;
}

int kosong()
{
	if(T.top == -1)
		return 1;
	else
		return 0;
}

int penuh()
{
	if(T.top == max - 1)
		return 1;
	else
		return 0;
}

void input(string namaka, string tujuan, string berangkat, string tiba, string kelas, float harga, int kursi)
{
	if(kosong() == 1 || penuh() == 0)
	{
		T.top++;
		T.namaka[T.top] = namaka;
		T.tujuan[T.top] = tujuan;
		T.berangkat[T.top] = berangkat;
		T.tiba[T.top] = tiba;
		T.kelas[T.top] = kelas;
		T.harga[T.top] = harga;
		T.kursi[T.top] = kursi;
		cout << "\nJadwal kereta api " << T.namaka[T.top] << " berhasil diinput!" << endl;
	}
	else
		cout << "Jadwal sudah melewati batas maksimum!";
}

void tampil()
{
	if(kosong() == 0)
	{
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\t\t\t\t\tJADWAL KEBERANGKATAN KERETA API" << endl;
		cout << "\t\t\t\t\tSTASIUN BESAR YOGYAKARTA (TUGU)" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\nKereta Api/ID\t\tTujuan\t\tBerangkat\tTiba\t\tKelas\t\tHarga (Rp)\tKursi\n" << endl;
		for(int i=T.top; i >= 0; i--)
		{
			cout << T.namaka[i] << "\t\t" << T.tujuan[i] << "\t\t" << T.berangkat[i] << "\t\t" << T.tiba[i] << "\t\t";
			cout << T.kelas[i] << "\t\t" << T.harga[i] << "\t\t" << T.kursi[i] << endl;
		}
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	}
	else
		cout << "Tidak ada jadwal kereta api!\n\n";
}

void pembuka(string user)
{
	system("cls");
	cout << "Login berhasil !" << endl;
	cout << "Selamat datang di aplikasi KAI Access. Anda login sebagai " << user << endl;
	cout << "Menu yang tersedia :" << endl;
}

void admin()
{	
	pembuka("admin");
	awal();
	int pil, kursi;
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
				cout << "Ketersediaan Kursi          : "; cin >> kursi;
				input(namaka, tujuan, berangkat, tiba, kelas, harga, kursi);
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
}

void other()
{

}

void login()
{
	char pil;
	string username, password;
	do
	{
		system("cls");
		cout << "--------------------------------------" << endl;
		cout << "\t\tKAI ACCESS" << endl;
		cout << "\tSTASIUN TUGU YOGYAKARTA YK" << endl;
		cout << "--------------------------------------" << endl;
		cout << "Isi username dan password untuk login !" << endl;
		cout << "Username    : "; cin >> username;
		cout << "Password    : "; cin >> password;
		if(username == "admin" && password == "admin")
		{
			admin();
			break;
		}
		else if(username == "amikom" && password == "amikom")
		{
			other();
			break;
		}
		else
		{
			cout << "Maaf, username/password salah ! Login ulang ? [Y/N] : "; cin >> pil;
			if(pil == 'Y' || pil == 'y')
				continue;
			else
			{
				cout << "Terimakasih telah menggunakan layanan KAI Access" << endl;
				break;
			}
		}	
	} while(pil == 'y' || pil == 'Y');
}

int main()
{
	login();
	return 0;
}
