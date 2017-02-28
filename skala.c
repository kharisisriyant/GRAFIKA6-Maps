#include "skala.h"
#include <math.h>

titik scaleDot(titik p0, titik p1, float s){
	titik output;
	output.x = p1.x;
	output.y = p1.y;
	int jarakx = abs(p1.x - p0.x);
	int jaraky = abs(p1.y - p0.y);
	if (p1.x < p0.x){
		output.x = ((int)(((float)p0.x) - ((float)jarakx * s)));
	}
	else {
		output.x = ((int)(((float)p0.x) + ((float)jarakx * s)));
	}
	if (p1.y < p0.y){
		output.y = ((int)(((float)p0.y) - ((float)jaraky * s)));
	}
	else {
		output.y = ((int)(((float)p0.y) + ((float)jaraky * s)));
	}
	
	
	
	return output;
}

void scaleBanyakDot(titik p0, titik *p1, float s, int banyaktitik){
	for (int i = 0; i < banyaktitik;i++){
		p1[i] = scaleDot(p0, p1[i], s);
	}
} 

titik scaleDotInWindow(titik p){
	titik pusat;
//	pusat.x = windowPosition.x + windowSideLength/2;
//	pusat.y = windowPosition.y + windowSideLength/2;
	pusat.x = 0;
	pusat.y = 0;

	float ratio = (float) GLOBAL_WINDOW_X/ (float) windowSideLength;

	titik result = scaleDot(pusat, p, ratio);
}