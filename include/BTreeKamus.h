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
#define MAX_BUFFER 1024
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

/*================ BALANCING ==============*/
typedef struct balancing *AddressBalancing;
typedef struct balancing
{
    Kamus Kamus;
    AddressBalancing Next;
} Balancing;

AddressBalancing InitBalance();
/* Menginisialisasikan variabel bertipe AddressBalancing menjadi NULL
    I.S: Function sudah mengembalikan nilai NULL
    F.S: Function sudah mengembalikan nilai NULL
*/

AddressBalancing CreateNodeBalance(Kamus NewKamus);

/* Mengalokasikan memori seukuran satu AddressBalancing dan mengisi info yang ada di dalamnya dengan NewKamus
    I.S: Memori belum teralokasikan dan belum berisikan informasi dari NewKamus
    F.S: Memori sudah teralokasikan dan sudah berisikan informasi dari NewKamus
*/

int BalancingIsEmpty(AddressBalancing Balancing);
/* Mengecek apakah linked list itu kosong apa tidak
    I.S: Belum mengembalikan nilai apapun
    F.S: Mengembalikan nilai 1 jika kosong dan 0 jika tidak kosong
*/

void InsertBalancing(AddressBalancing *Balancing, Kamus NewKamus);
/* Menambahkan node barud di akhir linked list yang berisikan informasi dari NewKamus
    I.S: Node baru belum bertambah pada linked list
    F.S: Node baru sudah bertambah pada linked list
*/

void DeleteBalancing(AddressBalancing *Balancing, String Target);
/* Menghapus node yang memiliki informasi yang sama dengan Target
    I.S: Node yang memiliki informasi yang sama dengan target belum terhapus
    I.S: Node yang memiliki informasi yang sama dengan target sudah terhapus
*/

void BalancingTree(Address *Tree);
/* Mengubah struktur data tree yang tidak balance menjadi balance
    I.S: Struktur tree belum balance
    F.S: Struktur tree sudah balance
*/

void SortBalancing(Address Tree, AddressBalancing *ListBalancing);
/* Mengurutkan informasi yang ada di tree dan dimasukannya kedalam ListBalancing yang merupakan sebuah linked list
    I.S: Data yang ada di tree belum masuk dan belum terurut di dalam Linked List ListBalancing
    F.S: Data yang ada di tree sudah masuk dan sudah terurut di dalam Linked List ListBalancing
*/

void InsertTreeBalancing(Address *Tree, AddressBalancing *ListBalancing);
/* Memasukan informasi yang sudah terurut di dalam ListBalancing ke dalam struktur tree dengan
    mencari informasi yang ada di tengah lalu membagi dua list secara rekursif
    I.S: Tree belum balance
    F.S: Tree sudah balance
*/

AddressBalancing MidBalancing(AddressBalancing NodeBalancing);
/* Mencari lalu mengembalikan alamat linked list yang berisikan informasi tree yang berada di tengah
    untuk dijadikan root
    I.S: Belum mengembalikan alamat linked list yang memegang informasi tree yang berada di posisi tengah
    I.S: Sudah mengembalikan alamat linked list yang memegang informasi tree yang berada di posisi tengah
*/

int CountListBalancing(AddressBalancing ListBalancing);
/* Menghitung seluruh jumlah informasi tree
    I.S: Jumlah seluruh informasi tree belum diketahui
    F.S: Jumlah seluruh informasi tree sudah diketahui dan dikembalikan
*/


/*Cek Apakah sudah seimbang Sumber: https://www.codezclub.com/c-check-binary-tree-avl-tree-or-not/*/
int height(Address ptr);
int isAVL(Address ptr);
/*Cek Apakah sudah seimbang Sumber: https://www.codezclub.com/c-check-binary-tree-avl-tree-or-not/*/

/*================ BALANCING ==============*/

/* ==================================================== */
/* ================= Roy ================== */

/* Modul amogus-9 */

void Koor(int Baris, int Kolom);
/* Mengatur tata letak kursor untuk output layar
    I.S:
    F.S: kursor program akan menunjuk ke index yang sudah di tentukan di parameter
*/

void SetColor(int kode1, int kode2);
/* Mengatur warna dari teks yang muncul di layar
    I.S: diketahui kode background dan foreground, kode sudah di define di dalam body
    F.S: membuat teks yang ada di layar sesuai dengan kode backgorund dan foreground yang ada pada parameter
*/

void DefaultColor();
/* Mengatur warna dari teks yang muncul di layar menjadi background hitam dan teks berwarna putih
    I.S: teks dilayar masih acak warnanya
    F.S: teks sudah berwarna putih dan background berwarna hitam
*/

