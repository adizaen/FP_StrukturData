#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <stdio.h>
#define max 10

using namespace std;

namespace KA {

	struct detail_KA {
		int* id = new int;
		string* nama = new string;
		string* tujuan = new string;
		string* berangkat = new string;
		string* tiba = new string;
		string* kelas = new string;
		float* harga = new float;
		int* kursi = new int;
	};

	struct stack_KA {
		int top;
		detail_KA* KAdet = new detail_KA[max];
	}KA;

	void awal() {
		KA.top = -1;
	}

	int kosong()
	{
		if (KA.top == -1)
			return 1;
		else
			return 0;
	}

	int penuh()
	{
		if (KA.top == max - 1)
			return 1;
		else
			return 0;
	}

	void input(string nama, string tujuan, string berangkat, string tiba, string kelas, float harga, int kursi)
	{
		if (kosong() == 1 || penuh() == 0)
		{
			KA.top++;
			*KA.KAdet[KA.top].id = KA.top;
			*KA.KAdet[KA.top].nama = nama;
			*KA.KAdet[KA.top].tujuan = tujuan;
			*KA.KAdet[KA.top].berangkat = berangkat;
			*KA.KAdet[KA.top].tiba = tiba;
			*KA.KAdet[KA.top].kelas = kelas;
			*KA.KAdet[KA.top].harga = harga;
			*KA.KAdet[KA.top].kursi = kursi;
			cout << "\nJadwal kereta api " << *KA.KAdet[KA.top].nama << " berhasil diinput!\n" << endl;
		}
		else
			cout << "Jadwal sudah melewati batas maksimum!";
	}

	int hapus()
	{
		if (kosong() == 0)
		{
			cout << "Jadwal kereta " << *KA.KAdet[KA.top].nama << " berhasil dihapus !" << endl;

			delete KA.KAdet[KA.top].id;
			delete KA.KAdet[KA.top].nama;
			delete KA.KAdet[KA.top].tujuan;
			delete KA.KAdet[KA.top].berangkat;
			delete KA.KAdet[KA.top].tiba;
			delete KA.KAdet[KA.top].kelas;
			delete KA.KAdet[KA.top].harga;
			delete KA.KAdet[KA.top].kursi;
			delete[KA.top] KA.KAdet;

			KA.top--;

			return 1;

			/* stack diakses dari indeks terbesar. gak ngaruh disini, tapi yah, gitu.
			// dibawah juga banyak yang sama.
			for (int i = B.top; i >= 0; i--)
			{
				if (B.dB[i].namaKA == T.idKA[T.top].nama)
				{
					B.dB[i].kode = "";
					B.dB[i].namaKA = "";
					B.dB[i].tujuan = "";
					B.dB[i].berangkat = "";
					B.dB[i].tiba = "";
					B.dB[i].kelas = "";
					for (int j = 0; j < 3; j++)
					{
						if (B.dB[i].nik[j] != "")
							B.dB[i].nik[j] = "";
						else
							continue;
					}
				}
			}*/
		}
		else
			return 0;

			cout << "Tidak ada jadwal kereta api!\n\n";
	}

	void tampil()
	{
		if (kosong() == 0)
		{
			cout << "-------------------------------------------------------------------------------------------------------------" << endl;
			cout << "\t\t\t\t\tJADWAL KEBERANGKATAN KERETA API" << endl;
			cout << "\t\t\t\t\tSTASIUN BESAR YOGYAKARTA (TUGU)" << endl;
			cout << "-------------------------------------------------------------------------------------------------------------" << endl;
			cout << "\nKereta Api/ID\t\tTujuan\t\tBerangkat\tTiba\t\tKelas\t\tHarga (Rp)\tKursi\n" << endl;
			for (int i = KA.top; i >= 0; i--)
			{
				cout << *KA.KAdet[KA.top].nama << "\t\t" << *KA.KAdet[KA.top].tujuan << "\t\t" << *KA.KAdet[KA.top].berangkat << "\t\t" << *KA.KAdet[KA.top].tiba << "\t\t";
				cout << *KA.KAdet[KA.top].kelas << "\t\t" << *KA.KAdet[KA.top].harga << "\t\t" << *KA.KAdet[KA.top].kursi << endl;
			}
			cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		}
		else
			cout << "Tidak ada jadwal kereta api!\n\n";
	}

