#include <stdio.h> // Diperlukan untuk input/output standar seperti printf dan scanf
#include <string.h> // Diperlukan untuk fungsi manipulasi string seperti strcmp atau strcpy

// --- Pembatas Definisi Struktur Data dan Konstanta ---
// Struktur untuk menyimpan informasi kota tujuan
typedef struct {
    int id;
    char kotaTujuan[50];
    int hargaTiket; // Harga tiket sekarang fixed, bukan rentang
} Destinasi;

// Konstanta untuk biaya fasilitas
#define BIAYA_EKSEKUTIF 40000

// --- Pembatas Deklarasi Fungsi ---
// Fungsi untuk menampilkan daftar kota tujuan
void tampilkanDaftarTujuan(const Destinasi daftar[], int jumlah);

// Fungsi untuk mendapatkan input dari pengguna dan memvalidasi pilihan tujuan
int pilihTujuan(const Destinasi daftar[], int jumlah);

// Fungsi untuk mendapatkan detail penumpang, jumlah tiket, dan fasilitas
void inputInfoPenumpang(char nama[], char tanggal[], int *jumlahTiket, int *pilihanFasilitas);

// Fungsi untuk menghitung total harga tiket termasuk fasilitas dan jumlah
long hitungTotalHargaTiket(int hargaDasarPerTiket, int jumlahTiket, int pilihanFasilitas);

// Fungsi untuk mencetak tiket akhir
void cetakTiket(const char namaPenumpang[], const char kotaTujuan[], long totalHargaTiket, const char tanggalBerangkat[], int pilihanFasilitas, int jumlahTiket);

// --- Pembatas Fungsi Utama (main) ---
int main() {
    // Definisi dan inisialisasi data kota tujuan dengan harga fixed
    Destinasi daftarTujuan[] = {
        {1, "Tarutung", 130000},
        {2, "Sibolga", 150000},
        {3, "Balige", 110000},
        {4, "Dolok Sanggul", 130000},
        {5, "Sidikalang", 110000},
        {6, "Pahae", 60000},
        {7, "Padang Sidempuan", 150000},
        {8, "Sipirok", 140000},
        {9, "Tantom Angkola", 150000},
        {10, "Aek Kahombu", 150000},
        {11, "Lintong Nihuta", 120000},
        {12, "Siborong-borong", 120000}
    };
    int jumlahTujuan = sizeof(daftarTujuan) / sizeof(daftarTujuan[0]);

    // Variabel untuk menyimpan input pengguna
    char namaPenumpang[100];
    char tanggalBerangkat[20]; // Format DD-MM-YYYY
    int pilihanTujuanID;
    int jumlahTiket;
    int pilihanFasilitas; // 0 = Biasa, 1 = Eksekutif
    int hargaDasarPerTiket; // Ini akan menyimpan harga fixed dari destinasi terpilih
    long totalHargaTiket;

    printf("Selamat datang di Sistem Ticketing Koperasi Bintang Tapanuli (KBT)!\n");
    printf("Titik Keberangkatan: Medan\n\n");

    // Langkah 1: Tampilkan daftar kota tujuan
    tampilkanDaftarTujuan(daftarTujuan, jumlahTujuan);

    // Langkah 2: Pilih tujuan
    pilihanTujuanID = pilihTujuan(daftarTujuan, jumlahTujuan);
    
    // Langkah 3: Input info penumpang, jumlah tiket, dan fasilitas
    inputInfoPenumpang(namaPenumpang, tanggalBerangkat, &jumlahTiket, &pilihanFasilitas);

    // Langkah 4: Hitung harga tiket
    // Cari destinasi yang dipilih berdasarkan ID
    Destinasi *destinasiTerpilih = NULL;
    for (int i = 0; i < jumlahTujuan; i++) {
        if (daftarTujuan[i].id == pilihanTujuanID) {
            destinasiTerpilih = &daftarTujuan[i];
            break;
        }
    }

    if (destinasiTerpilih != NULL) {
        hargaDasarPerTiket = destinasiTerpilih->hargaTiket; // Ambil harga fixed
        totalHargaTiket = hitungTotalHargaTiket(hargaDasarPerTiket, jumlahTiket, pilihanFasilitas);
        
        // Langkah 5: Cetak tiket
        cetakTiket(namaPenumpang, destinasiTerpilih->kotaTujuan, totalHargaTiket, tanggalBerangkat, pilihanFasilitas, jumlahTiket);
    } else {
        printf("Terjadi kesalahan: Tujuan tidak ditemukan.\n");
    }

    return 0;
}

