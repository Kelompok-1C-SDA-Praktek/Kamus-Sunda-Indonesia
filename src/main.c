#include "BTreeKamus.h"

int main()
{
    /* Deklarasi variabel */
    Address KamusTree = NULL;
    bool Exit = false;
    
    /* Program utama */
    // Memuat data
    LoadDataKamus(&KamusTree);

    /* Run */
    while(!Exit) Execute(Menu(), &KamusTree, &Exit);

    /* End program */
    ExitApps();
    return 0;
}