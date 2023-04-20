#ifndef BTREEKAMUS_H
#define BTREEKAMUS_H
#include <windows.h>
#include <stdbool.h>
#include "NonRestricted.h"
/* Informasi Author
    Nama        :   1. Roy Aziz Barera (Ketua)  221524030
                    2. Naila Saniyah Nur'aini   221524024
                    3. Retryanzani Dwi Fauzan   221524028
    Kelas       :   1A
    Prodi       :   D4 Teknik Informatika
    Tanggal     :   29/3/2023
*/
#define MAX_BUFFER 4092
typedef char *String;

typedef struct kamus
{
    String Sunda, Indonesia, Contoh;
} Kamus;

typedef struct binary *Address;
typedef struct binary
{
    int Height;
    Address Left, Right;
    Kamus Kamus;
} Binary;

/* ==================================================== */
/* ================= Coding Area Roy ================== */

/* Modul amogus-9 */
/* Mengambil index dari kursor
    I.S: -
    F.S: -
*/
HWND WINAPI GetConsoleWindowNT(void);

/* Mengatur tata letak kursor untuk output layar
    I.S: diketahui index baris yang akan di setting
    F.S: kursor program akan menunjuk ke index yang sudah di tentukan di parameter
*/
void Koor(int Baris, int Kolom);

/* Mengatur warna dari teks yang muncul di layar
    I.S: diketahui kode background dan foreground, kode sudah di define di dalam body
    F.S: membuat teks yang ada di layar sesuai dengan kode backgorund dan foreground yang ada pada parameter
*/
void SetColor(int kode1, int kode2);

/* Mengatur warna dari teks yang muncul di layar menjadi background hitam dan teks berwarna putih
    I.S: teks dilayar masih acak warnanya
    F.S: teks sudah berwarna putih dan background berwarna hitam
*/
void DefaultColor();

/* Berguna untuk menampilkan pesan error
    I.S: pesan yang dikirim pada parameter belum tampil
    F.S: pesan yang dikirim di parameter sudah tampil dan berwarna merah
*/
void ErrorMsg(String ErrorMessage);

/* Berguna untuk menampilkan pesan sukses
    I.S: pesan yang dikirim pada parameter belum tampil
    F.S: pesan yang dikirim di parameter sudah tampil dan berwarna hijau
*/
void SuccMsg(String SuccesMessage);

/* Modul */
/* Untuk menampilkan menu dan memilihnya
    I.S: menu belum tampil ke layar
    F.S: menu sudah tampil ke layar dan mengembalikan nilai yang sudah dipilih di menu
*/
int Menu();

/* Untuk mengkonfirmasi kepada pengguna untuk menekan tombol apapun untuk lanjut ke tahap berikutnya
    I.S: belum ada teks apapun yang tampil ke layar
    F.S: teks tekan tombol apapun untuk melanjutkan...
*/
void Pause();

/* Hanya untuk memvalidasi pilihan kepada pengguna yang hanya dapat menampung y atau n saja
    I.S: belum tampil ke layar pilihan y atau n
    F.S: sudah tampil ke layar pilihan y atu n dan juga akan mengembalikan nilai true jika pengguna
            menekan tombol y dan false jika n
*/
bool Validasi();

/* Hanya untuk animasi keluar aplikasi saja
    I.S: belum tampil animasi keluar program
    F.S: sudah tampil animasi keluar program
*/
void ExitApps();

/* Main Excute */
/* Untuk mengeksekusi pilihan yang sudah dipilih di modul menu
    I.S: pilihan menu sudah diketahui
    F.S: mengeksekusi menu yang sudah di pilih mengggunaakn switch case
*/
void Execute(int Choice, Address *Tree, bool *Exit);

/* ==================================================== */
/* ==================================================== */

/* Modul Insert Yang dibutuhkan */
/* Untuk menambahkan kosakata baru ke dalam file dan juga struktur data tree saat ini
    I.S: Kosakata baru belum masuk ke dalam tree dan juga belum tertulis di file
    F.S: Kosakata baru sudah masuk ke dalam tree dan juga sudah tertulis di file
*/
void InsertKata(Address *Tree);

/* Untuk melakukan input perulangan pada saat memasukan sebuah kosakata baru ke dalam satu
    variabel misal variabel : Sunda / Indonesia / Contoh dalam tipe data String atau Pointer Of Char
    I.S: Variabel kamus belum terisi kosakata apapun
    F.S: Variabel kamus sudah terisi kosakata yang diinputkan pengguna
*/
void InputKamus(String *NewVocab);

