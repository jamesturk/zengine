#ifndef __mt19937ar__
#define __mt19937ar__

//This .h file written for ZEngine by James Turk to declare the methods implemented in mt19937ar.c
//See mt19937ar.c for license of the Mersenne Twister.

#include <cstdio>  //changed for ZEngine
/* Period parameters */  
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

void init_genrand(unsigned long s);
unsigned long genrand_int32(void);
long genrand_int31(void);
double genrand_real1(void);
double genrand_real2(void);
double genrand_real3(void);
double genrand_res53(void);

#endif //__mt19937ar__

