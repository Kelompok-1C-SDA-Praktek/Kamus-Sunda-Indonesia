#include "BTreeKamus.h"

int main()
{
    /* Deklarasi variabel */
    Address RootKamus = NULL;
    bool Exit = false;
    
    /* Program utama */
    // Memuat data
    LoadDataKamus(&RootKamus);
    /* Run */
    while(!Exit) Execute(Menu(), &RootKamus, &Exit);
    /* End program */
    ExitApps();
    return 0;
}