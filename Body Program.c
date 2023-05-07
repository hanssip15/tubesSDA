/* Library Local */

#include "Header.h"

/* Body Program */

address Alokasi(info NamaPelanggan, int jmlTiket, struct tm waktuDatang, struct tm waktuEstimasi)
{
    address P;

    P = (address)malloc(sizeof(Pelanggan));

    if (!P)
    {
        printf("Memori Penuh!");
        getch();
        exit(0);
    }
    else
    {
        P->namaPelanggan = NamaPelanggan;
        P->TiketDipesan = jmlTiket;
        P->waktuDatang = waktuDatang;
        P->waktuEstimasi = waktuEstimasi;

        P->next = Nil;
        P->prev = Nil;
    }

    return P;
}

void CreatePelanggan(Pelanggan *User, int countPelanggan)
{
    (*User).next = Nil;
    (*User).prev = Nil;
    (*User).idPelanggan = countPelanggan + 1;
    (*User).namaPelanggan = Nil;
    (*User).namaPelanggan = (info)malloc(sizeof(char) * 100);
    scanf(" %[^\n]", User->namaPelanggan);
}
void initialisasiList(LinkedList list[])
{
    for (size_t i = 0; i < jumlahLoket; i++)
    {
        CreateList(&list[i]);
    }
}
void CreateList(LinkedList *X)
{
    X->front = Nil;
    X->rear = Nil;
}
bool isEmpty(LinkedList loket)
{
    if (loket.front == NULL)
        return true;
    return false;
}
struct tm convertSecondsToTime(long seconds)
{
    struct tm timeinfo = {0};
    timeinfo.tm_hour = seconds / 3600;       // Jumlah jam
    timeinfo.tm_min = (seconds % 3600) / 60; // Jumlah menit
    timeinfo.tm_sec = (seconds % 3600) % 60; // Jumlah detik

    return timeinfo;
}
int convertTMtosecond(struct tm input)
{
    return ((input.tm_hour * 3600) + (input.tm_min * 60) + input.tm_sec);
}
void insertPelanggan(LinkedList *Loket, Pelanggan input)
{
    time_t t = time(NULL);               // Mendapatkan waktu saat ini dalam time_t
    struct tm *timeinfo = localtime(&t); // Mendapatkan waktu lokal dalam struct tm

    address newPelanggan = Alokasi(input.namaPelanggan, input.TiketDipesan, input.waktuDatang, input.waktuEstimasi);
    newPelanggan->waktuDatang = *timeinfo;
    if (isEmpty(*Loket))
    {
        (*Loket).front = newPelanggan;

        *timeinfo = convertSecondsToTime(convertTMtosecond(*timeinfo) + (newPelanggan->TiketDipesan * 60));
        newPelanggan->waktuEstimasi = *timeinfo;
    }
    else
    {
        address LastPelanggan = (*Loket).rear;
        newPelanggan->prev = LastPelanggan;
        LastPelanggan->next = newPelanggan;

        int tambahan = 0;
        tambahan = (convertTMtosecond(LastPelanggan->waktuEstimasi) - convertTMtosecond(*timeinfo));
        if (tambahan < 0)
        {
            tambahan = 0;
        }

        *timeinfo = convertSecondsToTime(convertTMtosecond(*timeinfo) + (newPelanggan->TiketDipesan * 60) + tambahan);
        newPelanggan->waktuEstimasi = *timeinfo;
    }
    (*Loket).rear = newPelanggan;
}

void TambahAntrean(LinkedList Loket[], Pelanggan input)
{
    bool FindLoket = false;
    // Memeriksa apakah ada loket kosong, jika iya, insert ke dalam loket tersebut
    for (int i = 0; i < jumlahLoket; i++)
    {
        if (!FindLoket && isEmpty(Loket[i]))
        {
            insertPelanggan(&Loket[i], input);
            FindLoket = true;
        }
    }

    // Jika tidak ada loket kosong, cari loket dengan waktu estimasi akhir paling kecil
    if (!FindLoket)
    {
        LinkedList *LoketRekomendasi = &Loket[0];
        for (size_t i = 1; i < jumlahLoket; i++)
        {
            if (convertTMtosecond(Loket[i].rear->waktuEstimasi) < convertTMtosecond((*LoketRekomendasi).rear->waktuEstimasi))
            {
                LoketRekomendasi = &Loket[i];
            }
        }
        insertPelanggan(LoketRekomendasi, input);
    }
}

