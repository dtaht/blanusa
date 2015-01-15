#include <stdio.h>
#include <math.h>

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

#define MAXB 10000

int main(int argc, char **argv) {
	double results[MAXB];
	for (int i = 0; i < MAXB; i++) {
		results[i] = blanusa_pow(i);
	}
	for (int i = 0; i < MAXB; i++) {
		printf("%g\n", results[i]);
	}
}

