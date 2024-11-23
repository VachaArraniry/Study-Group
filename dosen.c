#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>



typedef struct 
{
char nama [200];
}Dosen ;

typedef struct {
    char nama [200], kelas [200], alasan [250];
}Mahasiswa ;

typedef struct {
    char namaDosen [200], namaKelas [200], deskripsi [200], tanggal [20];
}Kelas;

Dosen pengguna[100];
Mahasiswa blacklist[100];
Kelas grup[100];

int jmlBlacklist = 0, jmlKelas = 0, jmlDosen = 0;

const char *fileDosen = "dosen.dat";
const char *fileKelas = "Kelas.dat";
const char *fileBlacklist = "blacklist.dat";
const char *filerequestKelas = "requestKelas.dat";


void buatKelas(int loginDosen); 
void blacklistMahasiswa();
void tampilkanBlacklist();
void permintaanKelas();
void saveData();
void loadData();


int main(int loginDosen) {  //menu dosen
     
     int pilih;
     
     while(1) {
        system("cls");
        printf("===== Menu Dosen =====\n");
        printf("1. Buat Kelas\n");
        printf("2. Blacklist Mahasiswa\n");
        printf("3. Permintaan Kelas\n");
        printf("4. Logout\n");
        printf("======================\n");
        printf("\nPilih Opsi : ");scanf("%d", &pilih);

        switch(pilih) {
            case 1:
                buatKelas(loginDosen);
                break;
            case 2:
                blacklistMahasiswa();
                break;
            case 3:
                permintaanKelas();
                break;
            case 4:
                system("cls");
                printf(">>>>> Anda telah Logout <<<<<");Sleep(2000);
                return 0;
            default:
                printf("Pilihan tidak ada coba lagi!\n");Sleep(1000);
        }
        system("cls");
        }
        
    
}

void buatKelas(int loginDosen) {
    if (jmlKelas > 50) {
        printf("Maaf, jumlah kelas sudah mencapai batas.\n");
        return;
    }
    system("cls");
    printf("====== PEMBUATAN KELAS ======\n");
    printf("Masukkan nama kelas\t\t: ");
    scanf(" %[^\n]s", grup[jmlKelas].namaKelas);
    printf("Masukkan Tanggal Dibuat\t\t: ");
    scanf(" %[^\n]s", grup[jmlKelas].tanggal);
    printf("Masukkan deskripsi kelas\t: ");
    scanf(" %[^\n]s", grup[jmlKelas].deskripsi);
    printf("Masukkan nama Dosen/Profesor\t: ");
    scanf(" %[^\n]s", grup[jmlKelas].namaDosen);
    
    

    strcpy(grup[jmlKelas].namaDosen, pengguna[loginDosen].nama); jmlKelas++;  
    saveData(fileKelas);
    system("cls");
    printf("Kelas berhasil dibuat.\n");Sleep(2000);
}   

void blacklistMahasiswa() {
    int pilih;
    if (jmlBlacklist >= 100) {
        printf("Daftar blacklist penuh.\n");
        return;
    }
    while (1)
    {
    system("cls");
    printf("========= MENU BLACKLIST =========\n");
    printf("1. Tampilkan blacklist\n");
    printf("2. Blacklist Mahasiswa.\n");
    printf("3. Kembali ke halaman sebelumnya.\n");
    printf("\nPilih Opsi : ");
    scanf("%d", &pilih);
    switch (pilih)
    {
    case 1:
        tampilkanBlacklist();
        break;
    case 2:
        printf("Blacklist Mahasiswa.\n");
        printf("Masukkan nama mahasiswa\t: ");
        scanf(" %[^\n]", blacklist[jmlBlacklist].nama);
        printf("Masukkan Tanggal\t: ");
        scanf(" %[^\n]", blacklist[jmlBlacklist].kelas);
        printf("Alasan\t\t\t: ");
        scanf(" %[^\n]", blacklist[jmlBlacklist].kelas);
        jmlBlacklist++;
        saveData();
        printf("Mahasiswa berhasil di-blacklist.\n");
        break;

    case 3:
        return;

    default:
    printf("pilihan tidak tersedia coba lagi");
        break;
    }
    
    }
}

