#ifndef PRODUK_H
#define PRODUK_H

#include <string>
#include <cstdint>

// Kapasitas maksimum array produk
const int MAX_PRODUK = 110;

// Struct bersarang untuk menyimpan tanggal
struct tanggal {
    int hari;
    int bulan;
    int tahun;
};

// Struct utama untuk data produk
struct produk {
    tanggal tgl_ditambahkan;
    uint16_t harga;
    uint16_t stok;
    std::string kategori;
    std::string nama_produk;
    std::string deskripsi;
    std::string merk_produk;
    std::string mata_uang;
    int index;
};

#endif // PRODUK_H