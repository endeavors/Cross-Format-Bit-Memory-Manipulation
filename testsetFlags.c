#include "pa3.h"
#include <stdio.h>
#include <stdlib.h>
#include "test.h"
void testsetFlags()
{
    optind = 1;
    optarg = NULL;
    int argc = 3;
    struct argsInfo argsInfo;
    char * argv[] = { "exe", "-i","22"};
    argsInfo = setFlags(argc ,argv  );
    TEST(argsInfo.mode == I_FLAG | H_FLAG);
    TEST(argsInfo.inputBase == 22);

   int argg = 3;
   optind = 1;
   optarg = NULL;
    struct argsInfo stt;
    char * ar[] = {"exe", "-e", "932"};
    stt = setFlags(argg,ar);
    TEST(stt.mode == E_FLAG);
    TEST(stt.inputBase == 10);

    optind = 1;
    optarg = NULL;
    int argcc = 4;
    struct argsInfo st;
    char * argvv[] = {"exe", "-o", "2,8,10,16","932"};
    st = setFlags(argcc,argvv);
    TEST(st.mode == O_FLAG);
    TEST(st.inputBase == 10);
    TEST(st.outputBases == BASE_MASK(2) | BASE_MASK(8) |
        BASE_MASK(10) | BASE_MASK(16));

    optind = 1;
    optarg = NULL;
    int arv = 6;
    struct argsInfo si;
    char * ari[] = {"exe", "-f", "testfile.txt","-o","22","32"};
    si = setFlags(arv,ari);
    TEST(si.mode == O_FLAG | H_FLAG);
    TEST(si.inputBase == 10);
    TEST(si.outputBases == BASE_MASK(22));

    optind = 1;
    optarg = NULL;
    int arr = 1;
    struct argsInfo sy;
    char *syy[] = {"exe"};
    sy = setFlags(arr,syy);
    TEST(sy.mode ==H_FLAG);
    TEST(sy.inputBase == 10);
    TEST(sy.outputBases == 0);
   
    optind = 1;
    optarg = NULL;
    int a = 8;
    struct argsInfo aa;
    char *ai[] = {"exe", "-e", "-o","10","-i","36","10","CSE30"};
    aa = setFlags(a,ai);
    TEST(aa.mode == O_FLAG | E_FLAG | I_FLAG);
    TEST(aa.inputBase == 36);
    TEST(aa.outputBases == BASE_MASK(10));

    optind = 1;
    optarg = NULL;
    int y = 5;
    struct argsInfo yi;
    char *yy[] = {"exe", "-o", "2" ,"--", "-8"};
    yi = setFlags(y, yy);
    TEST(yi.mode == O_FLAG);
    TEST(yi.inputBase == 10);
    TEST(yi.outputBases == BASE_MASK(2));

    optind = 1;
    optarg = NULL;
    int b = 3;
    struct argsInfo bb;
    char *bi[] = {"exe","-eb", "23.005"};
    bb = setFlags(b,bi);
    TEST(bb.mode == E_FLAG | B_FLAG);
    TEST(bb.inputBase == 10);
    TEST(bb.outputBases == 0);
 
    optind = 1;
    optarg = NULL;
    int c = 10;
    struct argsInfo cc;
    char *ci[] = {"exe", "-b", "-e", "-o", "2,8,16,36",
    "71", "19.99", "513", "3.1.4", "123xyz", "90210"};
    cc = setFlags(c,ci);
    TEST(cc.mode == E_FLAG | B_FLAG | O_FLAG);
    TEST(cc.inputBase == 10);
    TEST(cc.outputBases ==  BASE_MASK(2) | BASE_MASK(8) |
        BASE_MASK(16) | BASE_MASK(36));

    optind = 1;
    optarg = NULL;
    int u = 5;
    struct argsInfo uu;
    char *ui[] = {"exe", "-i", "2", "-o","15"};
    uu = setFlags(u,ui);
    TEST(uu.mode == I_FLAG | O_FLAG);
    TEST(uu.inputBase == 2);
    TEST(uu.outputBases == BASE_MASK(15));

    optind = 1;
    optarg = NULL;
    int x = 4;
    struct argsInfo s;
    char * argi[] = {"exe", "-io", "4","32"};
    s = setFlags(x,argi);
    TEST(s.mode == O_FLAG | I_FLAG);
    TEST(s.inputBase == 0);
    TEST(s.outputBases == 0);
  
    optind = 1;
    optarg = NULL;
    int t = 3;
    struct argsInfo r;
    char *rr[] = {"exe", "-f", "testfile.txt"};
    r = setFlags(t,rr);
    TEST(r.mode == F_FLAG);
    TEST(r.inputBase == 10);
    TEST(r.outputBases == 0);

    optind = 1;
    optarg = NULL;
    int count = 7;
    struct argsInfo art;
    char *aat[] = {"exe","-i","422","-o","42u","-i","42"};
    art = setFlags(count,aat);
    TEST(art.mode == I_FLAG | O_FLAG);
    printf("%d", art.inputBase);
    TEST(art.inputBase == 0);
    TEST(art.outputBases == 0);

    printf("\n\n");

    optind = 1;
    optarg = NULL;
    int ct = 8;
    struct argsInfo tt;
    char *ti[] = {"exe", "-o", "4,12,32,22","-ebh","-i","32","-f","5"};
    tt = setFlags(ct,ti);
    TEST(tt.mode =  E_FLAG | B_FLAG | H_FLAG | I_FLAG | O_FLAG | F_FLAG);
    printf("%d\n", tt.inputBase);
    TEST(tt.inputBase == 32);
    TEST(tt.outputBases == BASE_MASK(4) | BASE_MASK(12) | BASE_MASK(32) |
        BASE_MASK(22));
//    printf("%c", *tt.inFileStr);
    
    
    /*printf("%c\n",s.mode);
    printf("%d\n",s.inputBase);
    printf("%d\n",s.outputBases);*/
    //printf("%s", argsInfo.mode);
   // printf("%s", argsInfo.outputBases);
   // printf("%s", argsInfo.inputBase);
}

int main()
{
    testsetFlags();
    return 0;
}
