/* Define */

#ifndef Header_h
#define Header_h

#define Nil NULL

/* Library C */

#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

#define jumlahLoket 3
#define jumlahFilm 9

/* Tipe Data Bentukan */

typedef char *info;
typedef struct tPelanggan *address;

typedef struct
{
    info judul;
    int ruang;
    bool listBangku[32];
    struct tm waktuTayang;
}Film;

typedef struct //Digunakan untuk menampung pelanggan dan ruangan (?)
{
    address front;
    address rear;
}LinkedList;

typedef struct tPelanggan
{
    int idPelanggan;
    info namaPelanggan;
    int TiketDipesan;
    struct tm waktuDatang;
    struct tm waktuEstimasi;
    address next;
    address prev;
}Pelanggan;

typedef struct
{
    int rows, columns;
} table;

/* Modul Program */
table ReadResolution();
void printc(char Pesan[]);
void CenterVertical(int line);
void printn(char Pesan[]);
void prints(char Pesan[]);

void CreatePelanggan(Pelanggan *User, int countPelanggan);
/* Membentuk sebuah node untuk diisi data seorang pelanggan */
/*
    IS: Pelanggan belum terbentuk pada program
    FS: Pelanggan sudah terbentuk dan sudah bisa ditambah propertinya
*/

void CreateList(LinkedList *X);
/* Berfungsi untuk membentuk struktur data Linked List yang nantinya akan digunakan untuk menyimpan data Film dan Ruangan*/
/*
    IS: LInked list untuk menampung data film dan ruangan belum terbentuk
    FS: Linked list untuk menampung data film dan ruangan telah terbentuk
*/

void TambahAntrean(LinkedList Loket[], Pelanggan input);
/* Berfungsi untuk membentuk struktur data Linked List yang nantinya akan digunakan untuk menyimpan data Film dan Ruangan*/
/*
    IS: Data pelanggan belum dimasukan dalam antrean 
    FS: Data pelanggan sudah  dimasukan dalam posisi terakhir antrean
*/

void HeaderCGV();
/* Membuat ASCII art yang digunakan sebagai header tampilan program*/

void SecondMenu(Pelanggan *User, Film propertiFilm[], LinkedList Loket[], int *pilihanUser, int *jmlhTiket);
/* Menampilkan tampilan kedua pada program dan menerima input dari user */

void MainMenu(Pelanggan *User, int countPelanggan);
/* Menampilkan tampilan utama pada program dan menerima input dari user */

void createPropertiFilm(Film propertiFilm[], int index, info Judul, int ruang, int jam, int menit, int detik);
/* Membentuak sebuah variabel untuk menampung properti untuk sebuah film */
/*
    IS: propertiFilm belum terbentuk
    FS: propertiFilm sudah terbentuk dan siap dioperasikan 
*/

void ThirdMenu(int pilihanUser, Film propertiFilm[], int jmlhTiket);
/* Menampilkan tampilan ketiga pada program dan menerima input dari user */

void tampilAntreanLoket(LinkedList List[]);
/* Menampilkan UI yang berisi loket dan pelanggan yang mengantri */
/*
    IS: antrian loket belum ditampikan
    FS: menampilkan pelanggan yang ada pada antrian (baik ada maupun tidak ada
*/

int bangkuTersedia(Film Bangku[], int pilihanUser);
/* Pengecekan ketersediaan kursi di ruangan ketika pelanggan membeli tiket */
/*
    IS: Jumlah kursi kosong di ruangan belum diketahui
    FS: Jumlah kursi kosong di ruangan setelah pelanggan membeli tiket diketahui
*/

address Alokasi(info NamaPelanggan, int jmlTiket, struct tm waktuDatang, struct tm waktuEstimasi);
/* Untuk mengalokasi memori yang nanti nya akan digunakan pada program */
/*
    IS: Variabel belum memesan memori
    FS: Variabel sudah memesan memori dan sudah dapat dioperasikan
*/

bool isEmpty(LinkedList loket);
/* Pengecekan antrean apakah antean kosong atau tidak */
/*
    IS: Kondisi antrean tidak diketahui
    FS: Kondisi antrean sudah diketahui 
*/

void MenuAkhir(Pelanggan *User, Film propertiFilm[], int pilihanUser);
/* Menampilkan menu akhir setelah seorang pelanggan selesai melakukan pembelian tiket */

void initialisasiList(LinkedList list[]);
/* Membentuk / Menginisialisasi sebuah linked list yang nanti nya akan dipergunakan sebagai loket yang menampung antrian */
/*
    IS: Belum terbentuk sebuah list untuk menampung antrian (Loket) 
    FS: Sudah terbentuk loket untuk menampung antrian 
*/

void DeleteNodeQueue(LinkedList Loket);
/* Menghapus node Pelanggan dalam Queue setelah melewati waktu tertentu*/
/*
    IS: Node pelanggan pada Queue yang ditunjuk head belum dihapus
    FS: Node pelanggan pada Queue yang ditunjuk head dihapus, dan digantikan node setelahnya
*/

void DeleteNodeQueue(LinkedList Loket);

#endif