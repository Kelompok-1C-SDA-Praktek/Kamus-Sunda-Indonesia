#include "BTreeKamus.h"
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

/* Define Kode Warna */
#define FG_BLACK 0x00
#define FG_BLUE 0x01
#define FG_GREEN 0x02
#define FG_CYAN 0x03
#define FG_RED 0x04
#define FG_MAGENTA 0x05
#define FG_YELLOW 0x06
#define FG_WHITE 0x07

#define BG_BLACK 0x00
#define BG_BLUE 0x10
#define BG_GREEN 0x20
#define BG_CYAN 0x30
#define BG_RED 0x40
#define BG_MAGENTA 0x50
#define BG_YELLOW 0x60
#define BG_WHITE 0x70

#define NONE 0

/* End Define*/

const char FileKamus[26] = "Kamus-Sunda-Indonesia.dat";

/* ==================================================== */
/* ================= Area Coding Roy ================== */

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
void SetColor(int kode1, int kode2)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, kode1 | kode2);
}

void DefaultColor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, BG_BLACK | FG_WHITE);
}

void ErrorMsg(Infotype ErrorMessage)
{
    SetColor(BG_RED, FG_BLACK);
    printf("%s\n", ErrorMessage);
    DefaultColor();
}

void ExitApps()
{
    SetColor(BG_BLUE, FG_WHITE);
    printf("Terima kasih telah menggunakan aplikasi kami (^_^) \n");
    printf("Keluar aplikasi");
    SetColor(FG_WHITE, BG_RED);
    for (int i = 1; i <= 3; i++)
    {
        printf(".");
        sleep(1);
    }
}

int Menu()
{
    int Choice;
    char ChoiceString[MAX_BUFFER];
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
    fflush(stdin);
    Choice = Menu();
    return Choice;
}

void Stun()
{
    SetColor(BG_GREEN, FG_BLACK);
    printf("\nTekan tombol apapun untuk melanjutkan...\n");
    Koor(0, 0);
    getch();
    DefaultColor();
}

bool Validasi()
{
    char Choice = ' ';
    printf("Tekan tombol [Y] jika iya...\n");
    printf("Tekan tombol [N] jika tidak...\n");
    while ((Choice != 'Y') && (Choice != 'N'))
    {
        Choice = toupper(getch());
    }
    return (Choice == 'Y');
}

/* ============================================== */

void Execute(int Choice, Address *Tree, int *Exit)
{
    switch (Choice)
    {
    case 1:
        // Menampilkan isi kamus Sunda secara traversal InOrder
        system("cls");
        printf("Kamus:\n");
        ((*Tree) == NULL) ? ErrorMsg("Kamus tidak terdeteksi...") : PrintTree((*Tree));
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
        if (Validasi())
            *Exit = 1;
        break;
    }
}

void InsertKata(Address *Tree)
{
    Address NewTree = AlokTree(); // aloktree

    system("cls");
    printf("Saat ini anda akan menambahkan kosakata bahasa Sunda\n");
    InputKamus(&NewTree->Kamus.Sunda);

    system("cls");
    printf("Saat ini anda akan menambahkan kosakata bahasa Indonesia\n");
    InputKamus(&NewTree->Kamus.Indonesia);

    system("cls");
    printf("Ingin menambahkan contohnya?\n");
    if (Validasi())
    {
        system("cls");
        printf("Saat ini anda akan menambahkan contoh penggunaan bahasa sunda nya\n");
        InputKamus(&NewTree->Kamus.Contoh);
    }
    else
        NewTree->Kamus.Contoh = NULL;

    InsertToFile(MergeKamus(NewTree->Kamus));
    InsertToTree(&(*Tree), NewTree->Kamus);
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
            printf("\nTambahkan kosakata lain yang mirip?\n");
            if (!Validasi())
                break;
        }
    }
}

void Input(Infotype *NewVocab)
{
    char Buffer[MAX_BUFFER];
    int LenOfVocab = 0;

    printf("Masukan kata: ");

    /* Mulai melakukan penginputan kata */
    /* Mengambil input dari user */
    scanf(" %[^\n]", Buffer);

    LenOfVocab = strlen(Buffer);

    if (LenOfVocab != 0)
    {
        /* Mengalokasikan memori yang cukup untuk menyimpan kosakata */
        (*NewVocab) = AlokString(LenOfVocab + 2); // 2 untuk . dan \n

        /* Mengkopi input ke dalam memori yang baru dialokasikan */
        strcpy((*NewVocab), Buffer);
        strcat((*NewVocab), ".");
        (*NewVocab)[LenOfVocab+2] = 0;
    }
    fflush(stdin);
}

