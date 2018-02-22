
/* README:
 *
 * mcarlo is a program designed to estimate the value of pi
 * by utilizing threads via the pthread library
 *
 * Call the program using  "./mcarlo", and pass a positive integer
 * which will determin the amount of iterations to perform
 *
 * EX: "./mcarlo 100000000
 *
 * Author: Gabriel Hunt
 *
 * Date Last Modified: 2/21/2018
 *
 */

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


double numInCircle, numTotal;
int  cycles;
double  sum;
void *runner(void *param); /* the thread */

int main(int argc, char *argv[])
{
	// Declare and initialize variable
	pthread_t tid;
	pthread_attr_t attr;
	numInCircle = 0;
	numTotal = 0;
	sum = 0.0;

	// Error check: verify correct number of arguments
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s  <integer value>\n", argv[0]);
		return -1;
	}


	// Error check: verify value is a positive integer
	if (atoi(argv[1]) < 0)
	{
		fprintf(stderr, "Argument %d must be non-negative\n", 
			atoi(argv[1]));
		return -1;
	}


	// Convert input from string to interget
	// This variable tracks the number of iterations
	cycles = atoi(argv[1]);

	//Get default attributes
	pthread_attr_init(&attr);

	// Create Thread
	pthread_create(&tid, &attr, runner, argv[1]);

	//Wait for thread to exit
	pthread_join(tid, NULL);

	// Perform division as per the provided algorithm.
	// Saved result to seperate variable for debugging purposes
	double fraction = (numInCircle/numTotal);

	// Print estimated value of pi to screen
	printf("pi = %f\n", (4*fraction));

	return 0;
}

// Helper method produces a random double value
double random_double()
{
	return random() / ((double)RAND_MAX + 1);
}

// Calculation portion of program
void *runner(void *param)
{
	double x = 0.0;
	double y = 0.0;

	int i = 0;

	// Calculation performed as per the provided algorithm 
	while (i < cycles)
	{
		x = random_double() * 2.0 - 1.0;
		y = random_double() * 2.0 - 1.0;

		if (sqrt(x*x + y*y) < 1.0)
			numInCircle++;

		numTotal++;
		i++;
	}	
}
