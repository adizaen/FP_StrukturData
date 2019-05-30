#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <stdio.h>
#define max 10
#include "KA.h"

using namespace std;

namespace Booking {

	struct detail_Booking
	{
		string* kode = new string;
		string* namaKA = new string;
		string* tujuan = new string;
		string* berangkat = new string;
		string* tiba = new string;
		string* kelas = new string;
		string* nik = new string[3];
		string* nama = new string[3];
	};

	struct stack_Booking
	{
		int top;
		detail_Booking Bookdet[100];
		// 100 karena 1 kereta maksimal 10 kursi. sedangkan stack bisa menampung 10 kereta. 10*10 = 100
	}Book;

	// fungsi non void untuk mengacak huruf dan angka sebagai kode booking

	string kode_booking() {
		string kode;
		char letter;
		int posisi = Book.top;
		for (int angka = posisi; angka < posisi + 1; angka++)
		{
			for (int i = 0; i < 1; i++)
			{
				if (angka % 2 != 0 && angka <= 50)
				{
					if (angka <= 25)
					{
						letter = 'R';
					}
					else
					{
						letter = 'T';
					}
					kode = static_cast<char>(letter) + to_string(angka + 1) + static_cast<char>(letter + 2) + static_cast<char>(letter + 4) + to_string(angka + 13);
				}
				else if (angka % 2 == 0 && angka <= 50)
				{
					if (angka <= 25)
					{
						letter = 'S';
					}
					else
					{
						letter = 'P';
					}
					kode = static_cast<char>(letter) + to_string(angka + 3) + static_cast<char>(letter + 4) + static_cast<char>(letter + 7) + to_string(angka + 59);
				}
				else if (angka % 2 != 0 && angka > 50)
				{
					if (angka <= 75)
					{
						letter = 'M';
					}
					else
					{
						letter = 'K';
					}
					kode = static_cast<char>(letter) + to_string(angka + 1) + static_cast<char>(letter + 1) + static_cast<char>(letter + 3) + to_string(angka - 3);
				}
				else if (angka % 2 == 0 && angka > 50)
				{
					if (angka <= 25)
					{
						letter = 'J';
					}
					else
					{
						letter = 'G';
					}
					kode = static_cast<char>(letter) + to_string(angka + 3) + static_cast<char>(letter + 3) + static_cast<char>(letter + 6) + to_string(angka - 11);
				}
			}
		}
		return kode;
	}

