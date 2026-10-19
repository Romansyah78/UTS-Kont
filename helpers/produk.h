#include <cstdint>
#include <string>

#pragma once

using namespace std;

struct tanggal{
    int hari;
    int bulan;
    int tahun;
};
struct produk {
    tanggal tgl_ditambahkan;
    uint16_t harga;
    uint16_t stok;
    string kategori;
    string nama_produk;
    string deskripsi;
    string merk_produk;
    string mata_uang;
    int index;
};

int bacaCSV(produk daftarProduk[110]);
int cariProduk(produk daftarProduk[110], int jumlahPencarianDitemukan, int pilihan);
void sortProduk(produk daftarProduk[110], int jumlahProduk, int sortBy, int sortForm);
