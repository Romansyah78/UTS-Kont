#include<iostream>
#include <limits>

#include "editData.h"
#include "produk.h"
#include "tampilan.h"
#include "statistikAndMemory.h"

using namespace std;

int main() {
    int interaksi; 
    int filter, sortBy, sortForm;
    int ubahAction;
    cout << "Pilih Interaksi:" << endl;
    cout << "1. Tampilkan Data" << endl;
    cout << "2. Ubah Data" << endl;
    cout << "3. Tampilkan Statistik" << endl;
    cout << "4. Tampilkan Memori" << endl;
    cout << "" << endl;
    cout << "Masukkan nomor pilihan: ";
    cin >> interaksi;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(interaksi == 1) {
        cout << "Filter:" << endl;
        cout << "1. Search by Name" << endl;
        cout << "2. Search by Category" << endl;
        cout << "" << endl;
        cout << "Masukkan nomor filter: ";
        cin >> filter;

        cout << "Sort by:" << endl;
        cout << "1. Stock" << endl;
        cout << "2. Price" << endl;
        cout << "" << endl;
        cout << "Masukkan nomor pilihan: ";
        cin >> sortBy;

        cout << "Sort form:" << endl;
        cout << "1. Ascending" << endl;
        cout << "2. Descending" << endl;
        cout << "" << endl;
        cout << "Masukkan nomor pilihan: ";
        cin >> sortForm;
        
        int searchAction[3] = {filter, sortBy, sortForm};

        produk daftarProduk[110];
        int jumlahProduk = bacaCSV(daftarProduk);
        int jumlahProdukDitemukan = cariProduk(daftarProduk, jumlahProduk, searchAction[0]);
        sortProduk(daftarProduk, jumlahProdukDitemukan, searchAction[1], searchAction[2]);
        buatTabel(daftarProduk, jumlahProdukDitemukan);

    } else if(interaksi == 2) {
        produk daftarProduk[110];
        int jumlahProduk = bacaCSV(daftarProduk);
        cout << "Interaksi Ubah:" << endl;
        cout << "1. Tambah Data" << endl;
        cout << "2. Hapus Data" << endl;
        cout << "3. Edit Data" << endl;
        cout << "Masukkan nomor pilihan: ";
        cin >> ubahAction;

        if(ubahAction == 1) {
            tambahData(daftarProduk, jumlahProduk);
        } else if(ubahAction == 2) {
            hapusData(daftarProduk, jumlahProduk);
        } else if(ubahAction == 3) {
            editData(daftarProduk, jumlahProduk);
        } else {
            cout << "Pilihan tidak valid" << endl;
        }
    } else if(interaksi == 3) {
        produk daftarProduk[110];
        int jumlahProduk = bacaCSV(daftarProduk);
        printStatistik(daftarProduk, jumlahProduk);
    } else if(interaksi == 4){
        printMemori();
    } else{
        cout << "Pilihan tidak valid" << endl;
    }

}