#include "mathlib.h" 
#include <stdio.h>


#define EPSILON 1e-14

static inline double Abs(double x ) {
	return x < 0 ? -x : x;
}


double Sin(double x) { 
	double num = x;
	double den = 1.0;
	double sum = num/den;
	double term = num/den;
//	int factorial_ = 3.0;
	for (double factorial = 3.0; Abs(term) > EPSILON; factorial += 2.0) {
		double  mul = -x * x;
		num = num * mul; 
		den = den * (factorial-1) * factorial;
		term = num/den;
		sum = sum + term;
	}
	return sum; 
}

 double Cos(double x) {
       double num = 1.0;
      double den = 1.0;
       double sum = num/den;
       double term = num/den;
       for (double factorial = 2.0; Abs(term) > EPSILON; factorial += 2.0) {
           double  mul = -x * x;
   	       num = num * mul;
           den = den * (factorial-1)* factorial ;
           term = num/den;
          sum = sum + term;
      }
      return sum;
 }

 double Tan(double x) {
 	double num = Sin(x);
	double den = Cos(x);
 	return num/den;
}

double Exp(double x) {
	double num = 1.0;
	double den = 1.0;
	double term = num/den;
	double sum = term;
	for (double factorial = 1.0; Abs(term) > EPSILON; factorial += 1.0) {
		term = (x / factorial) * term;
		sum = sum + term;
		
	}
		return sum;
	
}


