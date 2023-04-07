#ifndef BTREEKAMUS_H
#define BTREEKAMUS_H
#include "NonRestricted.h"
#include <windows.h>
#include <stdbool.h>

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


/* ==================================================== */
/* ================= Coding Area Roy ================== */

/* Modul amogus-9 */
HWND WINAPI GetConsoleWindowNT(void);
void Koor(int Baris, int Kolom);
void SetColor(int kode1, int kode2) ;
void DefaultColor();
void ErrorMsg(Infotype ErrorMessage);

/* Modul */
int Menu();
void Stun();
bool Validasi();
void ExitApps();

void Execute(int Choice, Address *Tree, int *Exit);
void InsertToFile(Infotype NewVocab);
void Input(Infotype *NewVocab);

void InsertKata(Address *Tree);
void InputKamus(AddressNodeNR *Bahasa);

Infotype MergeKamus(Kamus Kamus);
Infotype KamusToString(AddressNodeNR Bahasa);

void ConvFromCharToChar(Infotype *Vocab, char CharFrom, char CharThis);

void RefactorContoh(Infotype *Contoh);

Address InitTree();
Address AlokTree();
void PrintTree(Address Root);
void PrintKamus(Kamus Kamus);

/* =============== End Of Coding Area Roy ============= */

void InsertToTree(Address *Tree, Kamus Kamus);
Address CreateTree(Kamus Kamus);


#endif // !BTREEKAMUS_H