	void bersih()
	{
		// pakai aja fungsi hapus yang sudah ada.
		for (int i = KA.top; i >= 0; i--) {
			hapus();
		}
		cout << "Semua jadwal berhasil dibersihkan !" << endl;
	}

	// fungsi pencarian data berdasarkan stasiun tujuan
	void searching()
	{
		string tujuan;
		int j = 0;
		int index[max];

		cout << "\nMasukkan stasiun tujuan : ";
		cin >> tujuan;

		for (int i = KA::KA.top; i >= 0; i--)
		{
			if (*KA::KA.KAdet[i].tujuan == tujuan)
			{
				index[j] = i;
				j++;
			}
		}
		if (j > 0)
		{
			cout << "Terdapat " << j << " jadwal keberangkatan ke " << tujuan << "\n\n";
			cout << "------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "\t\t\t\t\tJADWAL KEBERANGKATAN KERETA API" << endl;
			cout << "\t\t\t\t\tSTASIUN BESAR YOGYAKARTA (TUGU)" << endl;
			cout << "------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "\nKereta Api/ID\t\tTujuan\t\tBerangkat\tTiba\t\tKelas\t\tHarga (Rp)\tKursi\n" << endl;
			for (int i = 0; i < j; i++)
			{
				cout << *KA::KA.KAdet[index[i]].nama << "\t\t" << *KA::KA.KAdet[index[i]].tujuan << "\t\t" << *KA::KA.KAdet[index[i]].berangkat << "\t\t" << *KA::KA.KAdet[index[i]].tiba << "\t\t";
				cout << *KA::KA.KAdet[index[i]].kelas << "\t\t" << *KA::KA.KAdet[index[i]].harga << "\t\t" << *KA::KA.KAdet[index[i]].kursi << endl;
			}
			cout << "------------------------------------------------------------------------------------------------------------------" << endl;
		}
		else
		{
			cout << "\nTidak ada jadwal keberangkatan kereta api ke " << tujuan << " !" << endl;
		}
	}

