 #include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define INTERVAL 50000
int main(int argc, char **argv)
{
	//mpi variables
	int dest,src,tag,procID, noproc;
	MPI_Status status;
	
	//pi variables
	long long int i, num_steps = atoll(argv[1]);
	double x=0,aux, pi,sum1,final_pi;
	long long int lower,upper,range,remainder=0.0;	

	clock_t start,end;
	start=clock();
//	#pragma omp parallel num_threads(4)
//	#pragma omp for

	double step = 1.0/(double) num_steps;

	//MPI setup
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &noproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &procID);
	
	sum1=0.0;
	//for(int j=0;j<noproc;j++) sum[j]=0.0;
	
	//solving subproblem	
	range = num_steps/noproc;
	remainder = num_steps%noproc;
	lower = procID;
	lower *=range;
	upper = lower + range;
	if (procID == (noproc -1)) 
		upper = num_steps;
	else if (procID == 0)
	{	
		lower = 0;
		upper = range;
	}
	//printf("PROC_ID %d\t lower:%lld \t upper:%lld\n",procID,lower,upper);
	for(i=lower; i<upper;i=i+1)
	{
			
		double aux;
		x=(i+0.5)*step;
		double prod = x*x;
		aux=4.0/(1.0+prod);
		sum1=sum1+aux;
	}
	
	pi = step*sum1;  
	//printf("value of sum at %d is : %.22f\n",procID,sum1);
	//sending and receiving sums. 
	tag=0;
	if(procID==0)
	{
		final_pi = pi;
		for(src=1;src<noproc;src=src+1)
		{
			MPI_Recv(&pi,1,MPI_DOUBLE,src,tag,MPI_COMM_WORLD,&status);
		//	printf("Received sum from %d is : %.22f\n",src,sum1);
			final_pi=final_pi+pi;
			
		}
		//pi=final_pi*step;
		end=clock();
		double tot_time = end - start;
		double insec = tot_time/CLOCKS_PER_SEC;
		printf("Value of Pi : %.22f time taken : %.6f\n",final_pi,insec);
		//printf("Final value of PI: %.22f\n",final_pi);
	}
	else
	{
		dest=0;
		MPI_Send(&pi,1,MPI_DOUBLE,dest,tag,MPI_COMM_WORLD);
	}
	MPI_Finalize();
	/*
	double final_sum=0.0;
	for(int j=0;j<20;j++)
	{
		final_sum+=sum[j];
		pi+=sum[j]*step;
	}
   	pi=step*final_sum;
	end=clock();
	double tot_time = end - start;
	double insec = tot_time/CLOCKS_PER_SEC;
	printf("Value of Pi : %.22f time taken : %.6f\n",pi,insec);
	*/
}

