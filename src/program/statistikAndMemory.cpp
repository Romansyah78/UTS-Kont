#include<iostream>

#include "produk.h"
#include "statistikAndMemory.h"

using namespace std;

void printStatistik(produk daftarProduk[110], int jumlahProduk) {
    int totalProduk = jumlahProduk;
    int totalStok = 0;
    float totalHarga = 0.0;

    for (int i = 0; i < jumlahProduk; ++i) {
        totalStok += daftarProduk[i].stok;
        totalHarga += daftarProduk[i].harga;
    }

    float rataRataHarga = totalHarga / jumlahProduk;

    cout << "Statistik Produk:" << endl;
    cout << "Total Produk: " << totalProduk << endl;
    cout << "Total Stok: " << totalStok << endl;
    cout << "Rata-rata Harga: " << rataRataHarga << endl;
}

void printMemori() {
    cout << "Ukuran struct tanggal  : " << sizeof(tanggal) << " byte\n";
    cout << "Ukuran struct produk   : " << sizeof(produk) << " byte\n";
    cout << "Kapasitas Array (110)  : " << "110" << " elemen\n";
    cout << "Total Alokasi Array    : " << sizeof(produk) * 110 << " byte (" << (sizeof(produk) * 110) / 1024.0 << " KB)\n";
}