	// fungsi untuk sorting berdasarkan harga termurah dan berangkat terpagi di struct sementara/temporary sturct
	void sorting(int pil)
	{
		//tidak perlu deklarasi ulang stuct, buat aja objek struct baru
		stack_KA Temp_KA;

		// copy data dari struct utama ke temporary struct/struct sementara
		Temp_KA.top = -1;
		for (int i = 0; i <= KA.top; i++)
		{
			Temp_KA.top++;
			*Temp_KA.KAdet[i].id = *KA.KAdet[i].id;
			*Temp_KA.KAdet[i].nama = *KA.KAdet[i].nama;
			*Temp_KA.KAdet[i].tujuan = *KA.KAdet[i].tujuan;
			*Temp_KA.KAdet[i].berangkat = *KA.KAdet[i].berangkat;
			*Temp_KA.KAdet[i].tiba = *KA.KAdet[i].tiba;
			*Temp_KA.KAdet[i].kelas = *KA.KAdet[i].kelas;
			*Temp_KA.KAdet[i].harga = *KA.KAdet[i].harga;
			*Temp_KA.KAdet[i].kursi = *KA.KAdet[i].kursi;
		}

		string nama[max], tujuan[max], berangkat[max], tiba[max], kelas[max];
		float harga[max];
		int kursi[max];

		if (pil == 1)
		{
			for (int i = 1; i <= KA.top; i++)
			{
				for (int j = 0; j <= KA.top - i; j++)
				{
					// sorting berdasarkan keberangkatan terpagi
					// jadwal paling pagi diletakan paling atas( dari atas kebawah )
					if (Temp_KA.KAdet[j].berangkat < Temp_KA.KAdet[j + 1].berangkat)
					{
						// proses pertukaran data
						nama[j] = *Temp_KA.KAdet[j].nama;
						tujuan[j] = *Temp_KA.KAdet[j].tujuan;
						berangkat[j] = *Temp_KA.KAdet[j].berangkat;
						tiba[j] = *Temp_KA.KAdet[j].tiba;
						kelas[j] = *Temp_KA.KAdet[j].kelas;
						harga[j] = *Temp_KA.KAdet[j].harga;
						kursi[j] = *Temp_KA.KAdet[j].kursi;

						*Temp_KA.KAdet[j].nama = *Temp_KA.KAdet[j + 1].nama;
						*Temp_KA.KAdet[j].tujuan = *Temp_KA.KAdet[j + 1].tujuan;
						*Temp_KA.KAdet[j].berangkat = *Temp_KA.KAdet[j + 1].berangkat;
						*Temp_KA.KAdet[j].tiba = *Temp_KA.KAdet[j + 1].tiba;
						*Temp_KA.KAdet[j].kelas = *Temp_KA.KAdet[j + 1].kelas;
						*Temp_KA.KAdet[j].harga = *Temp_KA.KAdet[j + 1].harga;
						*Temp_KA.KAdet[j].kursi = *Temp_KA.KAdet[j + 1].kursi;

						*Temp_KA.KAdet[j + 1].nama = nama[j];
						*Temp_KA.KAdet[j + 1].tujuan = tujuan[j];
						*Temp_KA.KAdet[j + 1].berangkat = berangkat[j];
						*Temp_KA.KAdet[j + 1].tiba = tiba[j];
						*Temp_KA.KAdet[j + 1].kelas = kelas[j];
						*Temp_KA.KAdet[j + 1].harga = harga[j];
						*Temp_KA.KAdet[j + 1].kursi = kursi[j];
					}
				}
			}
		}
		else if (pil == 2)
		{
			for (int i = 1; i <= KA.top; i++)
			{
				for (int j = 0; j <= KA.top - i; j++)
				{
					// sorting berdasarkan harga termurah
					if (*Temp_KA.KAdet[j].harga < *Temp_KA.KAdet[j + 1].harga)
					{
						nama[j] = *Temp_KA.KAdet[j].nama;
						tujuan[j] = *Temp_KA.KAdet[j].tujuan;
						berangkat[j] = *Temp_KA.KAdet[j].berangkat;
						tiba[j] = *Temp_KA.KAdet[j].tiba;
						kelas[j] = *Temp_KA.KAdet[j].kelas;
						harga[j] = *Temp_KA.KAdet[j].harga;
						kursi[j] = *Temp_KA.KAdet[j].kursi;

						*Temp_KA.KAdet[j].nama = *Temp_KA.KAdet[j + 1].nama;
						*Temp_KA.KAdet[j].tujuan = *Temp_KA.KAdet[j + 1].tujuan;
						*Temp_KA.KAdet[j].berangkat = *Temp_KA.KAdet[j + 1].berangkat;
						*Temp_KA.KAdet[j].tiba = *Temp_KA.KAdet[j + 1].tiba;
						*Temp_KA.KAdet[j].kelas = *Temp_KA.KAdet[j + 1].kelas;
						*Temp_KA.KAdet[j].harga = *Temp_KA.KAdet[j + 1].harga;
						*Temp_KA.KAdet[j].kursi = *Temp_KA.KAdet[j + 1].kursi;

						*Temp_KA.KAdet[j + 1].nama = nama[j];
						*Temp_KA.KAdet[j + 1].tujuan = tujuan[j];
						*Temp_KA.KAdet[j + 1].berangkat = berangkat[j];
						*Temp_KA.KAdet[j + 1].tiba = tiba[j];
						*Temp_KA.KAdet[j + 1].kelas = kelas[j];
						*Temp_KA.KAdet[j + 1].harga = harga[j];
						*Temp_KA.KAdet[j + 1].kursi = kursi[j];
					}
				}
			}
		}
		else
		{
			cout << "Angka yang anda input tidak valid !" << endl;
		}

		// menampilkan hasil sorting
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\t\t\t\t\tJADWAL KEBERANGKATAN KERETA API" << endl;
		cout << "\t\t\t\t\tSTASIUN BESAR YOGYAKARTA (TUGU)" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\nKereta Api/ID\t\tTujuan\t\tBerangkat\tTiba\t\tKelas\t\tHarga (Rp)\tKursi\n" << endl;
		for (int i = KA.top; i >= 0; i--)
		{
			cout << *Temp_KA.KAdet[i].nama << "\t\t" << *Temp_KA.KAdet[i].tujuan << "\t\t" << *Temp_KA.KAdet[i].berangkat << "\t\t" << *Temp_KA.KAdet[i].tiba << "\t\t";
			cout << *Temp_KA.KAdet[i].kelas << "\t\t" << *Temp_KA.KAdet[i].harga << "\t\t" << *Temp_KA.KAdet[i].kursi << endl;
		}
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	}
}

