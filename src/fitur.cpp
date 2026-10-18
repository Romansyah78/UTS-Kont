#include "fitur.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>

// Helper untuk mengubah string menjadi huruf kecil (case-insensitive search)
static std::string toLower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return str;
}

// Helper untuk membandingkan dua struct tanggal
static bool bandingkanTanggal(const tanggal& a, const tanggal& b) {
    if (a.tahun != b.tahun) return a.tahun < b.tahun;
    if (a.bulan != b.bulan) return a.bulan < b.bulan;
    return a.hari < b.hari;
}

// Menampilkan seluruh data produk dalam tabel terformat
void tampilkanTabel(const produk daftarProduk[], int jumlahData) {
    if (jumlahData == 0) {
        std::cout << "Data produk kosong.\n";
        return;
    }

    std::cout << std::left 
              << std::setw(6)  << "Index"
              << std::setw(30) << "Nama Produk"
              << std::setw(20) << "Kategori"
              << std::setw(20) << "Merk"
              << std::setw(10) << "Harga"
              << std::setw(8)  << "Stok"
              << std::setw(12) << "Tgl Tambah" << "\n";
    std::cout << std::string(106, '-') << "\n";

    for (int i = 0; i < jumlahData; ++i) {
        const produk& p = daftarProduk[i];
        char bufferTgl[15];
        snprintf(bufferTgl, sizeof(bufferTgl), "%04d-%02d-%02d", 
                 p.tgl_ditambahkan.tahun, p.tgl_ditambahkan.bulan, p.tgl_ditambahkan.hari);

        std::string namaTrunc = (p.nama_produk.length() > 27) ? p.nama_produk.substr(0, 24) + "..." : p.nama_produk;
        std::string katTrunc  = (p.kategori.length() > 18) ? p.kategori.substr(0, 15) + "..." : p.kategori;
        std::string merkTrunc = (p.merk_produk.length() > 18) ? p.merk_produk.substr(0, 15) + "..." : p.merk_produk;

        std::cout << std::left 
                  << std::setw(6)  << p.index
                  << std::setw(30) << namaTrunc
                  << std::setw(20) << katTrunc
                  << std::setw(20) << merkTrunc
                  << std::setw(10) << p.harga
                  << std::setw(8)  << p.stok
                  << std::setw(12) << bufferTgl << "\n";
    }
}

// Pencarian produk berdasarkan substring nama, kategori, atau merk
void cariProduk(const produk daftarProduk[], int jumlahData, const std::string& kataKunci) {
    std::string keyLower = toLower(kataKunci);
    int ditemukan = 0;

    std::cout << "\nHasil Pencarian untuk: \"" << kataKunci << "\"\n";
    std::cout << std::string(106, '-') << "\n";

    for (int i = 0; i < jumlahData; ++i) {
        const produk& p = daftarProduk[i];
        if (toLower(p.nama_produk).find(keyLower) != std::string::npos ||
            toLower(p.kategori).find(keyLower) != std::string::npos ||
            toLower(p.merk_produk).find(keyLower) != std::string::npos) {
            
            std::cout << "[" << p.index << "] " << p.nama_produk 
                      << " | Merk: " << p.merk_produk 
                      << " | Kategori: " << p.kategori 
                      << " | Harga: " << p.harga << " " << p.mata_uang 
                      << " | Stok: " << p.stok << "\n";
            ditemukan++;
        }
    }

    if (ditemukan == 0) {
        std::cout << "Tidak ada produk yang cocok dengan kata kunci.\n";
    } else {
        std::cout << "Total ditemukan: " << ditemukan << " produk.\n";
    }
}

// Pengurutan manual menggunakan algoritma Bubble Sort
void urutkanProduk(produk daftarProduk[], int jumlahData, int kriteria, bool ascending) {
    for (int i = 0; i < jumlahData - 1; ++i) {
        for (int j = 0; j < jumlahData - i - 1; ++j) {
            bool tukar = false;

            if (kriteria == 1) { // Berdasarkan Harga
                if (ascending) tukar = daftarProduk[j].harga > daftarProduk[j + 1].harga;
                else tukar = daftarProduk[j].harga < daftarProduk[j + 1].harga;
            } else if (kriteria == 2) { // Berdasarkan Stok
                if (ascending) tukar = daftarProduk[j].stok > daftarProduk[j + 1].stok;
                else tukar = daftarProduk[j].stok < daftarProduk[j + 1].stok;
            } else if (kriteria == 3) { // Berdasarkan Tanggal
                bool lebihKecil = bandingkanTanggal(daftarProduk[j].tgl_ditambahkan, daftarProduk[j + 1].tgl_ditambahkan);
                bool lebihBesar = bandingkanTanggal(daftarProduk[j + 1].tgl_ditambahkan, daftarProduk[j].tgl_ditambahkan);
                
                if (ascending) tukar = lebihBesar;
                else tukar = lebihKecil;
            }

            if (tukar) {
                produk temp = daftarProduk[j];
                daftarProduk[j] = daftarProduk[j + 1];
                daftarProduk[j + 1] = temp;
            }
        }
    }
    std::cout << "Pengurutan berhasil dilakukan.\n";
}

// Menghitung statistik inventaris dan total nilai aset
void hitungStatistik(const produk daftarProduk[], int jumlahData) {
    if (jumlahData == 0) {
        std::cout << "Data produk kosong.\n";
        return;
    }

    uint64_t totalNilaiAset = 0;
    uint32_t totalHarga = 0;
    int idxStokBanyak = 0;
    int idxStokSedikit = 0;

    for (int i = 0; i < jumlahData; ++i) {
        const produk& p = daftarProduk[i];
        totalNilaiAset += (static_cast<uint64_t>(p.harga) * p.stok);
        totalHarga += p.harga;

        if (p.stok > daftarProduk[idxStokBanyak].stok) idxStokBanyak = i;
        if (p.stok < daftarProduk[idxStokSedikit].stok) idxStokSedikit = i;
    }

    double rataRataHarga = static_cast<double>(totalHarga) / jumlahData;

    std::cout << "\n=== REKAPITULASI STATISTIK INVENTARIS ===\n";
    std::cout << "Total Item Unik      : " << jumlahData << " item\n";
    std::cout << "Total Nilai Aset     : " << totalNilaiAset << " USD\n";
    std::cout << "Rata-rata Harga Item : " << std::fixed << std::setprecision(2) << rataRataHarga << " USD\n";
    std::cout << "Stok Terbanyak       : " << daftarProduk[idxStokBanyak].nama_produk 
              << " (" << daftarProduk[idxStokBanyak].stok << " unit)\n";
    std::cout << "Stok Tersedikit      : " << daftarProduk[idxStokSedikit].nama_produk 
              << " (" << daftarProduk[idxStokSedikit].stok << " unit)\n";
}

// Menampilkan analisis penggunaan memori struct
void tampilkanInfoMemori() {
    std::cout << "\n=== ANALISIS PENGGUNAAN MEMORI (SIZEOF) ===\n";
    std::cout << "Ukuran struct tanggal  : " << sizeof(tanggal) << " byte\n";
    std::cout << "Ukuran struct produk   : " << sizeof(produk) << " byte\n";
    std::cout << "Kapasitas Array (MAX)  : " << MAX_PRODUK << " elemen\n";
    std::cout << "Total Alokasi Array    : " << sizeof(produk) * MAX_PRODUK << " byte (" 
              << (sizeof(produk) * MAX_PRODUK) / 1024.0 << " KB)\n";
}
