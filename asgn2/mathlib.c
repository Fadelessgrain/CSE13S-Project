#include "mathlib.h"

#include <math.h>

#define EPSILON 1e-14

//checks the to see if its positive or negative, then takes ab Abs values of it
static inline double Abs(double x) {
    return x < 0 ? -x : x;
}

//code below was inspired by lecture slides
double Sin(double x) {
    // normolizes x
    x = fmod(x, 2 * M_PI);
    //numerator of the Taylor series is the 'input' aka the x
    double num = x;
    //denominator is 1 since the first part of the Taylor series is just x
    double den = 1.0;
    // counter that keeps track of the sum
    double sum = num / den;
    //counter that keeps tracks of what term we are on
    double term = num / den;
    // loops until term is > then 1e-14
    // the factorial starts at 3 because the Taylor series for Sin calculates the odd terms
    for (double factorial = 3.0; Abs(term) > EPSILON; factorial += 2.0) {
        double mul = -x * x;
        //updates the new counter
        num = num * mul;
        //updates new denominator
        den = den * (factorial - 1) * factorial;
        //updates the term
        term = num / den;
        //updates sum
        sum = sum + term;
    } //when the condition is met, return the sum we keept on updating
    return sum;
}

//code above was inspired by lecture slides

//the Cos function is simialr to the Sin function but the numerator starts at 1 and not at x
//because of the Taylor series fos Cos
double Cos(double x) {
	//normalizes x
    x = fmod(x, 2 * M_PI);
    double num = 1.0;
    double den = 1.0;
    double sum = num / den;
    double term = num / den;
    //the factorial starts at two because the Taylor series for Cos calculates the evens
    for (double factorial = 2.0; Abs(term) > EPSILON; factorial += 2.0) {
        double mul = -x * x;
        num = num * mul;
        den = den * (factorial - 1) * factorial;
        term = num / den;
        sum = sum + term;
    }
    return sum;
}

double Tan(double x) {
    double num = Sin(x);
    double den = Cos(x);
    return num / den;
}
//code below inspired by the lecture slides and the asgn2 document
double Exp(double x) {
    double num = 1.0;
    double den = 1.0;
    double term = num / den;
    double sum = term;
    for (double factorial = 1.0; Abs(term) > EPSILON; factorial += 1.0) {
        term = (x / factorial) * term;
        sum = sum + term;
    }
    return sum;
}
//code above inspired by the lecture slides and the asgn2 document

//code below inspired by the lecture slides
double Log(double x) {
    double ex = 1.0;
    double power = Exp(ex);
    while (Abs(x - power) > EPSILON) {
        ex = ex + ((x - power) / power);
        power = Exp(ex);
    }
    return ex;
}
//code above inspired by the lecture slides
