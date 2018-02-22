/* README:
 * collatz is a program designed to take a positive integer from the user
 * and apply the Collatzconjecture to the integer. 
 * Call the program using "./collatz", and pass a positive integer with the 
 * command.
 * EX: "./collatz 35"
 * Author: Gabriel Hunt
 * Date Last Modified: 2/13/2018 
 */



#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int num;

int main(int argc, char *argv[])
{

	// Prcoess ID
	pid_t pid;
	
	// Check the number of arguments 
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <start number> \n", argv[0]);
		return -1;
	}
	
	// Convert user input from string to integer
	num = atoi (argv[1]);
	
	// Check that input is a positive integer
	if (num < 0)
	{
		fprintf(stderr, "Only positive values are allowed: %s \n",
			 argv[1]);
		return -1;
	}

	// Create child process
	pid = fork();

	// Child process
	if (pid == 0)
	{
		int remainder = 0;

		// Loop through function until num reaches 1
		while (num > 1)
		{
			// if remainder is 0, number is even
			// else, number is odd
			remainder = num % 2;
			if (remainder == 0)
			{
				num = num/2;
				printf("%d\n", num);
			}

			else
			{
				num = 3 * num + 1;
				printf("%d\n", num);
			}
		}
		return 0;
	}

	// Parent process
	else if (pid > 0)
	{
		// Wait until child process completes 
		wait(NULL);
		return 0;
	}
}
