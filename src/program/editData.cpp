#include<iostream>
#include<string>
#include <fstream>

#include "produk.h"

using namespace std;

string escapeTextInput(string input) {
    if (input.find_first_of(",\"") == string::npos) {
        return input;
    }

    string escape = "\"";
    for (size_t i = 0; i < input.size(); i++) {
        if (input[i] == '"') {
            escape += '"';
        }
        escape += input[i];
    }
    escape += '"';
    return escape;
}

void saveCSV(produk daftarProduk[110], int jumlahData) {
    ofstream file("data/products-duplicates-100.csv");

    file << "Index,Name,Description,Brand,Category,Price,Currency,Stock,Tahun,Bulan,Tanggal\n";

    for (int i = 0; i < jumlahData; ++i) {
        file << daftarProduk[i].index << "," ;
        file << daftarProduk[i].nama_produk << ",";
        file << escapeTextInput(daftarProduk[i].deskripsi) << ",";
        file << escapeTextInput(daftarProduk[i].merk_produk) << ",";
        file << daftarProduk[i].kategori << ",";
        file << daftarProduk[i].harga << ",";
        file << daftarProduk[i].mata_uang << ",";
        file << daftarProduk[i].stok << ",";
        file << daftarProduk[i].tgl_ditambahkan.tahun << ",";
        file << daftarProduk[i].tgl_ditambahkan.bulan << ",";
        file << daftarProduk[i].tgl_ditambahkan.hari << "\n";;
    }

    file.close();
}

void hapusData(produk daftarProduk[110], int jumlahData) {
    int index;
    cout << "Masukkan index produk yang ingin dihapus(nomor): ";
    cin >> index;
    if (cin.fail()) {
        cout << "Input anda bukan angka" << endl;
        return;
    }
    if (index < 0 || index >= jumlahData) {
        cout << "Index tidak valid" << endl;
        return;
    }

    for (int i = index; i < jumlahData - 1; ++i) {
        daftarProduk[i] = daftarProduk[i + 1];
    }
    saveCSV(daftarProduk, jumlahData - 1);
}

void tambahData(produk daftarProduk[110], int jumlahData) {
    produk item;
    item.index = jumlahData + 1;

    cout << "Masukkan nama produk: ";
    cin.ignore();
    getline(cin, item.nama_produk);

    cout << "Masukkan deskripsi produk: ";
    getline(cin, item.deskripsi);

    cout << "Masukkan merk produk: ";
    getline(cin, item.merk_produk);

    cout << "Masukkan kategori produk: ";
    getline(cin, item.kategori);

    cout << "Masukkan harga produk: ";
    cin >> item.harga;
    if (cin.fail()) {
            cout << "Input anda bukan angka" << endl;
            return;
        }

    cout << "Masukkan mata uang produk: ";
    cin.ignore();
    getline(cin, item.mata_uang);

    cout << "Masukkan stok produk: ";
    cin >> item.stok;
    if (cin.fail()) {
            cout << "Input anda bukan angka" << endl;
            return;
        }

    cout << "Masukkan tahun ditambahkan: ";
    cin >> item.tgl_ditambahkan.tahun;
    if (cin.fail()) {
            cout << "Input anda bukan angka" << endl;
            return;
        }

    cout << "Masukkan bulan ditambahkan: ";
    cin >> item.tgl_ditambahkan.bulan;
    if (cin.fail()) {
            cout << "Input anda bukan angka" << endl;
            return;
        }
    cout << "Masukkan hari ditambahkan: ";
    cin >> item.tgl_ditambahkan.hari;
    if (cin.fail()) {
            cout << "Input anda bukan angka" << endl;
            return;
        }

    daftarProduk[jumlahData] = item;
    saveCSV(daftarProduk, jumlahData + 1);
}

void editData(produk daftarProduk[110], int jumlahData) {
    int index;
    cout << "Masukkan index produk yang ingin di edit(nomor): ";
    cin >> index;
    if (cin.fail()) {
        cout << "Input anda bukan angka" << endl;
        return;
    }
    if (index < 0 || index >= jumlahData) {
        cout << "Index tidak valid" << endl;
        return;
    }

    produk item = daftarProduk[index];
    cout << "Pilih data yang ingin diedit:" << endl;
    cout << "1. Nama Produk" << endl;
    cout << "2. Deskripsi Produk" << endl;
    cout << "3. Merk Produk" << endl;
    cout << "4. Kategori Produk" << endl;
    cout << "5. Harga Produk" << endl;
    cout << "6. Mata Uang Produk" << endl;
    cout << "7. Stok Produk" << endl;
    cout << "8. Tanggal Ditambahkan" << endl;

    int pilihan;
    cout << "Masukkan pilihan (1-8): ";
    cin >> pilihan;

    if (cin.fail() || pilihan < 1 || pilihan > 8) {
        cout << "Pilihan tidak valid" << endl;
        return;
    }

    if(pilihan == 1) {
        cout << "Masukkan nama produk: ";
        cin.ignore();
        getline(cin, item.nama_produk);
    } else if (pilihan == 2) {
        string input;
        cout << "Masukkan deskripsi produk: ";
        cin.ignore();
        getline(cin, input);
        item.deskripsi = escapeTextInput(input);
    } else if (pilihan == 3) {
        string input;
        cout << "Masukkan merk produk: ";
        cin.ignore();
        getline(cin, input);
        item.merk_produk = escapeTextInput(input);
    } else if (pilihan == 4) {
        cout << "Masukkan kategori produk: ";
        cin.ignore();
        getline(cin, item.kategori);
    } else if (pilihan == 5) {
        cout << "Masukkan harga produk: ";
        cin >> item.harga;
        if (cin.fail()) {
            cout << "Input anda bukan angka" << endl;
            return;
        }
    } else if (pilihan == 6) {
        cout << "Masukkan mata uang produk: ";
        cin.ignore();
        getline(cin, item.mata_uang);
    } else if (pilihan == 7) {
        cout << "Masukkan stok produk: ";
        cin >> item.stok;
        if (cin.fail()) {
            cout << "Input anda bukan angka" << endl;
            return;
        }
    } else if (pilihan == 8) {
        cout << "Masukkan tahun ditambahkan: ";
        cin >> item.tgl_ditambahkan.tahun;

        cout << "Masukkan bulan ditambahkan: ";
        cin >> item.tgl_ditambahkan.bulan;

        cout << "Masukkan hari ditambahkan: ";
        cin >> item.tgl_ditambahkan.hari;
        if (cin.fail()) {
            cout << "Input anda bukan angka" << endl;
            return;
        }
    }

    daftarProduk[index] = item;
    saveCSV(daftarProduk, jumlahData);
}