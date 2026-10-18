#include <fstream>
#include <string>
#include <iostream>

#include "produk.h"

using namespace std;

int bacaCSV(produk daftarProduk[110]) {
    ifstream file("data/products-duplicates-100.csv");

    string line;
    if (!getline(file, line)) {
        throw runtime_error("File CSV kosong");
    }
    int jumlahProduk = 0;
    while (getline(file, line)) {
        string kolom[11];
        size_t jumlahKolom = 0;
        string nilai;
        bool diDalamKutipan = false;

        for (size_t i = 0; i < line.size(); i++) {
            const char karakter = line[i];
            if (karakter == '"') {
                if (diDalamKutipan && i + 1 < line.size() && line[i + 1] == '"') {
                    nilai += '"';
                    ++i;
                } else {
                    diDalamKutipan = !diDalamKutipan;
                }
            } else if (karakter == ',' && !diDalamKutipan) {
                kolom[jumlahKolom++] = nilai;
                nilai.clear();
            } else {
                nilai += karakter;
            }
        }
        kolom[jumlahKolom++] = nilai;
        if (jumlahProduk >= 110) {
            throw runtime_error("Jumlah produk pada CSV melebihi kapasitas array (110)");
        }

        int harga = stoi(kolom[5]);
        int stok = stoi(kolom[7]);

        produk item{};
        item.index = stoi(kolom[0]);
        item.nama_produk = kolom[1];
        item.deskripsi = kolom[2];
        item.merk_produk = kolom[3];
        item.kategori = kolom[4];
        item.harga = static_cast<uint16_t>(harga);
        item.mata_uang = kolom[6];
        item.stok = static_cast<uint16_t>(stok);
        item.tgl_ditambahkan.tahun = stoi(kolom[8]);
        item.tgl_ditambahkan.bulan = stoi(kolom[9]);
        item.tgl_ditambahkan.hari = stoi(kolom[10]);
        daftarProduk[jumlahProduk] = item;
        jumlahProduk++;
    }

    return jumlahProduk;
}

