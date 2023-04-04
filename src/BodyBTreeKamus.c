#include "BTreeKamus.h"
#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <unistd.h>

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
    scanf(" %s", ChoiceString);

    if(sscanf(ChoiceString, "%d", &Choice) == 1)
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
    switch (Choice)
    {
    case 1:
        // Menampilkan isi kamus Sunda secara traversal InOrder
        Stun();
        break;
    case 2:
        // Tambahkan kosakata baru kedalam kamus
        Stun();
        break;
    case 0:
        // Tambahkan kosakata baru kedalam kamus
        printf("Apakah anda yakin untuk keluar?\n");
        printf("Tekan tombol 'Enter' jika ingin keluar, \ntekan tombol apapun untuk membatalkan\n");
        if(getch() == 13)
            *Exit = 1;
        break;
    }
}