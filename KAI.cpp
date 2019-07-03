#include <iostream>
#include <string>
#include <windows.h>
#define max 10

using namespace std;

//Struct berisi info kereta api.
struct KeretaApi {
	int id;
	string nama;
	string tujuan;
	string berangkat;
	string tiba;
	string kelas;
	float harga;
	int kursi;
};

//Stack berisi kereta api
struct StackKA {
	int top;
	struct KeretaApi KeretaApi[max];
}KA;

//Linked list berisi info booking penumpang
//Header diawali dengan Kode Booking dan detail Kereta Api
struct KodeBooking {
	string kodeBooking;
	int idKA;
	int kursiDipesan;
	struct DetailPenumpang* penumpang;
	struct KodeBooking* next_kodebooking;
}*headBooking;

//Lalu diikuti dengan info penumpang
struct DetailPenumpang {
	string namaPenumpang;
	string nikPenumpang;
	struct DetailPenumpang* next_penumpang;
};

//Inisiasi semua fungsi
void pembuka(string user);
void admin();
void other();
void login();
void initKA();
int isEmptyKA();
int isFullKA();
void pushKA(string nama, string tujuan, string berangkat, string tiba, string kelas, float harga, int kursi);
void popKA();
void cleanKA();
void tampilKA();
void sortKA(int pil);
void searchKA();
void dataPenumpangKA();
void booking();
string buatKodeBooking();
void infoBooking();
void batalBooking();

void pembuka(string user)
{
	system("cls");
	cout << "Login berhasil !" << endl;
	cout << "Selamat datang di aplikasi KAI Access. Anda login sebagai " << user << "\n\n";
	cout << "Menu yang tersedia :";
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
		if (username == "admin" && password == "admin")
		{
			admin();
			break;
		}
		else if (username == "amikom" && password == "amikom")
		{
			other();
			break;
		}
		else
		{
			cout << "Maaf, username/password salah ! Login ulang ? [Y/N] : "; cin >> pil;
			if (pil == 'Y' || pil == 'y')
				continue;
			else
			{
				cout << "Terimakasih telah menggunakan layanan KAI Access" << endl;
				break;
			}
		}
	} while (pil == 'y' || pil == 'Y');
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

		switch (pil)
		{
		case 1:
			cout << "Lengkapi data berikut !" << endl;
			cout << "-----------------------------------------------\n";
			cout << "Nama KAI/ID                 : "; cin >> namaka;
			cout << "Stasiun Tujuan              : "; cin >> tujuan;
			cout << "Waktu Berangkat             : "; cin >> berangkat;
			cout << "Waktu Tiba                  : "; cin >> tiba;
			cout << "Jenis Kelas [ EKS/BUS/EKO ] : "; cin >> kelas;
			cout << "Harga                       : Rp "; cin >> harga;
			cout << "Ketersediaan Kursi          : "; cin >> kursi;
			pushKA(namaka, tujuan, berangkat, tiba, kelas, harga, kursi);
			break;
		case 2:
			popKA();
			break;
		case 3:
			tampilKA();
			break;
		case 4:
			cleanKA();
			break;
		case 5:
			int pilih;
			cout << "\nUrutkan berdasarkan : ";
			cout << "\n[1] Keberangkatan Terpagi\n[2] Harga Termurah\n\nPilihan anda : "; cin >> pilih;
			sortKA(pilih);
			break;
		case 6:
			searchKA();
			break;
		case 7:
			dataPenumpangKA();
			break;
		case 8:
			login();
			break;
		case 9:
			cout << "Terimakasih telah menggunakan layanan KAI Access\n";
		default:
			cout << "Maaf, angka yang anda inputkan tidak valid !" << endl;
		}
	} while (pil != 9);
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

		switch (pil)
		{
		case 1:
			searchKA();
			break;
		case 2:
			booking();
			break;
		case 3:
			infoBooking();
			break;
		case 4:
			batalBooking();
			break;
		case 5:
			login();
			break;
		case 6:
			cout << "Terimakasih telah menggunakan layanan KAI Access\n";
			exit(0);
		default:
			cout << "Maaf, angka yang anda inputkan tidak valid !" << endl;
		}
	} while (pil != 6);
}

