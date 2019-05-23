#include <iostream>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#define max 10

using namespace std;
    
struct KA{   
    string id;
    string nama;
    string tujuan;
	string berangkat;
	string tiba;
	string kelas;
	float harga;
	int kursi;
};

struct Tumpuk{
    int top;
    struct KA idKA[max];
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

void input(string nama, string tujuan, string berangkat, string tiba, string kelas, float harga, int kursi)
{
	if(kosong() == 1 || penuh() == 0)
	{
		T.top++;
		T.idKA[T.top].id = T.top;
		T.idKA[T.top].nama = nama;
		T.idKA[T.top].tujuan = tujuan;
		T.idKA[T.top].berangkat = berangkat;
		T.idKA[T.top].tiba = tiba;
		T.idKA[T.top].kelas = kelas;
		T.idKA[T.top].harga = harga;
		T.idKA[T.top].kursi = kursi;
		cout << "\nJadwal kereta api " << T.idKA[T.top].nama << " berhasil diinput!\n" << endl;
	}
	else
		cout << "Jadwal sudah melewati batas maksimum!";
}

void hapus()
{
	if(kosong() == 0)
	{
		cout << "Jadwal kereta " << T.idKA[T.top].nama << " berhasil dihapus !" << endl;
		T.top--;
	}
	else
		cout << "Tidak ada jadwal kereta api!\n\n";
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
			cout << T.idKA[i].nama << "\t\t" << T.idKA[i].tujuan << "\t\t" << T.idKA[i].berangkat << "\t\t" << T.idKA[i].tiba << "\t\t";
			cout << T.idKA[i].kelas << "\t\t" << T.idKA[i].harga << "\t\t" << T.idKA[i].kursi << endl;
		}
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	}
	else
		cout << "Tidak ada jadwal kereta api!\n\n";
}

void bersih()
{
	T.top = -1;
	cout << "Semua jadwal berhasil dibersihkan !" << endl;
}

void pembuka(string user)
{
	system("cls");
	cout << "Login berhasil !" << endl;
	cout << "Selamat datang di aplikasi KAI Access. Anda login sebagai " << user << "\n\n";
	cout << "Menu yang tersedia :";
}

void sorting()
{
	struct Temp_KA
	{
		string id;
    	string nama;
    	string tujuan;
		string berangkat;
		string tiba;
		string kelas;
		float harga;
		int kursi;
	};

	struct Temp_Tumpuk
	{
		int top;
    	struct Temp_KA TidKA[max];
	} TE;

	TE.top = -1;
	for(int i=0; i <= T.top; i++)
	{
		TE.top++;
		TE.TidKA[i].id = T.idKA[i].id;
		TE.TidKA[i].nama = T.idKA[i].nama;
		TE.TidKA[i].tujuan = T.idKA[i].tujuan;
		TE.TidKA[i].berangkat = T.idKA[i].berangkat;
		TE.TidKA[i].tiba = T.idKA[i].tiba;
		TE.TidKA[i].kelas = T.idKA[i].kelas;
		TE.TidKA[i].harga = T.idKA[i].harga;
		TE.TidKA[i].kursi = T.idKA[i].kursi;
	}

	int pil;
	cout << "\nUrutkan berdasarkan : ";
	cout << "\n[1] Keberangkatan Terpagi\n[2] Harga Termurah\n\nPilihan anda : "; cin >> pil;
	int index[max];
	for(int i=0; i <= T.top; i++)
	{
		index[i] = i;
	}

	if(pil == 1)
	{
		for(int i=1; i <= T.top; i++)
		{
			for(int j=0; j <= T.top - i; j++)
			{
				if(TE.TidKA[j].berangkat < TE.TidKA[j + 1].berangkat)
				{
					int temp;
					temp = index[j];
					index[j] = index[j+1];
					index[j+1] = temp;
				}
			}
			
		}
		for(int i=T.top; i >= 0; i--)
		{
			cout << TE.TidKA[index[i]].berangkat << endl;
		}
	}
	/*else if(pil == 2)
	{
		for(int i=1; i < TE.top; i++)
		{
			for(int j=0; j <= TE.top - i; j++)
			{
				if(TE.TidKA[j].harga < TE.TidKA[j + 1].harga)
				{
					int temp;
					temp = index[j];
					index[j] = index[j+1];
					index[j+1] = temp;
				}
			}
		}
	}
	else
	{
		cout << "Angka yang anda input tidal valid !" << endl;
	}

	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\tJADWAL KEBERANGKATAN KERETA API" << endl;
	cout << "\t\t\t\t\tSTASIUN BESAR YOGYAKARTA (TUGU)" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\nKereta Api/ID\t\tTujuan\t\tBerangkat\tTiba\t\tKelas\t\tHarga (Rp)\tKursi\n" << endl;
	for(int i=T.top; i >= 0 ; i--)
	{
			cout << TE.TidKA[index[i]].nama << "\t\t" << TE.TidKA[index[i]].tujuan << "\t\t" << TE.TidKA[index[i]].berangkat << "\t\t" << TE.TidKA[index[i]].tiba << "\t\t";
			cout << TE.TidKA[index[i]].kelas << "\t\t" << TE.TidKA[index[i]].harga << "\t\t" << TE.TidKA[index[i]].kursi << endl;
	}
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	*/
}

