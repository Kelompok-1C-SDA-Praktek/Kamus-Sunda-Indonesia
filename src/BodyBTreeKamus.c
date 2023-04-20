#include "BTreeKamus.h"

#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

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

void ErrorMsg(String ErrorMessage)
{
    SetColor(BG_RED, FG_BLACK);
    printf("%s", ErrorMessage);
    DefaultColor();
}

void SuccMsg(String SuccesMessage)
{
    SetColor(BG_GREEN, FG_BLACK);
    printf("%s\n", SuccesMessage);
    DefaultColor();
}

/* ===================================================== */

int Menu()
{
    int Choice;
    char ChoiceString[MAX_BUFFER];
    system("cls");
    printf("\nMenu\n");
    printf("1. Tampilkan isi kamus Sunda - Indonesia\n");
    printf("2. Tambah kosakata kamus\n");
    printf("3. Mencari kosakata bahasa Sunda\n");
    printf("0. Keluar\n\n");
    printf("Masukan pilihan anda: ");
    scanf(" %[^\n]", ChoiceString);

    if (sscanf(ChoiceString, "%d", &Choice))
    {
        if (Choice >= 0 && Choice <= 3)
            return Choice;
    }

    ErrorMsg("Pilihan anda tidak ada...");
    sleep(1.5);
    fflush(stdin);
    Choice = Menu();
    return Choice;
}

void Pause()
{
    SetColor(BG_GREEN, FG_BLACK);
    printf("\nTekan tombol apapun untuk melanjutkan...\n");
    Koor(0, 0);
    getch();
    DefaultColor();
    fflush(stdin);
}

bool Validasi()
{
    char Choice = ' ';
    printf("Tekan tombol ");
    SetColor(NONE, FG_RED);
    printf("[Y]");
    DefaultColor();
    printf(" jika iya...\n");

    printf("Tekan tombol ");
    SetColor(NONE, FG_GREEN);
    printf("[N]");
    DefaultColor();
    printf(" jika tidak...\n");

    while ((Choice != 'Y') && (Choice != 'N'))
    {
        Choice = toupper(getch());
    }
    fflush(stdin);
    return (Choice == 'Y');
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
        sleep(0.5);
    }
}

/* ============================================== */
void Execute(int Choice, Address *Tree, bool *Exit)
{
    switch (Choice)
    {
    case 1:
        // Menampilkan isi kamus Sunda secara traversal InOrder
        system("cls");
        HeaderKamus();
        ((*Tree) == NULL) ? ErrorMsg("Kamus tidak terdeteksi...\n") : PrintTree((*Tree));
        Pause();
        break;
    case 2:
        // Tambahkan kosakata baru kedalam kamus
        system("cls");
        InsertKata(&(*Tree));
        break;

    case 3:
        // Mencari string
        system("cls");
        SearchKata((*Tree));
        break;
    case 0:
        // Tambahkan kosakata baru kedalam kamus
        printf("Apakah anda yakin untuk keluar?\n");
        if (Validasi())
            *Exit = true;
        break;
    }
}

void InsertKata(Address *Tree)
{
    // Input Kosa Kata Baru
    Kamus NewKamus;
    AddressNodeNR KamusSunda = NULL;
    bool ValidToContinou = true;

    system("cls");
    printf("Saat ini anda akan menambahkan kosakata bahasa Sunda\n");
    InputKamus(&NewKamus.Sunda);

    // Lakukan pengecekan pada setiap kosakata yang ada di dalam kamus sunda
    StringToList(&KamusSunda, NewKamus.Sunda);
    while (KamusSunda != NULL)
    {
        Address TempSunda = SearchTree((*Tree), KamusSunda->Info);
        if (TempSunda != NULL) // Ada yang sama
        {
            // Tidak bisa dilanjutkan karena sudah ada
            // Kalo mau edit aja kosakata yang lalu
            ErrorMsg("Peringatan!\n");
            printf("Kosakata ");
            ErrorMsg(KamusSunda->Info);
            printf(" sudah ada, silahkan lakukan pengeditan menggunakan fitur edit kata jika ingin menambahkan sesuatu pada kosakata tersebut\n");
            Pause();
            free(NewKamus.Sunda);
            ValidToContinou = false;
            break;
        }
        KamusSunda = KamusSunda->Next;
    }

    if (ValidToContinou)
    {

        system("cls");
        printf("Saat ini anda akan menambahkan kosakata bahasa Indonesia\n");
        InputKamus(&NewKamus.Indonesia);

        system("cls");
        printf("Ingin menambahkan contohnya?\n");
        if (Validasi())
        {
            system("cls");
            printf("Saat ini anda akan menambahkan contoh penggunaan bahasa sunda nya\n");
            InputKamus(&NewKamus.Contoh);
        }
        else
            NewKamus.Contoh = NULL;

        // Insert To File
        InsertToTree(&(*Tree), NewKamus);
        InsertToFile(MergeKamus(NewKamus));
    }
}