//Inisiasi stack kereta api
void initKA()
{
	KA.top = -1;
}

//Mengecek stack kereta api kosong
int isEmptyKA()
{
	if (KA.top == -1)
		return 1;
	else
		return 0;
}

//Mengecek stack kereta api penuh
int isFullKA()
{
	if (KA.top == max - 1)
		return 1;
	else
		return 0;
}

//Mengisi stack dan info kereta api
void pushKA(string nama, string tujuan, string berangkat, string tiba, string kelas, float harga, int kursi)
{
	if (isEmptyKA() == 1 || isFullKA() == 0)
	{
		KA.top++;
		KA.KeretaApi[KA.top].id = KA.top;
		KA.KeretaApi[KA.top].nama = nama;
		KA.KeretaApi[KA.top].tujuan = tujuan;
		KA.KeretaApi[KA.top].berangkat = berangkat;
		KA.KeretaApi[KA.top].tiba = tiba;
		KA.KeretaApi[KA.top].kelas = kelas;
		KA.KeretaApi[KA.top].harga = harga;
		KA.KeretaApi[KA.top].kursi = kursi;
		cout << "\nJadwal kereta api " << KA.KeretaApi[KA.top].nama << " berhasil diinput!\n" << endl;
	}
	else
		cout << "Jadwal sudah melewati batas maksimum!";
}

//Menghapus entry terakhir stack kereta api
void popKA() {
	if (isEmptyKA() != 1)
	{
		cout << "Jadwal kereta " << KA.KeretaApi[KA.top].nama << " berhasil dihapus!" << endl;
		KA.top--;
	}
	else
		cout << "\nMaaf, tidak ada data kereta api!";
}

//Mereset jadwal keberangkatan
void cleanKA() {
	KA.top = -1;
	cout << "Reset jadwal berhasil, jadwal kereta kosong!\n";
}

//Menampilkan semua keberangkatan kereta api
void tampilKA()
{
	if (isEmptyKA() == 0)
	{
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\t\t\t\t\tJADWAL KEBERANGKATAN KERETA API" << endl;
		cout << "\t\t\t\t\tSTASIUN BESAR YOGYAKARTA (TUGU)" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\nNo.\nKereta Api/ID\t\tTujuan\t\tBerangkat\tTiba\t\tKelas\t\tHarga (Rp)\tKursi\n" << endl;
		for (int i = KA.top; i >= 0; i--)
		{
			cout << i + 1 << "\t" << KA.KeretaApi[i].nama << "\t\t" << KA.KeretaApi[i].tujuan << "\t\t" << KA.KeretaApi[i].berangkat << "\t\t" << KA.KeretaApi[i].tiba << "\t\t";
			cout << KA.KeretaApi[i].kelas << "\t\t" << KA.KeretaApi[i].harga << "\t\t" << KA.KeretaApi[i].kursi << endl;
		}
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	}
	else
		cout << "Tidak ada jadwal kereta api!\n";
}

