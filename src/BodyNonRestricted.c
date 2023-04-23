#include "NonRestricted.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AddressNodeNR InitNR()
{
    return NULL;
}

String AlokString(int Len)
{
    return (String)malloc((Len) * sizeof(char));
}

AddressNodeNR CreateNodeNR(String Info)
{
    AddressNodeNR NewNode = (AddressNodeNR)malloc(sizeof(AddressNodeNR));
    if (NewNode != NULL)
    {
        NewNode->Info = AlokString(strlen(Info));
        NewNode->Info = Info;
        strcat(NewNode->Info, "\0");
        NewNode->Next = NULL;
    }
    else
    {
        printf("Terjadi kesalahan: Mungkin memori sudah penuh...\n");
    }
    return NewNode;
}

int NRIsEmpty(AddressNodeNR NR)
{
    return (NR == NULL);
}

void InsertNR(AddressNodeNR *NR, String Info)
{
    AddressNodeNR NewNode = CreateNodeNR(Info);
    if (NewNode != NULL)
    {
        if (*NR != NULL)
        {
            NewNode->Next = *NR;
            *NR = NewNode;
        }
        else
        {
            (*NR) = NewNode;
        }
    }
}

void DeleteNR(AddressNodeNR *NR, String Target)
{
    AddressNodeNR Prev = NULL, Del = *NR;
    if (NRIsEmpty(*NR))
    {
        printf("Data sudah kosong...\n");
    }
    else
    {
        while (Del != NULL && strcmp(Del->Info, Target) != 0)
        {
            Prev = Del;
            Del = Del->Next;
        }

        if (Del == NULL)
        {
            printf("Data tidak ditemukan...\n");
        }
        else if (Prev == NULL)
        {
            (*NR) = Del->Next;
            free(Del->Info);
            free(Del);
        }
        else
        {
            Prev->Next = Del->Next;
            free(Del->Info);
            free(Del);
        }
    }
}

void PrintNB(AddressNodeNR NB)
{
    int Count = 1;
    while (NB != NULL)
    {
        printf("%d. %s\n", Count, NB->Info);
        Count++;
        NB = NB->Next;
    }
}