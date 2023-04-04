#ifndef BTREEKAMUS_H
#define BTREEKAMUS_H
#include "NonRestricted.h"
/* Informasi Author
    Nama        :   1. Roy Aziz Barera (Ketua)
                    2. Naila Sania
                    3. Retryanzani
    Kelas       :   1A
    Prodi       :   D4 Teknik Informatika
    Tanggal     :   29/3/2023
*/

typedef char *Infotype;

typedef struct kamus
{
    AddressNodeNR Sunda, Indonesia;
    Infotype Contoh;
} Kamus;

typedef struct binary *Address;
typedef struct binary
{
    int Height;
    Address Left, Right;
    Kamus Kamus;
} Binary;

/* Modul */
int Menu();
void Stun();
void Execute(int Choice, Address *Tree, int *Exit);










/* Inisialisasi Node */
// void InitNode(Address *Node);
/* Membuat alamat node yang dikirimkan di parameter akan bernilai null */

/* Create Node */
// Address CreateNode(Infotype Info);
/* Mengirimkan alamat node yang nilainya Info nya berisi dari parameter Info */

/* Insert */
// void InsertBinary(Address *Root, Infotype Info);
/* Akan menambahkan node baru pada root dengan membandingkan nilai dengan root
dan jika setelah dibandingkan itu memiliki nilai yang lebih kecil maka akan disimpan
di anak kiri sedangkan jika lebih besar maka akan disimpan di anak sebelah
kanan berlaku bagi keturunannya
*/

/* Menampilkan data di dalam tree secara 
InOrder */
// void InOrderTraversal(Address Root);
/* Membutuhkan alamat pertama dari sebuah Root
Namun algoritma ini juga bisa digunakan untuk
Menampilkan nilai dari turunan turunan tertentu
*/


#endif // !BTREEKAMUS_H