//Menyortir keberangkatan kereta menurut jadwal atau harga
void sortKA(int pil)
{
	StackKA tempKA;

	//Copy data dari struct utama ke temporary struct/struct sementara
	tempKA.top = -1;
	for (int i = 0; i <= KA.top; i++)
	{
		tempKA.top++;
		tempKA.KeretaApi[i].id = KA.KeretaApi[i].id;
		tempKA.KeretaApi[i].nama = KA.KeretaApi[i].nama;
		tempKA.KeretaApi[i].tujuan = KA.KeretaApi[i].tujuan;
		tempKA.KeretaApi[i].berangkat = KA.KeretaApi[i].berangkat;
		tempKA.KeretaApi[i].tiba = KA.KeretaApi[i].tiba;
		tempKA.KeretaApi[i].kelas = KA.KeretaApi[i].kelas;
		tempKA.KeretaApi[i].harga = KA.KeretaApi[i].harga;
		tempKA.KeretaApi[i].kursi = KA.KeretaApi[i].kursi;
	}

	string nama[max], tujuan[max], berangkat[max], tiba[max], kelas[max];
	float harga[max];
	int kursi[max];

	//Sorting metode bubble sort
	if (pil == 1)
	{
		for (int i = 1; i <= KA.top; i++)
		{
			for (int j = 0; j <= KA.top - i; j++)
			{
				//Sorting berdasarkan keberangkatan terpagi
				//Jadwal paling pagi diletakan paling atas( dari atas kebawah ) == ascending
				if (tempKA.KeretaApi[j].berangkat < tempKA.KeretaApi[j + 1].berangkat)
				{
					//Proses pertukaran data
					nama[j] = tempKA.KeretaApi[j].nama;
					tujuan[j] = tempKA.KeretaApi[j].tujuan;
					berangkat[j] = tempKA.KeretaApi[j].berangkat;
					tiba[j] = tempKA.KeretaApi[j].tiba;
					kelas[j] = tempKA.KeretaApi[j].kelas;
					harga[j] = tempKA.KeretaApi[j].harga;
					kursi[j] = tempKA.KeretaApi[j].kursi;

					tempKA.KeretaApi[j].nama = tempKA.KeretaApi[j + 1].nama;
					tempKA.KeretaApi[j].tujuan = tempKA.KeretaApi[j + 1].tujuan;
					tempKA.KeretaApi[j].berangkat = tempKA.KeretaApi[j + 1].berangkat;
					tempKA.KeretaApi[j].tiba = tempKA.KeretaApi[j + 1].tiba;
					tempKA.KeretaApi[j].kelas = tempKA.KeretaApi[j + 1].kelas;
					tempKA.KeretaApi[j].harga = tempKA.KeretaApi[j + 1].harga;
					tempKA.KeretaApi[j].kursi = tempKA.KeretaApi[j + 1].kursi;

					tempKA.KeretaApi[j + 1].nama = nama[j];
					tempKA.KeretaApi[j + 1].tujuan = tujuan[j];
					tempKA.KeretaApi[j + 1].berangkat = berangkat[j];
					tempKA.KeretaApi[j + 1].tiba = tiba[j];
					tempKA.KeretaApi[j + 1].kelas = kelas[j];
					tempKA.KeretaApi[j + 1].harga = harga[j];
					tempKA.KeretaApi[j + 1].kursi = kursi[j];
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
				//Sorting berdasarkan harga termurah secara ascending dari harga termurah - termahal
				if (tempKA.KeretaApi[j].harga < tempKA.KeretaApi[j + 1].harga)
				{
					nama[j] = tempKA.KeretaApi[j].nama;
					tujuan[j] = tempKA.KeretaApi[j].tujuan;
					berangkat[j] = tempKA.KeretaApi[j].berangkat;
					tiba[j] = tempKA.KeretaApi[j].tiba;
					kelas[j] = tempKA.KeretaApi[j].kelas;
					harga[j] = tempKA.KeretaApi[j].harga;
					kursi[j] = tempKA.KeretaApi[j].kursi;

					tempKA.KeretaApi[j].nama = tempKA.KeretaApi[j + 1].nama;
					tempKA.KeretaApi[j].tujuan = tempKA.KeretaApi[j + 1].tujuan;
					tempKA.KeretaApi[j].berangkat = tempKA.KeretaApi[j + 1].berangkat;
					tempKA.KeretaApi[j].tiba = tempKA.KeretaApi[j + 1].tiba;
					tempKA.KeretaApi[j].kelas = tempKA.KeretaApi[j + 1].kelas;
					tempKA.KeretaApi[j].harga = tempKA.KeretaApi[j + 1].harga;
					tempKA.KeretaApi[j].kursi = tempKA.KeretaApi[j + 1].kursi;

					tempKA.KeretaApi[j + 1].nama = nama[j];
					tempKA.KeretaApi[j + 1].tujuan = tujuan[j];
					tempKA.KeretaApi[j + 1].berangkat = berangkat[j];
					tempKA.KeretaApi[j + 1].tiba = tiba[j];
					tempKA.KeretaApi[j + 1].kelas = kelas[j];
					tempKA.KeretaApi[j + 1].harga = harga[j];
					tempKA.KeretaApi[j + 1].kursi = kursi[j];
				}
			}
		}
	}
	else
	{
		cout << "Angka yang anda input tidak valid !" << endl;
	}

	//Menampilkan hasil sorting
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\tJADWAL KEBERANGKATAN KERETA API" << endl;
	cout << "\t\t\t\t\tSTASIUN BESAR YOGYAKARTA (TUGU)" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\nKereta Api/ID\t\tTujuan\t\tBerangkat\tTiba\t\tKelas\t\tHarga (Rp)\tKursi\n" << endl;
	for (int i = KA.top; i >= 0; i--)
	{
		cout << tempKA.KeretaApi[i].nama << "\t\t" << tempKA.KeretaApi[i].tujuan << "\t\t" << tempKA.KeretaApi[i].berangkat << "\t\t" << tempKA.KeretaApi[i].tiba << "\t\t";
		cout << tempKA.KeretaApi[i].kelas << "\t\t" << tempKA.KeretaApi[i].harga << "\t\t" << tempKA.KeretaApi[i].kursi << endl;
	}
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
}

//Mencari keberangkatan kereta sesuai stasiun tujuan
void searchKA()
{
	string tujuan;
	int j = 0;
	int index[max];

	cout << "\nMasukkan stasiun tujuan : ";
	cin >> tujuan;

	for (int i = 0; i <= KA.top; i++)
	{
		if (KA.KeretaApi[i].tujuan == tujuan)
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
			cout << KA.KeretaApi[index[i]].nama << "\t\t" << KA.KeretaApi[index[i]].tujuan << "\t\t" << KA.KeretaApi[index[i]].berangkat << "\t\t" << KA.KeretaApi[index[i]].tiba << "\t\t";
			cout << KA.KeretaApi[index[i]].kelas << "\t\t" << KA.KeretaApi[index[i]].harga << "\t\t" << KA.KeretaApi[index[i]].kursi << endl;
		}
		cout << "------------------------------------------------------------------------------------------------------------------" << endl;
	}
	else
	{
		cout << "\nTidak ada jadwal keberangkatan kereta api ke " << tujuan << " !" << endl;
	}
}