Infotype MergeKamus(Kamus Kamus)
{
    Infotype Sunda = KamusToString(Kamus.Sunda);
    Infotype Indonesia = KamusToString(Kamus.Indonesia);
    int Len = strlen(Sunda) + strlen(Indonesia);
    Infotype Result = AlokString(Len + 2);
    strcpy(Result, Sunda);
    strcat(Result, Indonesia);
    if (Kamus.Contoh != NULL)
    {
        Result[Len+1] = 0;
        Result[Len] = '.';
        Infotype Contoh = AlokString(1);
        Contoh[0] = 0;
        int LenContoh = 0;
        while (Kamus.Contoh != NULL)
        {
            RefactorContoh(&Kamus.Contoh->Info);
            LenContoh += strlen(Contoh) + strlen(Kamus.Contoh->Info);
            Contoh = (Infotype)realloc(Contoh, (LenContoh + 1) * sizeof(char));
            strcat(Contoh, Kamus.Contoh->Info);
            Contoh[LenContoh] = 0;
            Kamus.Contoh = Kamus.Contoh->Next;
        }
        Contoh = (Infotype)realloc(Contoh, (LenContoh + 2) * sizeof(char));
        strcat(Contoh, "\n");
        Contoh[LenContoh+1] = 0;
        Result = realloc(Result, (Len+LenContoh+2) * sizeof(char));
        strcat(Result, Contoh);
        Result[Len+LenContoh+2] = 0;
    }
    else
    {
        Result[Len] = '\n';
        Result[Len+1] = 0;
    }
    return Result;
}

Infotype KamusToString(AddressNodeNR Bahasa)
{
    if (Bahasa != NULL)
    {
        Infotype Result = AlokString(1);
        Result[0] = 0;
        int Len = 0;
        while (Bahasa != NULL)
        {
            if (Bahasa->Next == NULL)
                ConvFromCharToChar(&(*Bahasa).Info, '.', '=');
            else
                ConvFromCharToChar(&(*Bahasa).Info, '.', ',');
            Result = (Infotype)realloc(Result, (Len + strlen(Bahasa->Info) + 1) * sizeof(char));
            strcat(Result, Bahasa->Info);
            Len = Len + strlen(Result);
            Result[Len] = 0;
            Bahasa = Bahasa->Next;
        }
        return Result;
    }
    return NULL;
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
    Infotype Buka = AlokString(2);
    Infotype Tutup = AlokString(3);
    Buka[0] = '(';
    Buka[1] = 0;
    Tutup[0] = ')';
    Tutup[1] = ';';
    Tutup[2] = 0;
    Infotype Temp = (Infotype)malloc((strlen(*Contoh) + 4) * sizeof(char));
    strcpy(Temp, Buka);
    strcat(Temp, (*Contoh));
    strcat(Temp, Tutup);
    Temp[strlen((*Contoh))+3] = 0;
    // free((Contoh)); // bug
    *Contoh = Temp;
}

Address InitTree()
{
    return NULL;
}

void PrintKamus(Kamus Kamus)
{
    SetColor(BG_GREEN, FG_BLACK);
    printf(" Sunda \t");
    SetColor(BG_CYAN, FG_BLACK);
    printf(" Indonesia \n");

    Kamus.Sunda->Info = KamusToString(Kamus.Sunda);
    Kamus.Indonesia->Info = KamusToString(Kamus.Indonesia);
    ConvFromCharToChar(&Kamus.Sunda->Info, '=', '.');
    ConvFromCharToChar(&Kamus.Indonesia->Info, '=', '.');

    SetColor(BG_GREEN, FG_BLACK);
    printf(" %s ", Kamus.Sunda->Info);

    DefaultColor();
    printf("  ");
    SetColor(BG_YELLOW, FG_BLACK);
    printf("=");
    DefaultColor();
    printf("  ");

    SetColor(BG_CYAN, FG_BLACK);
    printf(" %s ", Kamus.Indonesia->Info);

    SetColor(BG_MAGENTA, FG_WHITE);
    printf("\nContoh Penggunaan:\n");
    PrintNB(Kamus.Contoh);
    printf("\n");
    DefaultColor();
}

void PrintTree(Address Root)
{
    if (Root != NULL)
    {
        PrintTree(Root->Left);
        PrintKamus(Root->Kamus);
        PrintTree(Root->Right);
    }
}

/* =============== End Of Coding Area Roy ============= */

Address AlokTree()
{
    Address NewTree = (Address)malloc(sizeof(Binary));
    if (NewTree != NULL)
    {
        NewTree->Height = 1;
        NewTree->Left = NULL;
        NewTree->Right = NULL;
        NewTree->Kamus.Sunda = NULL;
        NewTree->Kamus.Indonesia = NULL;
        NewTree->Kamus.Contoh = NULL;
    }
    else
    {
        ErrorMsg("Mungkin memori sudah penuh...");
        Stun();
    }
    return NewTree;
}

Address CreateTree(Kamus Kamus)
{
    Address NewTree = AlokTree();
    if (NewTree != NULL)
    {
        NewTree->Height = 1;
        NewTree->Kamus = Kamus;
        NewTree->Left = NULL;
        NewTree->Right = NULL;
    }
    else
    {
        ErrorMsg("Terjadi kesalahan saat membuat atribut kamus...");
        Stun();
    }
    return NewTree;
}

void InsertToTree(Address *Tree, Kamus Kamus)
{
    if (*Tree == NULL)
        (*Tree) = CreateTree(Kamus);
    else if (strcmp(Kamus.Sunda->Info, (*Tree)->Kamus.Sunda->Info) < 0) // Jika Kamus sunda yang baru lebih kecil dari kamus yang lama
        InsertToTree(&(*Tree)->Left, Kamus);
    else
        InsertToTree(&(*Tree)->Right, Kamus);
}
