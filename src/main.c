#include "BTreeKamus.h"
#include "NonRestricted.h"
#include <stdio.h>

int main()
{
    Address KamusTree;
    int Exit = 0;
    while(!Exit)
    {
        Execute(Menu(), &KamusTree, &Exit);
    }
    return 0;
}