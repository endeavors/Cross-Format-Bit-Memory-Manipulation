#include "pa3.h"
#include "test.h"

void testprintBase()
{
    printBase(100,32);
    printf("\n");
    printBase(80,32);
    printf("\n");
    printBase(9123,10);
    printf("\n");
    printBase(123,2);
    printf("\n");

    
    printBase(0,12);
    printf("\n");
    printBase(500009,36);
    printf("\n");
}
int main()
{
    testprintBase();
    return 0;
}
