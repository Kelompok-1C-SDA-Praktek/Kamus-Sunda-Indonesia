#include "BTreeKamus.h"
#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <unistd.h>

const char FileKamus[26] = "Kamus-Sunda-Indonesia.dat";

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
    printf("\nTekan tombol apapun untuk untuk melanjutkan...\n");
    getch();
}

void Execute(int Choice, Address *Tree, int *Exit)
{
    Infotype NewVocab;
    switch (Choice)
    {
    case 1:
        // Menampilkan isi kamus Sunda secara traversal InOrder
        Stun();
        break;
    case 2:
        // Tambahkan kosakata baru kedalam kamus
        Input(&NewVocab);
        InsertToFile(NewVocab);
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
    /* Deklarasi variabel */
    char OneChar;
    int LenOfVocab = 1;

    /* Alokasikan memori untuk menampung 1 karakter dan 1 null terminator */
    (*NewVocab) = CreateString(LenOfVocab + 1);

    system("cls");
    printf("Masukan kata: ");

    /* Mulai melakukan penginputan kata */
    while (OneChar != '\r') /* \r adalah karakter tombol Enter */
    {
        /* pengecekan apakah ada tombol yang ditekan atau tidak */
        if (kbhit())
        {
            /* Mengambil karakter di buffer keyboard terakhir dan memasukannya ke dalam variabel OneChar */
            OneChar = getch();

            /* Jika yang ditekan adalah tombol 'backspace' maka hapus karakter terakhir saat ini */
            if (OneChar == '\b')
            {
                /* Operasi ini sah jika panjang dari kata memiliki lebih dari 1 */
                if (LenOfVocab > 1)
                {
                    /* Bebaskan memori null terminator terakhir */
                    free((*NewVocab)[LenOfVocab - 1]);
                    /* Membuat index terakhir menjadi null terminator */
                    (*NewVocab)[LenOfVocab - 2] = 0;
                    /* Kurangi panjang kosakatanya */
                    LenOfVocab--;
                    /* Alokasikan ulang dengan panjang kosakata saat ini */
                    (*NewVocab) = (Infotype)realloc((*NewVocab), LenOfVocab * sizeof(char));
                }
            }
            else
            {
                /* Bisa menlakukan realokasi jika memiliki minimal 1 huruf */
                if (LenOfVocab > 1)
                    (*NewVocab) = (Infotype)realloc((*NewVocab), LenOfVocab + 1 * sizeof(char));
                /* Mengisi index yang sudah dialokasikan dengan karakter tombol yang ditekan */
                (*NewVocab)[LenOfVocab - 1] = OneChar;
                /* Menambahkan null terminator */
                (*NewVocab)[LenOfVocab] = 0;
                LenOfVocab++;
            }
            system("cls");
            printf("Masukan kata: ");
            printf("%s", (*NewVocab));
        }
    }
}