// --- Pembatas Implementasi Fungsi ---
void tampilkanDaftarTujuan(const Destinasi daftar[], int jumlah) {
    printf("--- Daftar Kota Tujuan ---\n");
    printf("No.\tKota Tujuan\t\tHarga Tiket (Rp)\n");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < jumlah; i++) {
        printf("%-3d\t%-20s\t%d\n", daftar[i].id, daftar[i].kotaTujuan, daftar[i].hargaTiket);
    }
    printf("-------------------------------------------------------------------\n\n");
}

int pilihTujuan(const Destinasi daftar[], int jumlah) {
    int pilihan;
    int valid = 0;
    do {
        printf("Masukkan nomor tujuan yang Anda inginkan: ");
        scanf("%d", &pilihan);
        // Membersihkan buffer input setelah scanf
        while (getchar() != '\n'); 

        // Cek validitas pilihan
        for (int i = 0; i < jumlah; i++) {
            if (daftar[i].id == pilihan) {
                valid = 1;
                break;
            }
        }
        if (!valid) {
            printf("Pilihan tidak valid. Mohon masukkan nomor tujuan yang tertera di daftar.\n");
        }
    } while (!valid);
    return pilihan;
}

void inputInfoPenumpang(char nama[], char tanggal[], int *jumlahTiket, int *pilihanFasilitas) {
    printf("Masukkan Nama Penumpang: ");
    // Menggunakan fgets untuk membaca string, lebih aman dari scanf untuk spasi
    fgets(nama, 100, stdin);
    nama[strcspn(nama, "\n")] = 0; // Menghilangkan newline dari fgets

    printf("Masukkan Tanggal Keberangkatan (DD-MM-YYYY): ");
    fgets(tanggal, 20, stdin);
    tanggal[strcspn(tanggal, "\n")] = 0; // Menghilangkan newline dari fgets

    do {
        printf("Masukkan Jumlah Tiket yang dipesan (min 1): ");
        scanf("%d", jumlahTiket);
        while (getchar() != '\n');
        if (*jumlahTiket <= 0) {
            printf("Jumlah tiket minimal 1. Mohon masukkan angka yang valid.\n");
        }
    } while (*jumlahTiket <= 0);

    do {
        printf("Pilih Fasilitas (0: KBT Biasa, 1: KBT Eksekutif): ");
        scanf("%d", pilihanFasilitas);
        while (getchar() != '\n');
        if (*pilihanFasilitas != 0 && *pilihanFasilitas != 1) {
            printf("Pilihan fasilitas tidak valid. Mohon masukkan 0 atau 1.\n");
        }
    } while (*pilihanFasilitas != 0 && *pilihanFasilitas != 1);
}

// Fungsi ini sekarang hanya menerima harga dasar per tiket (yang sudah fixed)
long hitungTotalHargaTiket(int hargaDasarPerTiket, int jumlahTiket, int pilihanFasilitas) {
    long hargaFinalPerTiket = hargaDasarPerTiket;
    if (pilihanFasilitas == 1) { // KBT Eksekutif
        hargaFinalPerTiket += BIAYA_EKSEKUTIF;
    }
    return hargaFinalPerTiket * jumlahTiket;
}

void cetakTiket(const char namaPenumpang[], const char kotaTujuan[], long totalHargaTiket, const char tanggalBerangkat[], int pilihanFasilitas, int jumlahTiket) {
    printf("\n");
    printf("====================================\n");
    printf("           TIKET KBT\n");
    printf("====================================\n");
    printf("Nama Penumpang    : %s\n", namaPenumpang);
    printf("Kota Tujuan       : %s\n", kotaTujuan);
    printf("Tanggal Berangkat : %s\n", tanggalBerangkat);
    printf("Jumlah Tiket      : %d\n", jumlahTiket);
    printf("Fasilitas         : %s\n", (pilihanFasilitas == 0 ? "KBT Biasa" : "KBT Eksekutif"));
    printf("Total Harga Tiket : Rp %ld\n", totalHargaTiket);
    printf("====================================\n");
    printf("Terima kasih telah menggunakan KBT!\n");
}