//Mencari data penumpang dari satu keberangkatan
void dataPenumpangKA()
{
	if (isEmptyKA() == 0)
	{
		tampilKA();

		int pil;
		cout << "\nPilihan anda : "; cin >> pil;

		if (pil > 0 && pil <= KA.top + 1)
		{
			int j = 0;
			int index[max];

			KodeBooking* currBooking = headBooking;

			for (int i = 0; i <= KA.top; i++)
			{
				if (currBooking != NULL)
				{
					if (KA.KeretaApi[currBooking->idKA].nama == KA.KeretaApi[pil - 1].nama)
					{
						index[j] = i;
						j++;
					}
				}
				else
					break;
			}
			if (j > 0)
			{
				cout << "-------------------------------------" << endl;
				cout << "\tData Penumpang" << endl;
				cout << "-------------------------------------" << endl;
				cout << "\nNama Kereta   : " << KA.KeretaApi[currBooking->idKA].nama << endl;
				cout << "Tujuan        : " << KA.KeretaApi[currBooking->idKA].tujuan << endl;
				cout << "Berangkat     : " << KA.KeretaApi[currBooking->idKA].berangkat << endl;
				cout << "Tiba          : " << KA.KeretaApi[currBooking->idKA].tiba << endl;
				cout << "-------------------------------------" << endl;
				cout << "\nNo.\tNIK\t\tNama\n" << endl;

				for (currBooking; currBooking != NULL; currBooking = currBooking->next_kodebooking)
				{
					if (KA.KeretaApi[pil - 1].nama == KA.KeretaApi[currBooking->idKA].nama)
					{
						DetailPenumpang* currPenumpang = new DetailPenumpang;
						currPenumpang = currBooking->penumpang;

						for (int i = 0; i < currBooking->kursiDipesan; i++)
						{
							cout << i + 1 << currPenumpang->nikPenumpang << "\t\t" << currPenumpang->namaPenumpang << endl;
							currPenumpang = currPenumpang->next_penumpang;
						}
					}
				}
				cout << "-------------------------------------" << endl;
			}
			else
				cout << "Tidak ada data penumpang untuk kereta api " << KA.KeretaApi[pil - 1].nama << endl;
		}
		else
			cout << "Maaf, angka yang anda inputkan tidak valid !" << endl;
	}
	else
		cout << "Maaf, tidak ada jadwal keberangkatan kereta api !" << endl;
}

