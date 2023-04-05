#ifndef BTREEKAMUS_H
#define BTREEKAMUS_H
#include "NonRestricted.h"
/* Informasi Author
    Nama        :   1. Roy Aziz Barera (Ketua)  221524030
                    2. Naila Saniyah Nur'aini   221524024
                    3. Retryanzani Dwi Fauzan   221524028
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
void InsertToFile(Infotype NewVocab);
void Input(Infotype *NewVocab);

#endif // !BTREEKAMUS_H