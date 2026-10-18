#include "produk.h"
#include "file_io.h"
#include "fitur.h"
#include <iostream>
#include <string>
#include <limits>

// Menampilkan pilihan menu utama program
void tampilkanMenu() {
    std::cout << "\n=========================================\n";
    std::cout << "   SISTEM MANAJEMEN INVENTARIS PRODUK    \n";
    std::cout << "=========================================\n";
    std::cout << "1. Tampilkan Seluruh Data Produk\n";
    std::cout << "2. Cari Produk (Nama / Kategori / Merk)\n";
    std::cout << "3. Urutkan Data Produk\n";
    std::cout << "4. Hitung Statistik & Total Aset Inventaris\n";
    std::cout << "5. Analisis Penggunaan Memori (sizeof)\n";
    std::cout << "6. Simpan Data ke Berkas CSV\n";
    std::cout << "0. Keluar\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "Pilih menu [0-6]: ";
}

int main() {
    // Alokasi memori array of struct untuk menyimpan data produk
    produk daftarProduk[MAX_PRODUK];
    
    // Membaca data dari CSV saat program pertama kali berjalan
    std::cout << "Membaca berkas data 'data/products-duplicates-100.csv'...\n";
    int jumlahData = bacaCSV(daftarProduk, "data/products-duplicates-100.csv");
    
    if (jumlahData > 0) {
        std::cout << "Berhasil memuat " << jumlahData << " data produk valid.\n";
        std::cout << "Data tidak valid dicatat dalam 'output/log_error.txt'.\n";
    } else {
        std::cout << "Peringatan: Tidak ada data valid yang dapat dimuat.\n";
    }

    int pilihan = -1;
    while (pilihan != 0) {
        tampilkanMenu();
        
        // Validasi jika pengguna memasukkan karakter non-angka
        if (!(std::cin >> pilihan)) {
            std::cout << "Masukan tidak valid! Harap masukkan angka.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (pilihan) {
            case 1:
                std::cout << "\n--- DAFTAR PRODUK INVENTARIS ---\n";
                tampilkanTabel(daftarProduk, jumlahData);
                break;

            case 2: {
                std::string kataKunci;
                std::cout << "Masukkan kata kunci pencarian: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, kataKunci);
                cariProduk(daftarProduk, jumlahData, kataKunci);
                break;
            }

            case 3: {
                int kriteria = 0;
                int urutan = 0;
                std::cout << "\nPilih Kriteria Pengurutan:\n";
                std::cout << "1. Harga\n";
                std::cout << "2. Stok\n";
                std::cout << "3. Tanggal Ditambahkan\n";
                std::cout << "Pilihan [1-3]: ";
                std::cin >> kriteria;

                std::cout << "Pilih Arah Pengurutan:\n";
                std::cout << "1. Ascending (Kecil ke Besar)\n";
                std::cout << "2. Descending (Besar ke Kecil)\n";
                std::cout << "Pilihan [1-2]: ";
                std::cin >> urutan;

                if (kriteria >= 1 && kriteria <= 3 && (urutan == 1 || urutan == 2)) {
                    urutkanProduk(daftarProduk, jumlahData, kriteria, urutan == 1);
                    std::cout << "\nData setelah diurutkan:\n";
                    tampilkanTabel(daftarProduk, jumlahData);
                } else {
                    std::cout << "Kriteria atau arah pengurutan tidak valid!\n";
                }
                break;
            }

            case 4:
                hitungStatistik(daftarProduk, jumlahData);
                break;

            case 5:
                tampilkanInfoMemori();
                break;

            case 6: {
                if (simpanCSV(daftarProduk, jumlahData, "data/products-duplicates-100.csv")) {
                    std::cout << "Data berhasil disimpan kembali ke berkas CSV.\n";
                } else {
                    std::cout << "Gagal menyimpan data ke berkas CSV.\n";
                }
                break;
            }

            case 0:
                std::cout << "Terima kasih! Program selesai.\n";
                break;

            default:
                std::cout << "Pilihan menu tidak tersedia. Silakan coba lagi.\n";
                break;
        }
    }

    return 0;
}