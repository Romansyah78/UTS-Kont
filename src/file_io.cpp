#include "file_io.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

// Mencatat pesan kesalahan ke file output/log_error.txt
void catatError(int nomorBaris, const std::string& isiBaris, const std::string& alasan) {
    std::ofstream logFile("output/log_error.txt", std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Gagal membuka output/log_error.txt untuk mencatat kesalahan.\n";
        return;
    }
    logFile << "[Baris " << nomorBaris << "] Error: " << alasan
            << " | Data: " << isiBaris << "\n";
}

// Helper untuk memisahkan baris CSV berdasarkan tanda koma
static std::vector<std::string> parseCSVLine(const std::string& line) {
    std::vector<std::string> tokens;
    std::string token;
    bool diDalamKutipan = false;

    for (std::size_t i = 0; i < line.size(); ++i) {
        const char karakter = line[i];
        if (karakter == '"') {
            if (diDalamKutipan && i + 1 < line.size() && line[i + 1] == '"') {
                token += '"';
                ++i;
            } else {
                diDalamKutipan = !diDalamKutipan;
            }
        } else if (karakter == ',' && !diDalamKutipan) {
            tokens.push_back(token);
            token.clear();
        } else {
            token += karakter;
        }
    }
    tokens.push_back(token);
    return tokens;
}

static std::string escapeCSVField(const std::string& field) {
    if (field.find_first_of(",\"\r\n") == std::string::npos) {
        return field;
    }

    std::string escaped = "\"";
    for (std::size_t i = 0; i < field.size(); ++i) {
        if (field[i] == '"') {
            escaped += '"';
        }
        escaped += field[i];
    }
    escaped += '"';
    return escaped;
}

// Membaca file CSV dan memasukkannya ke array daftarProduk
int bacaCSV(produk daftarProduk[], const std::string& namaFile) {
    std::ifstream file(namaFile);
    if (!file.is_open()) {
        std::cerr << "Gagal membuka file: " << namaFile << std::endl;
        return 0;
    }

    // Reset/bersihkan log error lama saat membaca baru
    std::ofstream resetLog("output/log_error.txt", std::ios::trunc);
    resetLog.close();

    std::string line;
    int jumlahData = 0;
    int nomorBaris = 0;

    // Lewati baris header (Index,Name,Description,...)
    if (std::getline(file, line)) {
        nomorBaris++;
    }

    while (std::getline(file, line) && jumlahData < MAX_PRODUK) {
        nomorBaris++;
        if (line.empty()) continue;

        std::vector<std::string> fields = parseCSVLine(line);

        if (fields.size() != 11) {
            catatError(nomorBaris, line, "Jumlah kolom harus 11");
            continue;
        }

        try {
            produk p;
            p.index = std::stoi(fields[0]);
            p.nama_produk = fields[1];
            p.deskripsi = fields[2];
            p.merk_produk = fields[3];
            p.kategori = fields[4];
            
            int hargaVal = std::stoi(fields[5]);
            p.mata_uang = fields[6];
            int stokVal = std::stoi(fields[7]);

            if (hargaVal < 0 || stokVal < 0 ||
                hargaVal > std::numeric_limits<uint16_t>::max() ||
                stokVal > std::numeric_limits<uint16_t>::max()) {
                catatError(nomorBaris, line, "Harga atau stok di luar rentang uint16_t");
                continue;
            }

            p.harga = static_cast<uint16_t>(hargaVal);
            p.stok = static_cast<uint16_t>(stokVal);

            p.tgl_ditambahkan.tahun = std::stoi(fields[8]);
            p.tgl_ditambahkan.bulan = std::stoi(fields[9]);
            p.tgl_ditambahkan.hari = std::stoi(fields[10]);
            if (p.tgl_ditambahkan.bulan < 1 || p.tgl_ditambahkan.bulan > 12 ||
                p.tgl_ditambahkan.hari < 1 || p.tgl_ditambahkan.hari > 31) {
                catatError(nomorBaris, line, "Tanggal tidak valid");
                continue;
            }

            daftarProduk[jumlahData] = p;
            jumlahData++;

        } catch (const std::exception& e) {
            catatError(nomorBaris, line, std::string("Gagal konversi tipe data: ") + e.what());
        }
    }

    file.close();
    return jumlahData;
}

// Menyimpan kembali data array ke file CSV
bool simpanCSV(const produk daftarProduk[], int jumlahData, const std::string& namaFile) {
    std::ofstream file(namaFile);
    if (!file.is_open()) {
        return false;
    }

    file << "Index,Name,Description,Brand,Category,Price,Currency,Stock,Tahun,Bulan,Tanggal\n";

    for (int i = 0; i < jumlahData; ++i) {
        const produk& p = daftarProduk[i];
        
        file << p.index << ","
             << escapeCSVField(p.nama_produk) << ","
             << escapeCSVField(p.deskripsi) << ","
             << escapeCSVField(p.merk_produk) << ","
             << escapeCSVField(p.kategori) << ","
             << p.harga << ","
             << escapeCSVField(p.mata_uang) << ","
             << p.stok << ","
             << p.tgl_ditambahkan.tahun << ","
             << p.tgl_ditambahkan.bulan << ","
             << p.tgl_ditambahkan.hari << "\n";
    }

    file.close();
    return true;
}