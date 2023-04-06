#include "BTreeKamus.h"
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

const char FileKamus[26] = "Kamus-Sunda-Indonesia.dat";

HWND WINAPI GetConsoleWindowNT(void)
{
    typedef HWND WINAPI (*GetConsoleWindowT)(void);

    GetConsoleWindowT GetConsoleWindow;

    HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));

    GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib, TEXT("GetConsoleWindow"));
    if (GetConsoleWindow == NULL)
    {
        return NULL;
    }
    return GetConsoleWindow();
}

void Koor(int Baris, int Kolom)
{
    HANDLE h;
    COORD c;
    c.Y = Baris;
    c.X = Kolom;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h, c);
}

/* ============================================== */

int Menu()
{
    int Choice;
    char ChoiceString[1024];
    system("cls");
    printf("\nMenu\n");
    printf("1. Tampilkan isi kamus Sunda - Indonesia\n");
    printf("2. Tambah kosakata kamus\n");
    printf("0. Keluar\n\n");
    printf("Masukan pilihan anda: ");
    scanf(" %[^\n]", ChoiceString);

    if (sscanf(ChoiceString, "%d", &Choice))
    {
        if (Choice >= 0 && Choice <= 2)
            return Choice;
    }

    printf("Pilihan anda tidak ada...\n");
    sleep(1.5);
    Choice = Menu();
    return Choice;
}

void Stun()
{
    printf("\nTekan tombol apapun untuk melanjutkan...\n");
    getch();
}

void Execute(int Choice, Address *Tree, int *Exit)
{
    switch (Choice)
    {
    case 1:
        // Menampilkan isi kamus Sunda secara traversal InOrder
        Stun();
        break;
    case 2:
        // Tambahkan kosakata baru kedalam kamus
        system("cls");
        InsertKata(&(*Tree));
        break;
    case 0:
        // Tambahkan kosakata baru kedalam kamus
        printf("Apakah anda yakin untuk keluar?\n");
        printf("Tekan tombol 'Enter' jika ingin keluar, \ntekan tombol apapun untuk membatalkan\n");
        if (getch() == 13)
            *Exit = 1;
        break;
    }
}

void InsertToFile(Infotype NewVocab)
{
    FILE *fp;
    /* Buka file */
    fp = fopen(FileKamus, "a+");

    /* Cek apakah file tersebut ada dan dapat dibuka */
    if (fp == NULL)
    {
        printf("Kesalahan saat membaca file %s\n", FileKamus);
        /* Tutup file */
        fclose(fp);
        Stun();
    }
    /* Tuliskan kosakata baru di akhir file */
    else
    {
        /* Tuliskan NewVocab ke dalam file di EOF */
        fprintf(fp, "%s", NewVocab);
        /* Tutup file */
        fclose(fp);
        printf("\nSukses menambahkan kosakata baru ke dalam file\n");
        Stun();
    }
}

void Input(Infotype *NewVocab)
{
    char Buffer[1024];
    int LenOfVocab = 0;

    printf("Masukan kata: ");

    /* Mulai melakukan penginputan kata */
    /* Mengambil input dari user */
    scanf(" %[^\n]", Buffer);

    /* Menghilangkan newline character */
    LenOfVocab = strlen(Buffer);

    /* Jika input kosong, kembali ke menu */
    if (LenOfVocab != 0)
    {

        /* Mengalokasikan memori yang cukup untuk menyimpan kosakata */
        (*NewVocab) = CreateString(LenOfVocab + 2);

        /* Mengkopi input ke dalam memori yang baru dialokasikan */
        strcpy((*NewVocab), Buffer);
        strcat((*NewVocab), ".");
    }
}

void InsertKata(Address *Tree)
{
    Address NewTree = (Address)malloc(sizeof(Binary));

    system("cls");
    printf("Saat ini anda akan menambahkan kosakata bahasa Sunda\n");
    InputKamus(&NewTree->Kamus.Sunda);

    system("cls");
    printf("Saat ini anda akan menambahkan kosakata bahasa Indonesia\n");
    InputKamus(&NewTree->Kamus.Indonesia);

    printf("Ingin menambahkan contohnya?\n");
    printf("Tekan tombol [Enter] jika iya...\n");
    printf("Tekan tombol lain untuk melewati tahapan ini...\n");
    if (getch() == '\r')
    {
        system("cls");
        printf("Saat ini anda akan menambahkan contoh penggunaan bahasa sunda nya\n");
        InputKamus(&NewTree->Kamus.Contoh);
    }
    else
        NewTree->Kamus.Contoh = NULL;

    InsertToFile(MergeKamus(NewTree));
}

void InputKamus(AddressNodeNR *Bahasa)
{
    Infotype NewVocab;
    bool FirstInit = false;
    while (true)
    {
        Input(&NewVocab);
        system("cls");
        if (NewVocab != NULL)
        {
            if (!FirstInit)
            {
                (*Bahasa) = InitNR();
                FirstInit = true;
            }
            InsertNR(&(*Bahasa), NewVocab);
            printf("\n");
            PrintNB(*Bahasa);
            printf("\nTekan tombol [Enter] untuk menambahkan kosakata baru\n");
            printf("yang memiliki arti yang sama\n\n");
            printf("Tekan tombol apapun untuk melanjutkan...\n");
            if (getch() != '\r')
                break;
        }
    }
}

Infotype MergeKamus(Address Tree)
{
    Infotype Sunda = KamusToString(Tree->Kamus.Sunda);
    Infotype Indonesia = KamusToString(Tree->Kamus.Indonesia);
    strcat(Sunda, Indonesia);
    if (Tree->Kamus.Contoh != NULL)
    {
        Sunda[strlen(Sunda) - 1] = '.';
        Infotype Contoh = CreateString(2);
        Contoh[0] = 0;
        while (Tree->Kamus.Contoh != NULL)
        {
            RefactorContoh(&(Tree)->Kamus.Contoh->Info);
            strcat(Contoh, Tree->Kamus.Contoh->Info);
            Tree->Kamus.Contoh = Tree->Kamus.Contoh->Next;
        }
        strcat(Contoh, "\n");
        strcat(Sunda, Contoh);
    }
    else
        Sunda[strlen(Sunda) - 1] = '\n';

    return Sunda;
}

Infotype KamusToString(AddressNodeNR Bahasa)
{
    Infotype Result = CreateString(1);
    Result[0] = 0;
    while (Bahasa != NULL)
    {
        if (Bahasa->Next == NULL)
            ConvFromCharToChar(&(*Bahasa).Info, '.', '=');
        else
            ConvFromCharToChar(&(*Bahasa).Info, '.', ',');
        strcat(Result, Bahasa->Info);
        Bahasa = Bahasa->Next;
    }
    return Result;
}

void ConvFromCharToChar(Infotype *Vocab, char CharFrom, char CharThis)
{
    for (unsigned int i = 0; i < strlen(*Vocab); i++)
    {
        if ((*Vocab)[i] == CharFrom)
            (*Vocab)[i] = CharThis;
    }
}

void RefactorContoh(Infotype *Contoh)
{
    Infotype Buka = "(";
    Infotype Tutup = ");";
    Infotype Temp = (Infotype)malloc((strlen(*Contoh) + 3) * sizeof(char));
    strcpy(Temp, Buka);
    strcat(Temp, (*Contoh));
    strcat(Temp, Tutup);

    free(*Contoh);
    *Contoh = Temp;
}
