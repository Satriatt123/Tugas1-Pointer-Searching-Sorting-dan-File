#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

using namespace std;

struct karyawan {
    int idkaryawan;
    char namakaryawan[100];
};

struct barang {
    char nama[100];
    int harga;
    int stok;
};

void simpankaryawan(karyawan* arr, int n) {
    FILE* f = fopen("karyawan.txt", "a");
    if (!f) {
        cout << "Gagal membuka file karyawan.txt!" << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d %s\n", (arr + i)->idkaryawan, (arr + i)->namakaryawan);
    }
    fclose(f);
    cout << "Data berhasil disimpen nih!" << endl;
}

int bacakaryawan(karyawan* arr, int batas) {
    FILE* f = fopen("karyawan.txt", "r");
    if (!f) return 0;
    
    int n = 0;
    while (n < batas && fscanf(f, "%d %99s", &(arr + n)->idkaryawan, (arr + n)->namakaryawan) == 2) {
        n++;
    }
    fclose(f);
    return n;
}

void tambahdatakaryawan() {
    int jml;
    cout << "Masukkan jumlah karyawan: ";
    cin >> jml;
    
    if (jml <= 0) {
        cout << "Inputan salah bro!" << endl; 
        return;
    }

    karyawan* arr = new karyawan[jml];
    for (int i = 0; i < jml; i++) {
        cout << "\nKaryawan ke-" << (i + 1) << endl;
        cout << "ID karyawan: ";
        cin >> (arr + i)->idkaryawan;
        cout << "Nama karyawan: ";
        cin >> (arr + i)->namakaryawan;
    }
    simpankaryawan(arr, jml);
    delete[] arr;
}

void lihatdatakaryawan() {
    karyawan* arr = new karyawan[200];
    int n = bacakaryawan(arr, 200);

    if (n == 0) {
        cout << "Belum ada datanya." << endl;
    } else {
        cout << "\n===== DATA KARYAWAN =====" << endl;
        for (int i = 0; i < n; i++) {
            cout << "Karyawan ke-" << (i + 1) << endl;
            cout << "ID   : " << (arr + i)->idkaryawan << endl;
            cout << "Nama : " << (arr + i)->namakaryawan << endl;
        }
    }
    delete[] arr;
}

void searchingdatakaryawan() {
    int id_cari;
    cout << "Masukkan ID karyawan yang mau dicari: ";
    cin >> id_cari;

    karyawan* arr = new karyawan[200];
    int n = bacakaryawan(arr, 200);
    bool dapet = false;

    for (int i = 0; i < n; i++) {
        if ((arr + i)->idkaryawan == id_cari) {
            cout << "\nData ketemu!" << endl;
            cout << "ID   : " << (arr + i)->idkaryawan << endl;
            cout << "Nama : " << (arr + i)->namakaryawan << endl;
            dapet = true;
            break;
        }
    }
    if (!dapet) cout << "Datanya ga ada!" << endl;
    delete[] arr;
}

void menuadmin() {
    int pilih;
    do {
        system("cls");
        cout << "========================" << endl;
        cout << "       Halo Admin!" << endl;
        cout << "========================" << endl;
        cout << "1. Tambah data karyawan" << endl;
        cout << "2. Lihat data karyawan" << endl;
        cout << "3. Searching data karyawan" << endl;
        cout << "4. Logout" << endl;
        cout << "========================" << endl;
        cout << "Pilih menu: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambahdatakaryawan(); break;
            case 2: lihatdatakaryawan(); break;
            case 3: searchingdatakaryawan(); break;
            case 4: break;
            default: cout << "Pilihan salah!" << endl;
        }
        if (pilih != 4) system("pause");
    } while (pilih != 4);
}