void InputKamus(String *NewVocab)
{
    *NewVocab = AlokString(1);
    (*NewVocab)[0] = 0;
    while (true)
    {
        Input(&(*NewVocab));
        system("cls");
        printf("%s\n", *NewVocab);
        if ((*NewVocab) != NULL)
        {

            printf("\nTambahkan kosakata lain yang mirip?\n");
            if (!Validasi())
                break;
        }
    }
}

void Input(String *NewVocab)
{
    char Buffer[MAX_BUFFER];
    unsigned int LenOfVocab = 0;

    printf("Masukan kata: ");

    /* Mulai melakukan penginputan kata */
    /* Mengambil input dari user */
    scanf(" %[^\n]", Buffer);

    LenOfVocab = strlen(Buffer);

    if (LenOfVocab != 0)
    {
        String Temp;
        Buffer[0] = toupper(Buffer[0]);
        /* Mengalokasikan memori yang cukup untuk menyimpan kosakata */
        (Temp) = AlokString(LenOfVocab + 2); // 2 untuk . dan \n

        /* Mengkopi input ke dalam memori yang baru dialokasikan */
        strcpy(Temp, Buffer);
        strcat(Temp, ".");
        (Temp)[LenOfVocab + 1] = 0;
        unsigned int LenOfNewVocab = strlen(*NewVocab);
        LenOfVocab = strlen(Temp);
        (*NewVocab) = realloc((*NewVocab), (LenOfNewVocab + LenOfVocab + 1) * sizeof(char));
        strcat((*NewVocab), Temp);
        (*NewVocab)[LenOfVocab + LenOfNewVocab] = 0;
    }
    fflush(stdin);
}

void InsertToFile(String NewVocab)
{
    FILE *fp;

    fp = fopen(FileKamus, "a+");

    if (fp == NULL)
    {
        ErrorMsg("Gagal membuka file Kamus-Sunda-Indonesia.dat\n");
        fclose(fp);
    }
    else
    {
        /* Abi,Urang. '=' Saya,Gueh. (Abi jajan ka Bandung, Urang gelut jeung maneh.) */
        /* Abi,Urang.=Saya,Gueh.(Abi jajan ka Bandung,Urang gelut jeung maneh.) */
        fprintf(fp, "%s", NewVocab);
        fclose(fp);
        SuccMsg("Berhasil menuliskan kosakata baru ke dalam file Kamus-Sunda-Indonesia.dat");
    }
    Pause();
}

String MergeKamus(Kamus NewKamus)
{
    String Result = AlokString(strlen(NewKamus.Contoh) + strlen(NewKamus.Indonesia) + strlen(NewKamus.Contoh) + 5);
    Result[strlen(NewKamus.Contoh) + strlen(NewKamus.Indonesia) + strlen(NewKamus.Contoh) + 5] = 0;

    ConvFromCharToChar(&NewKamus.Sunda, '.', ',');
    ConvFromCharToChar(&NewKamus.Indonesia, '.', ',');
    ConvFromCharToChar(&NewKamus.Contoh, '.', ',');

    /* 18 + 4 '=' "()" 0 "*/
    strcpy(Result, NewKamus.Sunda);
    strcat(Result, "=");
    strcat(Result, NewKamus.Indonesia);
    strcat(Result, "(");
    strcat(Result, NewKamus.Contoh);
    strcat(Result, ")");
    strcat(Result, "\n");
    return Result;
}

