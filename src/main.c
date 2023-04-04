#include "BTreeKamus.h"
#include "NonRestricted.h"

int main()
{
    /* Deklarasi variabel */
    Address KamusTree;
    int Exit = 0;

    /* Program utama */
    while(!Exit) Execute(Menu(), &KamusTree, &Exit);

    /* End program */
    return 0;
}