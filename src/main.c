#include "BTreeKamus.h"
// #include "NonRestricted.h"

int main()
{
    /* Deklarasi variabel */
    Address KamusTree = NULL;
    bool Exit = false;
    
    /* Program utama */
    // Pengaturan ukuran console dengan lebar 1000 dan tinggi 600 
    LoadDataKamus(&KamusTree);

    /* Run */
    while(!Exit) Execute(Menu(), &KamusTree, &Exit);

    /* End program */
    ExitApps();
    return 0;
}
