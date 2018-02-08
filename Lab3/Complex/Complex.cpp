#include<iostream>
using namespace std;

#include "Complex.h"

complex::complex() {
     cout << "In default constructor for object: " << this << endl;
     real=0.0;
     imag=0.0;
}

complex::complex(const complex & src) {
     cout << "In copy constructor for object: " << this << endl;
     real=src.real;
     imag=src.imag;
}

complex::~complex() {
     cout << "In destructor for object: " << this << endl;
}

complex::complex(float r, float i) {
     real=r;
     imag=i;
}

float complex::getReal() const {
     return (real);
}

float complex::getImag() const {
     return (imag);
}

void  complex::setReal(float r) {
     real=r;
}

void  complex::setImag(float i) {
     imag=i;
}

void complex::print() const {
     cout << "(" << real << "," << imag << ")";
}     

complex complex::operator+ (const complex & rhs) const {
     cout << "In operator+ for object: " << this 
          << " using as rhs object: " << &rhs << endl;
     complex tmp;
     tmp.real = real + rhs.real;
     tmp.imag = imag + rhs.imag;
     return tmp;
}

complex complex::operator- (const complex & rhs) const {
     complex tmp;
     tmp.real = real - rhs.real;
     tmp.imag = imag - rhs.imag;
     return tmp;
}

complex complex::operator* (const complex & rhs) const {
     complex tmp;
     tmp.real=(real*rhs.real)-(imag*rhs.imag);
     tmp.imag=(real*rhs.imag)+(imag*rhs.real);
     return tmp;
}

complex complex::operator/ (const complex & rhs) const {
     complex tmp;
     float mag;

     mag = (rhs.real*rhs.real)+(rhs.imag*rhs.imag);
     tmp.real = (real*rhs.real)+(imag*rhs.imag);
     tmp.real = tmp.real/mag;
     tmp.imag = (imag*rhs.real)-(real*rhs.imag);
     tmp.imag = tmp.imag/mag;
     return tmp;
}

bool complex::operator== (const complex & rhs) const {
     if ( (real==rhs.real) && (imag==rhs.imag) ) return (true);
     else return (false);
}
