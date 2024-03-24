#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef NUMT1
#define NUMT1	         1	// number of threads to use -- do once for 1 and once for 4
#endif

#ifndef NUMT2
#define NUMT2	         4	// number of threads to use -- do once for 1 and once for 4
#endif

#ifndef SIZE
#define SIZE       	20384	// array size -- you get to decide
#endif

#define NUMTRIES        20	// how many times to run the timing to get reliable timing data

float A[SIZE];
float B[SIZE];
float C[SIZE];

int
main( )
{
#ifdef   _OPENMP
	fprintf( stderr, "OpenMP version %d is supported here\n", _OPENMP );
#else
	fprintf( stderr, "OpenMP is not supported here - sorry!\n" );
	exit( 0 );
#endif

	// initialize the arrays:
	for( int i = 0; i < SIZE; i++ )
	{
		A[i] = 1.;
		B[i] = 2.;
	}

        omp_set_num_threads( NUMT1 );

        double maxMegaMults1 = 0.;

        for( int t = 0; t < NUMTRIES; t++ )
        {
                double time0 = omp_get_wtime( );

                #pragma omp parallel for
                for( int i = 0; i < SIZE; i++ )
                {
                        C[i] = A[i] * B[i];
                }

                double time1 = omp_get_wtime( );
                double megaMults = (double)SIZE/(time1-time0)/1000000.;
                if( megaMults > maxMegaMults1 )
                        maxMegaMults1 = megaMults;
        }

        fprintf( stderr, "For %d threads, Peak Performance = %8.2lf MegaMults/Sec\n", NUMT1, maxMegaMults1 );

        omp_set_num_threads( NUMT2 );

        double maxMegaMults2 = 0.;

        for( int t = 0; t < NUMTRIES; t++ )
        {
                double time0 = omp_get_wtime( );

                #pragma omp parallel for
                for( int i = 0; i < SIZE; i++ )
                {
                        C[i] = A[i] * B[i];
                }

                double time1 = omp_get_wtime( );
                double megaMults = (double)SIZE/(time1-time0)/1000000.;
                if( megaMults > maxMegaMults2 )
                        maxMegaMults2 = megaMults;
        }

        fprintf( stderr, "For %d threads, Peak Performance = %8.2lf MegaMults/Sec\n", NUMT2, maxMegaMults2 );

	// note: %lf stands for "long float", which is how printf prints a "double"
	//        %d stands for "decimal integer", not "double"

	// Speedup = (Peak performance for 4 threads) / (Peak performance for 1 thread)

        double S = maxMegaMults2 / maxMegaMults1;

        fprintf( stderr, "Speedup = %8.2lf\n", S );

        float Fp = (4./3.) * ( 1. - (1./S) );

        fprintf( stderr, "Parallel Fraction = %8.2lf\n", Fp );

        return 0;
}