void tampilkanBlacklist() {
    int pilih;
    while(1){
    system("cls");
    printf("====== Blacklist Mahasiswa ======\n");
    printf("Daftar Blacklist Mahasiswa:\n");
    loadData(fileDosen);
    for (int i = 0; i < jmlBlacklist; i++) {
        printf("%d. Nama\t: %s\n    Kelas\t: %s\n", i+1 , blacklist[i].nama, blacklist[i].kelas);
    }
    printf("pilih 0 untuk kembali ke halaman sebelumnya. \n");
    scanf("%d", &pilih);
    if (pilih == 0) return;
    }
}

void permintaanKelas() {
    FILE *file = fopen(filerequestKelas, "rb");
    FILE *fileDisetujui = fopen(filerequestKelas, "ab");
    if (file == NULL || fileDisetujui == NULL) {
    
        printf("\nFile kosong.....\n");
        Sleep(1000);
        return;
    }

    char line[200];
    int requestNumber = 0;

    printf("\nDaftar Permintaan Kelas:\n");
    while (fgets(line, sizeof(line), file)) {
        char namaKelas[200], tanggal[20], deskripsi[200];
        sscanf(line, "%[^;];%[^;];%[^\n]", namaKelas, tanggal, deskripsi);
        printf("%d.Nama: %s\n  Tanggal: %s\n  Deskripsi: %s\n\n", ++requestNumber, namaKelas, tanggal, deskripsi);
    }

    if (requestNumber == 0) {
        printf("Tidak ada permintaan yang tersedia.\n");
        fclose(file);
        fclose(fileDisetujui);
        Sleep(1000);
        return;
    }

    rewind(file);
    printf("\nMasukkan nomor permintaan yang ingin disetujui (atau 0 untuk keluar): ");
    int pilih;
    scanf("%d", &pilih);

    if (pilih == 0) {
        printf("Tidak ada tindakan yang dilakukan.\n"); 
        fclose(file);
        fclose(fileDisetujui);
        Sleep(1000);
        return;
    }

    int currentLine = 0;
    FILE *tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL) {
        printf("Gagal membuka file sementara.\n");
        fclose(file);
        fclose(fileDisetujui);
        Sleep(2000);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        currentLine++;
        if (currentLine == pilih) {
            fprintf(fileDisetujui, "%s", line);
            printf("Permintaan disetujui dan disimpan di 'requestDisetujui.dat'!\n"); Sleep(2000);
        } else {
            fprintf(tempFile, "%s", line); 
        }
    }

    fclose(file);
    fclose(fileDisetujui);
    fclose(tempFile);

    remove(fileKelas);
    rename("temp.dat", fileKelas);
}
void saveData(){
    FILE *file;

    file = fopen(fileKelas, "wb");
    fwrite(&jmlKelas, sizeof(int), 1, file);
    fwrite(grup, sizeof(Kelas), jmlKelas, file);
    fclose(file);

    file = fopen(fileBlacklist, "wb");
    fwrite(&jmlBlacklist, sizeof(int), 1, file);
    fwrite(blacklist, sizeof(Mahasiswa), jmlBlacklist, file);
    fclose(file);
}

void loadData(){
    FILE *file;

    file = fopen(fileDosen, "ab");
    if(file!= NULL){
        fread(&jmlDosen, sizeof(int), 1, file);
        fread(pengguna, sizeof(Dosen), jmlDosen, file);
        fclose(file);
    }

    file = fopen(fileKelas, "ab");
    if(file!= NULL){
        fread(&jmlKelas, sizeof(int), 1, file);
        fread(grup, sizeof(Kelas), jmlKelas, file);
        fclose(file);
    }

    file = fopen(fileBlacklist, "ab");
    if(file!= NULL){
        fread(&jmlBlacklist, sizeof(int), 1, file);
        fread(blacklist, sizeof(Mahasiswa), jmlBlacklist, file);
        fclose(file);
    }
}