//Memesanan tiket
void booking()
{
	system("cls");

	//User menginput tujuan
	cout << "Masukkan stasiun tujuan : ";
	string inputTujuan;
	cin >> inputTujuan;

	//Mengecek keberangkatan dengan tujuan yang sesuai dengan input user
	int totalKeberangkatan = 0; //Counter posisi pada stack KA
	int keberangkatan[max]; //Penyimpan posisi pada stack yang sesuai dengan input
	for (int i = 0; i <= KA.top; i++)
	{
		if (KA.KeretaApi[i].tujuan == inputTujuan)
		{
			keberangkatan[totalKeberangkatan] = i; //Menyimpan posisi stack KA pada array
			totalKeberangkatan++; //Total keberangkatan dengan tujuan yang sama bertambah
		}
	}

	if (totalKeberangkatan > 0)
	{
		//Output semua keberangkatan yang berhasil ditemukan yang sesuai input
		cout << "\nTerdapat " << totalKeberangkatan << " jadwal keberangkatan ke " << inputTujuan << "\n\n";
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\t\t\t\t\t\tJADWAL KEBERANGKATAN KERETA API" << endl;
		cout << "\t\t\t\t\t\tSTASIUN BESAR YOGYAKARTA (TUGU)" << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\nNo\tKereta Api/ID\t\tTujuan\t\tBerangkat\tTiba\t\tKelas\t\tHarga (Rp)\tKursi\n" << endl;
		for (int i = 0; i < totalKeberangkatan; i++)
		{
			cout << i + 1 << "\t";
			cout << KA.KeretaApi[keberangkatan[i]].nama << "\t\t";
			cout << KA.KeretaApi[keberangkatan[i]].tujuan << "\t\t";
			cout << KA.KeretaApi[keberangkatan[i]].berangkat << "\t\t";
			cout << KA.KeretaApi[keberangkatan[i]].tiba << "\t\t";
			cout << KA.KeretaApi[keberangkatan[i]].kelas << "\t\t";
			cout << KA.KeretaApi[keberangkatan[i]].harga << "\t\t";
			cout << KA.KeretaApi[keberangkatan[i]].kursi << endl;
		}
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;

		//Input user memilih salah satu keberangkatan
		int pil;
		do
		{
			cout << "\nNomor yang anda pilih : ";
			cin >> pil;

			if (pil < 0 || pil > totalKeberangkatan) {
				cout << "Maaf, pilihan tidak valid !" << endl;
			}
		} while (pil < 0 || pil > totalKeberangkatan);

		//Memesan tiket booking sesuai pilihan
		if (pil > 0 || pil < totalKeberangkatan)
		{
			cout << "\nAnda memilih kereta api " << KA.KeretaApi[keberangkatan[pil - 1]].nama << " dengan tujuan " << KA.KeretaApi[keberangkatan[pil - 1]].tujuan << endl;
			int jumlahKursi = 0;
			do
			{
				do
				{
					cout << "Jumlah kursi yang anda pesan  [ Max 3 ] : ";
					cin >> jumlahKursi; //Input jumlah kursi yang ingin dipesan
				} while (jumlahKursi <= 0 || jumlahKursi > 3);

				if (jumlahKursi > 0 && jumlahKursi < KA.KeretaApi[keberangkatan[pil - 1]].kursi)
				{
					//Buat objek struct sebagai penyimpanan sementara yang nanti akan dipindah ke headBooking
					KodeBooking* tempBooking = new KodeBooking;

					tempBooking->kodeBooking = buatKodeBooking(); //Generate kode booking
					tempBooking->idKA = KA.KeretaApi[keberangkatan[pil - 1]].id; //Menyimpan idKA
					tempBooking->kursiDipesan = jumlahKursi; //Menyimpan jumlah kursi

					//Output detail pemesanan tiket
					cout << "\n";
					cout << "------------------------------------------------" << endl;
					cout << "\tFormulir Pemesanan Tiket KAI" << endl;
					cout << "------------------------------------------------" << endl;
					cout << "\nKODE BOOKING " << tempBooking->kodeBooking;
					cout << endl;
					cout << "\nIdentitas Kereta Api" << endl;
					cout << "Nama Kereta\t: " << KA.KeretaApi[tempBooking->idKA].nama << endl;
					cout << "Stasiun Tujuan\t: " << KA.KeretaApi[tempBooking->idKA].tujuan << endl;
					cout << "Waktu Berangkat\t: " << KA.KeretaApi[tempBooking->idKA].berangkat << endl;
					cout << "Waktu Tiba\t: " << KA.KeretaApi[tempBooking->idKA].tiba << endl;
					cout << "Kelas\t\t: " << KA.KeretaApi[tempBooking->idKA].kelas << endl;
					cout << "------------------------------------------------" << endl;

					//Buat objek struct yang akan menyimpan posisi pembacaan dari struct penumpang yang ada pada tempBooking
					DetailPenumpang* currPenumpang = new DetailPenumpang;
					//Inisiasi objek struct penumpang yang ada pada tempBooking
					tempBooking->penumpang = new DetailPenumpang;
					//Posisi awal currPenumpang = tempBooking->penumpang = head dari objek struct penumpang
					currPenumpang = tempBooking->penumpang;
					for (int i = 0; i < jumlahKursi; i++)
					{
						//Melakukan imput data ke dalam struct yang posisinya sekarang sudah disimpan di currPenumpang
						cout << "\nData Penumpang ke - " << i + 1 << endl;
						cout << "Masukkan NIK\t: "; cin >> currPenumpang->nikPenumpang;
						cout << "Masukkan Nama\t: "; cin >> currPenumpang->namaPenumpang;

						//Memindah posisi currPenumpang ke linked list selanjutnya dari objek penumpang
						currPenumpang->next_penumpang = new DetailPenumpang;

						//Menutup linked list dengan NULL
						if (i + 1 == jumlahKursi) {
							currPenumpang->next_penumpang = NULL;
						}
						//Atau lanjut menginput penumpang selanjutnya
						else {
							currPenumpang = currPenumpang->next_penumpang;
						}

					}

					//Setelah selesai menginput semua ada maka tempBooking akan dipindah ke headBooking yaitu linked list utama
					if (headBooking != NULL) { //Jika headBooking kosong maka akan langsung dipindah
						tempBooking->next_kodebooking = headBooking; //Memindahkan tempBooking->next_kodebooking menjadi menunjuk ke headBooking
						headBooking = tempBooking; //Ganti headBooking dengan tempBooking
					}
					else { //Jika tidak maka headBooking akan dipindah ke headBooking->next_kodebooking dan headBooking akan diisi tempBooking
						headBooking = tempBooking; //Ganti headBooking dengan tempBooking
						headBooking->next_kodebooking = NULL; //headBooking->next_kodebooking disini diisi NULL karena akan berada di akhir linked list
					}

					//Pembayaran booking tiket
					cout << "\n------------------------------------------------" << endl;
					cout << "Kursi dipesan\t: " << headBooking->kursiDipesan << endl;
					cout << "Harga/kursi\t: Rp " << KA.KeretaApi[headBooking->idKA].harga << endl;
					int total = jumlahKursi * KA.KeretaApi[headBooking->idKA].harga, bayar;
					cout << "Total bayar\t: Rp " << total << endl;
					do
					{
						cout << "Dibayar\t\t: Rp "; cin >> bayar;
						if (bayar < total)
							cout << "Maaf, uang yang dibayarkan tidak cukup !" << endl;
						else
						{
							cout << "Kembali\t\t: Rp " << bayar - total << endl;
							cout << "\n------------------------------------------------" << endl;
							cout << "STATUS : Pemesanan tiket berhasil!" << endl;
							KA.KeretaApi[headBooking->idKA].kursi = KA.KeretaApi[headBooking->idKA].kursi - jumlahKursi;
						}
					} while (bayar < total);
				}
			} while (jumlahKursi == 0);
		}
		else
			cout << "Maaf, tidak tersedia nomor " << pil << " pada jadwal !" << endl;
	}
	else
		cout << "\nTidak ada jadwal keberangkatan kereta api ke " << inputTujuan << " !" << endl;
}

