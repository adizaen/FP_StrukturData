#include <iostream>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <stdio.h>
#define max 10

using namespace std;
    
// daftar rangkaian kereta api
struct KA{   
	int id;
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

// menyiapkan struct untuk pertama kali
void awal()
{
	T.top = -1;
}

// cek struct dalam kondisi kosong atau tidak
int kosong()
{
	if(T.top == -1)
		return 1;
	else
		return 0;
}

// cek struct dalam kondisi penuh atau tidak
int penuh()
{
	if(T.top == max - 1)
		return 1;
	else
		return 0;
}

// input data kedalam struct
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

// nested struct dimana booking sebagai parent dan detail_booking sebagai child
// struct ini digunakan untuk tumpukan data pemesanan tiket
struct detail_booking
{
	string kode;
	string namaKA;
	string tujuan;
	string berangkat;
	string tiba;
	string kelas;
	string nik[3];
	string nama[3];
};

struct booking
{
	int top;
	struct detail_booking dB[100];
	// 100 karena 1 kereta maksimal 10 kursi. sedangkan stack bisa menampung 10 kereta. 10*10 = 100
} B;

// menghapus data teratas di dalam struct
void hapus()
{
	if(kosong() == 0)
	{
		cout << "Jadwal kereta " << T.idKA[T.top].nama << " berhasil dihapus !" << endl;
		T.top--;
		
		// stack diakses dari indeks terbesar. gak ngaruh disini, tapi yah, gitu.
		// dibawah juga banyak yang sama.
		for(int i = B.top; i >= 0; i--)
		{
			if(B.dB[i].namaKA == T.idKA[T.top].nama)
			{
				B.dB[i].kode = "";
				B.dB[i].namaKA = "";
				B.dB[i].tujuan = "";
				B.dB[i].berangkat = "";
				B.dB[i].tiba = "";
				B.dB[i].kelas = "";
				for(int j=0; j < 3; j++)
				{
					if(B.dB[i].nik[j] != "")
						B.dB[i].nik[j] = "";
					else
						continue;
				}
			}
		}
	}
	else
		cout << "Tidak ada jadwal kereta api!\n\n";
}

// menampilkan data didalam struct
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

// mengosongkan struct/reset struct
void bersih()
{
	// pakai aja fungsi hapus yang sudah ada.
	for(int i = T.top; i >= 0; i--){
		hapus();
		T.top--;
	}
	cout << "Semua jadwal berhasil dibersihkan !" << endl;
}

// fungsi untuk sorting berdasarkan harga termurah dan berangkat terpagi di struct sementara/temporary sturct
void sorting(int pil)
{
	struct Temp_KA
	{
		int id;
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

	// copy data dari struct utama ke temporary struct/struct sementara
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

	string nama[max], tujuan[max], berangkat[max], tiba[max], kelas[max];
	float harga[max];
	int kursi[max];

	if(pil == 1)
	{
		for(int i=1; i <= T.top; i++)
		{
			for(int j=0; j <= T.top-i; j++)
			{
				// sorting berdasarkan keberangkatan terpagi
				// jadwal paling pagi diletakan paling atas( dari atas kebawah )
				if(TE.TidKA[j].berangkat < TE.TidKA[j + 1].berangkat)
				{
					// proses pertukaran data
					nama[j] = TE.TidKA[j].nama;
					tujuan[j] = TE.TidKA[j].tujuan;
					berangkat[j] = TE.TidKA[j].berangkat;
					tiba[j] = TE.TidKA[j].tiba;
					kelas[j] = TE.TidKA[j].kelas;
					harga[j] = TE.TidKA[j].harga;
					kursi[j] = TE.TidKA[j].kursi;

					TE.TidKA[j].nama = TE.TidKA[j+1].nama;
					TE.TidKA[j].tujuan = TE.TidKA[j+1].tujuan;
					TE.TidKA[j].berangkat = TE.TidKA[j+1].berangkat;
					TE.TidKA[j].tiba = TE.TidKA[j+1].tiba;
					TE.TidKA[j].kelas = TE.TidKA[j+1].kelas;
					TE.TidKA[j].harga = TE.TidKA[j+1].harga;
					TE.TidKA[j].kursi = TE.TidKA[j+1].kursi;

					TE.TidKA[j+1].nama = nama[j];
					TE.TidKA[j+1].tujuan = tujuan[j];
					TE.TidKA[j+1].berangkat = berangkat[j];
					TE.TidKA[j+1].tiba = tiba[j];
					TE.TidKA[j+1].kelas = kelas[j];
					TE.TidKA[j+1].harga = harga[j];
					TE.TidKA[j+1].kursi = kursi[j];
				}
			}
		}
	}
	else if(pil == 2)
	{
		for(int i=1; i <= T.top; i++)
		{
			for(int j=0; j <= T.top-i; j++)
			{
				// sorting berdasarkan harga termurah
				if(TE.TidKA[j].harga < TE.TidKA[j + 1].harga)
				{
					nama[j] = TE.TidKA[j].nama;
					tujuan[j] = TE.TidKA[j].tujuan;
					berangkat[j] = TE.TidKA[j].berangkat;
					tiba[j] = TE.TidKA[j].tiba;
					kelas[j] = TE.TidKA[j].kelas;
					harga[j] = TE.TidKA[j].harga;
					kursi[j] = TE.TidKA[j].kursi;

					TE.TidKA[j].nama = TE.TidKA[j+1].nama;
					TE.TidKA[j].tujuan = TE.TidKA[j+1].tujuan;
					TE.TidKA[j].berangkat = TE.TidKA[j+1].berangkat;
					TE.TidKA[j].tiba = TE.TidKA[j+1].tiba;
					TE.TidKA[j].kelas = TE.TidKA[j+1].kelas;
					TE.TidKA[j].harga = TE.TidKA[j+1].harga;
					TE.TidKA[j].kursi = TE.TidKA[j+1].kursi;

					TE.TidKA[j+1].nama = nama[j];
					TE.TidKA[j+1].tujuan = tujuan[j];
					TE.TidKA[j+1].berangkat = berangkat[j];
					TE.TidKA[j+1].tiba = tiba[j];
					TE.TidKA[j+1].kelas = kelas[j];
					TE.TidKA[j+1].harga = harga[j];
					TE.TidKA[j+1].kursi = kursi[j];
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
	for(int i=T.top; i >= 0 ; i--)
	{
			cout << TE.TidKA[i].nama << "\t\t" << TE.TidKA[i].tujuan << "\t\t" << TE.TidKA[i].berangkat << "\t\t" << TE.TidKA[i].tiba << "\t\t";
			cout << TE.TidKA[i].kelas << "\t\t" << TE.TidKA[i].harga << "\t\t" << TE.TidKA[i].kursi << endl;
	}
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	
}

// fungsi pencarian data berdasarkan stasiun tujuan
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
		cout << "------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\t\t\t\t\tJADWAL KEBERANGKATAN KERETA API" << endl;
		cout << "\t\t\t\t\tSTASIUN BESAR YOGYAKARTA (TUGU)" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\nKereta Api/ID\t\tTujuan\t\tBerangkat\tTiba\t\tKelas\t\tHarga (Rp)\tKursi\n" << endl;
		for(int i=0; i < j ; i++)
		{
			cout << T.idKA[index[i]].nama << "\t\t" << T.idKA[index[i]].tujuan << "\t\t" << T.idKA[index[i]].berangkat << "\t\t" << T.idKA[index[i]].tiba << "\t\t";
			cout << T.idKA[index[i]].kelas << "\t\t" << T.idKA[index[i]].harga << "\t\t" << T.idKA[index[i]].kursi << endl;
		}
		cout << "------------------------------------------------------------------------------------------------------------------" << endl;
	}
	else
	{
		cout << "\nTidak ada jadwal keberangkatan kereta api ke " << tujuan << " !" << endl;
	}
}

// tulisan pembuka setelah pengguna login di aplikasi
// ada 2 user yaitu admin dan user biasa
void pembuka(string user)
{
	system("cls");
	cout << "Login berhasil !" << endl;
	cout << "Selamat datang di aplikasi KAI Access. Anda login sebagai " << user << "\n\n";
	cout << "Menu yang tersedia :";
}

// fungsi non void untuk mengacak huruf dan angka sebagai kode booking
string kode_booking()
{
	string kode;
	char letter;
	int posisi = B.top;
	for(int angka = posisi; angka < posisi + 1; angka++)
	{
		for(int i=0; i < 1; i++)
		{
			if(angka % 2 != 0 && angka <= 50)
			{
				if(angka <= 25)
				{
					letter = 'R';
				}
				else
				{
					letter = 'T';
				}
				kode = static_cast<char>(letter) + to_string(angka + 1) + static_cast<char>(letter + 2) + static_cast<char>(letter + 4) + to_string(angka + 13);
			}
			else if(angka % 2 == 0 && angka <= 50)
			{
				if(angka <= 25)
				{
					letter = 'S';
				}
				else
				{
					letter = 'P';
				}
				kode = static_cast<char>(letter) + to_string(angka + 3) + static_cast<char>(letter + 4) + static_cast<char>(letter + 7) + to_string(angka + 59);
			}	
			else if(angka % 2 != 0 && angka > 50)
			{
				if(angka <= 75)
				{
					letter = 'M';
				}
				else
				{
					letter = 'K';
				}
				kode = static_cast<char>(letter) + to_string(angka + 1) + static_cast<char>(letter + 1) + static_cast<char>(letter + 3) + to_string(angka - 3);
			}
			else if(angka % 2 == 0 && angka > 50)
			{
				if(angka <= 25)
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
	int j=0;
	int index[max];
	cout << "Masukkan stasiun tujuan : ";
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
		cout << "\nTerdapat " << j << " jadwal keberangkatan ke " << tujuan << "\n\n";
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\t\t\t\t\t\tJADWAL KEBERANGKATAN KERETA API" << endl;
		cout << "\t\t\t\t\t\tSTASIUN BESAR YOGYAKARTA (TUGU)" << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\nNo\tKereta Api/ID\t\tTujuan\t\tBerangkat\tTiba\t\tKelas\t\tHarga (Rp)\tKursi\n" << endl;
		for(int i=0; i < j ; i++)
		{
			cout << i+1 << "\t" << T.idKA[index[i]].nama << "\t\t" << T.idKA[index[i]].tujuan << "\t\t" << T.idKA[index[i]].berangkat << "\t\t" << T.idKA[index[i]].tiba << "\t\t";
			cout << T.idKA[index[i]].kelas << "\t\t" << T.idKA[index[i]].harga << "\t\t" << T.idKA[index[i]].kursi << endl;
		}
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		
		do
		{
			cout << "\nNomor yang anda pilih : "; cin >> pil;
			if(pil < 1 || pil > j)
				cout << "Maaf, pilihan tidak valid !" << endl;
		} while(pil < 1 || pil > j);
		if(pil <= j && pil > 0)
		{
			cout << "\nAnda memilih kereta api " << T.idKA[index[pil - 1]].nama << " dengan tujuan " << T.idKA[index[pil - 1]].tujuan << endl; 
			do
			{
				cout << "Jumlah kursi yang anda pesan [Max 3] : "; cin >> jumlah;
				if(jumlah > 0 && jumlah < 4 && jumlah <= T.idKA[index[pil - 1]].kursi)
				{
					B.top++;
					cout << "\n";
					cout << "------------------------------------------------" << endl;
					cout << "\tFormulir Pemesanan Tiket KAI" << endl;
					cout << "------------------------------------------------" << endl;
					kode = kode_booking();
					cout << "\nKODE BOOKING " << kode;
					cout << endl;
					cout << "\nIdentitas Kereta Api" << endl;
					cout << "Nama Kereta      : " << T.idKA[index[pil - 1]].nama << endl;
					cout << "Stasiun Tujuan   : " << T.idKA[index[pil - 1]].tujuan << endl;
					cout << "Waktu Berangkat  : " << T.idKA[index[pil - 1]].berangkat << endl;
					cout << "Waktu Tiba       : " << T.idKA[index[pil - 1]].tiba << endl;
					cout << "Kelas            : " << T.idKA[index[pil - 1]].kelas << endl;
					cout << "------------------------------------------------" << endl;

					// proses input data dari struct utama ke struct khusus pemesanan
					B.dB[B.top].kode = kode;
					B.dB[B.top].namaKA = T.idKA[index[pil - 1]].nama;
					B.dB[B.top].tujuan = T.idKA[index[pil - 1]].tujuan;
					B.dB[B.top].berangkat = T.idKA[index[pil - 1]].berangkat;
					B.dB[B.top].tiba = T.idKA[index[pil - 1]].tiba;
					B.dB[B.top].kelas = T.idKA[index[pil - 1]].kelas;

					int total, bayar;
					for(int i=0; i < jumlah; i++)
					{
						cout << "\nData Penumpang ke - " << i+1 << endl;
						cout << "Masukkan NIK  : "; cin >> B.dB[B.top].nik[i];
						cout << "Masukkan Nama : "; cin >> B.dB[B.top].nama[i];
					}
					cout << "\n------------------------------------------------" << endl;
					cout << "Kursi dipesan : " << jumlah << endl;
					cout << "Harga/kursi   : Rp " << T.idKA[index[pil - 1]].harga << endl;
					total = jumlah * T.idKA[index[pil - 1]].harga;
					cout << "Total bayar   : Rp " << total << endl;
					do
					{
						cout << "Dibayar       : Rp "; cin >> bayar;
						if(bayar < total)
							cout << "Maaf, uang yang dibayarkan tidak cukup !" << endl;
						else
						{	
							cout << "Kembali       : Rp " << bayar - total << endl;
							cout << "\n------------------------------------------------" << endl;
							cout << "STATUS : Pemesanan tiket berhasil !" << endl;
							T.idKA[index[pil - 1]].kursi = T.idKA[index[pil - 1]].kursi - jumlah; 
						}
					} while(bayar < total);
				} 
				else if(jumlah > T.idKA[index[pil - 1]].kursi)
					cout << "Maaf, kursi yang tersisa sebanyak " << T.idKA[index[pil - 1]].kursi << " kursi" << endl;
				else if(jumlah > 3)
					cout << "Maaf, jumlah pemesanan tidak boleh lebih dari 3 kursi" << endl;
				else
					cout << "Maaf, nomor yang anda inputkan tidak valid !" << endl;
			} while(jumlah > 3 || jumlah <= 0);
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
	int j=0;
	int index[max];
	cout << "Masukkan kode booking : "; cin >> kode;

	for(int i=0; i <= B.top; i++)
	{
		if(B.dB[i].kode == kode)
		{
			index[j] = i;
			j++;
		}
	}
	if(j > 0)
	{
		string nama;
		int l=0;
		for(int i=0; i < j; i++)
		{
			nama = B.dB[index[i]].namaKA;
		}
		for(int k=0; k <= T.top; k++)
		{
			if(T.idKA[k].nama == nama)
			{
				l++;
			}
		}
		if(l > 0)
		{
			cout << "----------------------------------------" << endl;
			cout << "\t\tData Tiket" << endl;
			cout << "----------------------------------------" << endl;
			cout << "\nKode Booking    : " << kode << endl;
			for(int i=0; i < j ; i++)
			{
				cout << "Nama Kereta     : " << B.dB[index[i]].namaKA << endl;
				cout << "Stasiun Tujuan  : " << B.dB[index[i]].tujuan << endl;
				cout << "Waktu Berangkat : " << B.dB[index[i]].berangkat << endl;
				cout << "Waktu Tiba      : " << B.dB[index[i]].tiba << endl;
				cout << "Kelas           : " << B.dB[index[i]].kelas << endl;
				cout << "----------------------------------------" << endl;
				cout << "\nNo\tNIK\t\tNama\n" << endl;
				for(int j=0; j < 3; j++)
				{
					if(B.dB[index[i]].nik[j] != "")
						cout << j+1 << "\t" << B.dB[index[i]].nik[j] << "\t\t" << B.dB[index[i]].nama[j] << endl;
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

void data_penumpang()
{
	if(kosong() == 0)
	{
		cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\t\t\t\t\tJADWAL KEBERANGKATAN KERETA API" << endl;
		cout << "\t\t\t\t\tSTASIUN BESAR YOGYAKARTA (TUGU)" << endl;
		cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\nNo.\tKereta Api/ID\t\tTujuan\t\tBerangkat\tTiba\t\tKelas\t\tHarga (Rp)\tKursi\n" << endl;
		for(int i=0; i <= T.top; i++)
		{
			cout << i+1 << "\t" << T.idKA[i].nama << "\t\t" << T.idKA[i].tujuan << "\t\t" << T.idKA[i].berangkat << "\t\t" << T.idKA[i].tiba << "\t\t";
			cout << T.idKA[i].kelas << "\t\t" << T.idKA[i].harga << "\t\t" << T.idKA[i].kursi << endl;
		}
		cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
		int pil;
		cout << "\nPilihan anda : "; cin >> pil;
		if(pil > 0 && pil <= T.top + 1)
		{
			int j=0;
			int index[max];
			for(int i=0; i <= B.top; i++)
			{
				if(B.dB[i].namaKA == T.idKA[pil - 1].nama)
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
				cout << "\nNama Kereta   : " << T.idKA[pil - 1].nama << endl;
				cout << "Tujuan        : " << T.idKA[pil - 1].tujuan << endl;
				cout << "Berangkat     : " << T.idKA[pil - 1].berangkat << endl;
				cout << "Tiba          : " << T.idKA[pil - 1].tiba << endl;
				cout << "-------------------------------------" << endl;
				cout << "\nNIK\t\tNama\n" << endl;
				for(int i=0; i < j; i++)
				{
					for(int k=0; k < 3; k++)
					{
						if(B.dB[index[i]].nik[k] != "")
							cout << B.dB[index[i]].nik[k] << "\t\t" << B.dB[index[i]].nama[k] << endl;
						else
							continue;
					}
				}
				cout << "-------------------------------------" << endl;
			}
			else
				cout << "Tidak ada data penumpang untuk kereta api " << T.idKA[pil - 1].nama << endl;
		}
		else
			cout << "Maaf, angka yang anda inputkan tidak valid !" << endl;
	}
	else
		cout << "Maaf, tidak ada jadwal keberangkatan kereta api !" << endl;
}

void batalkan_pemesanan()
{
	if(B.top != -1)
	{
		string kode;
		char pil;
		int k = 0;
		cout << "\nMasukkan kode booking : "; cin >> kode;
		for(int i=0; i <= B.top; i++)
		{
			if(B.dB[i].kode == kode)
			{
				k++;
				cout << "Kode booking " << kode << ", Pemesanan tiket kereta api " << B.dB[i].namaKA << " dengan tujuan " << B.dB[i].tujuan << "." << endl;
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

					for(int i=0; i <= T.top; i++)
					{
						for(int k=0; k <= B.top; k++)
						{
							if(T.idKA[i].nama == B.dB[k].namaKA && T.idKA[i].kelas == B.dB[k].kelas && B.dB[k].kode == kode)
							{
								int jumlah = 0;
								for(int j=0; j < 3; j++)
								{
									if(B.dB[k].nik[j] != "")
									{
										jumlah++;
									}
								}
								T.idKA[i].kursi = T.idKA[i].kursi + jumlah;
							}
						}
					}

					B.dB[i].kode = "";
					B.dB[i].namaKA = "";
					B.dB[i].tujuan = "";
					B.dB[i].berangkat = "";
					B.dB[i].tiba = "";
					B.dB[i].kelas = "";
					for(int j=0; j < 3; j++)
					{
						if(B.dB[i].nik[j] != "")
						{
							B.dB[i].nik[j] = "";
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

// fungsi untuk user admin dan user biasa
void login();
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
						input(namaka, tujuan, berangkat, tiba, kelas, harga, kursi);
				} while(kursi > 10 || kursi < 1);
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
				int pilih;
				cout << "\nUrutkan berdasarkan : ";
				cout << "\n[1] Keberangkatan Terpagi\n[2] Harga Termurah\n\nPilihan anda : "; cin >> pilih;
				sorting(pilih);
				break;
			case 6 :
				searching();
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
				searching();
				break;
			case 2 :
				booking();
				break;
			case 3 :
				detail_booking();
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
	awal();
	B.top = -1;
	SetConsoleTitle(TEXT("KAI ACCESS STASIUN TUGU YOGYAKARTA"));
	login();
	return 0;
}
