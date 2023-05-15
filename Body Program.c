/* Library Local */

#include "Header.h"

/* Body Program */
table ReadResolution()
{
    table Result;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    Result.columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    Result.rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return Result;
}
void printc(char Pesan[])
{
    int columns = ReadResolution().columns;
    if (((columns - strlen(Pesan)) / 2) > 1)
    {
        for (size_t i = 0; i < ((columns - strlen(Pesan)) / 2); i++)
        {
            printf(" ");
        }
    }
    // ^ Printf spasi sebanyak yang dibutuhkan teks agar memiliki posisi tengah

    printf("%s", Pesan);
    // ^ Print pesan yang ingin diletakan di tengah layar
}

void printn(char Pesan[])
{
    int columns = ReadResolution().columns/2;
    for (size_t i = 0; i < ((columns - strlen(Pesan)) / 2 + 1); i++)
    {
        printf(" ");
    }
    printf("%s", Pesan);
}

void prints(char Pesan[]){
    int columns = ReadResolution().columns/2;
    for (size_t i = 0; i < ((columns - strlen(Pesan)) / 2 + 1); i++)
    {
        printf(" ");
    }
}

void CenterVertical(int line)
{
    for (size_t i = 0; i < ((ReadResolution().rows / 2) - line); i++)
    {
        printf("\n");
    }
}

address Alokasi(info NamaPelanggan, int jmlTiket, struct tm waktuDatang, struct tm waktuEstimasi)
{
    address P;

    P = (address)malloc(sizeof(Pelanggan));

    if (!P)
    {
        prints(" ");printf("Memori Penuh!");
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
    return (loket.front == NULL);
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
    int arg;
    // Memeriksa apakah ada loket kosong, jika iya, insert ke dalam loket tersebut
    for (int i = 0; i < jumlahLoket; i++)
    {
        if (!FindLoket && isEmpty(Loket[i]))
        {
            insertPelanggan(&Loket[i], input);
            FindLoket = true;
            arg = i;
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
                arg = i;
            }
        }
        insertPelanggan(LoketRekomendasi, input);
    }

    //Delete Queue
    //DeleteNodeQueue(Loket[arg]); minimal bisa jalan bentar
}

void DeleteNodeQueue(LinkedList Loket)
{
    struct tm *local;
    time_t t = time(NULL);
    local = localtime(&t);

    if (Loket->front != NULL && (Loket->front->waktuEstimasi.tm_hour > local->tm_hour ||
        (Loket->front->waktuEstimasi.tm_hour == local->tm_hour &&Loket->front->waktuEstimasi.tm_min > local->tm_min) ||
        (Loket->front->waktuEstimasi.tm_hour == local->tm_hour &&Loket->front->waktuEstimasi.tm_min == local->tm_min &&Loket->front->waktuEstimasi.tm_sec >= local->tm_sec))) {

        address temp = Loket->front;
        Loket->front = Loket->front->next;

        if (Loket->front != NULL) {
            Loket->front->prev = NULL;
        } else {
            Loket->rear = NULL;
        }

        free(temp);
    }
}

