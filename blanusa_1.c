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

/* calculate the first blanusa snark 

		   (x-3)(x-1)^3
		   (x+1)(x+2)(x^4+x^3-7x^2-5x+6)(x^4+x^3-5x^2-3x+4)^2

   calculate the second blanusa snark

    		   (x-3)(x-1)^3(x^3+2x^2-3x-5)
		   (x^3+2x^2-x-1)(x^4+x^3-7x^2-6x+7)(x^4+x^3-5x^2-4x+3);

*/


/* compiled without -ffast-math, this inserts tons of calls to pow.
   with fast-math, it looks like it does the right thing with CSE */

double blanusa1_pow(double x) {
  return (x-3)*pow(x-1,3) *
    (x+1)*(x+2)*
    (pow(x,4)+pow(x,3)-7*pow(x,2)-5*x+6)*
    pow((pow(x,4)+pow(x,3) - 5 * pow(x,2)-3*x+4),2);
}

/*    calculate the second blanusa snark

    		   (x-3)(x-1)³(x^3+2x^2-3x-5)
		   (x^3+2x^2-x-1)(x^4+x^3-7x^2-6x+7)(x^4+x^3-5x^2-4x+3);

*/

double blanusa2_pow(double x) {
    return (x-3)*pow(x-1,3)*(pow(x,3)+2*pow(x,2)-3*x-5) *
    (pow(x,3)+2*pow(x,2)-x-1) *
    (pow(x,4) + pow(x,3)- 7* pow(x,2)-6*x+7)*
    (pow(x,4) + pow(x,3)- 5* pow(x,2)-4*x+3);
}

/* Wolfram alpha translated this into something different - as did my emacs,
   when entered into a comment. I had (in error) combined the first
and second blanusa snarks, which wolfram optimized for a cleaner
equation (which did, indeed, run faster than the original code did!)

(x-3)²(x-1)⁶(x+1)(x+2)(x³+2x²-3x-5)(x³+2x²-x-1)(x⁴+x³-7x²-6x+7)
(x⁴+x³-7x²-5x+6)(x⁴+x³-5x²-4x+3)(x⁴+x³+5x²-3x+4)²

*/

double blanusa_wolfram(double x) {
  double r = pow(x-3,2)*pow(x-1,6)*(x+1)*(x+2)*
    (pow(x,3)+2*pow(x,2)-3*x-5)*
    (pow(x,3)+2*pow(x,2)-x-1)*
    (pow(x,4)+pow(x,3)-5*pow(x,2)+6*x+7)*
    (pow(x,4)+pow(x,3)-7*pow(x,2)-5*x+6)*
    (pow(x,4)+pow(x,3)-5*pow(x,2)+3) *
    pow(pow(x,4)+pow(x,3)-5*pow(x,2)+3*x+4,2);
  return r;
}

void timespec_diff(struct timespec *temp, struct timespec *start, struct timespec *end)
{
  //  if(temp && start && end) return;
  if ((end->tv_nsec-start->tv_nsec)<0) {
		temp->tv_sec = end->tv_sec-start->tv_sec-1;
		temp->tv_nsec = 1000000000 + end->tv_nsec-start->tv_nsec;
	} else {
		temp->tv_sec = end->tv_sec-start->tv_sec;
		temp->tv_nsec = end->tv_nsec-start->tv_nsec;
	}
}

/* Declaring these, this large, in main, causes a segfault */

double results[MAXB];
double results2[MAXB];

#define START 0

/* A sufficiently smart compiler would replace all this with a single
   call to printf, doing all the calculations at compile time. That
   doesn't seem to happen... */


int main(int argc, char **argv) {
	struct timespec end;
	struct timespec start;
	struct timespec dur;

	if(clock_gettime(DEF_TIMER,&start) == -1) {
		perror("Bad clock");
		exit(-1);
	}

	for (int i = START; i < MAXB; i++) {
		results[i] = blanusa1_pow(i);
	}

	if(clock_gettime(DEF_TIMER,&end) == -1) {
		perror("Bad clock");
		exit(-1);
	}

	timespec_diff(&dur,&start,&end);

	printf("Duration: %ld.%09ld\n",
			   dur.tv_sec, dur.tv_nsec);

	/* Try the alternate version */
	
	if(clock_gettime(DEF_TIMER,&start) == -1) {
		perror("Bad clock");
		exit(-1);
	}
	for (int i = START; i < MAXB; i++) {
		results2[i] = blanusa2_pow(i);
	}

	if(clock_gettime(DEF_TIMER,&end) == -1) {
		perror("Bad clock");
		exit(-1);
	}

	timespec_diff(&dur,&start,&end);
	printf("Duration: %ld.%09ld\n",
			   dur.tv_sec, dur.tv_nsec);
	for (int i = START; i < MAXB; i++) {
	  	  printf("%g\n", results[i]);
	  //	  printf("DIFF: %g %g %g\n", results[i]-results2[i],
	  // results[i], results2[i]);
	}
}