void searching()
{
	string tujuan;
	int j=0;
	int index[max];

	cout << "\nMasukkan stasiun tujuan : ";
	cin >> tujuan;
	
	for(int i=0; i <= T.top; i++)
	{
		if(T.idKA[i].tujuan == tujuan)
		{
			index[j] = i;
			j++;
		}
	}
	if(j > 0)
	{
		cout << "Terdapat " << j << " jadwal keberangkatan ke " << tujuan << "\n\n";
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\t\t\t\t\tJADWAL KEBERANGKATAN KERETA API" << endl;
		cout << "\t\t\t\t\tSTASIUN BESAR YOGYAKARTA (TUGU)" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\nKereta Api/ID\t\tTujuan\t\tBerangkat\tTiba\t\tKelas\t\tHarga (Rp)\tKursi\n" << endl;
		for(int i=0; i < j ; i++)
		{
			cout << T.idKA[index[i]].nama << "\t\t" << T.idKA[index[i]].tujuan << "\t\t" << T.idKA[index[i]].berangkat << "\t\t" << T.idKA[index[i]].tiba << "\t\t";
			cout << T.idKA[index[i]].kelas << "\t\t" << T.idKA[index[i]].harga << "\t\t" << T.idKA[index[i]].kursi << endl;
		}
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	}
	else
	{
		cout << "\nTidak ada jadwal keberangkatan kereta api ke " << tujuan << " !" << endl;
	}
}

void login();
void admin()
{	
	pembuka("admin");
	awal();
	int pil, kursi;
	string namaka, tujuan, berangkat, tiba, kelas;
	float harga;
	do
	{
		cout << "\n1. Input Jadwal\n2. Hapus Jadwal Teratas\n3. Tampilkan Jadwal\n4. Reset Jadwal\n";
		cout << "5. Sorting Jadwal\n6. Cari Jadwal\n7. Logout\n8. Keluar\n\nMasukkan pilihan : ";
		cin >> pil;

		switch(pil)
		{
			case 1 :
				cout << "Lengkapi data berikut !" << endl;
				cout << "-----------------------------------------------\n";
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
				hapus();
				break;
			case 3 :
				tampil();
				break;
			case 4 :
				bersih();
				break;
			case 5 :
				sorting();
				break;
			case 6 :
				searching();
				break;
			case 7 :
				login();
				break;
			default :
				cout << "Terimakasih telah menggunakan layanan KAI Access\n";
				exit(0);
		}
	} while(pil != 8 && pil > 0 && pil < 9);
}

void other()
{
	pembuka("user");
	int pil;
	do
	{
		cout << "\n1. Cari Jadwal\n2. Sorting Jadwal\n3. Booking\n";
		cout << "4. Logout\n5. Keluar\n\nMasukkan pilihan : ";
		cin >> pil;

		switch(pil)
		{
			case 1 :
				searching();
				break;
			case 2 :
			case 3 :
				
				break;
			case 4 :
				login();
				break;
			default :
				cout << "Terimakasih telah menggunakan layanan KAI Access\n";
				exit(0);
		}
	} while(pil != 5 && pil > 0 && pil < 6);
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
	SetConsoleTitle(TEXT("KAI ACCESS STASIUN TUGU YOGYAKARTA"));
	login();
	//getch();
	return 0;
}