void HeaderCGV()
{
    printf("============================================================\n");
    printf(" .----------------.  .----------------.  .----------------. \n");
    printf("| .--------------. || .--------------. || .--------------. |\n");
    printf("| |     ______   | || |    ______    | || | ____   ____  | |\n");
    printf("| |   .' ___  |  | || |  .' ___  |   | || ||_  _| |_  _| | |\n");
    printf("| |  / .'   \\_|  | || | / .'   \\_|   | || |  \\ \\   / /   | |\n");
    printf("| |  | |         | || | | |    ____  | || |   \\ \\ / /    | |\n");
    printf("| |  \\ `.___.'\\  | || | \\ `.___]  _| | || |    \\ ' /     | |\n");
    printf("| |   `._____.'  | || |  `._____.'   | || |     \\_/      | |\n");
    printf("| |              | || |              | || |              | |\n");
    printf("| '--------------' || '--------------' || '--------------' |\n");
    printf(" '----------------'  '----------------'  '----------------' \n");
    printf("============================================================\n");
}
void SecondMenu(Pelanggan *User, Film propertiFilm[], LinkedList Loket[], int *pilihanUser, int *jmlhTiket)
{
    int cekBangku = 0;
    time_t t = time(NULL);
    struct tm *local_time = localtime(&t);
    HeaderCGV();
    printf("Selamat Datang di Bioskop CGV Tuan/Nyonya %s \n", (*User).namaPelanggan);
    printf("Antrian Saat Ini: (Nama) (Jumlah Tiket) (Estimasi Selesai)\n");
    tampilAntreanLoket(Loket);
    printf("Berikut Daftar Film yang Tersedia Pada Hari %s", asctime(local_time));
    printf("__________________________________________________________\n");
    printf("| %-5s | %-20s | %-10s | %-10s |\n", "No", "Judul", "Ruangan", "Jam Tayang");
    printf("__________________________________________________________\n");
    for (int i = 0; i < 9; i++)
    {
        if(cekBangku = bangkuTersedia(propertiFilm, i+1) != 0) {
            printf("| %-5d | %-20s | %-10d | %d : %d : %d |\n", i + 1, propertiFilm[i].judul, propertiFilm[i].ruang, propertiFilm[i].waktuTayang.tm_hour, propertiFilm[i].waktuTayang.tm_min, propertiFilm[i].waktuTayang.tm_sec);
        } else {
            printf("| %-5d | Film %s Sudah Habis Tiketnya!! |\n", i + 1, propertiFilm[i].judul);
        }
    }
    printf("__________________________________________________________\n");
    printf("Silahkan Input Pilihan Anda: ");
    scanf("%d", pilihanUser);
startJumlahTiket:
    printf("Jumlah Tiket yang dipesan: ");
    scanf("%d", jmlhTiket);
    (*User).TiketDipesan = *jmlhTiket;
    cekBangku = bangkuTersedia(propertiFilm, *pilihanUser);
    if(*jmlhTiket > cekBangku || *jmlhTiket == 0) {
        printf("Jumlah Tiket yang Dipesan Melebihi yang Tersedia!!\n");
        goto startJumlahTiket;
    } 
}
void ThirdMenu(int pilihanUser, Film *propertiFilm, int jmlhTiket)
{
    int i;
    int inputan = 0;

    for (int jmlTiketloop = 0; jmlTiketloop < jmlhTiket; jmlTiketloop++)
    {
        HeaderCGV();
        printf(" %-5s: %-20s\n", "Film", propertiFilm[pilihanUser - 1].judul);
        printf(" %-5s: %d\n", "Ruangan", propertiFilm[pilihanUser - 1].ruang);
        printf(" %-5s: %d : %d : %d\n", "Jam Tayang", propertiFilm[pilihanUser - 1].waktuTayang.tm_hour, propertiFilm[pilihanUser - 1].waktuTayang.tm_min, propertiFilm[pilihanUser - 1].waktuTayang.tm_sec);
        printf("Kursi yang Tersedia\n");
        for (i = 0; i < 32; i++)
        {
            char pesan[2];
            if (propertiFilm[pilihanUser - 1].listBangku[i] == true)
            {
                strcpy(pesan, "X");
            }
            else
            {
                strcpy(pesan, "O");
            }
            if (i % 6 == 0)
            {
                printf("\n________________________________");
                printf("\n|%s-%-2d|", pesan, i + 1);
            }
            else
            {
                printf("%s-%-2d|", pesan, i + 1);
            }
        }
    StartPilihKursi:
        printf("\nSilahkan Pilih Kursi Anda: ");
        scanf("%d", &inputan);
        if (propertiFilm[pilihanUser - 1].listBangku[inputan - 1] == TRUE)
        {
            printf("Kursi yanng anda pilih tidak valid..\n");
            goto StartPilihKursi;
        }
        propertiFilm[pilihanUser - 1].listBangku[inputan - 1] = true;

        system("cls");
    }
}

