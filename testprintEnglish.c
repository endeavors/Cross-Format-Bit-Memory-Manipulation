#include "pa3.h"
#include "test.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
void testprintEnglish()
{
    printEnglish(9);
    printf("\n");
    printEnglish(0);
    printf("\n");
    printEnglish(1234569147);
    printf("\n");
    printEnglish(123456789);
    printf("\n");


}
int main()
{
    testprintEnglish();
    return 0;
}
