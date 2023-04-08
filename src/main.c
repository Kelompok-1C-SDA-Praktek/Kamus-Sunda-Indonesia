#include "BTreeKamus.h"
#include "NonRestricted.h"

int main()
{
    /* Deklarasi variabel */
    Address KamusTree = InitTree();
    int Exit = 0;

    /* Program utama */
    // Pengaturan ukuran console dengan lebar 1000 dan tinggi 600 
    HWND hWnd = GetConsoleWindowNT();
    MoveWindow(hWnd, 180, 50, 1000, 600, 1);

    /* Run */
    while(!Exit) Execute(Menu(), &KamusTree, &Exit);

    /* End program */
    ExitApps();
    return 0;
}