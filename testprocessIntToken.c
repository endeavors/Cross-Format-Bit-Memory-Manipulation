#include <errno.h>
#include "pa3.h"
#include "test.h"

void testprocessIntToken(int argc, char* argv[])
{
    struct argsInfo argsInfo = setFlags(argc, argv);
    int index = optind;
    for (; index < argc; index++){
        processIntToken(argv[index], argsInfo);
    }



    optind = 1;
    optarg = NULL;

}

int main(int argc, char* argv[]){
    testprocessIntToken(argc, argv);
    return 0;
}
