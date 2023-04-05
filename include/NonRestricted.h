#ifndef NONRESTRICTED_H
#define NONRESTRICTED_H

typedef char *Infotype;
typedef struct nodeNR *AddressNodeNR;
typedef struct nodeNR
{
    Infotype Info;
    AddressNodeNR Next;
} NodeNR;

AddressNodeNR InitNR();

Infotype CreateString(int Len);

AddressNodeNR CreateNodeNR(Infotype Info);

int NRIsEmpty(AddressNodeNR NR);

void InsertNR(AddressNodeNR *NR, Infotype Info);

void DeleteNR(AddressNodeNR *NR, Infotype Target);

void PrintNB(AddressNodeNR NB);

#endif // !NONRESTRICTED_H