//Membuat kode booking
string buatKodeBooking()
{
	string kode;
	char letter;

	const int MAX = 35;
	char alphaNumeric[MAX] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

	for (int i = 0; i < 6; i++)
	{
		kode = kode + alphaNumeric[rand() % MAX];
	}

	return kode;
}

//Mencari info kereta dan penumpang dari kode booking
void infoBooking()
{
	cout << "Masukkan kode booking : ";
	string inputKodeBooking;
	cin >> inputKodeBooking;

	KodeBooking* currBooking = new KodeBooking;

	for (currBooking = headBooking; currBooking != NULL; currBooking = currBooking->next_kodebooking) {
		if (currBooking->kodeBooking == inputKodeBooking) {
			cout << "----------------------------------------" << endl;
			cout << "\t\tData Tiket" << endl;
			cout << "----------------------------------------" << endl;
			cout << "\nKode Booking\t: " << currBooking->kodeBooking << endl;
			cout << "Nama Kereta\t: " << KA.KeretaApi[currBooking->idKA].nama << endl;
			cout << "Stasiun Tujuan\t: " << KA.KeretaApi[currBooking->idKA].tujuan << endl;
			cout << "Waktu Berangkat\t: " << KA.KeretaApi[currBooking->idKA].berangkat << endl;
			cout << "Waktu Tiba\t: " << KA.KeretaApi[currBooking->idKA].tiba << endl;
			cout << "Kelas\t\t: " << KA.KeretaApi[currBooking->idKA].kelas << endl;
			cout << "----------------------------------------" << endl;
			cout << "\nNo\tNIK\t\tNama\n" << endl;

			DetailPenumpang* currPenumpang = new DetailPenumpang;
			int count = 0;
			for (currPenumpang = currBooking->penumpang; currPenumpang != NULL; currPenumpang = currPenumpang->next_penumpang)
			{
				cout << count + 1 << "\t" << currPenumpang->nikPenumpang << "\t\t" << currPenumpang->namaPenumpang << endl;
				count++;
			}
			cout << "----------------------------------------" << endl;
		}
		else {
			continue;
		}
	}
}