void ErrorMsg(String ErrorMessage);
/* Berguna untuk menampilkan pesan error
    I.S: pesan yang dikirim pada parameter belum tampil
    F.S: pesan yang dikirim di parameter sudah tampil dan berwarna merah
*/

void SuccMsg(String SuccesMessage);
/* Berguna untuk menampilkan pesan sukses
    I.S: pesan yang dikirim pada parameter belum tampil
    F.S: pesan yang dikirim di parameter sudah tampil dan berwarna hijau
*/

/* Modul Kami*/
int Menu();
/* Untuk menampilkan menu dan memilihnya
    I.S: menu belum tampil ke layar
    F.S: menu sudah tampil ke layar dan mengembalikan nilai yang sudah dipilih di menu
*/

void Pause();
/* Untuk mengkonfirmasi kepada pengguna untuk menekan tombol apapun untuk lanjut ke tahap berikutnya
    I.S: belum ada teks apapun yang tampil ke layar
    F.S: teks tekan tombol apapun untuk melanjutkan...
*/

bool Validasi();
/* Hanya untuk memvalidasi pilihan kepada pengguna yang hanya dapat menampung y atau n saja
    I.S: belum tampil ke layar pilihan y atau n
    F.S: sudah tampil ke layar pilihan y atu n dan juga akan mengembalikan nilai true jika pengguna
            menekan tombol y dan false jika n
*/

void ExitApps();
/* Hanya untuk animasi keluar aplikasi saja
    I.S: belum tampil animasi keluar program
    F.S: sudah tampil animasi keluar program
*/

/* Main Excute */
void Execute(int Choice, Address *Tree, bool *Exit);
/* Untuk mengeksekusi pilihan yang sudah dipilih di modul menu
    I.S: pilihan menu sudah diketahui
    F.S: mengeksekusi menu yang sudah di pilih mengggunaakn switch case
*/

/* ==================================================== */
/* ==================================================== */

/* Modul Insert Yang dibutuhkan */
void InsertKata(Address *Tree);
/* Untuk menambahkan kosakata baru ke dalam file dan juga struktur data tree saat ini
    I.S: Kosakata baru belum masuk ke dalam tree dan juga belum tertulis di file
    F.S: Kosakata baru sudah masuk ke dalam tree dan juga sudah tertulis di file
*/

void InputKamus(String *NewVocab);
/* Untuk melakukan input perulangan pada saat memasukan sebuah kosakata baru ke dalam satu
    variabel misal variabel : Sunda / Indonesia / Contoh dalam tipe data String atau Pointer Of Char
    I.S: Variabel kamus belum terisi kosakata apapun
    F.S: Variabel kamus sudah terisi kosakata yang diinputkan pengguna
*/

void Input(String *NewVocab);
/* Untuk menampung proses input pada saat melakukan inputan kosakata baru yang di panggil di modul InsertKata
    I.S: String NewVocab belum di tambahkan kosakata baru
    F.S: String NewVocab sudah di tambahkan kosakata baru
*/

void InsertToFile(String NewVocab);
/* Untuk menuliskan String apapun ke dalam file Kamus-Sunda-Indonesia.dat / Namun untuk kasus ini saya menuliskan
    gabungan kosakata bahasa sunda,indonesia dan juga contohnya dengan contoh format "Abi,Urang,Aing.=Saya,Aku,Gueh.(Abi ganteng pisan.)"
    I.S: String yang ada di parameter belum dituliskan kedalam file Kamus-Sunda-Indonesia.dat
    F.S: String yang ada di parameter sudah dituliskan kedalam file Kamus-Sunda-Indonesia.dat
*/

String MergeKamus(Kamus NewKamus);
/* Untuk menuliskan String yang ada di parameter NewVocab ke dalam file di End Of File
    I.S: String di parameter NewVocab belum tertulis di dalam file
    F.S: String di parameter NewVocab belum tertulis di dalam file pada End Of File
*/

void ConvFromCharToChar(String *Vocab, char CharFrom, char CharThis);
/* Mengubah sebuah string yang mengandung karakter apa(CharFrom) di ubah ke karakter apa(CharThis)
    I.S: Karakter yang ada di string belum berubah sesuai dengan yang sudah di perintahd di parameter
    F.S: Karakter yang ada di string sudah berubah sesuai dengan yang sudah di perintahd di parameter
*/

/* ==================================================== */
/* ==================================================== */

