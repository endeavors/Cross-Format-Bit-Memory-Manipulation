/*
 * Unit Test for printIntBinary.s
 *
 * void printIntBinary( long num );
 *
 * Print num as binary with a space between every 4 bits. 
 */

#include "test.h"       /* For TEST() macro and stdio.h */
#include <stdlib.h>     /* For rand() function prototype */
#include <limits.h>     /* For LONG_MIN and LONG_MAX */
#include "pa3.h"        /* For printIntBinary() function prototype */

void
testprintIntBinary()
{

    printf( "Testing printIntBinary()\n\n" );

    printf( "First line in each group below is the *expected* output.\n" );
    printf( "Second line in each group is what *printIntBinary* outputs.\n");
    printf( "They should match exactly!\n" );

    /*
     * Test with 0.
     */
    printf( "\nTesting with value 0 - should print:\n"
	    "0000 0000 0000 0000 0000 0000 0000 0000\n" );

    printIntBinary( 0 );
    printf( "\n" );


    /*
     * Test with 1.
     */
    printf( "\nTesting with value 1 - should print:\n"
	    "0000 0000 0000 0000 0000 0000 0000 0001\n" );

    printIntBinary( 1 );
    printf( "\n" );


    /*
     * Test with -1.
     */
    printf( "\nTesting with value -1 - should print:\n"
	    "1111 1111 1111 1111 1111 1111 1111 1111\n" );

    printIntBinary( -1 );
    printf( "\n" );


    /*
     * Test with LONG_MAX.
     */
    printf( "\nTesting with value LONG_MAX - should print:\n"
	    "0111 1111 1111 1111 1111 1111 1111 1111\n" );

    printIntBinary( LONG_MAX );
    printf( "\n" );


    /*
     * Test with LONG_MIN.
     */
    printf( "\nTesting with value LONG_MIN - should print:\n"
	    "1000 0000 0000 0000 0000 0000 0000 0000\n" );

    printIntBinary( LONG_MIN );
    printf( "\n" );


    /*
     * Test with -2078169706.
     */
    printf( "\nTesting with value 0x8421A596 (-2078169706) - should print:\n"
	    "1000 0100 0010 0001 1010 0101 1001 0110\n" );

    /* printIntBinary( -2078169706 ); */
    printIntBinary( 0x8421A596 );
    printf( "\n" );


    /*
     * Test with 1772454945.
     */
    printf( "\nTesting with value 0x69A58421 (1772454945) - should print:\n"
	    "0110 1001 1010 0101 1000 0100 0010 0001\n" );

    printIntBinary( 1772454945 );
    /* printIntBinary( 0x69A58421 ); */
    printf( "\n" );


    /*
     * You can use the Unix command bc (basic calculator) for more.
     *
     * % bc
     * obase=2
     * 1772454945
     * 1101001101001011000010000100001
     * ^D  <Control>-D
     */

    /*
     * Cycle thru power of 2 values shift 1 bit left all the way across.
     * Then set all bits to 1 and shift a 0 bit right all the way across.
     *
     */

    {
      unsigned long int i;

      printf( "\nCycle a 1 bit across right to left:\n" );
      for( i = 1; i != 0; i = i << 1 )
      {
	printf( "%11ld\t", i );
	printIntBinary( i );
	printf( "\n" );
      }

      printf( "\nSet all bits to 1 and shift 0's left to right:\n" );
      for( i = -1; i != 0; i = i >> 1 )
      {
	printf( "%11ld\t", i );
	printIntBinary( i );
	printf( "\n" );
      }

    }


    printf( "\n\nFinished running tests on printIntBinary()\n" );

}

int
main()
{
    testprintIntBinary();

    return 0;
}