/* Untuk menampung proses input pada saat melakukan inputan kosakata baru yang di panggil di modul InsertKata
    I.S: String NewVocab belum di tambahkan kosakata baru
    F.S: String NewVocab sudah di tambahkan kosakata baru
*/
void Input(String *NewVocab);

/* Untuk menuliskan String apapun ke dalam file Kamus-Sunda-Indonesia.dat / Namun untuk kasus ini saya menuliskan
    gabungan kosakata bahasa sunda,indonesia dan juga contohnya dengan contoh format "Abi,Urang,Aing.=Saya,Aku,Gueh.(Abi ganteng pisan.)"
    I.S: String yang ada di parameter belum dituliskan kedalam file Kamus-Sunda-Indonesia.dat
    F.S: String yang ada di parameter sudah dituliskan kedalam file Kamus-Sunda-Indonesia.dat
*/
void InsertToFile(String NewVocab);

/* Untuk menuliskan String yang ada di parameter NewVocab ke dalam file di End Of File
    I.S: String di parameter NewVocab belum tertulis di dalam file
    F.S: String di parameter NewVocab belum tertulis di dalam file pada End Of File
*/
String MergeKamus(Kamus NewKamus);

/* Mengubah sebuah string yang mengandung karakter apa(CharFrom) di ubah ke karakter apa(CharThis)
    I.S: Karakter yang ada di string belum berubah sesuai dengan yang sudah di perintahd di parameter
    F.S: Karakter yang ada di string sudah berubah sesuai dengan yang sudah di perintahd di parameter
*/
void ConvFromCharToChar(String *Vocab, char CharFrom, char CharThis);

/* ==================================================== */
/* ==================================================== */

/* Menambahkan kosakata baru ke dalam struktur tree yang ada di program, namun proses insertnya ini
    perkosakata bahasa sunda sehingga memudahkan nanti saat proses pencarian
    I.S: Kosakata baru belum bertambah di struktur data tree
    F.S: Kosakata baru sudah bertambah di struktur data tree
*/
void InsertToTree(Address *Tree, Kamus NewKamus);

/* Mengalokasikan satu buah alamat untuk struktur data tree
    I.S: Belum membuat alamat baru sebesar struktur data Binary
    F.S: Sudah membuat alamat baru sebesar struktur data Binary dan mengembalikan alamat tersebut yang sudah di alokasikan
*/
Address AlokTree();

/* Mengalokasikan dan memasukan nilai nilai yang ada di parameter ke dalam alamat binary yang sudah di alokasikan di
    dalamnya
    I.S: Alamat binary belum di alokasikan dan belum terisi oleh nilai yang ada di parameter
    F.S: Alamat binary sudah di alokasikan dan belum terisi oleh nilai yang ada di parameter
*/
Address CreateKamus(Kamus NewKamus, String VocabSunda);

/* Melakukan proses insert suatu alamat baru ke dalam struktur binary tree dengan menggunakan proses rekursif
    I.S: Alamat binary tree yang baru belum masuk ke dalam sturktur data
    F.S: Alamat binary tree yang baru sudah masuk ke dalam sturktur data
*/
void InsertBinaryTree(Address *Tree, Kamus NewKamus, String VocabSunda);

/* Mencetak isi dari binary tree menggunakan teknik rekursif
    I.S: Nilai yang ada di dalam alamat struktur data yang ada di dalam parameter belum tampil ke layar
    F.S: Nilai yang ada di dalam alamat struktur data yang ada di dalam parameter sudah tampil ke layar
*/
void PrintTree(Address Root);

/* Menampilkan isi dari variabel kamus yang terdiri dari string sunda, indonesia dan contoh
    I.S: Isi dari nilai yang ada di kamus belum tampil ke layar
    F.S: Isi dari nilai yang ada di kamus sudah tampil ke layar
*/
void PrintKamus(Kamus Kamus);

void LoadDataKamus(Address *Tree);

void HeaderKamus();

int IsFileValid();

int CountChar(String StrCheck, char CharCheck);
/* ==================================================== */
/* ==================================================== */

/* =============== End Of Coding Area Roy ============= */
/*================Naila================================ */
Address SearchTree(Address Root, String Input);
void SearchKata(Address Tree);
/*================Naila================================ */
#endif // !BTREEKAMUS_H