void loginadmin() {
    string user, pass;
    bool sukses = false;
    do {
        cout << "\nMasukkan Username anda: ";
        cin >> user;
        cout << "Masukkan Password anda: ";
        cin >> pass;

        if (user == "dzinggo" && pass == "satriaganteng") {
            sukses = true;
            menuadmin();
        } else {
            cout << "Kamu bukan Admin!" << endl;
            system("pause");
            system("cls");
            cout << "========== WELCOME TO COCOA HEAVEN ==========" << endl;
            cout << "1. Login Admin" << endl;
            cout << "2. Karyawan" << endl;
            cout << "3. Keluar" << endl;
            cout << "=============================================" << endl;
        }
    } while (!sukses);
}

void tambahbarangkefile(barang* arr, int n) {
    FILE* f = fopen("barang.txt", "a");
    if (!f) return;
    for (int i = 0; i < n; i++) {
        fprintf(f, "%s %d %d\n", (arr + i)->nama, (arr + i)->harga, (arr + i)->stok);
    }
    fclose(f);
    cout << "Data tersimpan!" << endl;
}

void simpansemuabarang(barang* arr, int n) {
    FILE* f = fopen("barang.txt", "w");
    if (!f) return;
    for (int i = 0; i < n; i++) {
        fprintf(f, "%s %d %d\n", (arr + i)->nama, (arr + i)->harga, (arr + i)->stok);
    }
    fclose(f);
}

int bacabarang(barang* arr, int batas) {
    FILE* f = fopen("barang.txt", "r");
    if (!f) return 0;
    
    int n = 0;
    while (n < batas && fscanf(f, "%99s %d %d", (arr + n)->nama, &(arr + n)->harga, &(arr + n)->stok) == 3) {
        n++;
    }
    fclose(f);
    return n;
}

void bubbleSort(barang* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((arr + j)->harga > (arr + j + 1)->harga) {
                barang temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}

void quickSort(barang* arr, int awal, int akhir) {
    int low = awal, high = akhir;
    int pivot = (arr + (awal + akhir) / 2)->harga;

    do {
        while ((arr + low)->harga > pivot)
            low++;
        while ((arr + high)->harga < pivot)
            high--;

        if (low <= high) {
            barang temp = *(arr + low);
            *(arr + low) = *(arr + high);
            *(arr + high) = temp;
            low++;
            high--;
        }
    } while (low <= high);

    if (awal < high)
        quickSort(arr, awal, high);
    if (low < akhir)
        quickSort(arr, low, akhir);
}

void urutbynama(barang* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp((arr + j)->nama, (arr + j + 1)->nama) > 0) {
                barang temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}

void tambahdatabarang() {
    int jml;
    cout << "Masukkan jumlah barang: ";
    cin >> jml;
    if (jml <= 0) return;

    barang* arr = new barang[jml];
    for (int i = 0; i < jml; i++) {
        cout << "\nbarang ke- " << (i + 1) << endl;
        cout << "Nama Barang: ";
        cin >> (arr + i)->nama;
        cout << "Harga Barang: ";
        cin >> (arr + i)->harga;
        cout << "Stok Barang: ";
        cin >> (arr + i)->stok;
    }
    tambahbarangkefile(arr, jml);
    delete[] arr;
}

void lihatdatabarang() {
    barang* arr = new barang[200];
    int n = bacabarang(arr, 200);
    
    if (n == 0) {
        cout << "Belum ada datanya bro." << endl;
        delete[] arr; 
        return;
    }

    int tipe_sort;
    cout << "1. Ascending" << endl;
    cout << "2. Descending" << endl;
    cout << "Pilih sorting: ";
    cin >> tipe_sort;

    if (tipe_sort == 1) {
        bubbleSort(arr, n);
    } else if (tipe_sort == 2) {
        quickSort(arr, 0, n - 1);
    } else { 
        cout << "Pilihan error!" << endl; 
        delete[] arr; 
        return; 
    }

    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << "Data barang ke- " << (i + 1) << endl;
        cout << (arr + i)->nama << endl << (arr + i)->harga << endl << (arr + i)->stok << endl;
        cout << "=======================" << endl;
    }
    delete[] arr;
}