	// fungsi pemesanan/booking
	void booking()
	{
		int pil, jumlah;
		system("cls");

		string tujuan, kode;
		int j = 0;
		int index[max];
		cout << "Masukkan stasiun tujuan : ";
		cin >> tujuan;

		for (int i = 0; i <= KA::KA.top; i++)
		{
			if (*KA::KA.KAdet[i].tujuan == tujuan)
			{
				index[j] = i;
				j++;
			}
		}
		if (j > 0)
		{
			cout << "\nTerdapat " << j << " jadwal keberangkatan ke " << tujuan << "\n\n";
			cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "\t\t\t\t\t\tJADWAL KEBERANGKATAN KERETA API" << endl;
			cout << "\t\t\t\t\t\tSTASIUN BESAR YOGYAKARTA (TUGU)" << endl;
			cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "\nNo\tKereta Api/ID\t\tTujuan\t\tBerangkat\tTiba\t\tKelas\t\tHarga (Rp)\tKursi\n" << endl;
			for (int i = 0; i < j; i++)
			{
				cout << i + 1 << "\t" << *KA::KA.KAdet[index[i]].nama << "\t\t" << *KA::KA.KAdet[index[i]].tujuan << "\t\t" << *KA::KA.KAdet[index[i]].berangkat << "\t\t" << *KA::KA.KAdet[index[i]].tiba << "\t\t";
				cout << *KA::KA.KAdet[index[i]].kelas << "\t\t" << *KA::KA.KAdet[index[i]].harga << "\t\t" << *KA::KA.KAdet[index[i]].kursi << endl;
			}
			cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;

			do
			{
				cout << "\nNomor yang anda pilih : "; cin >> pil;
				if (pil < 1 || pil > j)
					cout << "Maaf, pilihan tidak valid !" << endl;
			} while (pil < 1 || pil > j);
			if (pil <= j && pil > 0)
			{
				cout << "\nAnda memilih kereta api " << *KA::KA.KAdet[index[pil - 1]].nama << " dengan tujuan " << *KA::KA.KAdet[index[pil - 1]].tujuan << endl;
				do
				{
					cout << "Jumlah kursi yang anda pesan [Max 3] : "; cin >> jumlah;
					if (jumlah > 0 && jumlah < 4 && jumlah <= *KA::KA.KAdet[index[pil - 1]].kursi)
					{
						Book.top++;
						cout << "\n";
						cout << "------------------------------------------------" << endl;
						cout << "\tFormulir Pemesanan Tiket KAI" << endl;
						cout << "------------------------------------------------" << endl;
						kode = kode_booking();
						cout << "\nKODE BOOKING " << kode;
						cout << endl;
						cout << "\nIdentitas Kereta Api" << endl;
						cout << "Nama Kereta      : " << *KA::KA.KAdet[index[pil - 1]].nama << endl;
						cout << "Stasiun Tujuan   : " << *KA::KA.KAdet[index[pil - 1]].tujuan << endl;
						cout << "Waktu Berangkat  : " << *KA::KA.KAdet[index[pil - 1]].berangkat << endl;
						cout << "Waktu Tiba       : " << *KA::KA.KAdet[index[pil - 1]].tiba << endl;
						cout << "Kelas            : " << *KA::KA.KAdet[index[pil - 1]].kelas << endl;
						cout << "------------------------------------------------" << endl;

						// proses input data dari struct utama ke struct khusus pemesanan
						*Book.Bookdet[Book.top].kode = kode;
						*Book.Bookdet[Book.top].namaKA = *KA::KA.KAdet[index[pil - 1]].nama;
						*Book.Bookdet[Book.top].tujuan = *KA::KA.KAdet[index[pil - 1]].tujuan;
						*Book.Bookdet[Book.top].berangkat = *KA::KA.KAdet[index[pil - 1]].berangkat;
						*Book.Bookdet[Book.top].tiba = *KA::KA.KAdet[index[pil - 1]].tiba;
						*Book.Bookdet[Book.top].kelas = *KA::KA.KAdet[index[pil - 1]].kelas;

						float total, bayar;
						for (int i = 0; i < jumlah; i++)
						{
							cout << "\nData Penumpang ke - " << i + 1 << endl;
							cout << "Masukkan NIK  : "; cin >> Book.Bookdet[Book.top].nik[i];
							cout << "Masukkan Nama : "; cin >> Book.Bookdet[Book.top].nama[i];
						}
						cout << "\n------------------------------------------------" << endl;
						cout << "Kursi dipesan : " << jumlah << endl;
						cout << "Harga/kursi   : Rp " << *KA::KA.KAdet[index[pil - 1]].harga << endl;
						total = jumlah * (*KA::KA.KAdet[index[pil - 1]].harga);
						cout << "Total bayar   : Rp " << total << endl;
						do
						{
							cout << "Dibayar       : Rp "; cin >> bayar;
							if (bayar < total)
								cout << "Maaf, uang yang dibayarkan tidak cukup !" << endl;
							else
							{
								cout << "Kembali       : Rp " << bayar - total << endl;
								cout << "\n------------------------------------------------" << endl;
								cout << "STATUS : Pemesanan tiket berhasil !" << endl;
								*KA::KA.KAdet[index[pil - 1]].kursi = *KA::KA.KAdet[index[pil - 1]].kursi - jumlah;
							}
						} while (bayar < total);
					}
					else if (jumlah > *KA::KA.KAdet[index[pil - 1]].kursi)
						cout << "Maaf, kursi yang tersisa sebanyak " << *KA::KA.KAdet[index[pil - 1]].kursi << " kursi" << endl;
					else if (jumlah > 3)
						cout << "Maaf, jumlah pemesanan tidak boleh lebih dari 3 kursi" << endl;
					else
						cout << "Maaf, nomor yang anda inputkan tidak valid !" << endl;
				} while (jumlah > 3 || jumlah <= 0);
			}
			else
				cout << "Maaf, tidak tersedia nomor " << pil << " pada jadwal !" << endl;
		}
		else
		{
			cout << "\nTidak ada jadwal keberangkatan kereta api ke " << tujuan << " !" << endl;
		}
	}

	// fungsi untuk menampilkan data pemesan dari kode booking tertentu
	void detail_booking()
	{
		string kode;
		int j = 0;
		int index[max];
		cout << "Masukkan kode booking : "; cin >> kode;

		for (int i = 0; i <= Book.top; i++)
		{
			if (*Book.Bookdet[i].kode == kode)
			{
				index[j] = i;
				j++;
			}
		}
		if (j > 0)
		{
			string nama;
			int l = 0;
			for (int i = 0; i < j; i++)
			{
				nama = *Book.Bookdet[index[i]].namaKA;
			}
			for (int k = 0; k <= KA::KA.top; k++)
			{
				if (*KA::KA.KAdet[k].nama == nama)
				{
					l++;
				}
			}
			if (l > 0)
			{
				cout << "----------------------------------------" << endl;
				cout << "\t\tData Tiket" << endl;
				cout << "----------------------------------------" << endl;
				cout << "\nKode Booking    : " << kode << endl;
				for (int i = 0; i < j; i++)
				{
					cout << "Nama Kereta     : " << *Book.Bookdet[index[i]].namaKA << endl;
					cout << "Stasiun Tujuan  : " << *Book.Bookdet[index[i]].tujuan << endl;
					cout << "Waktu Berangkat : " << *Book.Bookdet[index[i]].berangkat << endl;
					cout << "Waktu Tiba      : " << *Book.Bookdet[index[i]].tiba << endl;
					cout << "Kelas           : " << *Book.Bookdet[index[i]].kelas << endl;
					cout << "----------------------------------------" << endl;
					cout << "\nNo\tNIK\t\tNama\n" << endl;
					for (int j = 0; j < 3; j++)
					{
						if (Book.Bookdet[index[i]].nik[j] != "")
							cout << j + 1 << "\t" << Book.Bookdet[index[i]].nik[j] << "\t\t" << Book.Bookdet[index[i]].nama[j] << endl;
						else
							break;
					}
					cout << "----------------------------------------" << endl;
				}
			}
			else
			{
				cout << "Maaf, jadwal kereta " << nama << " sudah dihapus/telah selesai !" << endl;
			}
		}
		else
		{
			cout << "\nKode booking " << kode << " tidak ditemukan !" << endl;
		}
	}

}