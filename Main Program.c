/* Library Local */

#include "Body Program.c"


int main()
{
    Pelanggan User;
    LinkedList Loket[jumlahLoket];
    Film propertiFilm[jumlahFilm];
    int pilihanUser, jmlhTiket;

    char anchor = 'Y';

    int countPelanggan = 0;

    // INITIALISASI
    createPropertiFilm(propertiFilm, 0, "Disney Mermaid", 1, 10, 00, 00);
    createPropertiFilm(propertiFilm, 1, "Conjuring", 2, 10, 00, 00);
    createPropertiFilm(propertiFilm, 2, "Buya Hamka", 3, 10, 00, 00);
    createPropertiFilm(propertiFilm, 3, "Buya Hamka", 1, 15, 00, 00);
    createPropertiFilm(propertiFilm, 4, "Disney Mermaid", 2, 15, 00, 00);
    createPropertiFilm(propertiFilm, 5, "Conjuring", 3, 15, 00, 00);
    createPropertiFilm(propertiFilm, 6, "Conjuring", 1, 21, 00, 00);
    createPropertiFilm(propertiFilm, 7, "Buya Hamka", 2, 21, 00, 00);
    createPropertiFilm(propertiFilm, 8, "Disney Mermaid", 3, 21, 00, 00);

    initialisasiList(Loket);
    // INITIALISASI

    while (anchor == 'Y' || anchor == 'y')
    {
        MainMenu(&User, countPelanggan);
        SecondMenu(&User, propertiFilm, Loket, &pilihanUser, &jmlhTiket);
        ThirdMenu(pilihanUser, propertiFilm, jmlhTiket);
        MenuAkhir(&User,propertiFilm,pilihanUser);
        TambahAntrean(Loket, User);
        Konfirmasi(anchor);
    }
    return 0;
}