void InsertToTree(Address *Tree, Kamus NewKamus);
/* Menambahkan kosakata baru ke dalam struktur tree yang ada di program, namun proses insertnya ini
    perkosakata bahasa sunda sehingga memudahkan nanti saat proses pencarian
    I.S: Kosakata baru belum bertambah di struktur data tree
    F.S: Kosakata baru sudah bertambah di struktur data tree
*/

Address AlokTree();
/* Mengalokasikan satu buah alamat untuk struktur data tree
    I.S: Belum membuat alamat baru sebesar struktur data Binary
    F.S: Sudah membuat alamat baru sebesar struktur data Binary dan mengembalikan alamat tersebut yang sudah di alokasikan
*/

Address CreateKamus(Kamus NewKamus, String VocabSunda, int Height);
/* Mengalokasikan dan memasukan nilai nilai yang ada di parameter ke dalam alamat binary yang sudah di alokasikan di
    dalamnya
    I.S: Alamat binary belum di alokasikan dan belum terisi oleh nilai yang ada di parameter
    F.S: Alamat binary sudah di alokasikan dan belum terisi oleh nilai yang ada di parameter
*/

void InsertBinaryTree(Address *Tree, Kamus NewKamus, String VocabSunda, int Height);
/* Melakukan proses insert suatu alamat baru ke dalam struktur binary tree dengan menggunakan proses rekursif
    dengan parameter awal Height bernilai 1
    I.S: Alamat binary tree yang baru belum masuk ke dalam sturktur data
    F.S: Alamat binary tree yang baru sudah masuk ke dalam sturktur data
*/

void PrintTree(Address Root);
/* Mencetak isi dari binary tree menggunakan teknik rekursif
    I.S: Nilai yang ada di dalam alamat struktur data yang ada di dalam parameter belum tampil ke layar
    F.S: Nilai yang ada di dalam alamat struktur data yang ada di dalam parameter sudah tampil ke layar
*/

void PrintKamus(Kamus Kamus);
/* Menampilkan isi dari variabel kamus yang terdiri dari string sunda, indonesia dan contoh
    I.S: Isi dari nilai yang ada di kamus belum tampil ke layar
    F.S: Isi dari nilai yang ada di kamus sudah tampil ke layar
*/

void HeaderKamus();
/* Menampilkan header kamus ke layar
    I.S: Header kamus belum tampil ke layar
    F.S: Header kamus sudah tampil ke layar
*/

bool HasChar(String Check, char Contain);
/* Mengecek apakah pada String terdapat sebuah karakter yang dikirim di parameter 'Contain'
    I.S: Karakter belum diketahui keberadaannya dan belum mengembalikan nilai true/false
    F.S: Mengembalikan nilai true jika terdapat karakter yang dicari dan nilai false jika tidak ada karakter yang dicari
*/

void LoadDataKamus(Address *Tree);
/* Memuat data yang ada di dalam file Kamus-Sunda-Indonesia.dat dan memasukan data yang ada ke dalam struktur binary tree
    I.S: Struktur data binary tree belum berisikan informasi yang ada di dalam file Kamus-Sunda-Indonesia.dat
    F.S: Struktur data binary tree sudah berisikan informasi yang ada di dalam file Kamus-Sunda-Indonesia.dat
*/

int IsFileValid();
/* Untuk mengecek apakah struktur yang ada di dalam file sudah benar dan juga akan mengembalikan nilai 0
    jika tidak ada kesalahan dalam struktur file, mengembalikan nilai -1 jika file masih kosong, dan mengembalikan baris
    yang memiliki kesalahan jika ada kesalahan
    I.S: Belum mengembalikan nilai hasil pengecekan file dalam tipe integer
    F.S: Sudah mengembalikan nilai hasil pengecekan file dalam tipe integer
*/

int CountChar(String StrCheck, char CharCheck);
/* Menghitung ada berapa banyak karakter tertentu pada sebuah String
    I.S: Belum mengembalikan nilai apapun
    F.S: Sudah mengembalikan nilai integer senilai dengan berapa jumlah karakter yang terkandung di String
*/

void StringToList(AddressNodeNR *List, String Vocab);
/* Memisahkan nilai string (kosakata) yang dipisahkan oleh . menjadi sebuah list
    I.S: Linked list belum berisikan kata yang di pisahkan menjadi bagian bagian
    F.S: Linked list sudah berisikan kata yang di pisahkan menjadi bagian bagian
*/

/* ==================================================== */
/* ==================================================== */

/* =============== Roy ============= */

/*================Naila================================ */
Address SearchTree(Address Root, String Input);
void SearchKata(Address Tree);
/*================Naila================================ */

#endif // !BTREEKAMUS_H