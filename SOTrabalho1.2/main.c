#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

float f(float x){
	return 5;
}

float f2(float x){
	math.sin(2*x);
}


int main(){
	float h = (b-a)/n;
	float area_total = (f(a)+f(a+h))*h/2;
	for(int i=1; i<n; i++){
		x_i = a+i*h;
		area_total += (f(x_i) + f(x_i+h))*h/2;
	}
}