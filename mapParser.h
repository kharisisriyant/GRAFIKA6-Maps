#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "glob_var_type.h"

typedef struct {
	titik p1;
	titik p2;
} line;

typedef struct{
	int n; //banyak titik
	titik* point; //titik pada bidang
} plane; //maksudnya bidang

void init(plane* bidang);

plane* readFile(char* path, int* total);

line* readFileRoad(char *path, int *total);

#endif
