#include <stdio.h>
#include "mkl_vsl.h"
#include "mkl.h"

#define NVECTOR 1000L  //10L         //1000000L                                # different settings
#define REPS 1000000L  //100000000L  //1000L
// module load intel/2019
// icc -o hw3 hw3.c -O2 -xHost -lmkl_rt -lpthread -lm -ldl                     # to compile in Intel
// gcc -o hw3 hw3.c -O2 -m64 -I${MKLROOT}/include \                            # to compilte in GNU GCC
// -L${MKLROOT}/lib/intel64 -Wl,--no-as-needed -lmkl_rt -lpthread -lm -ldl
// time ./hw3                                                                  # to run and time      

int main() // hw3.c
{
/* Initializing r and average s */
double r[NVECTOR], s=0.0;
VSLStreamStatePtr stream;
int i, j;
// vslNewStream( &stream, VSL_BRNG_R250, 777 );    // A generalized feedback shift register generator
// vslNewStream( &stream, VSL_BRNG_MCG59, 777 );   // 59-bit multiplicative congruential generator
vslNewStream( &stream, VSL_BRNG_MT19937, 777 );    // Mersenne Twister pseudorandom number generator 

/* Generating random numbers*/
for ( i=0; i<REPS; i++ ) {

vdRngExponential(VSL_RNG_METHOD_EXPONENTIAL_ICDF, stream, NVECTOR, r, 2.0, 3.0 );

for ( j=0; j<NVECTOR; j++ ) s += r[j];
}
/* Deleting the stream*/
vslDeleteStream( &stream );
printf( "Sample mean = %f (n=%ld)\n", s/(REPS*NVECTOR), REPS*NVECTOR );

return 0;
}