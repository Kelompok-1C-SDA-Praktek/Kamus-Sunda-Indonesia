#include "BTreeKamus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

AddressBalancing InitBalance()
{
    return NULL;
}

AddressBalancing CreateNodeBalance(Kamus NewKamus)
{
    AddressBalancing NewBalancing = (AddressBalancing)malloc(sizeof(Balancing));
    if (NewBalancing != NULL)
    {
        NewBalancing->Kamus = NewKamus;
        NewBalancing->Next = NULL;
    }
    else
    {
        printf("Terjadi kesalahan: Mungkin memori sudah penuh...\n");
    }
    return NewBalancing;
}

int BalancingIsEmpty(AddressBalancing Balancing)
{
    return (Balancing == NULL);
}

void InsertBalancing(AddressBalancing *Balancing, Kamus NewKamus)
{
    AddressBalancing NewBalancing = CreateNodeBalance(NewKamus);
    if (NewBalancing != NULL)
    {
        if (*Balancing != NULL)
        {
            AddressBalancing Temp = (*Balancing);
            while (Temp->Next != NULL)
            {
                Temp = Temp->Next;
            }
            Temp->Next = NewBalancing;
        }
        else
        {
            (*Balancing) = NewBalancing;
        }
    }
}

void DeleteBalancing(AddressBalancing *Balancing, String Target)
{
    AddressBalancing Prev = NULL, Del = *Balancing;
    if (BalancingIsEmpty(*Balancing))
    {
        printf("Data sudah kosong...\n");
    }
    else
    {
        while (Del != NULL && strcmp(Del->Kamus.Sunda, Target) != 0)
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
            (*Balancing) = Del->Next;
            free(Del->Kamus.Sunda);
            free(Del);
        }
        else
        {
            Prev->Next = Del->Next;
            free(Del->Kamus.Sunda);
            free(Del);
        }
    }
}

void DeleteAllTree(Address *Tree)
{
    if((*Tree) != NULL)
    {
        DeleteAllTree(&(*Tree)->Left);
        DeleteAllTree(&(*Tree)->Right);
        free((*Tree));
    }
}

void BalancingTree(Address *Tree)
{
    /* Masukan seluruh yang ada di tree ke dalam linked list
        masukan secara inorder agar terurut
     */
    int Loop = 1;
    while (Loop <= 10)
    {
        AddressBalancing ListBalancing = InitBalance();
        SortBalancing((*Tree), &ListBalancing);
        /* Hapus semua isi tree karena akan diisi oleh tree baru */
        DeleteAllTree(&(*Tree));
        *Tree = NULL;
        /* InsertTreeBalancing yang baru */
        if (ListBalancing != NULL)
            InsertTreeBalancing(&(*Tree), &(ListBalancing));
        if(isAVL((*Tree)))
            break;
        Loop++;
    }
}

void SortBalancing(Address Tree, AddressBalancing *ListBalancing)
{
    if (Tree != NULL)
    {
        SortBalancing(Tree->Left, &(*ListBalancing));
        InsertBalancing(&(*ListBalancing), Tree->Kamus);
        SortBalancing(Tree->Right, &(*ListBalancing));
    }
}

void InsertTreeBalancing(Address *Tree, AddressBalancing *ListBalancing)
{
    /* mencari 3 komponen penting
        1. Root (Yang akan menjadi objek insert)
        2. List Left
        3. List Right
     */
    // Root

    if ((*ListBalancing) != NULL)
    {

        AddressBalancing Root = MidBalancing((*ListBalancing));
        AddressBalancing PrevRoot = InitBalance();
        AddressBalancing ListLeft = InitBalance();
        AddressBalancing ListRight = InitBalance();

        InsertBinaryTree(&(*Tree), Root->Kamus, Root->Kamus.Sunda, 1);

        if (Root != NULL)
        {
            // Mengisi list bagian kiri dan kanan
            if (strcmp(Root->Kamus.Sunda, (*ListBalancing)->Kamus.Sunda) != 0)
                ListLeft = *ListBalancing;
            else
                ListLeft = NULL;
            ListRight = Root->Next;
            PrevRoot = ListLeft;

            while (PrevRoot != NULL)
            {
                if (PrevRoot->Next != NULL && Root != NULL)
                {
                    if (strcmp(PrevRoot->Next->Kamus.Sunda, Root->Kamus.Sunda) == 0)
                    {
                        break;
                    }
                }
                PrevRoot = PrevRoot->Next;
            }
            free(Root);
            Root = NULL;
            if (PrevRoot != NULL)
                PrevRoot->Next = NULL;
        }

        InsertTreeBalancing(&(*Tree), &ListLeft);
        InsertTreeBalancing(&(*Tree), &ListRight);
    }
}

AddressBalancing MidBalancing(AddressBalancing NodeBalancing)
{
    int LenList = CountListBalancing(NodeBalancing);
    LenList = (LenList % 2 == 1) ? LenList / 2 + 1 : LenList / 2;
    for (int i = 1; i < LenList; i++)
    {
        NodeBalancing = NodeBalancing->Next;
    }
    return NodeBalancing;
}

int CountListBalancing(AddressBalancing ListBalancing)
{
    int Total = 0;
    while (ListBalancing != NULL)
    {
        Total++;
        ListBalancing = ListBalancing->Next;
    }
    return Total;
}

int isAVL(Address ptr)
{
    int h_l, h_r, diff;
    if (ptr == NULL)
        return 1;
    h_l = height(ptr->Left);
    h_r = height(ptr->Right);
    diff = h_l > h_r ? h_l - h_r : h_r - h_l;
    if (diff <= 1 && isAVL(ptr->Left) && isAVL(ptr->Right))
        return 1;
    return 0;
}

int height(Address ptr)
{
    int h_left, h_right;

    if (ptr == NULL) /*Base Case*/
        return 0;

    h_left = height(ptr->Left);
    h_right = height(ptr->Right);

    if (h_left > h_right)
        return 1 + h_left;
    else
        return 1 + h_right;
} /*End of height()*/