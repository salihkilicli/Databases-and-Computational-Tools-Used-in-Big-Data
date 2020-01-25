#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int isprime(int n) {
  int i, sq;

  sq = (int) sqrt(n);
  for (i=3; i<=sq; i+=2)
    if ((n%i) == 0) return 0;

  return 1;
}

int main(int argc, char *argv[])
{
  int i, p=0, max;
  int np, rank, p_rank, length;
  char node[MPI_MAX_PROCESSOR_NAME];
  
  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &np);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(node, &length);   // MPI name

  max=100000000;   // 100 million (primes=5761455)
  //max=2100000000;  // 2.1 billion (primes=102886526)

  MPI_Bcast(&max, 1, MPI_INT, 0, MPI_COMM_WORLD);
  if (rank==0){
  printf("Numbers to be scanned = %d\n", max);
  }

  p_rank=0;
  for (i=1+rank*2; i<=max; i+=2*np) {
    if (isprime(i)) p_rank++;
  }
  printf("Rank=%2d/%d, Node=%s; Primes found=%d\n", rank, np, node, p_rank);
  MPI_Reduce(&p_rank, &p, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  MPI_Barrier(MPI_COMM_WORLD);
  if (rank==0){
  printf("Total primes = %d\n", p);
  }

  MPI_Finalize ();
}
