#include <stdio.h> 
#include <mpi.h> 
#include <math.h> 
#define N 10000000
#define a 10
#define b 100
int main(int argc, char** argv) {
	int myid, numprocs;
	double local = 0.0, dx = (double)(b - a) / N; /* С���ο�� */
	double x,Sum=0;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	--numprocs; /*���ݷ���ʱ��ȥ0�����ڵ�*/
	if (myid == 0) { /*0�����ڵ㣬��Ҫ�������ݷַ��ͽ���ռ�*/
		for (int i = 0; i < N; ++i) /*���ݷַ�: 0, */
			MPI_Send(&i, 1, MPI_DOUBLE, i % numprocs + 1, 1, MPI_COMM_WORLD);
		for (int source = 1; source <= numprocs; ++source) /*����ռ�*/
		{
			double d;
			MPI_Recv(&d, 1, MPI_DOUBLE, source, 99, MPI_COMM_WORLD, &status);
			Sum += d;
		}
	}
	else
	{
		for (int j = myid - 1; j < N; j = j + numprocs) 
		{
			int i;
			MPI_Recv(&i, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status); 
			x = a + i * dx + dx / 2; 
			local += x * x *x* dx;
		}
		MPI_Send(&local, 1, MPI_DOUBLE, 0, 99, MPI_COMM_WORLD); 
	}
	printf("I am process %d. I put total %f to process 0, and Sum=%f.\n", myid, local , Sum);
	MPI_Finalize();
}
