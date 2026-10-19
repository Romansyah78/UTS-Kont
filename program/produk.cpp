#include <fstream>
#include <string>
#include <iostream>

#include "produk.h"
#include "tampilan.h"

using namespace std;

int bacaCSV(produk listProduk[110]) {
    ifstream file("data/products-duplicates-100.csv");
    string line;
    if (!getline(file, line)) {
        cout << "File CSV kosong" << endl;
        return -1;
    }
    int jumlahProduk = 0;
    while (getline(file, line)) {
        string kolomData[11];
        size_t trackJmlKolom = 0;
        string nilai;
        bool diDalamKutipan = false;

        for (size_t i = 0; i < line.size(); i++) {
            char karakter = line[i];
            if (karakter == '"') {
                if (diDalamKutipan && line[i + 1] == '"') {
                    nilai += '"';
                    i++;
                } else {
                    diDalamKutipan = !diDalamKutipan;
                }
            } else if (karakter == ',' && !diDalamKutipan) {
                kolomData[trackJmlKolom++] = nilai;
                nilai.clear();
            } else {
                nilai += karakter;
            }
        }
        kolomData[trackJmlKolom++] = nilai;
        if (jumlahProduk >= 110) {
            cout << "Jumlah produk melebihi kapasitas array" << endl;
            return -1;
        }

        int harga = stoi(kolomData[5]);
        int stok = stoi(kolomData[7]);

        produk item{};
        item.index = stoi(kolomData[0]);
        item.nama_produk = kolomData[1];
        item.deskripsi = kolomData[2];
        item.merk_produk = kolomData[3];
        item.kategori = kolomData[4];
        item.harga = static_cast<uint16_t>(harga);
        item.mata_uang = kolomData[6];
        item.stok = static_cast<uint16_t>(stok);
        item.tgl_ditambahkan.tahun = stoi(kolomData[8]);
        item.tgl_ditambahkan.bulan = stoi(kolomData[9]);
        item.tgl_ditambahkan.hari = stoi(kolomData[10]);
        listProduk[jumlahProduk] = item;
        jumlahProduk++;
    }

    return jumlahProduk;
}

int cariProduk(produk daftarProduk[110], int jumlahProduk, int pilihan){
    int counter = 0;
    if(pilihan == 1) {
        string namaProduk;
        cout << "Masukkan nama produk: ";
        cin.ignore();
        getline(cin, namaProduk);
        for (int i = 0; i < jumlahProduk; i++) {
            if (daftarProduk[i].nama_produk.find(namaProduk) != string::npos) {
                daftarProduk[counter] = daftarProduk[i];
                counter++;
            }
        }
    } else if(pilihan == 2) {
        string kategoriProduk;
        cout << "Masukkan kategori produk: ";
        cin.ignore();
        getline(cin, kategoriProduk);
        for (int i = 0; i < jumlahProduk; i++) {
            if (daftarProduk[i].kategori.find(kategoriProduk) != string::npos) {
                daftarProduk[counter] = daftarProduk[i];
                counter++;
            }
        }
    } else {
        cout << "Pilihan filter tidak valid" << endl;
    }
    return counter;
}

void sortProduk(produk daftarProduk[110], int jumlahProduk, int sortBy, int sortForm) {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        for (int j = 0; j < jumlahProduk - i - 1; j++) {
            bool shouldSwap = false;
            if (sortBy == 1) {
                shouldSwap = (sortForm == 1) ? (daftarProduk[j].nama_produk > daftarProduk[j + 1].nama_produk) : (daftarProduk[j].nama_produk < daftarProduk[j + 1].nama_produk);
            } else if (sortBy == 2) {
                shouldSwap = (sortForm == 1) ? (daftarProduk[j].kategori > daftarProduk[j + 1].kategori) : (daftarProduk[j].kategori < daftarProduk[j + 1].kategori);
            } else if (sortBy == 3) {
                shouldSwap = (sortForm == 1) ? (daftarProduk[j].harga > daftarProduk[j + 1].harga) : (daftarProduk[j].harga < daftarProduk[j + 1].harga);
            }

            if (shouldSwap) {
                swap(daftarProduk[j], daftarProduk[j + 1]);
            }
        }
    }
}
