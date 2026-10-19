#include <fstream>
#include <string>
#include <iostream>

#include "produk.h"
#include "tampilan.h"

using namespace std;

int bacaCSV(produk listProduk[110]) {
    ifstream file("data/products-duplicates-100.csv");
    if (!file.is_open()) {
        cout << "File CSV tidak dapat dibuka" << endl;
        return -1;
    }

    string line;
    if (!getline(file, line)) {
        cout << "File CSV kosong" << endl;
        return -1;
    }

    int jumlahProduk = 0;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        string kolomData[11];
        size_t trackJmlKolom = 0;
        string nilai;
        bool diDalamKutipan = false;

        for (size_t i = 0; i < line.size(); i++) {
            char karakter = line[i];
            if (karakter == '"') {
                if (diDalamKutipan && i + 1 < line.size() && line[i + 1] == '"') {
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

        if (trackJmlKolom < 11) {
            continue;
        }

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
            if (toLower(daftarProduk[i].nama_produk).find(toLower(namaProduk)) != string::npos) {
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
            if (toLower(daftarProduk[i].kategori).find(toLower(kategoriProduk)) != string::npos) {
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
                shouldSwap = (sortForm == 1)
                    ? (daftarProduk[j].stok > daftarProduk[j + 1].stok)
                    : (daftarProduk[j].stok < daftarProduk[j + 1].stok);
            } else if (sortBy == 2) {
                shouldSwap = (sortForm == 1)
                    ? (daftarProduk[j].harga > daftarProduk[j + 1].harga)
                    : (daftarProduk[j].harga < daftarProduk[j + 1].harga);
            }

            if (shouldSwap) {
                swap(daftarProduk[j], daftarProduk[j + 1]);
            }
        }
    }
}
