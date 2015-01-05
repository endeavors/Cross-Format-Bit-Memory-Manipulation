/*
 * Filename: pa3.h
 * Author: Gurkirat Singh
 * Description: This file contains all the constants and prototypes of the
 *              functions we use in this program.
 */

#ifndef PA3_H
#define PA3_H

#define BASE_MASK(ob) (((long long) 0x1) << (ob))
#define H_FLAG 0x1
#define E_FLAG 0x2
#define B_FLAG 0x4
#define I_FLAG 0x8
#define O_FLAG 0x10
#define F_FLAG 0x20

#define DEFAULT_BASE 10
#define MIN_BASE 2
#define MAX_BASE 36

struct argsInfo {
  unsigned char mode;
  unsigned int inputBase;
  unsigned long long outputBases;
  char* inFileStr;
};

void printEnglish( long num );
void printIntBinary( long num );
void printFPBinary( float num );
void printBase( long num, int base );
long strToLong( const char* str, const int base );
int checkRange( long value, long minRange, long maxRange );
void processIntToken( char* inStr, struct argsInfo info );
void processFPToken( char* inStr, struct argsInfo info );
struct argsInfo setFlags( int argc, char* argv[] );

#endif /* PA3_H */