void editdatabarang() {
    char dicari[100];
    cout << "Masukkan nama barang yang mau diedit: ";
    cin >> dicari;

    barang* arr = new barang[200];
    int n = bacabarang(arr, 200);
    bool dapet = false;

    for (int i = 0; i < n; i++) {
        if (strcmp((arr + i)->nama, dicari) == 0) {
            cout << "\nData ketemu!" << endl;
            cout << "Nama  : " << (arr + i)->nama << endl;
            cout << "Harga : " << (arr + i)->harga << endl;
            cout << "Stok  : " << (arr + i)->stok << endl;

            cout << "\nInput data baru" << endl;
            cout << "Nama Barang: ";
            cin >> (arr + i)->nama;
            cout << "Harga Barang: ";
            cin >> (arr + i)->harga;
            cout << "Stok Barang: ";
            cin >> (arr + i)->stok;

            dapet = true;
            break;
        }
    }

    if (dapet) {
        simpansemuabarang(arr, n);
        cout << "\nUpdate sukses!" << endl;
    } else {
        cout << "Barang ga ketemu!" << endl;
    }
    delete[] arr;
}

void caridatabarang() {
    int cara;
    cout << "1. Sequential Search" << endl;
    cout << "2. Binary Search" << endl;
    cout << "Pilih metode: ";
    cin >> cara;

    char dicari[100];
    cout << "Masukkan nama barang: ";
    cin >> dicari;

    barang* arr = new barang[200];
    int n = bacabarang(arr, 200);
    bool dapet = false;
    int idx = -1;

    if (cara == 1) {
        for (int i = 0; i < n; i++) {
            if (strcmp((arr + i)->nama, dicari) == 0) {
                dapet = true;
                idx = i;
                break;
            }
        }
    } else if (cara == 2) {
        urutbynama(arr, n);
        int kiri = 0, kanan = n - 1;
        while (kiri <= kanan) {
            int tengah = kiri + (kanan - kiri) / 2;
            int hasil = strcmp((arr + tengah)->nama, dicari);
            
            if (hasil == 0) {
                dapet = true;
                idx = tengah;
                break;
            }
            if (hasil < 0) kiri = tengah + 1;
            else kanan = tengah - 1;
        }
    } else {
        cout << "Metode salah!" << endl;
    }

    if (dapet) {
        cout << "\nBarang ketemu nih!" << endl;
        cout << "Nama : " << (arr + idx)->nama << endl;
        cout << "Harga: " << (arr + idx)->harga << endl;
        cout << "Stok : " << (arr + idx)->stok << endl;
    } else if (cara == 1 || cara == 2) {
        cout << "\nBarang ga ditemukan!" << endl;
    }
    delete[] arr;
}

void menukaryawan() {
    int pilih;
    do {
        system("cls");
        cout << "========================" << endl;
        cout << "     Halo Karyawan!" << endl;
        cout << "========================" << endl;
        cout << "1. Tambah data barang" << endl;
        cout << "2. Lihat data barang" << endl;
        cout << "3. Edit data barang" << endl;
        cout << "4. Cari data barang" << endl;
        cout << "5. Logout" << endl;
        cout << "========================" << endl;
        cout << "Pilih menu: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambahdatabarang(); break;
            case 2: lihatdatabarang(); break;
            case 3: editdatabarang(); break;
            case 4: caridatabarang(); break;
            case 5: break;
            default: cout << "Salah input bro!" << endl;
        }
        if (pilih != 5) system("pause");
    } while (pilih != 5);
}

int main() {
    int pilih;
    do {
        system("cls");
        cout << "========== WELCOME TO COCOA HEAVEN ==========" << endl;
        cout << "1. Login Admin" << endl;
        cout << "2. Karyawan" << endl;
        cout << "3. Keluar" << endl;
        cout << "=============================================" << endl;
        cout << "Masukkan pilihan menu: ";
        cin >> pilih;

        switch (pilih) {
            case 1: loginadmin(); break;
            case 2: menukaryawan(); break;
            case 3: cout << "Sampai Jumpa!" << endl; break;
            default: cout << "Pilihan error!" << endl; system("pause");
        }
    } while (pilih != 3);

    return 0;
}