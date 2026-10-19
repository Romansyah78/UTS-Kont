#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include "tampilan.h"
#include "produk.h"

using namespace std;
string toLower(string str) {
    for (char &c : str) c = tolower(c);
    return str;
}

string potongTeks(string teks, size_t lebar) {
    if (teks.size() <= lebar) return teks;
    if (lebar <= 3) return teks.substr(0, lebar);
    return teks.substr(0, lebar - 3) + "...";
}

void buatTabel(produk daftarProduk[110], int jumlahProduk) {
    const int wId = 4, wNama = 24, wDesk = 30, wMerk = 20, wKat = 20, wHarga = 8, wMata = 8, wStok = 6, wTgl = 10;

    cout << left << "| " << setw(wId) << "Index";
    cout << left << " | " << setw(wNama)  << "Nama";
    cout << left << " | " << setw(wDesk)  << "Deskripsi";
    cout << left << " | " << setw(wMerk)  << "Merk";
    cout << left << " | " << setw(wKat)   << "Kategori";
    cout << left << " | " << setw(wHarga) << "Harga";
    cout << left << " | " << setw(wMata)  << "Mata Uang";
    cout << left << " | " << setw(wStok)  << "Stok";
    cout << left << " | " << setw(wTgl)   << "Tanggal";
    cout << " |" << endl;

    for (int i = 0; i < jumlahProduk; i++) {
        ostringstream tgl;
        tgl << daftarProduk[i].tgl_ditambahkan.hari << '-'
            << daftarProduk[i].tgl_ditambahkan.bulan << '-'
            << daftarProduk[i].tgl_ditambahkan.tahun;

        cout << left << "| " << setw(wId)    << daftarProduk[i].index;
        cout << left << " | " << setw(wNama)  << potongTeks(daftarProduk[i].nama_produk, wNama);
        cout << left << " | " << setw(wDesk)  << potongTeks(daftarProduk[i].deskripsi, wDesk);
        cout << left << " | " << setw(wMerk)  << potongTeks(daftarProduk[i].merk_produk, wMerk);
        cout << left << " | " << setw(wKat)   << potongTeks(daftarProduk[i].kategori, wKat);
        cout << left << " | " << setw(wHarga) << daftarProduk[i].harga;
        cout << left << " | " << setw(wMata)  << daftarProduk[i].mata_uang;
        cout << left << " | " << setw(wStok)  << daftarProduk[i].stok;
        cout << left << " | " << setw(wTgl)   << tgl.str();
        cout << " |" << endl;
    }
}