#include <stdio.h>
#include <time.h>

const char* namaHariIndo(int hari) {
    const char* namaHari[] = {
        "Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"
    };
    return namaHari[hari];
}

const char* namaBulanIndo(int bulan) {
    const char* namaBulan[] = {
        "Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli",
        "Agustus", "September", "Oktober", "November", "Desember"
    };
    return namaBulan[bulan];
}

void waktu() {
    time_t rawtime;
    struct tm* info;
    char buffer[80];

    time(&rawtime);
    info = localtime(&rawtime);

    int hari = info->tm_wday;
    const char* hariIndo = namaHariIndo(hari);
    int tanggal = info->tm_mday;
    int bulan = info->tm_mon;
    const char* bulanIndo = namaBulanIndo(bulan);
    int tahun = info->tm_year + 1900;
    int jam = info->tm_hour;
    int menit = info->tm_min;
    int detik = info->tm_sec;

    snprintf(buffer, sizeof(buffer), "%s, %d %s %d Pukul: %02d:%02d:%02d", hariIndo, tanggal, bulanIndo, tahun, jam, menit, detik);

    printf("Berikut Merupakan List Film yang Akan Tayang Pada Hari %s\n", buffer);

}
