#ifndef NONRESTRICTED_H
#define NONRESTRICTED_H

typedef char *String;
typedef struct nodeNR *AddressNodeNR;
typedef struct nodeNR
{
    String Info;
    AddressNodeNR Next;
} NodeNR;


AddressNodeNR InitNR();
/* Menginisialisasikan variabel bertipe AddressNodeNR menjadi NULL
    I.S: Function sudah mengembalikan nilai NULL
    F.S: Function sudah mengembalikan nilai NULL
*/

String AlokString(int Len);
/* Mengalokasikan pointer of char di memori sebesar len dan mengembalikan alamat yang di alokasikannya
    I.S: Memori belum di alokasikan untuk String sebesar Len
    F.S: Memori sudah di alokasikan untuk String sebesar Len
*/

AddressNodeNR CreateNodeNR(String Info);
/* Mengalokasikan memori seukuran satu AddressNodeNR dan mengisi info yang ada di dalamnya dengan Info
    I.S: Memori belum teralokasikan dan belum berisikan informasi dari Info
    F.S: Memori sudah teralokasikan dan sudah berisikan informasi dari Info
*/

int NRIsEmpty(AddressNodeNR NR);
/* Mengecek apakah linked list itu kosong apa tidak
    I.S: Belum mengembalikan nilai apapun
    F.S: Mengembalikan nilai 1 jika kosong dan 0 jika tidak kosong
*/

void InsertNR(AddressNodeNR *NR, String Info);
/* Menambahkan node barud di akhir linked list yang berisikan informasi dari Info
    I.S: Node baru belum bertambah pada linked list
    F.S: Node baru sudah bertambah pada linked list
*/

void DeleteNR(AddressNodeNR *NR, String Target);
/* Menghapus node yang memiliki informasi yang sama dengan Target
    I.S: Node yang memiliki informasi yang sama dengan target belum terhapus
    I.S: Node yang memiliki informasi yang sama dengan target sudah terhapus
*/

void PrintNB(AddressNodeNR NB);
/* Menampilkan informasi yang dimiliki oleh seluruh node yang saling terhubung
    I.S: Seluruh informasi pada node belum ditampilkan pada layar
    F.S: Seluruh informasi pada node sudah ditampilkan pada layar
*/

#endif // !NONRESTRICTED_H