void MainMenu(Pelanggan *User, int countPelanggan)
{
    HeaderCGV();
    printf("Selamat datang di bioskop CGV\n");
    printf("Silahkan masukan nama anda: \n");
    CreatePelanggan(User, countPelanggan);
}
// void createPropertiFilm(Film *propertiFilm) {
//     int i;
//     for (i=0; i<3; i++) {
//         propertiFilm[i].judul = "Cinta Sejati";
//         propertiFilm[i].ruang = 23;
//         propertiFilm[i].waktuTayang = 10.00;
//     }
// }

void createPropertiFilm(Film propertiFilm[], int index, info Judul, int ruang, int jam, int menit, int detik)
{
    int i, j;
    propertiFilm[index].judul = Judul;
    propertiFilm[index].ruang = ruang;

    struct tm tm_time = {0}; // Inisialisasi struktur tm dengan 0

    // Mengisi komponen waktu dalam struktur tm
    tm_time.tm_hour = jam;
    tm_time.tm_min = menit;
    tm_time.tm_sec = detik;

    propertiFilm[index].waktuTayang = tm_time;
    for (i = 0; i < jumlahFilm; i++)
    {
        for (j = 0; j < 32; j++)
        {
            propertiFilm[i].listBangku[j] = FALSE;
        }
    }
}

void tampilAntreanLoket(LinkedList List[])
{
    for (int i = 0; i < jumlahLoket; i++)
    {
        printf("Loket %d :\n-> ", i + 1);
        if (!isEmpty(List[i]))
        {
            address travelsal = List[i].front;
            while (travelsal != NULL)
            {
                printf("%s (%d)(%d:%d:%d), ", travelsal->namaPelanggan, travelsal->TiketDipesan, travelsal->waktuEstimasi.tm_hour, travelsal->waktuEstimasi.tm_min, travelsal->waktuEstimasi.tm_sec);
                travelsal = travelsal->next;
            }
        }
        printf("\n");
    }
}
int bangkuTersedia(Film Bangku[], int pilihanUser) {
    int i,cekBangku = 0;
    for (i=0; i<32; i++) {
        if(Bangku[pilihanUser-1].listBangku[i] == FALSE) {
            cekBangku++;
        }
    }
    return cekBangku;
}
void MenuAkhir(Pelanggan *User,Film propertiFilm[],int pilihanUser) {
    HeaderCGV();
    int penilaianPelanggan;
    printf("Terimakasih Sudah Memesan Tiket di CGV %s\n", (*User).namaPelanggan);
    printf("Berikut Merupakan Detail dari Pesanan Anda: \n");
    printf("%s Memesan %d Tiket Film %s di Ruangan %d dengan Jadwal Tayang %d : %d : %d\n", (*User).namaPelanggan , (*User).TiketDipesan, propertiFilm[pilihanUser-1].judul,propertiFilm[pilihanUser].ruang,propertiFilm[pilihanUser-1].waktuTayang.tm_hour,propertiFilm[pilihanUser-1].waktuTayang.tm_min,propertiFilm[pilihanUser-1].waktuTayang.tm_sec);
    startPenilaian:
    printf("\nSilahkan Beri Penilaian Untuk Kami (1-5): ");
    scanf("%d",&penilaianPelanggan);
    if(penilaianPelanggan < 1 || penilaianPelanggan > 5) {
        printf("Input Invalid Tolong Input dengan Benar!\n");
        goto startPenilaian;
    }

   
}