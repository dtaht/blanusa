#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifndef CLOCK_PROCESS_CPUTIME_ID
// std=c99 doesn't have clock_gettime for some reason
#error where the heck is clock_gettime?
#endif

#define MAXB 1000000
#define DEF_TIMER CLOCK_PROCESS_CPUTIME_ID
//#define DEF_TIMER CLOCK_REALTIME

/* calculate a blanusa snark 

		   (x-3)(x-1)^3
		   (x+1)(x+2)(x^4+x^3-7x^2-5x+6)(x^4+x^3-5x^2-3x+4)^2
    		   (x-3)(x-1)^3(x^3+2x^2-3x-5)
		   (x^3+2x^2-x-1)(x^4+x^3-7x^2-6x+7)(x^4+x^3-5x^2-4x+3);

*/

/* compiled without -ffast-math, this inserts tons of calls to pow.
   with fast-math, it looks like it does the right thing with CSE */

double blanusa_pow(double x) {
	double r = (x-3)*pow(x-1,3) *
		   (x+1)*(x+2)*(pow(x,4)+pow(x,3)-pow(7*x,2)-5*x+6)*
		   pow((pow(x,4)+pow(x,3)-pow(5*x,2)-3*x+4),2) *
    		   pow((x-3)*(x-1),3)*(pow(x,3)+pow(2*x,2)-3*x-5)*
		   (pow(x,3)+pow(2*x,2)-x-1)*(pow(x,4) +
		   pow(x,3)-pow(7*x,2)-6*x+7)*(pow(x,4) +
		   pow(x,3)-pow(5*x,2)-4*x+3);
	return r;
}

/* try expand not using pow
double blanusa_unrolled(double x) {
		   (x-3)*(x-1)*(x-3)*(x-1)*(x-3)*(x-1)
		   (x+1)(x+2)(x^4+x^3-7x^2-5x+6)(x^4+x^3-5x^2-3x+4)^2
    		   (x-3)(x-1)^3(x^3+2x^2-3x-5)
		   (x^3+2x^2-x-1)(x^4+x^3-7x^2-6x+7)(x^4+x^3-5x^2-4x+3);
}
*/



void timespec_diff(struct timespec *temp, struct timespec *start, struct timespec *end)
{
	if ((end->tv_nsec-start->tv_nsec)<0) {
		temp->tv_sec = end->tv_sec-start->tv_sec-1;
		temp->tv_nsec = 1000000000 + end->tv_nsec-start->tv_nsec;
	} else {
		temp->tv_sec = end->tv_sec-start->tv_sec;
		temp->tv_nsec = end->tv_nsec-start->tv_nsec;
	}
}

/* A sufficiently smart compiler would replace all this with a single
   call to printf, doing all the calculations at compile time. That
   doesn't seem to happen... */

int main(int argc, char **argv) {
	double results[MAXB];
	struct timespec end;
	struct timespec start;
	struct timespec dur;
	if(clock_gettime(DEF_TIMER,&start) == -1) {
		perror("Bad clock");
		exit(-1);
	}
	for (int i = 0; i < MAXB; i++) {
		results[i] = blanusa_pow(i);
	}

	if(clock_gettime(DEF_TIMER,&end) == -1) {
		perror("Bad clock");
		exit(-1);
	}

	timespec_diff(&dur,&start,&end);
	printf("Duration: %ld.%09ld\n",
			   dur.tv_sec, dur.tv_nsec);
	for (int i = 0; i < MAXB; i++) {
		printf("%g\n", results[i]);
	}
}

