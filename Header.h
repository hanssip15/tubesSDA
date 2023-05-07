/* Define */

#ifndef Header_h
#define Header_h

#define Nil NULL

/* Library C */

#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

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

/* Modul Program */
void CreatePelanggan(Pelanggan *User, int countPelanggan);
/**/
/*


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
//

void SecondMenu(Pelanggan *User, Film propertiFilm[], LinkedList Loket[], int *pilihanUser, int *jmlhTiket);
//

void MainMenu(Pelanggan *User, int countPelanggan);
//

void createPropertiFilm(Film propertiFilm[], int index, info Judul, int ruang, int jam, int menit, int detik);
//

void ThirdMenu(int pilihanUser, Film propertiFilm[], int jmlhTiket);
void tampilAntreanLoket(LinkedList List[]);
int bangkuTersedia(Film Bangku[], int pilihanUser);
address Alokasi(info NamaPelanggan, int jmlTiket, struct tm waktuDatang, struct tm waktuEstimasi);
bool isEmpty(LinkedList loket);
void MenuAkhir(Pelanggan *User, Film propertiFilm[], int pilihanUser);
void DeleteNodeQueue(LinkedList Loket[], int i);
#endif