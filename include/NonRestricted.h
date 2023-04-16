#ifndef NONRESTRICTED_H
#define NONRESTRICTED_H

typedef char *String;
typedef struct nodeNR *AddressNodeNR;
typedef struct nodeNR
{
    String Info;
    AddressNodeNR Next;
} NodeNR;

AddressNodeNR InitNR();

String AlokString(int Len);

AddressNodeNR CreateNodeNR(String Info);

int NRIsEmpty(AddressNodeNR NR);

void InsertNR(AddressNodeNR *NR, String Info);

void DeleteNR(AddressNodeNR *NR, String Target);

void PrintNB(AddressNodeNR NB);

#endif // !NONRESTRICTED_H