void ConvFromCharToChar(String *Vocab, char CharFrom, char CharThis)
{
    unsigned int LenOfVocab = strlen((*Vocab));
    for (unsigned int i = 0; i < LenOfVocab; i++)
    {
        if ((*Vocab)[i] == CharFrom && i != LenOfVocab - 1)
            (*Vocab)[i] = CharThis;
    }
}

void InsertToTree(Address *Tree, Kamus NewKamus)
{
    // Pisahkan kosakata bahasa sunda ke dalam Linked List
    AddressNodeNR ListVocabSunda = NULL;
    StringToList(&ListVocabSunda, NewKamus.Sunda);
    while (ListVocabSunda != NULL)
    {
        InsertBinaryTree(&(*Tree), NewKamus, ListVocabSunda->Info);
        ListVocabSunda = ListVocabSunda->Next;
    }
}

Address AlokTree()
{
    return (Address)malloc(sizeof(Binary));
}

Address CreateKamus(Kamus NewKamus, String VocabSunda)
{
    Address NewTree = AlokTree();
    if (NewTree != NULL)
    {
        NewTree->Height = 1;
        NewTree->Left = NULL;
        NewTree->Right = NULL;
        NewTree->Kamus.Sunda = VocabSunda;
        NewTree->Kamus.Indonesia = NewKamus.Indonesia;
        NewTree->Kamus.Contoh = NewKamus.Contoh;
    }
    else
    {
        ErrorMsg("Gagal memuat kosakata ke dalam aplikasi\n");
        Pause();
    }
    return NewTree;
}

