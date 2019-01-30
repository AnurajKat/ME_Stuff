 #include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define INTERVAL 50000
int main(int argc, char **argv)
{
	long long int i, num_steps = atoll(argv[1]);
	clock_t start, end;
	start=clock();
	double x=0,aux;
	double pi;
	double sum = 0.0;
	double step = 1.0/(double) num_steps;
#pragma omp parallel private(i,x,aux) shared(sum) num_threads(4)
   {
	#pragma omp for schedule(static) 
	for (i=0; i < num_steps; i=i+1)
	{
	  double aux;
         x=(i+0.5)*step;
         aux=4.0/(1.0+x*x);
	#pragma omp critical
         sum = sum + aux;
      }
   }
   pi=step*sum;
	end=clock();
	double tot_time = end - start;
	double insec= tot_time/CLOCKS_PER_SEC;
	printf("Value of Pi : %.22f\t\t time taken : %.6f\n",pi,insec);
}
