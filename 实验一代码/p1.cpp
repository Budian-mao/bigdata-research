#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
#include "mpi.h"
int main(int argc, char** argv) {
	int myid, numprocs;
	int i;
     int N=atoi(argv[1]);
      double data[100000];
	for (int j = 0; j < N; ++j)
	{
		data[j] = j * (j + 1);
	}
	double local = 0.0;
	double inte;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	for (i = myid; i < N; i = i + numprocs) 
	{ 
		local = local + sqrt(data[i]);
	}
	MPI_Reduce(&local, &inte, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if (myid == 0) 
	{ 
		printf("The result is%16.15f\n", inte);
	}
	MPI_Finalize();
}