void InsertBinaryTree(Address *Tree, Kamus NewKamus, String VocabSunda)
{
    if ((*Tree) == NULL)
        (*Tree) = CreateKamus(NewKamus, VocabSunda);
    else if (strcmp(VocabSunda, (*Tree)->Kamus.Sunda) < 0) // Jika Kamus sunda yang baru lebih kecil dari kamus yang lama
        InsertBinaryTree(&(*Tree)->Left, NewKamus, VocabSunda);
    else
        InsertBinaryTree(&(*Tree)->Right, NewKamus, VocabSunda);
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

void PrintKamus(Kamus Kamus)
{
    SetColor(NONE, FG_GREEN);
    if (Kamus.Sunda != NULL)
        printf("%s\t", Kamus.Sunda);

    SetColor(NONE, FG_YELLOW);
    printf(" = \t");

    SetColor(NONE, FG_CYAN);
    if (Kamus.Indonesia != NULL)
        printf("%s", Kamus.Indonesia);

    SetColor(NONE, FG_BLUE);
    (Kamus.Contoh != NULL) ? printf("\tContoh: %s\n", Kamus.Contoh) : printf("\tTidak ada contoh tersedia\n");

    DefaultColor();
}

void HeaderKamus()
{
    SetColor(NONE, FG_GREEN);
    printf("Sunda \t\t");
    SetColor(NONE, FG_CYAN);
    printf("Indonesia \t");
    SetColor(NONE, FG_BLUE);
    printf("Contoh \n");
}

bool HasChar(String Check, char Contain)
{
    int Len = strlen(Check);
    for (int i = 0; i < Len; i++)
    {
        if (Check[i] == Contain)
            return true;
    }
    return false;
}

void LoadDataKamus(Address *Tree)
{
    FILE *fp;
    fp = fopen(FileKamus, "r");
    Kamus TempKamus;
    if (fp == NULL)
    {
        ErrorMsg("Gagal memuat data pada file Kamus-Sunda-Indonesia.dat\n");
        fclose(fp);
    }
    else
    {
        char Buffer[MAX_BUFFER * 3];
        int Row = IsFileValid();
        if (Row == 0)
        {
            while (fscanf(fp, "%[^\n]\n", Buffer) == 1)
            {
                char Sunda[MAX_BUFFER];
                char Indonesia[MAX_BUFFER];
                char Contoh[MAX_BUFFER];
                /* Variabel sementara Kamus */
                sscanf(Buffer, "%[^=]=%[^(](%[^)])", Sunda, Indonesia, Contoh);
                TempKamus.Sunda = AlokString(strlen(Sunda) + 1);
                TempKamus.Indonesia = AlokString(strlen(Indonesia) + 1);
                TempKamus.Contoh = NULL;
                strcpy(TempKamus.Sunda, Sunda);
                TempKamus.Sunda[strlen(Sunda)] = 0;
                strcpy(TempKamus.Indonesia, Indonesia);
                TempKamus.Indonesia[strlen(Indonesia)] = 0;
                if (HasChar(Buffer, '('))
                {
                    TempKamus.Contoh = AlokString(strlen(Contoh) + 1);
                    TempKamus.Contoh[strlen(Contoh)] = 0;
                    strcpy(TempKamus.Contoh, Contoh);
                }
                InsertToTree(&(*Tree), TempKamus);
            }
            fclose(fp);
            SuccMsg("Berhasil memuat data kamu pada file Kamus-Sunda-Indonesia.dat");
        }
        else if (Row == -1)
        {
            ErrorMsg("Tidak dapat memuat apapun, file masih kosong\n");
            fclose(fp);
        }
        else
        {
            sprintf(Buffer, "%d", Row);
            ErrorMsg("Ada kesalahan format teks pada file Kamus-Sunda-Indonesia.dat\n");
            ErrorMsg("Silahkan perbaiki format teks pada file tersebut pada Baris ke ");
            ErrorMsg(Buffer);
            fclose(fp);
        }
    }
    Pause();
}

int IsFileValid()
{
    FILE *fp;
    fp = fopen(FileKamus, "r");
    if (fp == NULL)
    {
        ErrorMsg("Gagal melakukan proses pengecekan file Kamus-Sunda-Indonesia.dat");
        fclose(fp);
        Pause();
        return false;
    }
    else
    {
        char Buffer[MAX_BUFFER];
        int Row = 0;
        fseek(fp, 0, SEEK_END);
        if (ftell(fp) == 0)
        {
            return -1;
        }
        rewind(fp);
        while (fscanf(fp, "%[^\n]\n", Buffer) == 1)
        {
            Row++;
            if (CountChar(Buffer, '.') < 2 || CountChar(Buffer, '=') != 1 || CountChar(Buffer, '(') > 1 || CountChar(Buffer, ')') > 1)
                return Row;
        }
        fclose(fp);
        Row = 0;
        return Row;
    }
}

int CountChar(String StrCheck, char CharCheck)
{
    size_t Len = strlen(StrCheck);
    int Count = 0;
    for (size_t i = 0; i < Len; i++)
    {
        if (StrCheck[i] == CharCheck)
            Count++;
    }
    return Count;
}

void StringToList(AddressNodeNR *List, String Vocab)
{
    unsigned int LenOfTemp = 0;
    unsigned int LenOfSunda = 0;
    while (LenOfSunda != strlen(Vocab))
    {
        String Temp = AlokString(strlen(Vocab));
        Temp[strlen(Vocab)] = 0;
        while (Vocab[LenOfSunda] != '.' && Vocab[LenOfSunda] != ',')
        {
            Temp[LenOfTemp] = Vocab[LenOfSunda];
            LenOfTemp++;
            LenOfSunda++;
        }
        Temp[LenOfTemp] = 0;
        LenOfTemp = 0;
        LenOfSunda++;
        InsertNR(&(*List), Temp);
    }
}

/*=======================Naila=====================*/

Address SearchTree(Address Root, String Input)
{
    if (Root == NULL || strcmp(Root->Kamus.Sunda, Input) == 0)

        return Root;

    else if (strcmp(Input, Root->Kamus.Sunda) < 0)

        return SearchTree(Root->Left, Input);

    else
        return SearchTree(Root->Right, Input);
}

void SearchKata(Address Tree)
{
    char InputUser[MAX_BUFFER];
    Address TempTree;
    printf("Masukan kosakata yang akan dicari dalam bahasa sunda : ");
    scanf(" %[^\n]", InputUser);
    InputUser[0] = toupper(InputUser[0]);
    TempTree = SearchTree(Tree, InputUser);

    if (TempTree != NULL)
    {
        HeaderKamus();
        PrintKamus(TempTree->Kamus); // kalo ditemukan dalam tree
    }
    else
    {
        ErrorMsg("Kata Tidak DItemukan!\n"); // kalo tidak ditemukan
    }
    Pause();
}

/*=================================================*/