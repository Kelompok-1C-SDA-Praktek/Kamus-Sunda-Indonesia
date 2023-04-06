#ifndef BTREEKAMUS_H
#define BTREEKAMUS_H
#include "NonRestricted.h"
#include <windows.h>

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
    AddressNodeNR Sunda, Indonesia, Contoh;
    // Infotype Contoh;
} Kamus;

typedef struct binary *Address;
typedef struct binary
{
    int Height;
    Address Left, Right;
    Kamus Kamus;
} Binary;

/* Modul amogus-9 */
HWND WINAPI GetConsoleWindowNT(void);
void Koor(int Baris, int Kolom);

/* Modul */
int Menu();
void Stun();
void Execute(int Choice, Address *Tree, int *Exit);
void InsertToFile(Infotype NewVocab);
void Input(Infotype *NewVocab);

void InsertKata(Address *Tree);
void InputKamus(AddressNodeNR *Bahasa);

Infotype MergeKamus(Address Tree);
Infotype KamusToString(AddressNodeNR Bahasa);

void ConvFromCharToChar(Infotype *Vocab, char CharFrom, char CharThis);

void RefactorContoh(Infotype *Contoh);

#endif // !BTREEKAMUS_H