#include "pa3.h"
#include "test.h"

void testprocessFPToken(int argc, char*argv[])
{
    struct argsInfo argsInfo = setFlags(argc, argv);
    int index = optind;
    for(; index < argc; index++){
        processFPToken(argv[index], argsInfo);
    }
    optind = 1;
    optarg = NULL;
}

int main(int argc, char* argv[])
{
    testprocessFPToken(argc, argv);
    return 0;
}