//Membatalkan pemesanan tiket dengan input kode booking
void batalBooking()
{
	if (headBooking != NULL)
	{
		cout << "\nMasukkan kode booking : ";
		string inputKodeBooking;
		cin >> inputKodeBooking;

		KodeBooking* currBooking, * prevBooking = headBooking;
		for (currBooking = headBooking; currBooking != NULL; currBooking = currBooking->next_kodebooking) {
			if (currBooking->kodeBooking == inputKodeBooking) {
				cout << "Kode booking " << inputKodeBooking << ", Pemesanan tiket kereta api " << KA.KeretaApi[currBooking->idKA].nama << " dengan tujuan " << KA.KeretaApi[currBooking->idKA].tujuan << "." << endl;
				cout << "Apakah anda yakin ingin membatalkan pesanan [Y/N] : ";
				char pil;
				cin >> pil;

				if (pil == 'y' || pil == 'Y')
				{
					KA.KeretaApi[currBooking->idKA].kursi = KA.KeretaApi[currBooking->idKA].kursi + currBooking->kursiDipesan;
					if (currBooking == headBooking) {
						if (headBooking->next_kodebooking != NULL) {
							headBooking = headBooking->next_kodebooking;
							delete currBooking;
							break;
						}
						else {
							delete currBooking;
							headBooking = NULL;
							break;
						}
					}
					else {
						prevBooking->next_kodebooking = currBooking->next_kodebooking;
						delete currBooking;
						currBooking = NULL;
						break;
					}
				}
			}
			else
			{
				prevBooking = currBooking;
			}
		}
	}
	else
		cout << "Kode booking tidak ditemukan!" << endl;
}

int main()
{
	initKA();
	SetConsoleTitle(TEXT("KAI ACCESS STASIUN TUGU YOGYAKARTA"));

	headBooking = NULL;

	//Default entry
	pushKA("Lodaya/7075", "Bandung", "18.20", "23.12", "EKS", 200000, 25);	
	pushKA("Gajahwong/165", "Gambir", "15.30", "19.15", "BUS", 270000, 20);
	pushKA("Bengawan/9091", "Kroya", "06.20", "09.00", "EKO", 80000, 30);
	pushKA("Ranggajati/190", "Kroya", "17.15", "20.08", "EKO", 120000, 15);

	login();
	return 0;
}