void HeaderCGV()
{
    system("cls");
    printc("============================================================\n");
    printc(" .----------------.  .----------------.  .----------------. \n");
    printc("| .--------------. || .--------------. || .--------------. |\n");
    printc("| |     ______   | || |    ______    | || | ____   ____  | |\n");
    printc("| |   .' ___  |  | || |  .' ___  |   | || ||_  _| |_  _| | |\n");
    printc("| |  / .'   \\_|  | || | / .'   \\_|   | || |  \\ \\   / /   | |\n");
    printc("| |  | |         | || | | |    ____  | || |   \\ \\ / /    | |\n");
    printc("| |  \\ `.___.'\\  | || | \\ `.___]  _| | || |    \\ ' /     | |\n");
    printc("| |   `._____.'  | || |  `._____.'   | || |     \\_/      | |\n");
    printc("| |              | || |              | || |              | |\n");
    printc("| '--------------' || '--------------' || '--------------' |\n");
    printc(" '----------------'  '----------------'  '----------------' \n");
    printc("============================================================\n");
}
void SecondMenu(Pelanggan *User, Film propertiFilm[], LinkedList Loket[], int *pilihanUser, int *jmlhTiket)
{
    int cekBangku = 0;
    time_t t = time(NULL);
    struct tm *local_time = localtime(&t);
    HeaderCGV();
    prints(" ");printf("Selamat Datang di Bioskop CGV Tuan/Nyonya %s \n", (*User).namaPelanggan);
    prints(" ");printf("Antrian Saat Ini: (Nama) (Jumlah Tiket) (Estimasi Selesai)\n");
    tampilAntreanLoket(Loket);
    prints(" ");printf("Berikut Daftar Film yang Tersedia Pada Hari %s", asctime(local_time));
    prints(" ");printf("__________________________________________________________\n");
    prints(" ");printf("| %-5s | %-20s | %-10s | %-10s |\n", "No", "Judul", "Ruangan", "Jam Tayang");
    prints(" ");printf("__________________________________________________________\n");
    for (int i = 0; i < 9; i++)
    {
        if(cekBangku = bangkuTersedia(propertiFilm, i+1) != 0) {
            prints(" ");printf("| %-5d | %-20s | %-10d | %d : %d : %d |\n", i + 1, propertiFilm[i].judul, propertiFilm[i].ruang, propertiFilm[i].waktuTayang.tm_hour, propertiFilm[i].waktuTayang.tm_min, propertiFilm[i].waktuTayang.tm_sec);
        } else {
            prints(" ");printf("| %-5d | Film %s Sudah Habis Tiketnya!! |\n", i + 1, propertiFilm[i].judul);
        }
    }
    prints(" ");printf("__________________________________________________________\n");
    prints(" ");printf("Silahkan Input Pilihan Anda: ");
    scanf("%d", pilihanUser);
startJumlahTiket:
    prints(" ");printf("Jumlah Tiket yang dipesan: ");
    scanf("%d", jmlhTiket);
    (*User).TiketDipesan = *jmlhTiket;
    cekBangku = bangkuTersedia(propertiFilm, *pilihanUser);
    if(*jmlhTiket > cekBangku || *jmlhTiket == 0) {
        prints(" ");printf("Jumlah Tiket yang Dipesan Melebihi yang Tersedia!!\n");
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
        prints(" ");printf(" %-5s: %-20s\n", "Film", propertiFilm[pilihanUser - 1].judul);
        prints(" ");printf(" %-5s: %d\n", "Ruangan", propertiFilm[pilihanUser - 1].ruang);
        prints(" ");printf(" %-5s: %d : %d : %d\n", "Jam Tayang", propertiFilm[pilihanUser - 1].waktuTayang.tm_hour, propertiFilm[pilihanUser - 1].waktuTayang.tm_min, propertiFilm[pilihanUser - 1].waktuTayang.tm_sec);
        prints(" ");printf("Kursi yang Tersedia\n");
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
                printf("\n ");prints(" ");printf("________________________________\n");
                prints(" ");printf("|%s-%-2d|", pesan, i + 1);
            }
            else
            {
                printf("%s-%-2d|", pesan, i + 1);
            }
        }
    StartPilihKursi:
        printf("\n");prints(" ");printf("Silahkan Pilih Kursi Anda: ");
        scanf("%d", &inputan);
        if (propertiFilm[pilihanUser - 1].listBangku[inputan - 1] == TRUE)
        {
            prints(" ");printf("Kursi yanng anda pilih tidak valid..\n");
            goto StartPilihKursi;
        }
        propertiFilm[pilihanUser - 1].listBangku[inputan - 1] = true;

        system("cls");
    }
}

void MainMenu(Pelanggan *User, int countPelanggan)
{
    HeaderCGV();
    printc("Selamat datang di bioskop CGV\n");
    printc("Silahkan masukan nama anda: ");
    CreatePelanggan(User, countPelanggan);
}

void createPropertiFilm(Film propertiFilm[], int index, const char* judul, int studio, int jam, int menit, int detik)
{
    time_t now = time(NULL);
    struct tm* currentTime = localtime(&now);
    int currentHour = currentTime->tm_hour;

    if (currentHour > jam)
    {
        printf("Film '%s' sudah tidak tersedia.\n", judul);
        return;
    }

    propertiFilm[index].idFilm = index;
    strcpy(propertiFilm[index].judulFilm, judul);
    propertiFilm[index].studio = studio;
    propertiFilm[index].jamTayang.tm_hour = jam;
    propertiFilm[index].jamTayang.tm_min = menit;
    propertiFilm[index].jamTayang.tm_sec = detik;
}

void tampilAntreanLoket(LinkedList List[])
{
    for (int i = 0; i < jumlahLoket; i++)
    {
        prints(" ");printf("Loket %d : ", i + 1);
        prints(" ");printf("\n->");
        if (!isEmpty(List[i]))
        {
            address travelsal = List[i].front;
            while (travelsal != NULL)
            {
                prints(" ");printf("%s (%d)(%d:%d:%d), ", travelsal->namaPelanggan, travelsal->TiketDipesan, travelsal->waktuEstimasi.tm_hour, travelsal->waktuEstimasi.tm_min, travelsal->waktuEstimasi.tm_sec);
                travelsal = travelsal->next;
            }
        }
        prints(" ");printf("\n");
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
    prints(" ");printf("Terimakasih Sudah Memesan Tiket di CGV %s\n", (*User).namaPelanggan);
    prints(" ");printf("Berikut Merupakan Detail dari Pesanan Anda: \n");
    prints(" ");printf("%s Memesan %d Tiket Film %s di Ruangan %d dengan Jadwal Tayang %d : %d : %d\n", (*User).namaPelanggan , (*User).TiketDipesan, propertiFilm[pilihanUser-1].judul,propertiFilm[pilihanUser].ruang,propertiFilm[pilihanUser-1].waktuTayang.tm_hour,propertiFilm[pilihanUser-1].waktuTayang.tm_min,propertiFilm[pilihanUser-1].waktuTayang.tm_sec);
    startPenilaian:
    prints(" ");printf("Silahkan Beri Penilaian Untuk Kami (1-5): ");
    scanf("%d",&penilaianPelanggan);
    if(penilaianPelanggan < 1 || penilaianPelanggan > 5) {
        prints(" ");printf("Input Invalid Tolong Input dengan Benar!\n");
        goto startPenilaian;
    }
}

void Konfirmasi(char Anchor){
    HeaderCGV();
    printc("Apakah ingin lanjut memesan?\n");
    printc("(Y/N)\n");
    scanf("%c",&Anchor);
    return Anchor;
}