#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <stdio.h>
#include "KA.h"
#include "Booking.h"

using namespace std;

// tulisan pembuka setelah pengguna login di aplikasi
// ada 2 user yaitu admin dan user biasa
void pembuka(string user)
{
	system("cls");
	cout << "Login berhasil !" << endl;
	cout << "Selamat datang di aplikasi KAI Access. Anda login sebagai " << user << "\n\n";
	cout << "Menu yang tersedia :";
}

void data_penumpang()
{
	if(KA::kosong() == 0)
	{
		cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\t\t\t\t\tJADWAL KEBERANGKATAN KERETA API" << endl;
		cout << "\t\t\t\t\tSTASIUN BESAR YOGYAKARTA (TUGU)" << endl;
		cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\nNo.\tKereta Api/ID\t\tTujuan\t\tBerangkat\tTiba\t\tKelas\t\tHarga (Rp)\tKursi\n" << endl;
		for(int i=0; i <= KA::KA.top; i++)
		{
			cout << i+1 << "\t" << *KA::KA.KAdet[i].nama << "\t\t" << *KA::KA.KAdet[i].tujuan << "\t\t" << *KA::KA.KAdet[i].berangkat << "\t\t" << *KA::KA.KAdet[i].tiba << "\t\t";
			cout << *KA::KA.KAdet[i].kelas << "\t\t" << *KA::KA.KAdet[i].harga << "\t\t" << *KA::KA.KAdet[i].kursi << endl;
		}
		cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
		int pil;
		cout << "\nPilihan anda : "; cin >> pil;
		if(pil > 0 && pil <= KA::KA.top + 1)
		{
			int j=0;
			int index[max];
			for(int i=0; i <= Booking::Book.top; i++)
			{
				if(*Booking::Book.Bookdet[i].namaKA == *KA::KA.KAdet[pil - 1].nama)
				{
					index[j] = i;
					j++;
				}
			}
			if(j > 0)
			{
				cout << "-------------------------------------" << endl;
				cout << "\tData Penumpang" << endl;
				cout << "-------------------------------------" << endl;
				cout << "\nNama Kereta   : " << *KA::KA.KAdet[pil - 1].nama << endl;
				cout << "Tujuan        : " << *KA::KA.KAdet[pil - 1].tujuan << endl;
				cout << "Berangkat     : " << *KA::KA.KAdet[pil - 1].berangkat << endl;
				cout << "Tiba          : " << *KA::KA.KAdet[pil - 1].tiba << endl;
				cout << "-------------------------------------" << endl;
				cout << "\nNIK\t\tNama\n" << endl;
				for(int i=0; i < j; i++)
				{
					for(int k=0; k < 3; k++)
					{
						if(Booking::Book.Bookdet[index[i]].nik[k] != "")
							cout << Booking::Book.Bookdet[index[i]].nik[k] << "\t\t" << Booking::Book.Bookdet[index[i]].nama[k] << endl;
						else
							continue;
					}
				}
				cout << "-------------------------------------" << endl;
			}
			else
				cout << "Tidak ada data penumpang untuk kereta api " << *KA::KA.KAdet[pil - 1].nama << endl;
		}
		else
			cout << "Maaf, angka yang anda inputkan tidak valid !" << endl;
	}
	else
		cout << "Maaf, tidak ada jadwal keberangkatan kereta api !" << endl;
}

