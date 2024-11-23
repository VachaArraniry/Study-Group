#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct 
{
    char nama [50];
}Dosen ;

typedef struct {
    char nama [50], kelas [20];
}Mahasiswa ;

typedef struct {
    char namaDosen [50], namaKelas [50], deskripsi [200], tanggal[20];
}Kelas;

Dosen pengguna[100];
Kelas grup[100];

const char *fileRequest = "requestKelas.dat";
const char *fileKelas = "Kelas.dat";
const char *fileGabKel = "GabKel.dat";

void pilihKelas();
void kelasDosen();
void requestKelasM();
void prosesKelas(const char *namaKelas, const char *waktu);
int statusGabung();
void gabungKelas(int kelasID);
void keluarKelas(int kelasID);

void main() {
    int pilihan;
    
    while (1) {
        system("cls");
        printf("=== Student Page ===\n");
        printf("1. Pilih Kelas\n");
        printf("2. Request Kelas\n");
        printf("3. Keluar dari Program\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                pilihKelas();  
                break;
            case 2:
                requestKelasM();  
                break;
            case 3:
                printf("\nKeluar dari program.\n");
                return;  
            default:
                printf("\nOpsi tidak valid. Silakan coba lagi.\n\n");
                Sleep(5000);
        }
    }
}


void requestKelasM() {
    FILE *file = fopen(fileRequest, "ab");
    if (file == NULL) {
        printf("Gagal membuka file untuk menulis.\n");
        return;
    }

    char namaKelas[50], tanggal[20], deskripsi[100];

    printf("Masukkan nama kelas: ");
    scanf(" %[^\n]s", namaKelas);
    printf("Masukkan tanggal permintaan: ");
    scanf(" %[^\n]s", tanggal);
    printf("Masukkan deskripsi kelas: ");
    scanf(" %[^\n]s", deskripsi);

    fprintf(file, "%s;%s;%s\n", namaKelas, tanggal, deskripsi);
    fclose(file);

    printf("Permintaan Anda telah disimpan di '%s'!\n", fileKelas);
}

void KelasDosen() {
    FILE *file = fopen(fileKelas, "rb");
    if (file == NULL) {
        printf("Gagal membuka file kelas.\n");
        return;
    }

    Kelas kelas;
    int index = 1;

    printf("ID\tNama Kelas\tDosen\ttanggal\tDeskripsi\n");
    printf("-------------------------------------------------------\n");

    while (fread(&kelas, sizeof(Kelas), 1, file)) {
        printf("%d\t%s\t%s\t%s\t%s\n", index, kelas.namaKelas, kelas.namaDosen,kelas.tanggal, kelas.deskripsi);
        index++;
    }
    fclose(file);
}

void pilihKelas() {
    int kelasID, pilihan;
    system("cls");

    while (1) {
        printf("\n=== Daftar Kelas yang Tersedia ===\n");
        KelasDosen();

        printf("\nMasukkan kelas yang ingin Anda pilih, atau 0 untuk kembali ke menu utama: ");
        scanf("%d", &kelasID);

        if (kelasID == 0) return; 

        if (statusGabung(kelasID)) {
            printf("\nAnda sudah terdaftar di kelas ini.\n");
            printf("1. Keluar dari Kelas\n");
        } else {
            printf("\nAnda belum terdaftar di kelas ini.\n");
            printf("1. Bergabung ke Kelas\n");
        }
        printf("2. Kembali ke Daftar Kelas\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);

        if (pilihan == 1) {
            if (statusGabung(kelasID)) {
                keluarKelas(kelasID);  
            } else {
                gabungKelas(kelasID);  
            }
        } else if (pilihan == 2) {
            continue;  
        } else {
            printf("\nOpsi tidak valid.\n");
        }
    }
}

int statusGabung(int kelasID) {
    FILE *file = fopen(fileGabKel, "rb");
    if (file == NULL) {
        return 0;  
    }

    int id;
    while (fread(&id, sizeof(int), 1, file)) {
        if (id == kelasID) {
            fclose(file);
            return 1;  
        }
    }
    fclose(file);
    return 0;  
}
void gabungKelas(int kelasID) {
    
FILE *file = fopen(fileGabKel, "ab");
    if (file == NULL) {
        printf("Gagal membuka file gabung kelas.\n");
        return;
    }

    fwrite(&kelasID, sizeof(int), 1, file);
    fclose(file);
    printf("Anda berhasil bergabung dengan kelas ID %d.\n", kelasID);
}

void keluarKelas(int kelasID) {
    FILE *file = fopen(fileGabKel, "rb");
    if (file == NULL) {
        printf("Gagal membuka file gabung kelas.\n");
        return;
    }

    int id;
    int temp[100], count = 0;

    while (fread(&id, sizeof(int), 1, file)) {
        if (id != kelasID) {
            temp[count++] = id;
        }
    }
    fclose(file);

    file = fopen(fileGabKel, "wb");
    if (file == NULL) {
        printf("Gagal membuka file gabung kelas.\n");
        return;
    }

    fwrite(temp, sizeof(int), count, file);
    fclose(file);
    printf("Anda berhasil keluar dari kelas ID %d.\n", kelasID);
}