#include <time.h> 
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define INTERVAL 10000

int main()
{
 
    int interval; 
    double rand_x, rand_y, origin_dist, pi; 
    double circle_points = 0, square_points = 0; 
  
    // Initializing rand() 
    srand(time(NULL)); 
  
    // Total Random numbers generated = possible x 
    // values * possible y values
	#pragma omp parallel num_threads(10) 
    #pragma omp parallel for
    for (long long int i = 0; i < (INTERVAL * INTERVAL); i++) 
	{ 
  
        // Randomly generated x and y values 
	double randomX = rand() % INTERVAL +1 ;
	double randomY = rand() % INTERVAL +1 ;
        rand_x = randomX / INTERVAL; 
        rand_y = randomY/ INTERVAL; 
  	//printf ("rand_X %f rand y %f \n",rand_x,rand_y);
        // Distance between (x, y) from the origin 
        origin_dist = rand_x * rand_x + rand_y * rand_y; 
  
        // Checking if (x, y) lies inside the define 
        // circle with R=1 
        if (origin_dist <= 1) 
            circle_points= circle_points +1; 
  
        // Total number of points generated 
        square_points=square_points +1; 
  
        // estimated pi after this iteration 
        pi = (4 * circle_points) / square_points;
	
        // Pausing estimation for first 10 values (Optional) 
       // if (i < 20) 
        //    getchar(); 
    } 
  
    // Final Estimated Value 
    //cout << "\nFinal Estimation of Pi = " << pi; 
 	printf("Final Estimation of Pi = %f\n", pi); 
    return 0;
}
