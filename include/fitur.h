#ifndef FITUR_H
#define FITUR_H

#include "produk.h"
#include <string>

// Menampilkan seluruh data produk dalam bentuk tabel terformat
void tampilkanTabel(const produk daftarProduk[], int jumlahData);

// Mencari produk berdasarkan nama, kategori, atau merk
void cariProduk(const produk daftarProduk[], int jumlahData, const std::string& kataKunci);

// Mengurutkan data produk (1: Harga, 2: Stok, 3: Tanggal)
void urutkanProduk(produk daftarProduk[], int jumlahData, int kriteria, bool ascending);

// Menghitung statistik inventaris dan total nilai aset
void hitungStatistik(const produk daftarProduk[], int jumlahData);

// Menampilkan analisis penggunaan memori dan ukuran sizeof struct
void tampilkanInfoMemori();

#endif // FITUR_H