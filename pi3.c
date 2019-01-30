 #include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define INTERVAL 50000
int main(int argc, char **argv)
{
	long long int i, num_steps = atoll(argv[1]);
	double x=0,aux, pi, sum[20];
	clock_t start,end;
	start=clock();
	#pragma omp parallel num_threads(4)
	#pragma omp for
	for(int j=0;j<20;j++) sum[j]=0.0;
	double step = 1.0/(double) num_steps;
#pragma omp parallel private(i,x,aux) shared(sum) 
   {
	#pragma omp for schedule(static) 
	for (i=0; i < num_steps; i=i+1)
	{
	  double aux;
         x=(i+0.5)*step;
         aux=4.0/(1.0+x*x);
	int id = omp_get_thread_num();
         sum[id] = sum[id] + aux;
      }
   }
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
}