void batalkan_pemesanan()
{
	if(Booking::Book.top != -1)
	{
		string kode;
		char pil;
		int k = 0;
		cout << "\nMasukkan kode booking : "; cin >> kode;
		for(int i=0; i <= Booking::Book.top; i++)
		{
			if(*Booking::Book.Bookdet[i].kode == kode)
			{
				k++;
				cout << "Kode booking " << kode << ", Pemesanan tiket kereta api " << *Booking::Book.Bookdet[i].namaKA << " dengan tujuan " << *Booking::Book.Bookdet[i].tujuan << "." << endl;
				cout << "Apakah anda yakin ingin membatalkan pesanan [Y/N] : "; cin >> pil;
				if(pil == 'y' || pil == 'Y')
				{
					/*for(int i=0; i <= T.top; i++)
					{
						if(T.idKA[i].nama == B.dB[i].namaKA && T.idKA[i].kelas == B.dB[i].kelas)
						{
							int jumlah = 0;
							for(int j=0; j < 3; j++)
							{
								if(B.dB[i].nik[j] != "")
								{
									jumlah++;
								}
							}
							T.idKA[i].kursi = T.idKA[i].kursi + jumlah;
						}
					}*/

					for(int i=0; i <= KA::KA.top; i++)
					{
						for(int k=0; k <= Booking::Book.top; k++)
						{
							if(*KA::KA.KAdet[i].nama == *Booking::Book.Bookdet[k].namaKA && *KA::KA.KAdet[i].kelas == *Booking::Book.Bookdet[k].kelas && *Booking::Book.Bookdet[k].kode == kode)
							{
								int jumlah = 0;
								for(int j=0; j < 3; j++)
								{
									if(Booking::Book.Bookdet[k].nik[j] != "")
									{
										jumlah++;
									}
								}
								*KA::KA.KAdet[i].kursi = *(KA::KA.KAdet[i].kursi) + jumlah;
							}
						}
					}

					*Booking::Book.Bookdet[i].kode = "";
					*Booking::Book.Bookdet[i].namaKA = "";
					*Booking::Book.Bookdet[i].tujuan = "";
					*Booking::Book.Bookdet[i].berangkat = "";
					*Booking::Book.Bookdet[i].tiba = "";
					*Booking::Book.Bookdet[i].kelas = "";
					for(int j=0; j < 3; j++)
					{
						if(Booking::Book.Bookdet[i].nik[j] != "")
						{
							Booking::Book.Bookdet[i].nik[j] = "";
						}
						else
						{
							continue;
						}
					}
					cout << "Pemesanan tiket berhasil dibatalkan !" << endl;
				}
				else
				{
					cout << "Pembatalan tiket gagal !" << endl;
					break;
				}
			}
		}
		if(k == 0)
		{
			cout << "Maaf, kode booking " << kode << " tidak ditemukan !" << endl; 
		}
	}
	else
	{
		cout << "Maaf, tidak ada riwayat pemesanan di KAI access" << endl;
	}
}

void admin()
{	
	pembuka("admin");
	int pil, kursi;
	string namaka, tujuan, berangkat, tiba, kelas;
	float harga;
	do
	{
		cout << "\n1. Input Jadwal\n2. Hapus Jadwal Teratas\n3. Tampilkan Jadwal\n4. Reset Jadwal\n";
		cout << "5. Sorting Jadwal\n6. Cari Jadwal\n7. Daftar Penumpang\n8. Logout\n9. Keluar\n\nMasukkan pilihan : ";
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
				do
				{
					cout << "Ketersediaan Kursi [Max 10] : "; cin >> kursi;
					if(kursi > 10)
						cout << "Maaf, jumlah kursi tidak boleh lebih dari 10 kursi" << endl;
					else if(kursi < 1)
						cout << "Maaf, minimal 1 kursi" << endl;
					else
						KA::input(namaka, tujuan, berangkat, tiba, kelas, harga, kursi);
				} while(kursi > 10 || kursi < 1);
				break;
			case 2 :
				KA::hapus();
				break;
			case 3 :
				KA::tampil();
				break;
			case 4 :
				KA::bersih();
				break;
			case 5 :
				int pilih;
				cout << "\nUrutkan berdasarkan : ";
				cout << "\n[1] Keberangkatan Terpagi\n[2] Harga Termurah\n\nPilihan anda : "; cin >> pilih;
				KA::sorting(pilih);
				break;
			case 6 :
				KA::searching();
				break;
			case 7 :
				data_penumpang();
				break;
			case 8 :
				login();
				break;
			case 9 :
				cout << "Terimakasih telah menggunakan layanan KAI Access\n";
				exit(0);
			default :
				cout << "Maaf, angka yang anda inputkan tidak valid !" << endl;
		}
	} while(pil != 8);
}

void other()
{
	pembuka("user");
	int pil;
	do
	{
		cout << "\n1. Cari Jadwal\n2. Pemesanan\n3. Lihat Data Pemesanan\n";
		cout << "4. Batalkan Pemesanan\n5. Logout\n6. Keluar\n\nMasukkan pilihan : ";
		cin >> pil;

		switch(pil)
		{
			case 1 :
				KA::searching();
				break;
			case 2 :
				Booking::booking();
				break;
			case 3 :
				Booking::detail_booking();
				break;
			case 4 :
				batalkan_pemesanan();
				break;
			case 5 :
				login();
				break;
			case 6 :
				cout << "Terimakasih telah menggunakan layanan KAI Access\n";
				exit(0);
			default :
				cout << "Maaf, angka yang anda inputkan tidak valid !" << endl;
		}
	} while(pil != 5);
}

// fungsi login 
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
	KA::awal();
	Booking::Book.top = -1;
	SetConsoleTitle(TEXT("KAI ACCESS STASIUN TUGU YOGYAKARTA"));
	login();
	return 0;
}
