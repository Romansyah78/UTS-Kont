#ifndef FILE_IO_H
#define FILE_IO_H

#include "produk.h"
#include <string>

// Membaca data dari fail CSV ke dalam array produk
// Mengembalikan jumlah rekod valid yang berjaya dibaca
int bacaCSV(produk daftarProduk[], const std::string& namaFile = "data/products-duplicates-100.csv");

// Menyimpan data array produk kembali ke fail CSV
bool simpanCSV(const produk daftarProduk[], int jumlahData, const std::string& namaFile = "data/products-duplicates-100.csv");

// Mencatat baris data rosak/cacat ke fail log_error.txt
void catatError(int nomorBaris, const std::string& isiBaris, const std::string& alasan);

#endif // FILE_IO_H